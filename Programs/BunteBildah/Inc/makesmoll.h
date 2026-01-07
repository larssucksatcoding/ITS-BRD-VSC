/**
* @file       makesmoll.h
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Dec 2025
* @brief      mek big imag smols :3
*/

#ifndef MAKESMOLL_H
#define MAKESMOLL_H

#include "LCD_general.h"
#include "stdbool.h"

// the maximum allowed compression ratio. 
#define MAX_COMPRESSION_RATIO 5

/**
* @brief      returns true if compression can be applied to this image.
*             if it is, get_compressed_line can be used.
*             you can optionally disable compression completely by commenting
*             out the define of "#define MAKESMOL_C_USE_COMPRESSION" in the .c file.
*             it will ALSO calculate the needed compression ratio.
*/
bool make_smoll();

/**
* @brief      reads in multiple lines at and averages over n neighbouring pixels
*             to create a line that still fits in the screen.
*
* @param      line: the line this should be written to
* 
* @return     the line.
*/
COLOR* get_compressed_line(COLOR* line);

#endif
