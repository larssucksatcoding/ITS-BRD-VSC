
#include "color.h"

#define MAX_INT_5_BIT 32
#define MAX_INT_6_BIT 64
#define MAX_INT_8_BIT_F 256.0f

COLOR bmp_to_display_color(char rgbBlue, char rgbGreen, char rgbRed) {
    COLOR color = BLACK; // BLACK is 0

    // normalize 8bit values to values between 0.0 and 1.0
    double blue_float = (double) rgbBlue / MAX_INT_8_BIT_F;
    double green_float = (double) rgbGreen / MAX_INT_8_BIT_F;
    double red_float = (double) rgbRed / MAX_INT_8_BIT_F;

    // multiply normalized values by max of target values
    int blue_int = (int) blue_float * MAX_INT_5_BIT;
    int green_int = (int) green_float * MAX_INT_6_BIT;
    int red_int = (int) red_float * MAX_INT_5_BIT;

    // shift values into correct bit-indeces of color
    color |= blue_int;
    color |= (green_int << 5);
    color |= (red_int << 11);

    return color;
}

COLOR rgbtriple_to_display_color(RGBTRIPLE* triple) {
    return bmp_to_display_color(
        triple->rgbtBlue,
        triple->rgbtGreen,
        triple->rgbtRed
    );
}

COLOR rgbquad_to_display_color(RGBQUAD* quad) {
    return bmp_to_display_color(
        quad->rgbBlue,
        quad->rgbGreen,
        quad->rgbRed
    );
}

