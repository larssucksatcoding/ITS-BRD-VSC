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
  * @brief      saves the last fetched timestamp when a there was a phase stamp
  *
  * @param      last_phase_transition_timestamp pointer to variable
  */
void save_timestamp(volatile uint32_t *last_phase_transition_timestamp);


/**
  * @brief      starts a new time window.
  *
  * @param      -
  * 
  * @return     -
  */
void start_new_timewindow();


/**
  * @brief      checks whether the time window is over.
  *
  * @param      last_phase_transition_timestamp pointer to variable
  * 
  * @return     true if time window exceeded 
  */
bool is_timewindow_over(volatile uint32_t *last_phase_transition_timestamp);


/**
  * @brief      milliseconds since time window was started.
  * 
  * @return     time duration in ms.
  */
int ms_since_timewindow_start();



#endif

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */