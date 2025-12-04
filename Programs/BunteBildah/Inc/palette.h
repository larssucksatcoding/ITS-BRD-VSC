/**
* @file       palette.h
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Dec 2025
* @brief      handles the color palette: reads all values and picks out the right color for pixels
*/

#ifndef PALETTE_H
#define PALETTE_H

#include "BMP_types.h"

/**
  * @brief      creates a color palette with specified number of elements
  *
  * @param      size number of elements in color palette 
  * 
  * @return     -
  */
void create_palette(int size);

/**
  * @brief      returns color form Color Palette
  *
  * @param      index value of pixel (= index in color palette)
  * @param      PRGBTRIPLE pointer to RGBTRIPLE structure, colors in there will be updated 
  *
  * @return     int error code (pssible error: index out of bounds)
  */
int get_color(int index, PRGBTRIPLE);

/**
  * @brief      deletes palette to free memory
  *
  * @param      -
  * 
  * @return     -
  */
void delete_palette();

#endif