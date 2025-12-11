/*
 * BMP_types.h
 *
 *  Created on: 16.10.2016
 *      Author: Franz Korf
 */

#ifndef _BMP_TYPES_H
#define _BMP_TYPES_H

#include "MS_basetypes.h"

//
// types used within BMP files
//

#define BI_RGB	               0	     // uncompressed format
#define BI_RLE8	               1	     // compressed format
#define BMP_SIGNATURE          0x4d42
#define BI_RGB                 0
#define BI_RLE8                1
#define MAX_COLOR_TABLE_SIZE   256

typedef struct tagBITMAPFILEHEADER {
  WORD    bfType;               // 2Byte
  DWORD   bfSize;               // 4BYte
  WORD    bfReserved1;          // 2Byte
  WORD    bfReserved2;          // 2Byte
  DWORD   bfOffBits;            // 4Byte
} __attribute__((__packed__)) BITMAPFILEHEADER, *PBITMAPFILEHEADER;

// 14 Byte

typedef struct tagBITMAPINFOHEADER{
  DWORD  biSize;                // 4Byte
  LONG   biWidth;               // 4Byte
  LONG   biHeight;              // 4Byte
  WORD   biPlanes;              // 2Byte
  WORD   biBitCount;            // 2Byte
  DWORD  biCompression;         // 4Byte
  DWORD  biSizeImage;           // 4Byte
  LONG   biXPelsPerMeter;       // 4Byte
  LONG   biYPelsPerMeter;       // 4Byte
  DWORD  biClrUsed;             // 4Byte
  DWORD  biClrImportant;        // 4Byte
} __attribute__((__packed__)) BITMAPINFOHEADER, *PBITMAPINFOHEADER;

// 40 Byte

typedef struct tagRGBQUAD {
  unsigned char    rgbBlue;
  unsigned char    rgbGreen;
  unsigned char    rgbRed;
  unsigned char    rgbReserved;
} __attribute__((__packed__)) RGBQUAD, *PRGBQUAD;

typedef struct tagRGBTRIPLE {
  unsigned char rgbtBlue;
  unsigned char rgbtGreen;
  unsigned char rgbtRed;
} __attribute__((__packed__)) RGBTRIPLE, *PRGBTRIPLE;

#endif /* _BMP_TYPES_H */
// EOF
