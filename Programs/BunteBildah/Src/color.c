
#include "color.h"
#include "BMP_types.h"
#include "input.h"
#include "LCD_GUI.h"
#include "limits.h"

#define UINT5_MAX 0b00011111
#define UINT6_MAX 0b00111111
#define UINT8_MAX 0b11111111

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
COLOR rgb_to_display_color(unsigned char rgbBlue, unsigned char rgbGreen, unsigned char rgbRed) {
    COLOR color = (COLOR) 0;

    // normalize 8bit values to values between 0.0 and 1.0
    double blue_float = (double) rgbBlue / (double) UINT8_MAX;
    double green_float = (double) rgbGreen / (double) UINT8_MAX;
    double red_float = (double) rgbRed / (double) UINT8_MAX;

    // multiply normalized values by max of target values
    // note that green uses 6 bit and red and blue 5 bit
    // in the encoding used by the ITS-Board display.
    int blue_int = (int) (blue_float * UINT5_MAX);
    int green_int = (int) (green_float * UINT6_MAX);
    int red_int = (int) (red_float * UINT5_MAX);

    // shift values into correct bit-indeces of color
    color |= blue_int & BLUE;
    color |= (green_int << 5) & GREEN;
    color |= (red_int << 11) & RED;
    // color = (UINT5_MAX << 11);

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

void test_color_conversion() {
    // a total of 7 test strips will be drawn, testing all of the
    // possible combinations of r, g and b values.
	int height_per_strip = LCD_HEIGHT / 7;

	COLOR color;
	Coordinate coordinate = {0, 0};

	// red strip
	for (int y = height_per_strip * 0; y < height_per_strip * 1; y++) {
		coordinate.y = y;

		for (int x = 0; x < CHAR_MAX; x++) {
			coordinate.x = x;

			color = rgb_to_display_color(0, 0, x);
			GUI_drawPoint(coordinate, color, DOT_PIXEL_1X1, DOT_FILL_AROUND);
		}
	}

	// green strip
	for (int y = height_per_strip * 1; y < height_per_strip * 2; y++) {
		coordinate.y = y;

		for (int x = 0; x < CHAR_MAX; x++) {
			coordinate.x = x;

			color = rgb_to_display_color(0, x, 0);
			GUI_drawPoint(coordinate, color, DOT_PIXEL_1X1, DOT_FILL_AROUND);
		}
	}

	// blue strip
	for (int y = height_per_strip * 2; y < height_per_strip * 3; y++) {
		coordinate.y = y;

		for (int x = 0; x < CHAR_MAX; x++) {
			coordinate.x = x;

			color = rgb_to_display_color(x, 0, 0);
			GUI_drawPoint(coordinate, color, DOT_PIXEL_1X1, DOT_FILL_AROUND);
		}
	}

	// red + green strip
	for (int y = height_per_strip * 3; y < height_per_strip * 4; y++) {
		coordinate.y = y;

		for (int x = 0; x < CHAR_MAX; x++) {
			coordinate.x = x;

			color = rgb_to_display_color(0, x, x);
			GUI_drawPoint(coordinate, color, DOT_PIXEL_1X1, DOT_FILL_AROUND);
		}
	}
	
	// red + blue strip
	for (int y = height_per_strip * 4; y < height_per_strip * 5; y++) {
		coordinate.y = y;

		for (int x = 0; x < CHAR_MAX; x++) {
			coordinate.x = x;

			color = rgb_to_display_color(x, 0, x);
			GUI_drawPoint(coordinate, color, DOT_PIXEL_1X1, DOT_FILL_AROUND);
		}
	}

	// blue + green strip
	for (int y = height_per_strip * 5; y < height_per_strip * 6; y++) {
		coordinate.y = y;

		for (int x = 0; x < CHAR_MAX; x++) {
			coordinate.x = x;

			color = rgb_to_display_color(x, x, 0);
			GUI_drawPoint(coordinate, color, DOT_PIXEL_1X1, DOT_FILL_AROUND);
		}
	}

	// red + green + blue strip
	for (int y = height_per_strip * 6; y < height_per_strip * 7; y++) {
		coordinate.y = y;

		for (int x = 0; x < CHAR_MAX; x++) {
			coordinate.x = x;

			color = rgb_to_display_color(x, x, x);
			GUI_drawPoint(coordinate, color, DOT_PIXEL_1X1, DOT_FILL_AROUND);
		}
	}
}