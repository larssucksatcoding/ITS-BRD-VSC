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

#define MAX_PALETTE_SIZE        256

static COLOR palette[MAX_PALETTE_SIZE];
static int size;

void create_palette(int palette_size) {

    for(int i = 0; i < palette_size; i++) {
        palette[i] = read_rgbquad_as_color();
    }
    for (int i = palette_size; i < MAX_PALETTE_SIZE; i++) {
        palette[i] = LCD_BACKGROUND;
    }
}

int get_color(int index, COLOR* color) {
    // warum prüft man nicht direkt index >= in if statement?
    int error = false == (index >= size);
    if ( error == NOK) {
        ERR_HANDLER(error == NOK, "angeforderte Farbindex nicht existent (index out of bounds)");
        *color = WHITE;
        return error;
    }
    
    *color = palette[index];
    return error;
}

