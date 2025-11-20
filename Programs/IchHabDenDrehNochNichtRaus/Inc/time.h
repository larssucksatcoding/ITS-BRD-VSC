/**
  * @file       time.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Nov 2025
  * @brief      
  */

#ifndef TIME_H
#define TIME_H

#include "stdbool.h"


/* für C -Datei:
    variablen: 
      - start Zeit
      - letzter TimeStamp
      - 


*/


/**
  * @brief      initializes the module for first use. always call this before
  *             doing anything else.
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
// wofür brauchen wir ein Time Window? ich checke nicht
// können wir nicht einfach immer checken, wie viel Zeit
// seit unserem letzten TimeStamp vergangen ist oder?


/**
  * @brief      checks whether the time window is over.
  * 
  * @return     true if time window exceeded 
  */
bool is_timewindow_over();
// equal to - did 500 ms since last time stamp pass?


/**
  * @brief      the total time in seconds since the time window
  *             has been started. this will use the latest timestamp
  *             by gpio, even if it has not been saved yet.
  *   ---> --->  --->  --->    Was ist der Unterschied zwischen dem gpio timestamp 
  *            und unserem eigenen timestamp?
  *
  * @param      -
  * 
  * @return     
  */
double duration_timewindow();

/**
  * @brief      returns notting?
  *
  * @param      -
  * 
  * @return     -
  */
void time_s_in_timewindow();

#endif

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */