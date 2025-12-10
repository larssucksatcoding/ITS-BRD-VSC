
#ifndef COLOR_H
#define COLOR_H

#include "LCD_general.h"

/**
  * @brief  reads the next 3 bytes of the file and returns them to the native
  *         16 bit format used by the ITS-Board display. see RGBTRIPLE
  *         of BMP_types.h and COLOR of LCD_general.h for more information.
  * @retval the matching display color
  */
COLOR read_rgbtriple_as_color();

/**
  * @brief  reads the next 4 bytes of the file and returns them to the native
  *         16 bit format used by the ITS-Board display. see RGBQUAD 
  *         of BMP_types.h and COLOR of LCD_general.h for more information.
  * @retval the matching display color
  */
COLOR read_rgbquad_as_color();

#endif