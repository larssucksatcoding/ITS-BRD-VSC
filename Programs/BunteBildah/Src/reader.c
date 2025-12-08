/**
  * @file       reader.c
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Dec 2025
  * @brief      Loads, checks and handles information from input file
  */

#include "reader.h"
#include "BMP_types.h"
#include "headers.h"
#include "input.h"
#include "errorhandler.h"
#include <stdbool.h>
#include <stdio.h>
#include "LCD_general.h" // contains information about LCD width/height
#include "BMP_types.h"
#include "MS_basetypes.h"
#include "palette.h"
#include "color.h"


#define BITCOUNT_PALETTE      8
#define COMPRESSED            1

#define END_OF_FILE           -1

#define END_OF_LINE           0x00
#define END_OF_BITMAP         0x01
#define DELTA                 0x02

#define INDEX_IN_WIDTH        ((index < width) && (index < LCD_WIDTH))
#define LINE_WIDTH            ((width <= LCD_WIDTH) ? width : LCD_WIDTH)



PBITMAPFILEHEADER fileheader;
PBITMAPINFOHEADER infoheader;
static int  width;
static bool palette;
static bool big_width;
static bool big_height;
static bool compressed;
static bool eof;

static COLOR *line;


// flags + info, if we already read info for following pixels
static bool   next_pxl_absolute;
static bool   next_pxl_encoded;
static int    pixel_count;
static COLOR  start_color;
static bool   delta;
static int    delta_x;
static int    delta_y;

/*
*                           (Breite der Zeile)*(Anzahl Bits pro Eintrag) + 31
*  Anzahl Bytes pro Zeile = ---------------------------------------------------  * 4
*                                                 32
*
*/

/**
* @brief      sets static variables to default values
*/
static void reset_variables() {
  palette =  false;
  big_width = false;
  big_height = false;
  compressed = false;
  eof = false;

  next_pxl_absolute = false;
  next_pxl_encoded = false;
  pixel_count = 0;
  delta = false;
  delta_x = 0;
  delta_y = 0;
  eof = false;
}

/**
* @brief      reads next Char and sets end of file flag, as soon as 
*             the end has come upon  us
* 
* @return     value of nextByte 
*/
static BYTE next_byte() {
  int nextbyte = nextChar(); 
  if (nextbyte == END_OF_FILE) {
    eof = true;
  }
  return (BYTE) nextbyte;
}

/**
* @brief      reads bytes from file, that won't be displayed,
*             because the pic is wider than our display,
*             until we reach the next Line
*/
static void skip_to_next_line() {
  for (int i = LCD_WIDTH; i < width; i++) {
    while(!eof) {
      next_byte();
      if(!palette) {
        next_byte();
        next_byte();
      }
    }
  }
}

/**
* @brief      gets pixels of new line in RGB format
* 
* @return     void pixel data will be safed in static line (COLOR[])
*/
static void RGB_line() {
  RGBTRIPLE rgb; 
  for(int index = 0; INDEX_IN_WIDTH && !eof; index++) {
    rgb.rgbtBlue = next_byte();
    rgb.rgbtGreen = next_byte();
    rgb.rgbtRed = next_byte();

    // TODO: save line in line* here
    line[index] = rgbtriple_to_display_color(&rgb); 
  }
  if (big_width){
    skip_to_next_line();
  }
}

/**
* @brief      gets pixels of new line in uncompressed rle8 format
* 
* @return     COLOR* containing colors for LCD display
*/
static int RLE8_uncompressed_line() {
  int error = EOK;  
  BYTE nextPixel = next_byte();
  COLOR color;
  for(int index = 0; INDEX_IN_WIDTH && !eof; index++) {
    error = get_color(nextPixel, &color);
    line[index] = color;
    nextPixel = next_byte();
  }
  // check if we reached end of file
  if (big_width) {
    skip_to_next_line();
  }
  return error;
}

/**
* @brief      interprets info from compressed rle8 format to get information 
*             for each pixel in new line (sets flags, if we get information for more than this line)
* 
* @return     error if something went wrong
*/
static int RLE8_compressed_line(){
  BYTE firstByte = (BYTE) next_byte();
  BYTE secondByte = (BYTE) next_byte();
  int index = 0;
  int error = EOK;
  COLOR LCD_color;
  RGBTRIPLE rgb;

  // check if we know anything about first pixels

  if(next_pxl_absolute) {
    
    
  }
  else if (next_pxl_encoded) {


  }
  else if (delta) {


  }

  while (INDEX_IN_WIDTH && !eof) {
    if(firstByte == 0) {
      if(secondByte == END_OF_LINE) {
        return error;
      }
      else if(secondByte == END_OF_BITMAP) {
        eof = true;
        return error;
      }
      else if(secondByte == DELTA) {
        BYTE horizontalDelta = next_byte();
        BYTE verticalDelta = next_byte();
        
        return error;
      }
      else { // absolute mode
        int pixels_in_absolute = secondByte;
        if((index + pixels_in_absolute) > width || (index + pixels_in_absolute)) {
          next_pxl_absolute = true;
          if(big_width) {
            int leftover = LCD_WIDTH - index;
            pixel_count = pixels_in_absolute - leftover;
          }
          else {
            int leftover = width - index;
            pixel_count = pixels_in_absolute - leftover;
          }
        }
        for(int i = 0; i < pixels_in_absolute && INDEX_IN_WIDTH && !eof; i++, index++){
          error = get_color(next_byte(), &LCD_color);
          line[index] = LCD_color;
        }

      }
    }
    else {
      // Encoded mode, no escape value
      int pxl_with_next_color = firstByte;
      BYTE index = next_byte();
      error = get_color(index, &LCD_color);
      // = convert rgb
      for (int i = 0; i < pxl_with_next_color && index + i < width; i++) {
        line[index+i] = LCD_color;
      }
    }
    firstByte = next_byte();
  }
}



extern int load_picture() {
  reset_variables();

  int error = EOK;
  openNextFile();
  error = readHeaders();
  if (error == NOK) {
    return error;
  }

  // i think readHeaders() does this already
  getFileHeader(fileheader);
  getInfoHeader(infoheader);
  
  if(infoheader->biHeight > LCD_HEIGHT) {
    big_height = true;
  }
  if(infoheader->biWidth > LCD_WIDTH) {
    big_width = true;
  }
  if(infoheader->biBitCount == BITCOUNT_PALETTE) {
    palette = true;
  }
  if(infoheader->biCompression == COMPRESSED) {
    compressed = true;
  }

  width = infoheader->biWidth;
  COLOR array[width];
  line = &array[0];

  if(palette) {
    int size = infoheader->biClrUsed;
    if (size == 0) {
      size = MAX_COLOR_TABLE_SIZE;
    }
    create_palette(size);
  }
  return error;
}


COLOR* get_next_Line(){

  // format: RGB
  if(!palette){
    return RGB_line();
  }

  // format: RLE8, uncompressed
  else if(!compressed) {
    return RLE8_uncompressed_line();
  }

  // format: RLE8, compressed
  else if (compressed) {
    return RLE8_compressed_line();
  }

  return line;
}




