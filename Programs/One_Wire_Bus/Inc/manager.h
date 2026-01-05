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
*/
void detect_slaves();

/**
* @brief    bundles all steps for measuring and calculating temperature with current sensor
*           (match ROM, convert T, read Scratchpad, calculate Temperate, reset)
*/
void measure_temperature();

#endif


/**
* @brief    -
*
* @param    -
* 
* @return   -
*/