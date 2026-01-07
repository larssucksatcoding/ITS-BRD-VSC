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
* @brief      clears color information out of line
* 
* @return     void
*/
extern void clear_line(COLOR* line);

/**
* @brief      -
*
* @param      int* index - current index we are at
* @param      COLOR* line - line, Color[] where we safe color for each pixel
* @param      int pxl_amount - nr of pixels that are in absolute mode
* 
* @return     int error code (when we get a Index for palette which is not existent)
*/
static int absolute_mode(int* index, COLOR* line, int pxl_amount);

/**
* @brief      enters color for encoded pixels in line
*
* @param      int* index - current index we are at
* @param      COLOR* line - line, Color[] where we safe color for each pixel
* @param      int pxl_amount - nr of pixels with color
* @param      COLOR color - color of the pixels
* 
* @return     void - there is no error that can occur
*/
static void encoded_mode(int* index, COLOR* line, int pxl_amount, COLOR color);

/**
* @brief      checks if we left last line with lefotver information about next pixels or about a delta
*
* @param      int* index - current index
* @param      COLOR* line - line where we safe information bout our pixels
* 
* @return     int error code
*/
static int check_info_first_pxl(int* index, COLOR* line);

// PUBLIC FUNCTIONS

extern void reset_line_module();

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