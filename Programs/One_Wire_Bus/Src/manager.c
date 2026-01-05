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
#include "commands.h"
#include "init.h"
#include "LCD_GUI.h"
#include "slaves.h"
#include "time.h"
#include "error_handler.h"

void init() {
    initITSboard();
	GUI_init(DEFAULT_BRIGHTNESS);

    init_time();
    open_drain();
    reset_slaves();
    init_cmds();
}

int detect_slaves(){
    reset_slaves();
    int error = reset();
    if (error != EOK) {
        return error;
    }
    error = search_ROM();
    while (error == ROM_ERR){
        search_ROM();
    }
    
    while (more_slaves()){
        error = search_ROM();
    }
    return error;
}

int measure_temperature(){
    int error = reset();
    if (error != EOK) {
        return error;
    }
    match_ROM();
    convert_T();
    error = read_scratchpad();
    for (int i = 2; (error != EOK) & (i > 0); i++) {
        error = read_scratchpad();
        // for loop so we do not try reading a corrupt scratchpad for an endless long time
    }
    calculate_temperature();

    return error;
}

/**
* @brief    -
*
* @param    -
* 
* @return   -
*/