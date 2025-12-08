/**
* @file       palette.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Dec 2025
* @brief      handles the color palette: reads all values and picks out the right color for pixels
*/

#include "palette.h"
#include "BMP_types.h"
#include "LCD_GUI.h"
#include "color.h"
#include "input.h"
#include "errorhandler.h"
#include <mm_malloc.h>
#include "LCD_general.h"

COLOR *palette;
PRGBQUAD palette_quad;
int size;


void create_palette(int elements){
    size = elements;
    palette = (COLOR*) malloc (size);
    RGBTRIPLE color;
    BYTE reserved;
    for(int i = 0; i < size; i++) {
        color.rgbtRed = nextChar();
        color.rgbtGreen = nextChar();
        color.rgbtBlue = nextChar();
        reserved = nextChar();
        palette[i] = rgbtriple_to_display_color(&color);
    }
}

int get_color(int index, COLOR* color){
    int error = false == (index >= size);
    if ( error == NOK) {
        ERR_HANDLER(error == NOK, "angeforderte Farbindex nicht existent (index out of bounds)");
        *color = WHITE;
        return error;
    }
    
    *color = palette[index];
    return error;
}

void delete_palette(){
    if(palette_quad != NULL) {
        free(palette_quad);
        palette_quad = NULL;
    }
}

