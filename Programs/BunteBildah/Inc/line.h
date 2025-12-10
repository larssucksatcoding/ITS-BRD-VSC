/**
* @file       line.h
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Dec 2025
* @brief      reads a line from bmp
*/

#ifndef LINE_H
#define LINE_H

#include "LCD_general.h"
#include <stdbool.h>


/**
* @brief      reads bytes from file, that won't be displayed,
*             because the pic is wider than our display,
*             until we reach the next Line
*/
static void skip_to_next_line(bool palette);

/**
* @brief      clears color information out of line
* 
* @return      
*/
static void clear_line(COLOR* line);

/**
* @brief      -
*
* @param      -
* 
* @return     -
*/
static int absolute_mode(int* index, COLOR* line, int pxl_amount);

/**
* @brief      -
*
* @param      -
* 
* @return     -
*/
static void encoded_mode(int* index, COLOR* line, int pxl_amount, COLOR color);

/**
* @brief      -
*
* @param      -
* 
* @return     -
*/
static int check_info_first_pxl(int index, COLOR* line);

// PUBLIC FUNCTIONS


/**
* @brief      gets pixels of new line in RGB format
* 
* @return     void pixel data will be safed in static line (COLOR[])
*/
extern void RGB_line(COLOR* line);


/**
* @brief      gets pixels of new line in uncompressed rle8 format
* 
* @return     COLOR* containing colors for LCD display
*/
extern int RLE8_uncompressed_line(COLOR* line);


/**
* @brief      interprets info from compressed rle8 format to get information 
*             for each pixel in new line (sets flags, if we get information for more than this line)
* 
* @return     error if something went wrong
*/
extern int RLE8_compressed_line(COLOR* line);

#endif