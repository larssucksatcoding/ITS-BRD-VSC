/**
* @file     slaves.h
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    implements struct, stores information bout slaves
*           and implements slave specific functions
*/

#ifndef SLAVES_H
#define SLAVES_H

#include <stdint.h>

typedef struct  {
  uint8_t       family_code;
  int           ROM;
  int           scratchpad; // gotta check how big the scratchpad for each sensor is
  double        temperature;
} slave, *pslave;


/**
* @brief    calculates temperature by converting scratchpad bits into decimal
* 
* @return   temperature current slave measured
*/
double calculate_temperature();

/**
* @brief    rotates through slave[]. Sets current slave to next slave.
*           if current slave is last slave in array, first slave becomes 
*           new current slave.
*/
void next_slave();

/**
* @brief    returns pointer to slave programm is curenntly working with
* 
* @return   pointer to current slave.
*/
pslave get_current_slave();


#endif


/**
* @brief    -
*
* @param    -
* 
* @return   -
*/