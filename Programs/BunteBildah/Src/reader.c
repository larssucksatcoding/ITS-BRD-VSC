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
#include "line.h"
#include "color.h"
#include <stdlib.h>


#define BITCOUNT_PALETTE      8

#define END_OF_FILE           -1



#define INDEX_IN_WIDTH        ((index < width) && (index < LCD_WIDTH))
#define LINE_WIDTH            (width <= LCD_WIDTH ? width : LCD_WIDTH)



PBITMAPFILEHEADER fileheader;
PBITMAPINFOHEADER infoheader;
static int  width;
static bool palette;
static bool big_width;
static bool big_height;
static bool compressed;
static bool eof;

extern COLOR line[LCD_WIDTH];

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

  reset_line_module();
  // reset line module??
}



extern BYTE next_byte() {
  int nextbyte = nextChar(); 
  if (nextbyte == END_OF_FILE) {
    eof = true;
  }
  return (BYTE) nextbyte;
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
  if(infoheader->biCompression == BI_RLE8) {
    compressed = true;
  }

  width = infoheader->biWidth;
  // reset line module 
  if(palette) {
    int pal_size = infoheader->biClrUsed;
    if (pal_size == 0) {
      pal_size = MAX_COLOR_TABLE_SIZE;
    }
    create_palette(pal_size);
  }
  
  return error;
}

COLOR* get_next_Line(){
  
  clear_line(line);

  // TODO:
  // if big_width, we need to compress the image (exercise c)

  int error = EOK;
  // format: RGB
  if(!palette){
    RGB_line(line);
    // skip to next Line?
  }

  // format: RLE8, uncompressed
  else if(!compressed) {
    error =  RLE8_uncompressed_line(line);
    // skip to next line?
  }

  // format: RLE8, compressed
  else {
    error =  RLE8_compressed_line(line);
    // skip to next line?
  }

  return line;
}

extern int get_width(){
  return infoheader->biWidth;
}

extern void set_width(int new_width){
  width = new_width; 
}

extern int get_height(){
  return infoheader->biHeight;
}

extern void set_height(int new_height){
  // width = new_width; 
}

extern void end_of_file(){
  eof = true;
}




