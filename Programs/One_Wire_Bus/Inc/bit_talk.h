/**
* @file     bit_talk.h
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    Implements basic communication functions.
*           Like Sending and receiving bits and the reset operation
*/

#ifndef BIT_TALK_H
#define BIT_TALK_H

#include <stdbool.h>

/**
* @brief    sets the Output on PD0 and PD1 for OpenDrain Mode
*           initializes with Bus high
*/
void open_drain();

/**
* @brief    sets mode to push_pull sets bus high (pd0 & pd1 high)
*/
void push_pull();

/**
* @brief    master sends 1 to slaves (pulls the line for 6 müs)
*           (for open drain)
*/
void send_1();

/**
* @brief    master sends 0 to slaves (pulls line for 60 müs)
*           (for open drain)
*/
void send_0();

/**
* @brief    checks information on bus returns whether bus is high or low
* 
* @return   bool true - bus is HIGH (1)
*                false - bus is LOW (0) 
*/
char receive();

/**
* @brief    master sends reset signal to slaves (pulls line for 480 müs)
*/
void send_reset();



#endif


/**
* @brief    -
*
* @param    -
* 
* @return   -
*/