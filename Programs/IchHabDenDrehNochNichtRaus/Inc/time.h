/**
  * @file       time.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Nov 2025
  * @brief      
  */

#ifndef TIME_H
#define TIME_H

#include "stdbool.h"

/**
  * @brief      initializes the module for first use. always call this before
  *             doing anything else.
  *
  * @param      -
  * 
  * @return     -
  */
void init_time();


/**
  * @brief      saves a new time stamp.
  *
  * @param      -
  * 
  * @return     -
  */
void save_timestamp();


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
  * @param      -
  * 
  * @return     true if time window exceeded 
  */
bool is_timewindow_over();


/**
  * @brief      the total time in seconds since the time window
  *             has been started. this will use the latest timestamp
  *             by gpio, even if it has not been saved yet.
  *
  * @param      -
  * 
  * @return     -
  */
double time_s_since_timewindow_start();

/**
  * @brief      returns 
  *
  * @param      -
  * 
  * @return     -
  */
void time_s_in_timewindow();

#endif
