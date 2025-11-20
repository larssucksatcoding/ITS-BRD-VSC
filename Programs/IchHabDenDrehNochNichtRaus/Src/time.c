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

