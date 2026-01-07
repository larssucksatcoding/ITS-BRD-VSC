/**
 * @file       line.c
 * @author     Lars Müller-Stumpf, Noah Rajko
 * @date       Dec 2025
 * @brief      reads a line from bmp
 */

#include "line.h"
#include "BMP_types.h"
#include "LCD_GUI.h"
#include "LCD_general.h" // contains information about LCD width/height
#include "MS_basetypes.h"
#include "color.h"
#include "errorhandler.h"
#include "math.h"
#include "palette.h"
#include "reader.h"
#include <stdbool.h>

#define END_OF_LINE     0x00
#define END_OF_BITMAP   0x01
#define DELTA           0x02

#define LINE_WIDTH        LCD_WIDTH

// flags + info, if we already read info for following pixels

static int line_width;
static bool next_pxl_absolute;
static bool ends_at_word_boundary;
static bool next_pxl_encoded;
static int pixel_count;   // that many pixel we know aboout
static COLOR pixel_color; // color of pixel we know about (encoded)
static bool delta;
static int delta_x;
static int delta_y;

static int pic_width;

static bool padded;
static int padded_line_width;




extern void reset_line_module() {
  next_pxl_absolute     = false;
  ends_at_word_boundary = true;
  next_pxl_encoded      = false;
  pixel_count           = 0;
  pixel_color           = LCD_BACKGROUND;
  delta                 = false;
  delta_x               = 0;
  delta_y               = 0;

  pic_width = get_width();

  // TODO: refactor this so that the reader module already
  // returns the picture width with padding maybe?
  // calculation for how many padding bytes there are when the
  // picture is uncompressed. the amount of bytes per line
  // must be divisible by 4. see page 8 at the bottom
  int bits_per_pixel = get_bits_per_pixel();
  padded_line_width =
      (int)floor((double)((pic_width * bits_per_pixel) + 31.0) / 32.0) * 4;

  padded = padded_line_width != pic_width;

  // it is more convenient to have the padding in pixels and not in bytes.
  // in 8-bit encodings, this is already the case since one byte
  // correlates to one pixel. this is not the case for 24-bit encodings.

  if (bits_per_pixel == 24) {
    padded_line_width /= sizeof(RGBTRIPLE);
  }

  //clear line
  for (int index = 0; index < MAX_WIDTH; index++) {
    line[index] = LCD_BACKGROUND;
  }
}

extern void clear_line(COLOR *line) {
  for (int index = 0; index < pic_width; index++) {
    line[index] = LCD_BACKGROUND;
  }
}

static int check_info_first_pxl(int *index, COLOR *line) {
  int error = EOK;
  COLOR LCD_color;
  if (next_pxl_absolute) {
    error = absolute_mode(index, line, pixel_count);
  }

  else if (next_pxl_encoded) {
    encoded_mode(index, line, pixel_count, pixel_color);
  }

  else if (delta) {
    if (delta_y > 0) {
      delta_y--;
      // line = white line
      return error; // empty line
    }
    while (delta_x > 0) {
      line[*index] = LCD_BACKGROUND;
      delta_x--;
      (*index)++;
    }
    delta = false;
  }
  return error;
}

static int absolute_mode(int *index, COLOR *line, int pxl_amount) {
  int error = EOK;
  COLOR LCD_color;
  if ((*index + pxl_amount) > pic_width) {
    next_pxl_absolute = true;
    int leftover = pic_width - *index; // pixels leftover in this line
    pixel_count = pxl_amount - leftover; // pixel in absolute in next line
  } else if (next_pxl_absolute) {
    next_pxl_absolute = false;
    pixel_count = 0;
  }

  BYTE palette_index;
  for (     ; (pxl_amount > 0) && (*index < pic_width); (*index)++, pxl_amount--) {
    palette_index = next_byte();
    get_color(palette_index, &LCD_color);
    line[*index] = LCD_color;
  }

  if (!next_pxl_absolute && !ends_at_word_boundary) {
    next_byte();
    ends_at_word_boundary = true;
  }
  return error;
}

static void encoded_mode(int *index, COLOR *line, int pxl_amount, COLOR color) {

  for (   ; (pxl_amount > 0) && (*index < pic_width); (*index)++, pxl_amount--) {
    line[*index] = color;
  }
 
  bool leftover = pxl_amount > 0;
  if(leftover) {
    next_pxl_encoded = true;
    pixel_count = pxl_amount;
    pixel_color = color;
  }
  else {
    next_pxl_encoded = false;
    pixel_count = pxl_amount; // = 0
    pixel_color = LCD_BACKGROUND;
  }
}

// PUBLIC FUNCTIONS

// 24-bit (must be uncompressed)
extern void RGB_line(COLOR *line) {
  int index = 0;
  for (     ; index < pic_width; index++) {
    line[index] = read_rgbtriple_as_color();
  }
  if (padded) {
    for (     ; index < padded_line_width; index ++) {
      read_rgbtriple_as_color();
    }
  }
}

// 8-bit (uncompressed)
extern int RLE8_uncompressed_line(COLOR *line) {
  int error = EOK;
  BYTE pal_index;
  COLOR color;
  int index = 0;

  for (   ; index < pic_width; index++) {
    pal_index = next_byte();
    get_color(pal_index, &color);
    line[index] = color;
  }
  if(padded) {
    for (   ; index < padded_line_width; index ++){
      next_byte();
    }
  }
  return error;
}

// 8-bit (compressed)
extern int RLE8_compressed_line(COLOR *line) {
  int index = 0;
  int error = EOK;
  COLOR LCD_color;

  // check if we completed last line with leftover information
  error = check_info_first_pxl(&index, line);

  BYTE firstByte, secondByte;

  while (index < pic_width) {
    firstByte = next_byte();
    secondByte = next_byte();

    if (firstByte == 0) {
      if (secondByte == END_OF_LINE) {

        // ugly hack that might break later:
        // the 22x16 image is encoded as a sequence
        // of "16 00 00 00" until the bmp ends.
        // this while loop exits after "16 00"
        // because it already read all the required
        // pixels for the line. so the next time
        // around it reads "00 00" and just creates
        // an extra empty line.
        // so whenever we have a new line as the
        // first thing in this loop, just return
        // because cleary we just already had a
        // new line and the "00 00" is just for
        // info.
        if (index == 0) {
          error = RLE8_compressed_line(line);
        }

        return error;
      } else if (secondByte == END_OF_BITMAP) {
        end_of_file();
        return error;
      } else if (secondByte == DELTA) {
        delta_x = next_byte() + index;
        delta_y = next_byte() - 1;

        // idea:
        // LCD_color = last color that was drawn (needs new function)
        // pixel_count = (LINE_WIDTH * delta_y) + delta_x;
        // encoded_mode(&index, line, pixel_count, LCD_color);

        return error;
      } else { // absolute mode
        // wortgrenze anpassen
        ends_at_word_boundary = (secondByte % 2) == 0;
        error = absolute_mode(&index, line, secondByte);
      }
    } else {
      get_color(secondByte, &LCD_color);
      encoded_mode(&index, line, firstByte, LCD_color);
    }
  }

  return error;
}

// EOF
