/**
* @file       display.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Nov 2025
* @brief      This module implements the display interface. 
*/


/*  Includes  ------------------------*/

#include "display.h"
#include <stdlib.h>
#include "LCD_Debug.h"
#include "LCD_GUI.h"
#include "LCD_general.h"
#include "fonts.h"
#include <stdio.h>
#include "angle.h"


/*  Variables  -------------------------*/

// definitions for char array length.
// 1234,56 = "1234,56\0". 2 extra length needed for "," and "\0"
// ^^^^      <- integer part
//      ^^   <- decimal part
#define INTEGER_PART_LEN 4
#define DECIMAL_PART_LEN 2
#define CHAR_LEN (INTEGER_PART_LEN + DECIMAL_PART_LEN + 2)


Coordinate angle_c = {3, 3};
Coordinate angular_momentum_c = {3, 50};
Coordinate error_c = {20, 100};

double old_angle;
double old_angular_momentum;


int default_color = GBLUE;
int err_color = MAGENTA;
int default_font_color = WHITE;


char angle_display[CHAR_LEN];
char angular_momentum_display[CHAR_LEN];
char angle_new[CHAR_LEN];
char angular_momentum_new[CHAR_LEN];

bool display_is_updating = false;
int index = 0;

/*  Functions  -------------------------*/ 

void update_display() {
    // do nothing if display does not need to be updated
    // this is set to true by check_display_data()
    if (!display_is_updating) {
        return;
    }

    // update displayed angle if digit does not match at current index
    if (angle_display[index] != angle_new[index]) {
        Coordinate current_angle_c = angle_c;
        current_angle_c.x += index;

        GUI_disChar(current_angle_c, angle_new[index], 
            &Font20, default_color, default_font_color);
        angle_display[index] = angle_new[index];
    }

    // update displayed angular momentum if digit does not match at current index
    if (angular_momentum_display[index] != angular_momentum_new[index]) {
        Coordinate current_angular_momentum_c = angular_momentum_c;
        current_angular_momentum_c.x += index;

        GUI_disChar(current_angular_momentum_c, angular_momentum_new[index], 
            &Font20, default_color, default_font_color);
        angular_momentum_display[index] = angular_momentum_new[index];
    }

    // update next digit in next iteration.
    index++;

    // skip comma in next iteration
    if (index == INTEGER_PART_LEN) {
        index++;
    }

    // stop updating display if we reached the end of the string.
    if (index >= (CHAR_LEN - 1)) {
        index = 0;
        display_is_updating = false;
    }
}

void check_display_data() {
    double angle = get_angle();
    double angular_momentum = get_angular_momentum();

    sprintf(angle_new, "%04.2f", angle);
    sprintf(angular_momentum_new, "%04.2f", angular_momentum);

    display_is_updating = true;
    index = 0;
}

void print_error(char *e){
    GUI_disStr(error_c, e, &Font20, err_color, default_font_color);
}

void init_display(void) {
    GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
    GUI_clear(default_color);

    display_is_updating = false;
    index = 0;

    sprintf(angle_display, "%04.2f", 0.0);
    sprintf(angular_momentum_display, "%04.2f", 0.0);

    sprintf(angle_new, "%04.2f", 0.0);
    sprintf(angular_momentum_new, "%04.2f", 0.0);

    // write zeroes to display
    GUI_disStr(angle_c, angle_display, 
        &Font20, default_color, default_font_color);
    GUI_disStr(angular_momentum_c, angular_momentum_display, 
        &Font20, default_color, default_font_color);
}

void setErrMode(void) {
    GUI_clear(err_color);
}

void setNormalMode(void) {
    GUI_clear(default_color);
}

// EOF
