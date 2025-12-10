/**
  * @file       reader.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Dec 2025
  * @brief      Loads, checks, handles information from input file
  */

// Wichtige Variablen

// Farbpalette?
// compressed?
// current file struct
#ifndef READER_H
#define READER_H
#include "BMP_types.h"
#include "MS_basetypes.h"
#include "LCD_GUI.h"


// FUNCTION


/**
* @brief      reads next Char and sets end of file flag, as soon as 
*             the end has come upon  us
* 
* @return     value of nextByte 
*/
extern BYTE next_byte();

/**
* @brief      loads picture from python file and checks for important information
*
* @param      -
* 
* @return     Error Code if picture is
*/
extern int load_picture();

/**
* @brief      fetches next Pixel line from .bmp
*
* @param      -
* 
* @return     COLOR Array (uint16_t) for each pixel in next line one color
*/
extern COLOR* get_next_Line();

/**
* @brief      returns width of picture (either og picture width or LCD_width if picture width exceed Lcd width)
*
* @param      -
* 
* @return     int width 
*/
extern int get_width();

/**
* @brief      for when we make our picture smaller
*
* @param      -
* 
* @return     -
*/
extern void set_width(int new_width);

/**
* @brief      returns pictures height
*
* @param      -
* 
* @return     int height
*/
extern int get_height();

/**
* @brief      for when we make our picture smaller
*
* @param      -
* 
* @return     -
*/
extern void set_height(int new_height);


#endif 

/**
* @brief      -
*
* @param      -
* 
* @return     -
*/