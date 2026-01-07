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

#define     START_Y         5
#define     FAM_X           5 
#define     ROM_X           90
#define     TEMP_X          320
#define     LINE_HEIGHT     20
#define     B_NAME          "DS18B20"
#define     S_NAME          "DS18S20"
#define     FONT            Font12      //8, 12, 16, 20, 24 exist
#define     FAM_STR         "Sensor"
#define     ROM_STR         "PDROM"
#define     TEMP_STR        "Temp. [C]"

Coordinate c;

void display_string(const char *s){
    GUI_disStr(c, s, &Font16, FONT_BACKGROUND, FONT_FOREGROUND);
}

void display_txt(){
    c.x = FAM_X;
    display_string(FAM_STR);
    c.x = ROM_X;
    display_string(ROM_STR);
    c.x = TEMP_X;
    display_string(TEMP_STR);
    c.y += LINE_HEIGHT;
}

void init_display(){
    GUI_init(DEFAULT_BRIGHTNESS);
    c.y = START_Y;
    display_txt();
}

void reset_display(){
    GUI_clear(LCD_BACKGROUND);
    c.y = START_Y;
    display_txt();
}


void write_info(){
    if(c.y > 300) {
        reset_display();
    }
    display_txt();
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