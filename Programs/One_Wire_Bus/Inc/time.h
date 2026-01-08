/**
* @file     time.h
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    stuff that has to do with time.
*           defines some Makros, interface to boards clock
*/

#ifndef TIME_H
#define TIME_H

#define SEND_1          6
#define SEND_0          60
#define WAIT_AFTER_1    64 
#define WAIT_AFTER_0    10
#define SEND_RESET      480
#define SEND_READ_BIT   6
#define WAIT_FOR_BIT    6
#define TEMP_MEASURE    750000
#define WAIT_FOR_PRESENCE_PULSE 15
#define END_READ        55
#define END_PRESENCE    410

#define ONE_SEC 1000000


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