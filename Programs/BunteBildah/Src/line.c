/**
* @file       line.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Dec 2025
* @brief      reads a line from bmp
*/

#include "LCD_GUI.h"
#include "reader.h"
#include "errorhandler.h"
#include <stdbool.h>
#include "LCD_general.h" // contains information about LCD width/height
#include "MS_basetypes.h"
#include "palette.h"
#include "line.h"
#include "color.h"
#include "math.h"

#define END_OF_LINE           0x00
#define END_OF_BITMAP         0x01
#define DELTA                 0x02

#define PIXEL_WIDTH              ((pic_width <= LCD_WIDTH) ? pic_width : LCD_WIDTH) // nr of pixels in line
#define LINE_WIDTH              LCD_WIDTH

// flags + info, if we already read info for following pixels
static bool     next_pxl_absolute;
static bool     ends_at_word_boundary;
static bool     next_pxl_encoded;
static int      pixel_count;          // that many pixel we know aboout
static COLOR    pixel_color;          // color of pixel we know about (encoded)
static bool     delta;
static int      delta_x;
static int      delta_y;


static int      pic_width;

static int      padded_line_width_in_bytes;

// STATIC FUNCTIONS

extern void clear_line(COLOR* line) {
  for(int index = 0; index < LINE_WIDTH; index ++){
    line[index] = LCD_BACKGROUND;
  }
}

static void skip_to_next_line(bool palette) {

    // this function is only called by uncompressed lines

  for (int i = LINE_WIDTH; i < padded_line_width_in_bytes; i++) {
    next_byte();
  }
}

extern void reset_line_module() {
    next_pxl_absolute = false;
    ends_at_word_boundary = true;
    next_pxl_encoded = false;
    pixel_count = 0;
    pixel_color = LCD_BACKGROUND;
    delta = false;
    delta_x = 0;
    delta_y = 0;

    pic_width = get_width();
    
    // calculation for how many padding bytes there are when the
    // picture is uncompressed. the amount of bytes per line
    // must be divisible by 4. see page 8 at the bottom
    int bits_per_pixel = get_bits_per_pixel();
    padded_line_width_in_bytes = (int) floor((double) (pic_width * bits_per_pixel) + 31.0 / 32.0) * 4;
}

static int check_info_first_pxl(int* index, COLOR* line) {
    int error = EOK;
    COLOR LCD_color;
    if(next_pxl_absolute) {
        error = absolute_mode(index, line, pixel_count);
    }

    else if (next_pxl_encoded) {
        encoded_mode(index, line, pixel_count, pixel_color);
    }

    else if (delta) {
        if(delta_y > 0) {
            delta_y--;
            // line = white line
            return error; // empty line
        }
        while (delta_x > 0) {
            line[*index] = LCD_BACKGROUND;
            delta_x --;
            (*index) ++;
        }
        delta = false;
    }
    return error;
}

static int absolute_mode(int* index, COLOR* line, int pxl_amount) {
    int error = EOK;
    COLOR LCD_color;
    if((*index + pxl_amount) > PIXEL_WIDTH) {
        next_pxl_absolute = true;
        int leftover = PIXEL_WIDTH - *index; // pixels leftover in this line
        pixel_count = pxl_amount - leftover; // pixel in absolute in next line
    }
    else if (next_pxl_absolute) {
        next_pxl_absolute = false;
        pixel_count = 0;
    }

    BYTE palette_index = next_byte();
    for ( ; (pxl_amount > 0) && (*index < PIXEL_WIDTH) ; (*index)++ , pxl_amount --) {
        error = get_color(palette_index, &LCD_color);
        line[*index] = LCD_color;
        palette_index = next_byte();
    }

    if(!next_pxl_absolute && !ends_at_word_boundary) {
        next_byte();
        ends_at_word_boundary = true;
    }
    return error;
}


static void encoded_mode(int* index, COLOR* line, int pxl_amount, COLOR color) {
    // do you need to save the color somewhere here?
    // pixel_color = color;

    if((*index + pxl_amount) > PIXEL_WIDTH) {
        next_pxl_encoded = true;
        int leftover = PIXEL_WIDTH - *index; // pixels leftover in this line
        pixel_count = pxl_amount - leftover; // pixel in encoded in next line
    }
    else if (next_pxl_encoded) {
        next_pxl_encoded = false;
        pixel_count = 0;
        pixel_color = LCD_BACKGROUND;
    }

    for ( ;(pxl_amount > 0) && (*index < PIXEL_WIDTH); (*index)++, pxl_amount--) {
            line[*index] = color;
    }

}

// PUBLIC FUNCTIONS

// 24-bit (must be uncompressed)
extern void RGB_line(COLOR* line) {
  for(int index = 0; index < PIXEL_WIDTH; index++) {
    line[index] = read_rgbtriple_as_color();
  }
  skip_to_next_line(false);
}

// 8-bit (uncompressed)
extern int RLE8_uncompressed_line(COLOR* line) {
  int error = EOK;  
  BYTE pal_index = next_byte();
  COLOR color;
  for(int index = 0; index < PIXEL_WIDTH; index++) {
    error = get_color(pal_index, &color);
    line[index] = color;
    pal_index = next_byte();
  }
  skip_to_next_line(true);
  return error;
}

// 8-bit (compressed)
extern int RLE8_compressed_line(COLOR* line) {
    int index = 0;
    int error = EOK;
    COLOR LCD_color;

    // check if we completed last line with leftover information
    error = check_info_first_pxl(&index, line);

    BYTE firstByte, secondByte;

    while(index < pic_width) {
        firstByte = next_byte();
        secondByte = next_byte();

        if(firstByte == 0) {
            if(secondByte == END_OF_LINE) {
                return error;
            }
            else if(secondByte == END_OF_BITMAP) {
                end_of_file();
                return error;
            }
            else if(secondByte == DELTA) {
                delta_x = next_byte() + index;
                delta_y = next_byte() - 1;

                // idea:
                // LCD_color = last color that was drawn (needs new function)
                // pixel_count = (LINE_WIDTH * delta_y) + delta_x;
                // encoded_mode(&index, line, pixel_count, LCD_color);
        
                return error;
            }
            else { // absolute mode
                // wortgrenze anpassen
                ends_at_word_boundary = (secondByte % 2) == 0;
                error = absolute_mode(&index, line, secondByte);
            }
        }
        else {
            error = get_color(secondByte, &LCD_color);
            encoded_mode(&index, line, firstByte, LCD_color);
        }
    }

    return error;
}

// EOF


