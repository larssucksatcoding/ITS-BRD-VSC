/**
* @file     slaves.c
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    implements struct, stores information bout slaves
*           and implements slave specific functions
*/

#include "slaves.h"
#include <stdint.h>

#define     SENSOR_B        0x28
#define     SENSOR_S        0x10
#define     MAX_SLAVES      5

slave current_slave;
int c_s_number;
slave slaves[MAX_SLAVES];
uint8_t slave_count; 


/**
* @brief    -
*
* @param    -
* 
* @return   -
*/