
#ifndef COLOR_H
#define COLOR_H

#include "LCD_GUI.h"
#include "BMP_types.h"

/**
  * @brief  convert 24-bit rgbtriple to 16-bits needed by display.
  * @param  triple  the rgbtriple
  * @retval the matching display color
  */
COLOR rgbtriple_to_display_color(RGBTRIPLE* triple);

/**
  * @brief  convert 8-bit rgbquad to 16-bits needed by display.
  * @param  triple  the rgbquad
  * @retval the matching display color
  */
COLOR rgbquad_to_display_color(RGBQUAD* quad);

#endif