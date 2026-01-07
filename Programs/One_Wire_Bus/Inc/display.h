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
* @brief    writes Information (Family Code, ROM, temp) of current slave
*           to display sets y++ (y + Zeilenabstand) afterwards
*/
void write_info();

/**
* @brief    writes family code of current slave to display
*/
void write_fam_code();

/**
* @brief    writes rom code of current slave to display
*/
void write_rom();

/**
* @brief    writes measured (+calculated) temp of current slave to display
*/
void write_temp();

#endif


/**
* @brief    -
*
* @param    -
* 
* @return   -
*/