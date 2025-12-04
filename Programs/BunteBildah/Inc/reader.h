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
int load_picture();

/**
  * @brief      checks if input file is usable
  *
  * @param      -
  * 
  * @return     Error code (NOK/ EOK)
  */
int valid_input();

/**
  * @brief      fetches next Pixel line from .bmp
  *
  * @param      -
  * 
  * @return     WORD Array (uint16_t) next line
  */
WORD* get_next_Line();

/**
  * @brief      returns color of next Pixel
  *
  * @param      -
  * 
  * @return     BYTE* (uint8_t) containing 3 values (red, green, blue)
  */
PRGBTRIPLE get_color();



#endif 