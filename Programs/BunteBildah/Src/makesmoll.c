/**
* @file       makesmoll.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Dec 2025
* @brief      makes a big picture small
*/

#include "makesmoll.h"
#include "BMP_types.h"
#include "LCD_GUI.h"
#include "LCD_general.h"
#include "MS_basetypes.h"
#include "color.h"
#include "reader.h"
#include <math.h>
#include <stdbool.h>
#include "errorhandler.h"


// comment out this define to disable image compression
#define MAKESMOL_C_USE_COMPRESSION


#define RED_INDEX   0
#define GREEN_INDEX 1
#define BLUE_INDEX  2

static int compression_ratio = 1;
static int rgb_line[LCD_WIDTH*3];


static void reset_rgb_line() {
    for (int x = 0; x < LCD_WIDTH*3; x ++) {
        rgb_line[x] = 0;
    }
}

bool make_smoll() {
    #ifndef MAKESMOL_C_USE_COMPRESSION
    return false;

    #else
    int pic_width = get_width();
    int pic_height = get_height();

    int factor_width =  ceil((double) pic_width / (double) LCD_WIDTH);
    int factor_height =  ceil((double) pic_height / (double) LCD_HEIGHT);

    compression_ratio = (factor_width >= factor_height) ? factor_width : factor_height; 

    // throw a temper tantrum.
    bool compressionRatioExceeded = compression_ratio > MAX_COMPRESSION_RATIO;
    ERR_HANDLER(compressionRatioExceeded, "ich empfehle eine wilseco d 366 dampfwalze");
    
    bool fits_on_display = ((pic_width) <= LCD_WIDTH) && ((pic_height) <= LCD_HEIGHT);
    return !fits_on_display;
    #endif
}

COLOR* get_compressed_line(COLOR* line) {
    reset_rgb_line();

    double pixel_amount = pow(compression_ratio, 2.0); // how many pixels are compressed to one
    int compressed_picture_width = get_width() / compression_ratio;

    int line_red, line_green, line_blue;
    BYTE pixel_red, pixel_green, pixel_blue;

    for (int y = 0; y < compression_ratio; y++) {
        
        
        get_next_Line(line);
        
        // nyow compwess :3
        for (int x = 0; x < compressed_picture_width; x++) {
            int start_index = x * compression_ratio;
            int end_index = (x + 1) * compression_ratio;

            line_red = 0;
            line_green = 0;
            line_blue = 0;

            for (int index = start_index; index < end_index; index++) {
                extract_rgb_of_display_color(
                    line[index], &pixel_red, &pixel_green, &pixel_blue);
                line_red += pixel_red;
                line_green += pixel_green;
                line_blue += pixel_blue;
            }

            rgb_line[x*3 + RED_INDEX] += line_red;
            rgb_line[x*3 + GREEN_INDEX] += line_green;
            rgb_line[x*3 + BLUE_INDEX] += line_blue;
        }    
    }

    for (int i = 0; i < compressed_picture_width; i ++) {
        pixel_red   = rgb_line[(i*3) + RED_INDEX] / pixel_amount;
        pixel_green = rgb_line[(i*3) + GREEN_INDEX] / pixel_amount;
        pixel_blue  = rgb_line[(i*3) + BLUE_INDEX] / pixel_amount;
        COLOR pixel_color =  rgb_to_color(pixel_red, pixel_green, pixel_blue);
        line[i] = pixel_color;
    }

    for (int i = compressed_picture_width; i < LCD_WIDTH; i++) {
        line[i] = LCD_BACKGROUND;
    }

    return line;
}

