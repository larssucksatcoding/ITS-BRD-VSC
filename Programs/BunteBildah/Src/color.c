
#include "color.h"
#include "BMP_types.h"
#include "input.h"

#define UINT5_MAX 32
#define UINT6_MAX 64
#define UINT8_MAX 256

static RGBTRIPLE triple;
static RGBQUAD quad;

// =================
// PRIVATE FUNCTIONS
// =================

/**
  * @brief  helper function that takes actual 8-bit rgb values and
  *         converts them to a 16-bit color
  * @param  the rgb values
  * @retval the matching display color
  */
COLOR bmp_to_display_color(char rgbBlue, char rgbGreen, char rgbRed) {
    COLOR color = BLACK; // BLACK is 0

    // normalize 8bit values to values between 0.0 and 1.0
    double blue_float = (double) rgbBlue / UINT8_MAX;
    double green_float = (double) rgbGreen / UINT8_MAX;
    double red_float = (double) rgbRed / UINT8_MAX;

    // multiply normalized values by max of target values
    int blue_int = (int) blue_float * UINT5_MAX;
    int green_int = (int) green_float * UINT6_MAX;
    int red_int = (int) red_float * UINT5_MAX;

    // shift values into correct bit-indeces of color
    color |= blue_int;
    color |= (green_int << 5);
    color |= (red_int << 11);

    return color;
}

/**
  * @brief  convert 24-bit rgbtriple to 16-bits needed by display.
  * @param  triple  the rgbtriple
  * @retval the matching display color
  */
COLOR rgbtriple_to_display_color(RGBTRIPLE* triple) {
    return bmp_to_display_color(
        triple->rgbtBlue,
        triple->rgbtGreen,
        triple->rgbtRed
    );
}

/**
  * @brief  convert 8-bit rgbquad to 16-bits needed by display.
  * @param  triple  the rgbquad
  * @retval the matching display color
  */
COLOR rgbquad_to_display_color(RGBQUAD* quad) {
    return bmp_to_display_color(
        quad->rgbBlue,
        quad->rgbGreen,
        quad->rgbRed
    );
}

// ================
// PUBLIC FUNCTIONS
// ================

COLOR read_rgbtriple_as_color() {
    COMread((char *) &triple, sizeof(RGBTRIPLE), 1);
    return rgbtriple_to_display_color(&triple);
}

COLOR read_rgbquad_as_color() {
    COMread((char *) &quad, sizeof(RGBQUAD), 1);
    return rgbquad_to_display_color(&quad);
}

