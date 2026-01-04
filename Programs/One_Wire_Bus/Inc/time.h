/**
* @file     time.h
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    stuff that has to do with time.
*           defines some Makros, interface to boards clock
*/

#ifndef TIME_H
#define TIME_H

#include "stdbool.h"

#define SEND_1          6
#define SEND_0          60
#define SEND_RESET      480
#define SEND_READ_BIT   6

/**
* @brief      initializes the module for first use. always call this before
*             doing anything else.
*/
void init_time();

/**
* @brief    Waits for specified microseconds
*
* @param    int time_müs - microseconds (duration) for which we will pause
*/
void wait(int time_müs);


#endif

/**
* @brief    -
*
* @param    -
* 
* @return   -
*/