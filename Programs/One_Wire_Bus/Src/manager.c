/**
* @file     manager.c
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    implements abstract information/ operation on the bus.
*           - Which slaves are connected,
*           - get Temperature
*/

#include "manager.h"
#include "bit_talk.h"
#include "init.h"
#include "LCD_GUI.h"
#include "time.h"

void init() {
    initITSboard();
	GUI_init(DEFAULT_BRIGHTNESS);

    init_time();
    open_drain();
}

/**
* @brief    -
*
* @param    -
* 
* @return   -
*/