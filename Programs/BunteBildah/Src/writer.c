/**
* @file         writer.c
* @author       Lars Müller-Stumpf, Noah Rajko
* @date         Dec 2025
* @brief        writes to the display, draws the picture
*/

#include "writer.h"
#include "LCD_general.h"
#include "reader.h"

static int position_x;
static int position_y;

static void draw_pixel(COLOR color){

}

static void draw_line(){
    COLOR* line = get_next_Line(); // change this somehow!!! we do not want this twice!!!!!
    for(; position_x< LCD_WIDTH; position_x++){
        draw_pixel(line[position_x]);
    }

}

extern void draw_picture(){
    position_x = 0;
    position_y = 0;
    for(; position_y < LCD_HEIGHT; position_y++){
        draw_line();
    }
}
