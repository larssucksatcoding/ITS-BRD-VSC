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


void init_time(volatile uint32_t *last_phase_transition_ts) {
    initTimer();

    current_timestamp = 0;
    window_start_timestamp = 0;
    *last_phase_transition_ts = 0;
}

void update_current() {
    current_timestamp = getTimeStamp();
}

void save_timestamp(volatile uint32_t *last_phase_transition_ts) {
    *last_phase_transition_ts = getTimeStamp();
}

void start_new_timewindow(uint32_t *previous_window_end_timestamp) {
    window_start_timestamp = *previous_window_end_timestamp;
}

void start_first_timewindow() {
    window_start_timestamp = getTimeStamp();
}

bool is_timewindow_over(uint32_t *timestamp) {
    int time_in_ms = ms_since_timewindow_start(timestamp);

    bool phase_transition_occured = 
        (*timestamp == current_timestamp);

    return 
         (time_in_ms >= MAX_WINDOW_DURATION_IN_MS) ||
        ((time_in_ms >= MIN_WINDOW_DURATION_IN_MS) && phase_transition_occured);
}

int ms_since_timewindow_start(uint32_t *timestamp) {
    uint32_t timestamp_diff = 0;

    // check for overflow since last time window
    if (window_start_timestamp >= *timestamp) {

        // window_start_timestamp was taken before overflow, so we get difference
        // by getting "distance" to max int + the timestamp after the overflow
        timestamp_diff = 
            (UINT32_MAX - window_start_timestamp) + *timestamp;
    } else {
        timestamp_diff = 
            *timestamp - window_start_timestamp;
    }

    return timestamp_diff / TICKS_PER_MS;
}