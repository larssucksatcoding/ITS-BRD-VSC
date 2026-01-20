/**
  * @file       time.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Nov 2025
  * @brief      
  */

#ifndef TIME_H
#define TIME_H

#include "stdbool.h"
#include <stdint.h>


/**
  * @brief      initializes the module for first use. always call this before
  *             doing anything else.
  *
  * @param      last_phase_transition_timestamp pointer to variable
  */
void init_time(volatile uint32_t *last_phase_transition_timestamp);


/**
  * @brief      fetches new timestamp.
  */
void update_current();


/**
  * @brief      starts a new time window.
  *
  * @param      previous_window_end_timestamp pointer to timestamp where last window ended
  */
void start_new_timewindow(uint32_t *previous_window_end_timestamp);

/**
  * @brief      starts first time window by getting a Time Stamp 
  */
void start_first_timewindow();


/**
  * @brief      checks whether the time window is over.
  *
  * @param      loop_timestamp: timestamp taken at the start of superloop
  *             isr_timestamp:  timestamp taken by the isr when phase
  *             transition occurs.
  *
  * @return     true if time window exceeded 
  */
bool is_timewindow_over(uint32_t loop_timestamp, uint32_t isr_timestamp);


/**
  * @brief      milliseconds between time window start and timestamp.
  *
  * @param      timestamp timestamp to compare to start
  * 
  * @return     diff between timestamp and window start in ms.
  */
int ms_since_timewindow_start(uint32_t timestamp);



#endif

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */