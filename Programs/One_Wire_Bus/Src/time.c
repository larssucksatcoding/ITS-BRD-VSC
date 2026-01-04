/**
* @file     time.c
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    stuff that has to do with time.
*           defines some Makros, interface to boards clock
*/

#include "time.h"
#include "timer.h"
#include <stdbool.h>
#include <stdint.h>

#define TICKS_PER_MS (TICKS_PER_US * 1000)

void init_time() {
    initTimer();
}


void wait(int time_müs) {
    uint32_t start_time = getTimeStamp();
    uint32_t current_time = getTimeStamp();
    while((current_time - start_time) < time_müs) {
        current_time = getTimeStamp();
    }
    return;
}



/**
* @brief    -
*
* @param    -
* 
* @return   -
*/