/**
* @file       time.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Nov 2025
* @brief      
*/

/*  Includes  -------------------------------------------------*/
#include "time.h"
#include "timer.h"

#define MIN_WINDOW_DURATION     250     // time windows must be at least 250 ms
#define MAX_WINDOW_DURATION     500     // time windows mustn't be longer than 500 ms

static int start;
static int last_timestamp;



void init_time();



void save_timestamp();



void start_new_timewindow();
// wofür brauchen wir ein Time Window? ich checke nicht
// können wir nicht einfach immer checken, wie viel Zeit
// seit unserem letzten TimeStamp vergangen ist oder?



bool is_timewindow_over();
// equal to - did 500 ms since last time stamp pass?



double duration_timewindow();



void time_s_in_timewindow();