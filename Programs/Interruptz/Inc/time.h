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
  * @brief      fetches new timestamp.
  */
void update_current();


/**
  * @brief      saves the last fetched timestamp.
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
  * @return     true if time window exceeded 
  */
bool is_timewindow_over();


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