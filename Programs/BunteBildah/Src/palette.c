/**
* @file       palette.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Dec 2025
* @brief      handles the color palette: reads all values and picks out the right color for pixels
*/

#include "palette.h"
#include "LCD_GUI.h"
#include "color.h"
#include "errorhandler.h"
#include "LCD_general.h"
#include <stdio.h>

#define MAX_PALETTE_SIZE        256

static COLOR palette[MAX_PALETTE_SIZE];
static int size;

void create_palette(int palette_size) {
    size = palette_size;
    ERR_HANDLER(size > MAX_PALETTE_SIZE, "palette is too big for its own good");

    for(int i = 0; i < palette_size; i++) {
        palette[i] = read_rgbquad_as_color();
    }
    for (int i = palette_size; i < MAX_PALETTE_SIZE; i++) {
        palette[i] = LCD_BACKGROUND;
    }
}

void get_color(int index, COLOR* color) {
    char err_str[200];
    snprintf(err_str, 200, "palette: index %i >= size %i", index, size);
    ERR_HANDLER((index >= size), err_str);
    *color = palette[index];
}

