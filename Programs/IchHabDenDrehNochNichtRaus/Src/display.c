/**
  * @file display.c
  * @author Franz Korf, HAW Hamburg 
  * @date Mar 2016
  * @brief This modules implements a simple output module. 
  *        It places two terminals in the terminal area of keypad.
  *        One terminal will be used for standard output. The other one
  *        echos pressed digit keys.
  */


/*  Includes  ------------------------*/

#include "display.h"
#include <stdlib.h>
#include "LCD_Debug.h"
#include "LCD_GUI.h"
#include "LCD_general.h"
#include "fonts.h"
#include <stdio.h>


/*  Variables  -------------------------*/

Coordinate angle_c = {3, 3};
Coordinate angular_momentum_c = {3, 7};
Coordinate error_c = {3, 10};

double old_angle;
double old_angular_momentum;


int default_color = GBLUE;
int err_color = MAGENTA;
int default_font_color = WHITE;

// private functions

void clear_display(COLOR color){
    GUI_clear(color);
}

void print_angle(char *a){
    GUI_disStr(angle_c, a, &Font8, default_color, default_font_color);
}

void print_angular_momentum(char *am){
    GUI_disStr(angular_momentum_c, am, &Font8, default_color, default_font_color);
}

// public functions 

void update(double angle, double angular_momentum){
    if (angle != old_angle) {
        char aa[10];
        // angle to string
        sprintf(aa, "%4.2f", angle);
        print_angle(aa);
        old_angle = angle;
    }

    if (angular_momentum != old_angular_momentum) {
        char aam[10];
        // angle to string
        sprintf(aam, "%4.2f", angle);
        print_angle(aam);
        old_angular_momentum = angular_momentum;
    }
}

void print_error(char *e){
    GUI_disStr(error_c, e, &Font8, err_color, default_font_color);
}


void init_Display(void) {
   GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
   clear_display(GBLUE);
}

void setErrMode(void) {
    clear_display(err_color);
}

void setNormalMode(void) {
    clear_display(default_color);
}

// EOF
