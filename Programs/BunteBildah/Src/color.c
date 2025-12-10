
#include "color.h"
#include "BMP_types.h"
#include "input.h"

#define UINT5_MAX  32
#define UINT6_MAX  64
#define UINT8_MAX 256

static RGBTRIPLE triple;
static RGBQUAD quad;

// =================
// PRIVATE FUNCTIONS
// =================

/**
  * @brief  helper function that takes actual 8-bit r, g & b values and
  *         converts them to a single 16-bit color that is used by
  *         the ITS-Board display.
  * @param  the rgb values
  * @retval the matching display color
  */
static COLOR rgb_to_display_color(char rgbBlue, char rgbGreen, char rgbRed) {
    COLOR color = (COLOR) 0;

    // normalize 8bit values to values between 0.0 and 1.0
    double blue_float = (double) rgbBlue / UINT8_MAX;
    double green_float = (double) rgbGreen / UINT8_MAX;
    double red_float = (double) rgbRed / UINT8_MAX;

    // multiply normalized values by max of target values
    // note that green uses 6 bit and red and blue 5 bit
    // in the encoding used by the ITS-Board display.
    int blue_int = (int) blue_float * UINT5_MAX;
    int green_int = (int) green_float * UINT6_MAX;
    int red_int = (int) red_float * UINT5_MAX;

    // shift values into correct bit-indeces of color
    color |= blue_int;
    color |= (green_int << 5);
    color |= (red_int << 11);

    return color;
}

// ================
// PUBLIC FUNCTIONS
// ================

COLOR read_rgbtriple_as_color() {
    COMread((char *) &triple, sizeof(RGBTRIPLE), 1);
    return rgb_to_display_color(
        triple.rgbtBlue,
        triple.rgbtGreen,
        triple.rgbtRed
    );
}

COLOR read_rgbquad_as_color() {
    COMread((char *) &quad, sizeof(RGBQUAD), 1);
    return rgb_to_display_color(
        quad.rgbBlue,
        quad.rgbGreen,
        quad.rgbRed
    );
}

