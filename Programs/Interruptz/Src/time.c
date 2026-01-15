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

// current hardware timestamp, set by refresh_timer.
static uint32_t current_timestamp;

// into these, current_timestamp might be written.
// used by the time window calculations.
static uint32_t window_start_timestamp;
static uint32_t last_phase_transition_timestamp;

void init_time() {
    initTimer();

    current_timestamp = 0;
    window_start_timestamp = 0;
    last_phase_transition_timestamp = 0;
}

void refresh_timer() {
    current_timestamp = getTimeStamp();
}

void save_timestamp() {
    last_phase_transition_timestamp = current_timestamp;
}

void start_new_timewindow() {
    window_start_timestamp = current_timestamp;
}

bool is_timewindow_over() {
    int time_in_ms = ms_since_timewindow_start();

    bool phase_transition_occured = 
        (last_phase_transition_timestamp == current_timestamp);

    return 
         (time_in_ms >= MAX_WINDOW_DURATION_IN_MS) ||
        ((time_in_ms >= MIN_WINDOW_DURATION_IN_MS) && phase_transition_occured);
}

int ms_since_timewindow_start() {
    uint32_t timestamp_diff = 0;

    // check for overflow since last time window
    if (window_start_timestamp >= current_timestamp) {

        // window_start_timestamp was taken before overflow, so we get difference
        // by getting "distance" to max int + the timestamp after the overflow
        timestamp_diff = 
            (UINT32_MAX - window_start_timestamp) + current_timestamp;
    } else {
        timestamp_diff = 
            current_timestamp - window_start_timestamp;
    }

    return timestamp_diff / TICKS_PER_MS;
}