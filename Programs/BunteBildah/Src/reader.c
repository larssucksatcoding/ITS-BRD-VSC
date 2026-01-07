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
#include "makesmoll.h"


#define BITCOUNT_PALETTE      8

#define END_OF_FILE           -1


static BITMAPFILEHEADER fileheader;
static BITMAPINFOHEADER infoheader;
static int  width;
static bool palette;
static bool compressed;
static bool eof;

static int compression_ratio;
static bool made_smoll;

COLOR line[MAX_WIDTH];

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
  palette   =  false;
  compressed = false;
  eof = false;
  compression_ratio = 1;

  // reset_line_module();
  // reset line module??
}

extern BYTE next_byte() {
  int nextbyte = nextChar(); 
  if (nextbyte == END_OF_FILE) {
    eof = true;
  }
  return (BYTE) nextbyte;
}

static int get_palette_size() {
  // bfOffBits is a misleading name, since it contains the offset in bytes!!!
  int pixel_data_start_adress = fileheader.bfOffBits;
  int palette_start_adress = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
  int palette_size_in_bytes = pixel_data_start_adress - palette_start_adress;
  return palette_size_in_bytes / sizeof(RGBQUAD);
}

extern int load_picture() {
  reset_variables();

  int error = EOK;
  openNextFile();
  if (error == NOK) {
    return error;
  }

  getFileHeader(&fileheader);
  getInfoHeader(&infoheader);

  // i know, missplaced, but this needs some variables
  // from the headers as of now.
  reset_line_module();
  
  if(infoheader.biBitCount == BITCOUNT_PALETTE) {
    palette = true;
  }
  if(infoheader.biCompression == BI_RLE8) {
    compressed = true;
  }

  width = infoheader.biWidth;

  bool made_smoll;
  error = check_image_scaling_possible(&made_smoll);
  ERR_HANDLER(error != EOK, "ich empfehle eine wilseco d 366 dampfwalze");
  if (error != EOK) {
    return error;
  }

  // reset line module 
  if(palette) {
    int pal_size = get_palette_size();
    create_palette(pal_size);
  }
  
  return error;
}

COLOR* get_printable_line() {
  if(made_smoll) {
    return get_compressed_line(line);
  } else {
    return get_next_Line(line);
  }
}

COLOR* get_next_Line(COLOR* line) {
  clear_line(line);

  int error = EOK;

  // format: 24-bit RGB
  if(!palette){
    RGB_line(line);
  }

  // format: 8-bit, uncompressed
  else if(!compressed) {
    error =  RLE8_uncompressed_line(line);
  }

  // format: 8-bit, compressed
  else {
    error =  RLE8_compressed_line(line);
  }

  ERR_HANDLER(error != EOK, "ich kann so nicht arbeiten");

  return line;
}

extern int get_width(){
  return infoheader.biWidth;
}

extern void set_width(int new_width){
  width = new_width; 
}

extern int get_height(){
  return infoheader.biHeight;
}

extern int get_bits_per_pixel() {
  return infoheader.biBitCount;
}

extern void set_height(int new_height){
  // width = new_width; 
}

extern void end_of_file(){
  eof = true;
}

extern bool reached_eof() {
  return eof;
}

extern bool compressed_formate() {
  return compressed;
}


