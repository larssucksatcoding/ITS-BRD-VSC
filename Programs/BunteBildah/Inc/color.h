
#ifndef COLOR_H
#define COLOR_H

#include "LCD_general.h"
#include "MS_basetypes.h"

void extract_rgb_of_display_color(
	COLOR color, unsigned char* r, unsigned char* g, unsigned char* b);

/**
  * @brief  reads the next 3 bytes of the file and returns them to the native
  *         16 bit format used by the ITS-Board display. see RGBTRIPLE
  *         of BMP_types.h and COLOR of LCD_general.h for more information.
  * @retval the matching display color
  */
COLOR read_rgbtriple_as_color();

/**
* @brief  reads the next 3 bytes of the file and returns them to the native
*         16 bit format used by the ITS-Board display. see RGBTRIPLE
*         of BMP_types.h and COLOR of LCD_general.h for more information.
* @return the matching display color
*/
COLOR rgb_to_color(BYTE red, BYTE green, BYTE blue);


/**
  * @brief  reads the next 4 bytes of the file and returns them to the native
  *         16 bit format used by the ITS-Board display. see RGBQUAD 
  *         of BMP_types.h and COLOR of LCD_general.h for more information.
  * @retval the matching display color
  */
COLOR read_rgbquad_as_color();

/**
  * @brief  draws a few test strips on the screen to test the color
  *         conversion code. in totla seven strips will be drawn:
  *         red, green, blue, red + green, red + blue, green + blue,
  *         and then rgb combined.
  */
void test_color_conversion();

#endif