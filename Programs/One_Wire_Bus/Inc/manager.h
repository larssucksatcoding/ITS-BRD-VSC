/**
* @file     manager.h
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    implements command operations on an abstract level + 
*           provides operations for the bit arrays
*/

#ifndef MANAGER_H
#define MANAGER_H

#include "slaves.h"

/**
* @brief    initializes important stuff
*/
void init();

/**
* @brief    runs repeatedly through Search ROM until all slaves are detected. 
*           all slaves are stored in slave[] in the slaves module.
*
* @return   error code (EOK or no_slave detected)
*/
int detect_slaves();

/**
* @brief    bundles all steps for measuring and calculating temperature with current sensor
*           (match ROM, convert T, read Scratchpad, calculate Temperate, reset)
*
* @return   error code (EOK or NO_SLAVE)
*/
int measure_temperature();

/**
* @brief    copys source array into destination array. 
*           source array can be bigger than size
*           (bits 0 - size-1 will be copied from source to destination)
*
* @param    size    size of destination array 
*
* @param    source  char[] source[0]=LSB, source[source_size]=MSB
*                   can be bigger than size
*
* @param    destination char[] in the end destination[0]=LSB, destination[size]=MSB
*/
void copy_arr(int size, const unsigned char source[size], unsigned char destination[size]);

/**
* @brief        converts the bit data stored in bits into an integer number
*
* @param        bits array of length FAM_LENGTH which contains only 0 and 1 
*               bits[0]=LSB, bits[FAM_LENGTH-1]=MSB
*
* @param        number pointer dereferencing the destination 
*/
void bits_to_fam(unsigned char bits[FAM_LENGTH], unsigned int *number);

/**
* @brief        converts the bit data stored in bits into an integer number
*
* @param        bits array of length TEMP_LENGTH which contains only 0 and 1 
*               bits[0]=LSB, bits[TEMP_LENGTH-1]=MSB
*
* @param        temp pointer dereferencing the destination 
*/
void bits_to_temp(unsigned char bits[TEMP_LENGTH], int *temp);

/**
* @brief        converts the bit data stored in bits into an integer number
*
* @param        bits array of length ROM_LENGTH which contains only 0 and 1 
*               bits[0]=LSB, bits[ROM_LENGTH-1]=MSB
*
* @param        rom pointer dereferencing the destination 
*/
void bits_to_rom(unsigned char bits[ROM_LENGTH], unsigned long long *rom);

#endif


/**
* @brief    -
*
* @param    -
* 
* @return   -
*/