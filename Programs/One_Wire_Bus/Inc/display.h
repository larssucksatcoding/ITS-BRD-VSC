/**
* @file     display.h
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    implements the display interface
*/

#ifndef DISPLAY_H
#define DISPLAY_H

/**
* @brief    initializes GUI
*/
void init_display();

/**
* @brief    writes last measured temperature of current slave to display
*/
void print_temp();

/**
* @brief    writes Information (Family Code, ROM, temp) of current slave
*           to display sets y++ (y + Zeilenabstand) afterwards
*/
void write_info();

/**
* @brief    clears out the temp data
*/
void clear_temp();

/**
* @brief    clears family code and pdrom of all sensors
*/
void clear_sensor_pdrom();

#endif

//EOF