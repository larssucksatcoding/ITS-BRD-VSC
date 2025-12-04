/**
* @file       palette.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Dec 2025
* @brief      handles the color palette: reads all values and picks out the right color for pixels
*/

#include "palette.h"
#include "BMP_types.h"
#include "input.h"
#include "errorhandler.h"
#include <mm_malloc.h>


PRGBQUAD palette;
int size;


void create_palette(int elements){
    palette = (PRGBQUAD) malloc (elements);
    size = elements;
    RGBQUAD color;
    for(int i = 0; i < size; i++) {
        color.rgbRed = nextChar();
        color.rgbGreen = nextChar();
        color.rgbBlue = nextChar();
        color.rgbReserved = nextChar();
    }
}

int get_color(int index, PRGBTRIPLE rgb){
    int error = false == (index >= size);

    ERR_HANDLER(error == NOK, "angeforderte Farbindex nicht existent (index out of bounds)");
    rgb->rgbtRed = palette[index].rgbRed;
    rgb->rgbtGreen = palette[index].rgbGreen;
    rgb->rgbtBlue = palette[index].rgbBlue;
    return error;
}

void delete_palette(){
    if(palette != NULL) {
        free(palette);
        palette = NULL;
    }
}

