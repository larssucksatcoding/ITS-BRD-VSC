/**
* @file       makesmoll.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Dec 2025
* @brief      makes a big picture small
*/

#include "makesmoll.h"
#include "LCD_general.h"
#include <math.h>
#include <stdbool.h>

static int factor;


bool make_smoll(int* pic_width, int* pic_height){
    bool fits_on_display = ((*pic_width) <= LCD_WIDTH) && ((*pic_height) <= LCD_HEIGHT);
    if (fits_on_display){
        return false;
    }
    int factor_width =  ceil((*pic_width)/LCD_WIDTH);
    int factor_height =  ceil((*pic_height)/LCD_HEIGHT);

    factor = factor_width >= factor_height ? factor_width : factor_height; 
    *pic_height = (*pic_height)*factor;
    *pic_width = (*pic_width)*factor;
}