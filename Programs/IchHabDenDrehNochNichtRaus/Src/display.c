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


/*  Variables  -------------------------*/

Coordinate angle_c = {3, 3};
Coordinate angular_momentum_c = {3, 7};
Coordinate error_c = {3, 10};

double old_angle;
double old_angular_momentum;


int default_color = GBLUE;
int err_color = MAGENTA;
int default_font_color = WHITE;

/*  Functions  -------------------------*/ 

void update(double angle, double angular_momentum){
    if (angle != old_angle) {
        char aa[10];
        // angle to string
        sprintf(aa, "%4.2f", angle);
        GUI_disStr(angle_c, aa, 
            &Font8, default_color, default_font_color);
        old_angle = angle;
    }

    if (angular_momentum != old_angular_momentum) {
        char aam[10];
        // angle to string
        sprintf(aam, "%4.2f", angle);
        GUI_disStr(angular_momentum_c, aam, 
            &Font8, default_color, default_font_color);
        old_angular_momentum = angular_momentum;
    }
}

void print_error(char *e){
    GUI_disStr(error_c, e, &Font8, err_color, default_font_color);
}


void init_Display(void) {
   GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
   GUI_clear(default_color);
}

void setErrMode(void) {
    GUI_clear(err_color);
}

void setNormalMode(void) {
    GUI_clear(default_color);
}

// EOF
