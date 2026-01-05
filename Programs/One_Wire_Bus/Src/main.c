/**
* @file     main.c
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    it's the main duh
*/


#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#include "bit_talk.h"
#include "time.h"

#define ONE_SEC 1000

int main(void) {
    init_time();
    init_bt();
    while(true) {
        set_high();
        wait(ONE_SEC);
        open_drain();
        wait(ONE_SEC);
    }

}

/**
* @brief    -
*
* @param    -
* 
* @return   -
*/