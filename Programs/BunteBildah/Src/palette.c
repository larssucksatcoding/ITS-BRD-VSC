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
//#include <mm_malloc.h>
#include <stdlib.h>
#include "LCD_general.h"

static COLOR *palette = NULL;
static int size;

void create_palette(int palette_size) {
    size = palette_size;

    // muss das nicht malloc(sizeof(COLOR) * size)?
    // ist der parameter für malloc in byte?
    palette = (COLOR*) malloc (size);

    for(int i = 0; i < size; i++) {
        palette[i] = read_rgbquad_as_color();
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

void delete_palette() {
    if(palette != NULL) {
        free(palette);
        palette = NULL;
    }
}

