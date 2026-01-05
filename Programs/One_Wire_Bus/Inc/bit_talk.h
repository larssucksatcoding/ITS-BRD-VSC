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
*
* @param    -
* 
* @return   -
*/
void open_drain();

void push_pull();

void set_low();

void set_high();

void init_bt();

/**
* @brief    master sends 1 to slaves (pulls the line for 6 müs)
*/
void send_1();

/**
* @brief    master sends 0 to slaves (pulls line for 60 müs)
*/
void send_0();

/**
* @brief    master sends read bit to slaves 
*/
void send_read();

/**
* @brief    checks information on bus returns whether bus is high or low
* 
* @return   bool true - bus is HIGH (1)
*                false - bus is LOW (0) 
*/
bool receive();

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