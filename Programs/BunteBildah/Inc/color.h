
#ifndef COLOR_H
#define COLOR_H

#include "LCD_GUI.h"
#include "BMP_types.h"

COLOR rgbtriple_to_display_color(RGBTRIPLE* triple);

COLOR rgbquad_to_display_color(RGBQUAD* quad);

#endif