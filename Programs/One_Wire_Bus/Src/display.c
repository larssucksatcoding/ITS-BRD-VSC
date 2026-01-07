/**
* @file     display.c
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    implements the display interface
*/

#include "display.h"
#include "LCD_GUI.h"
#include "LCD_general.h"
#include "fonts.h"

#define     FAM_X           5 
#define     ROM_X           60
#define     TEMP_X          280
#define     LINE_HEIGHT     12
#define     B_NAME          "DS18B20"
#define     S_NAME          "DS18S20"
#define     FONT            Font12      //8, 12, 16, 20, 24 exist
#define     FAM_STR         "Sensor"
#define     ROM_STR         "PDROM"
#define     TEMP_STR        "Temp. [C]"


int y = 1;
Coordinate c;

void display_string(const char *s){
    GUI_disStr(c, s, &Font12, FONT_BACKGROUND, FONT_FOREGROUND);
}


void init_display(){
    GUI_init(DEFAULT_BRIGHTNESS);
    c.y = y;
    c.x = FAM_X;
    display_string(FAM_STR);
    c.x = ROM_X;
    display_string(ROM_STR);
    c.x = TEMP_X;
    display_string(TEMP_STR);
    y += LINE_HEIGHT;
}

void write_info(){
    write_fam_code();
    write_rom();
    write_temp();
}


void write_fam_code(){

}


void write_rom(){

}


void write_temp(){
    
}


/**
* @brief    -
*
* @param    -
* 
* @return   -
*/