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
COLOR* get_next_Line();


#endif 