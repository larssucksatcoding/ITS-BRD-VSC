/**
* @file     manager.h
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    implements abstract information/ operation on the bus.
*           - Which slaves are connected,
*           - get Temperature
*/

#ifndef MANAGER_H
#define MANAGER_H

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
void copy_arr(int size, const char source[size], char destination[size]);

#endif


/**
* @brief    -
*
* @param    -
* 
* @return   -
*/