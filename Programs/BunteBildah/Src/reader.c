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
#include "LCD_general.h" // contains information about LCD width/height
#include "BMP_types.h"
#include "MS_basetypes.h"
#include "palette.h"


#define BITCOUNT_PALETTE      8
#define COMPRESSED            1

#define END_OF_LINE           0x00
#define END_OF_BITMAP         0x01
#define DELTA                 0x02

#define INDEX_IN_WIDTH        ((index < width) && (index < LCD_WIDTH))



PBITMAPFILEHEADER fileheader;
PBITMAPINFOHEADER infoheader;
static int  width;
static bool palette;
static bool big_width;
static bool big_height;
static bool compressed;
static bool eof;

static COLOR *line;

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
* @brief      reads bytes from file, that won't be displayed,
*             because the pic is wider than our display,
*             until we reach the next Line
*/
static void skip_to_next_line() {
  if (width > LCD_WIDTH) {
    for (int i = LCD_WIDTH; i < width; i++) {
      nextChar();
      if(!palette) {
        nextChar();
        nextChar();
      }
    }
  }
}

/**
* @brief      
*
* @param      -
* 
* @return     -
*/
static COLOR* next_line_RGB() {
  RGBTRIPLE rgb; 
  for(int index = 0; INDEX_IN_WIDTH; index++) {
    rgb.rgbtBlue = nextChar();
    rgb.rgbtGreen = nextChar();
    rgb.rgbtRed = nextChar();
    
  }
  skip_to_next_line();  
}



extern int load_picture() {
  reset_variables();

  int error = EOK;
  openNextFile();
  error = readHeaders();
  if (error == NOK) {
    return error;
  }

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

  RGBTRIPLE rgb;
  int error = EOK;
  COLOR LCD_color;
  int index = 0; 
  // format: RGB

  if(!palette){
    return next_line_RGB();
  }

  // format: RLE8, uncompressed
  else if(!compressed) {
    BYTE nextPixel;
    for( ;INDEX_IN_WIDTH; index++) {
      nextPixel = nextChar();
      error = get_color(nextPixel, &rgb);
      // LCD_color = convert rgb 
      line[index] = LCD_color;
    }
    skip_to_next_line();
  }

  // format: RLE8, compressed
  else if (compressed) {
    BYTE nextByte;
    while (INDEX_IN_WIDTH) {
      nextByte = nextChar();
      if(nextByte == 0) {
        BYTE secondByte;
        secondByte = nextChar();
        if(secondByte == END_OF_LINE) {
          return line;
        }
        else if(secondByte == END_OF_BITMAP) {
          eof = true;
          return line;
        }
        else if(secondByte == DELTA) {

        }
        else { // absolute mode
          int pixels_in_absolute = secondByte;
          

        }
      }
      else {
        // Encoded mode, no escape value
        int pxl_with_next_color = nextByte;
        BYTE color = nextChar();
        error = get_color(color, &rgb);
        // = convert rgb
        for (int i = 0; i < pxl_with_next_color && index + i < width; i++) {
          line[index+i] = LCD_color;
        }
      }
    }
  }


  return line;
}




