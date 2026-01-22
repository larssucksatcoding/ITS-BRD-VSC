/**
* @file       display.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Nov 2025
* @brief      This module implements the display interface. 
*/


/*  Includes  ------------------------*/

#include "display.h"
#include "LCD_GUI.h"
#include "LCD_general.h"
#include "fonts.h"
#include <stdio.h>
#include "angle.h"
#include "interrupt.h"


/*  Variables  -------------------------*/

// definitions for char array length.
// 1234,56 = "1234,56\0". 2 extra length needed for "," and "\0"
// ^^^^      <- integer part
//      ^^   <- decimal part
#define INTEGER_PART_LEN 4
#define DECIMAL_PART_LEN 2
#define CHAR_LEN (INTEGER_PART_LEN + DECIMAL_PART_LEN + 2)
#define FORMAT_STR "%07.2f"

#define CHAR_X_LENGTH 15

Coordinate angle_c = {CHAR_X_LENGTH, 3};
Coordinate angular_momentum_c = {CHAR_X_LENGTH, 50};
Coordinate error_c = {20, 100};


int default_color = GBLUE;
int err_color = MAGENTA;
int default_font_color = WHITE;


char angle_display[CHAR_LEN];
char angular_momentum_display[CHAR_LEN];
char angle_new[CHAR_LEN];
char angular_momentum_new[CHAR_LEN];

static bool display_is_updating = false;
int index = 0;

/*  Functions  -------------------------*/ 

void double_to_str(double d, char* str) {

    // ignore negative numbers for now
    if (d < 0) {
        d = -d;
    }

    int integer_part = (int) d;
    
    // loop for extracting integer part
    // 1234 -> 4 (index 3 i 0)
    // 123  -> 3 (i2)
    // 12   -> 2 (i1)
    // 1    -> 1 (index 0 i 3)
    // for (int i = 0; i < INTEGER_PART_LEN; i++) {
    //     int str_index = INTEGER_PART_LEN - (i + 1);

    //     int remainder = integer_part % 10;
    //     str[str_index] = (char) remainder;

    //     integer_part /= 10;
    // }

    str[3] = (char) '0' + ((int)(d) % 10);
    str[2] = (char) '0' + ((int)(d / 10) % 10);
    str[1] = (char) '0' + ((int)(d / 100) % 10);
    str[0] = (char) '0' + ((int)(d / 1000) % 10);

    str[INTEGER_PART_LEN] = '.';

    // loop for decimal place
    str[INTEGER_PART_LEN + 1] = (char) '0' + ((int)(d *  10) % 10);
    str[INTEGER_PART_LEN + 2] = (char) '0' + ((int)(d * 100) % 10);
    str[INTEGER_PART_LEN + 3] = '\0';
}


void display_index_angle(int index) {
    Coordinate current_angle_c = angle_c;
    current_angle_c.x += index * CHAR_X_LENGTH;

    // mask_interrupt_pin(0);
    // mask_interrupt_pin(1);

    GUI_disChar(current_angle_c, angle_new[index], 
        &Font20, default_color, default_font_color);

    // unmask_interrupt_pin(0);
    // unmask_interrupt_pin(1);
}

void display_index_angular_momentum(int index) {
    Coordinate current_angular_momentum_c = angular_momentum_c;
    current_angular_momentum_c.x += index * CHAR_X_LENGTH;

    // mask_interrupt_pin(0);
    // mask_interrupt_pin(1);

    GUI_disChar(current_angular_momentum_c, angular_momentum_new[index], 
        &Font20, default_color, default_font_color);

    // unmask_interrupt_pin(0);
    // unmask_interrupt_pin(1);
}

void update_display() {
    // do nothing if display does not need to be updated
    // this is set to true by check_display_data()
    if (!display_is_updating) {
        return;
    }

    // update displayed angle if digit does not match at current index
    if (angle_display[index] != angle_new[index]) {
        display_index_angle(index);
        angle_display[index] = angle_new[index];
    }

    // update displayed angular momentum if digit does not match at current index
    if (angular_momentum_display[index] != angular_momentum_new[index]) {
        display_index_angular_momentum(index);
        angular_momentum_display[index] = angular_momentum_new[index];
    }

    // update next digit in next iteration.
    index++;

    // skip comma in next iteration
    if (index == INTEGER_PART_LEN) {
        // index++;
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

    // mask_interrupt_pin(0);
    // mask_interrupt_pin(1);

    snprintf(angle_new, CHAR_LEN, FORMAT_STR, angle);
    snprintf(angular_momentum_new, CHAR_LEN, FORMAT_STR, angular_momentum);

    // double_to_str(angle, angle_new);
    // double_to_str(angular_momentum, angular_momentum_new);

    // unmask_interrupt_pin(0);
    // unmask_interrupt_pin(1);

    display_is_updating = true;
    index = 0;
}

void print_error(char *e){
    GUI_disStr(error_c, e, &Font20, err_color, default_font_color);
}


void init_display(void) {
    GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
    GUI_clear(default_color);

    reset_display();
}

void reset_display() {
    display_is_updating = false;
    index = 0;

    char angle_display[CHAR_LEN];
    char angular_momentum_display[CHAR_LEN];

    // snprintf(angle_display, CHAR_LEN, FORMAT_STR, 0.0);
    // snprintf(angular_momentum_display, CHAR_LEN, FORMAT_STR, 0.0);

    double_to_str(0.0, angle_display);
    double_to_str(0.0, angular_momentum_display);

    // snprintf(angle_new, CHAR_LEN, FORMAT_STR, 0.0);
    // snprintf(angular_momentum_new, CHAR_LEN, FORMAT_STR, 0.0);

    double_to_str(0.0, angle_new);
    double_to_str(0.0, angular_momentum_new);


    for (int i = 0; i < CHAR_LEN - 1; i++) {
        display_index_angle(i);
        display_index_angular_momentum(i);
    }
}

void setErrMode(void) {
    GUI_clear(err_color);
}

void setNormalMode(void) {
    GUI_clear(default_color);
}

// EOF
