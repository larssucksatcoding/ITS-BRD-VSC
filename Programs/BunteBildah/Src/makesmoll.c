/**
* @file       makesmoll.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Dec 2025
* @brief      makes a big picture small
*/

#include "makesmoll.h"
#include "LCD_general.h"
#include "reader.h"
#include <math.h>
#include <stdbool.h>
#include "line.h"

#define MAKESMOL_C_USE_COMPRESSION

static int compression_ratio = 1;

static COLOR compression_line[MAX_WIDTH];


bool make_smoll() {
    int pic_width = get_width();
    int pic_height = get_height();

    int factor_width =  ceil((double) pic_width / (double) LCD_WIDTH);
    int factor_height =  ceil((double) pic_height / (double) LCD_HEIGHT);

    compression_ratio = (factor_width >= factor_height) ? factor_width : factor_height; 
    if (compression_ratio > MAX_COMPRESSION_RATIO) {
        // throw a temper tantrum.
    }
    
    #ifndef MAKESMOL_C_USE_COMPRESSION
    return false;

    #else
    bool fits_on_display = ((pic_width) <= LCD_WIDTH) && ((pic_height) <= LCD_HEIGHT);
    return !fits_on_display;
    #endif
}

COLOR* get_compressed_line(COLOR* line) {
    // e.g. if compression ratio is 5, every pixel in one "box"
    // counts as 1 / 25 of the final pixel of a box
    float pixel_strength = 1 / pow(compression_ratio, 2.0);

    int compressed_picture_width = get_width() / compression_ratio;
    int compressed_picture_height = get_height() / compression_ratio;

    for (int y = 0; y < compression_ratio; y++) {
        clear_line(compression_line);
        get_next_Line(compression_line);
        
        // nyow compwess :3
        for (int x = 0; x < compressed_picture_width; x++) {
            int start_index = x * compressed_picture_width;
            int end_index = (x + 1) * compressed_picture_width; 

            for (int dx = start_index; dx < end_index; dx++) {
                line[x] = compression_line[dx] * pixel_strength;
            }
        }

        // 0 -> 0 1 2 3 4
        // 1 -> 5 6 7 8 9
        // ...
        // pic_width -> 
    }

    return line;
}
