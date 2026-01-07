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
#include "display.h"
#include "init.h"
#include "slaves.h"
#include "time.h"
#include "error_handler.h"

void init() {
    initITSboard();

    init_time();
    open_drain();
    reset_slaves();
    init_cmds();
    init_display();
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


void copy_arr(int size, const unsigned char source[size], unsigned char destination[size]){
    for(int i = 0; i < size; i ++) {
        destination[i] = source[i];
    }
}

/**
* @brief    -
*
* @param    -
* 
* @return   -
*/