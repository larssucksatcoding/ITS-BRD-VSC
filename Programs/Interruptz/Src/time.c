/**
* @file       time.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Nov 2025
* @brief      
*/

/*  Includes  -------------------------------------------------*/
#include "time.h"
#include "timer.h"
#include "stdint.h"

#define MIN_WINDOW_DURATION_IN_MS     250     // time windows must be at least 250 ms
#define MAX_WINDOW_DURATION_IN_MS     500     // time windows mustn't be longer than 500 ms

#define TICKS_PER_MS (TICKS_PER_US * 1000)

static uint32_t current_timestamp;
static uint32_t window_start_timestamp;

/*  Private Functions  -------------------------------------------------*/

int ms_between_timestamps(uint32_t start, uint32_t end) {
    uint32_t timestamp_diff = 0;

    // check for overflow since last time window
    if (start > end) {
        // start was taken before and end after overflow, so we get difference
        // by getting "distance" of start timestamp to max int + end timestamp
        timestamp_diff = (UINT32_MAX - start) + end;
    } else {
        timestamp_diff = end - start;
    }

    return timestamp_diff / TICKS_PER_MS;
}

/*  Public Functions  -------------------------------------------------*/

void init_time(volatile uint32_t *last_phase_transition_ts) {
    initTimer();

    window_start_timestamp = 0;
    *last_phase_transition_ts = 0;
}

void start_new_timewindow(uint32_t *previous_window_end_timestamp) {
    window_start_timestamp = *previous_window_end_timestamp;
}

void start_first_timewindow() {
    window_start_timestamp = getTimeStamp();
}

bool is_timewindow_over(uint32_t loop_timestamp, uint32_t isr_timestamp) {

    // milliseconds between window start and last isr timestamp / last superloop timestamp
    int ms_window_isr  = ms_between_timestamps(window_start_timestamp, isr_timestamp);
    int ms_window_loop = ms_between_timestamps(window_start_timestamp, loop_timestamp);

    // the conditions we need to check are:
    // 1) (passed time since time window start > 250 ms) && phase transition occured
    // 2)  passed time since time window start > 500 ms
    // since the isr sets the time only when a phase transition occurs,
    // the first condition is satisfied by checking the time between
    // the start of the time window and the last timestamp set by the isr.
    // if the isr is not triggered in that time, we need a fallback to check for 
    // the second condition. in that case, we can check the time between the start 
    // of the time window and a timestamp taken at the start of the superloop.
    return 
        (ms_window_loop >= MAX_WINDOW_DURATION_IN_MS) ||
        ((ms_window_isr >= MIN_WINDOW_DURATION_IN_MS));
}

int ms_since_timewindow_start(uint32_t timestamp) {
    return ms_between_timestamps(window_start_timestamp, timestamp);
}
