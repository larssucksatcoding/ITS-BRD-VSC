/**
* @file         writer.c
* @author       Lars Müller-Stumpf, Noah Rajko
* @date         Dec 2025
* @brief        writes to the display, draws the picture
*/

#include "writer.h"
#include "LCD_GUI.h"
#include "LCD_general.h"
#include "reader.h"

// switch to drawing individual pixels by commenting out this define.
// you need to recompile afterwards.
#define WRITER_C_LINE_DRAW_MODE

/**
* @brief        helper function that writes one line to the display.
*               the mode of drawing can be chosen by defining
*               WRITER_C_LINE_DRAW_MODE in this c file.
*               if WRITER_C_LINE_DRAW_MODE is defined, the display
*               will draw entire lines to the display which is faster.
*               if it is not defined, the pixels will be drawn to the
*               screen individually.
*/
static void draw_line(Coordinate coordinate) {
    COLOR* line = get_next_Line();

    #ifdef WRITER_C_LINE_DRAW_MODE
    GUI_WriteLine(coordinate, LCD_WIDTH, line);

    #else
    for (int position_x = 0; position_x < LCD_WIDTH; position_x++) {
        coordinate.x = position_x;
        GUI_drawPoint(coordinate, line[position_x], DOT_PIXEL_1X1, DOT_FILL_AROUND);
    }
    #endif
}

// picture needs to be loaded first.
extern void draw_picture() {
    GUI_clear(LCD_BACKGROUND);

    Coordinate coordinate = {0, 0};

    for (int position_y = 0; position_y < LCD_HEIGHT; position_y++) {
        coordinate.y = position_y;
        draw_line(coordinate);

        if (reached_eof()) {
            break;
        }
    }
}
