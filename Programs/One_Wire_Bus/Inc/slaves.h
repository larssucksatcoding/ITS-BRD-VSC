/**
* @file     slaves.h
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    implements struct, stores information bout slaves
*           and implements slave specific functions
*/

#ifndef SLAVES_H
#define SLAVES_H

#define     ROM_LENGTH          64
#define     SCRATCHPAD_LENGTH   72    // scratchpad Length of DS18B20 (same for DS18S20?)
#define     MAX_SLAVE           4

#define     B_FAM               0x28  // DS18B20
#define     S_FAM               0x10

#include <stdint.h>

typedef struct  {
  uint8_t       family_code;
  char          ROM[ROM_LENGTH];
  char          scratchpad[SCRATCHPAD_LENGTH]; 
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

/**
* @brief    saves data in scratchpad field of current slave
*
* @param    scratchpad char[] array containing scratchpad data
*/
void save_scratchpad(char scratchpad[SCRATCHPAD_LENGTH]);

/**
* @brief    creates new slave with this ROM Code
*
* @param    rom array containing rom code of slave
*/
void new_slave(char rom[ROM_LENGTH]);

/**
* @brief    deletes all slaves and corresponding data
*/
void reset_slaves();




#endif


/**
* @brief    -
*
* @param    -
* 
* @return   -
*/