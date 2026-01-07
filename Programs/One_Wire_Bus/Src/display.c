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
#include "slaves.h"
#include <stdio.h>
#include "manager.h"

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
int counter = 0;

/* ~ ~ ~ ~ ~   P R I V A T E - F U N C T I O N S   ~ ~ ~ ~ ~ */

/**
* @brief    capsels the GUI_disStr method so font and color only appear once:
*           here.
*
* @param    string  string that shall be printed to the display
*/
void display_string(const char *string){
    GUI_disStr(c, string, &Font16, FONT_BACKGROUND, FONT_FOREGROUND);
}

/**
* @brief    prints the standard head to the display
*/
void print_header_text(){
    c.y = START_Y;
    c.x = FAM_X;
    display_string(FAM_STR);
    c.x = ROM_X;
    display_string(ROM_STR);
    c.x = TEMP_X;
    display_string(TEMP_STR);
    c.y += LINE_HEIGHT;
}

/**
* @brief    writes Family Code of current slave to the display
*/
void print_fam_code(){
    c.x = FAM_X;
    if (get_current_slave()->family_code == B_FAM) {
        display_string(B_NAME);
    }
    else {
        display_string(S_NAME);
    }
}

/**
* @brief    writes ROM Code of current slave to the display
*/
void print_rom(){
    c.x = ROM_X;
    unsigned long long rom;
    bits_to_rom(get_current_slave()->ROM, &rom);
    char rom_buff[21];
    int written = snprintf(rom_buff, sizeof(rom_buff), "0x%llx", rom);
    display_string(rom_buff);
}

/**
* @brief    writes last measured temperature of current slave to display
*/
void print_temp(){
    c.x = TEMP_X;
    char temp[15];
    int written = snprintf(temp, sizeof(temp), "%09.5lf", get_current_slave()->temperature);
    if(written < 0) {
        // error occurred damn it
    }
    display_string(temp);
}

/* ~ ~ ~ ~ ~   P U B L I C - F U N C T I O N S   ~ ~ ~ ~ ~ */

void init_display(){
    GUI_init(DEFAULT_BRIGHTNESS);
    print_header_text();

    // Beispiel Daten
    unsigned char rom[ROM_LENGTH]=
        {0,0,0,0,1,0,0,0,1,0,1
            ,0,0,1,0,1,0,0,1,0
            ,1,0,1,0,1,0,1,0,1
            ,0,0,1,1,1,1,0,1,0
            ,0,0,1,0,1,0,1,0,1
            ,0,0,1,1,1,0,0,0,0
            ,1,0,1,0,1,0,1,1};
    new_slave(rom);
    pslave slave = get_current_slave();
    slave->temperature = -20.5;
}


void write_info(){
    if(c.y > 300){
        GUI_clear(LCD_BACKGROUND);
        print_header_text();
    }
    print_fam_code();
    print_rom();
    print_temp();
    c.y += LINE_HEIGHT;
}

/**
* @brief    -
*
* @param    -
* 
* @return   -
*/