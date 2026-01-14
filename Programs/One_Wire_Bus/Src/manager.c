/**
* @file     manager.c
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    implements command operations on an abstract level + 
*           provides operations for the bit arrays
*/

#include "manager.h"
#include "bit_talk.h"
#include "commands.h"
#include "display.h"
#include "init.h"
#include "slaves.h"
#include "time.h"
#include "error_handler.h"
#include <locale.h>
#include "LCD_GUI.h"

/* ~ ~ ~ ~ ~   P U B L I C - F U N C T I O N S   ~ ~ ~ ~ ~ */

void init() {
    initITSboard();
    
    init_gpio();

    GUI_init(DEFAULT_BRIGHTNESS);
    init_display();
    

    init_time();
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
    
    wait(ONE_SEC);
    while (more_slaves()){
        error = reset();
        error = search_ROM();
    }
    next_slave(); // sets current slave to first slave
    return error;
}

int measure_temperature(){
    int error = reset();
    if (error != EOK) {
        return error;
    }
    match_ROM();
    convert_T();

    reset();
    match_ROM();
    read_scratchpad();
    calculate_temperature();

    return error;
}

/* ~ ~ ~ ~ Functions for calculation and array operations ~ ~ ~ ~ */

void copy_arr(int size, const unsigned char source[size], unsigned char destination[size]){
    for(int i = 0; i < size; i ++) {
        destination[i] = source[i];
    }
}

void bits_to_fam(unsigned char bits[FAM_LENGTH], unsigned int *number) {
    if (number == NULL) {
        return;
    }
    *number = 0;

    for(int i = FAM_LENGTH-1; i >= 0; i--) {
        *number = *number << 1;
        *number += bits[i];
    }
}

void bits_to_temp(unsigned char bits[TEMP_LENGTH], int *temp){
    if (temp == NULL) {
        return;
    }
    int16_t value = 0;  //!< so that 16bit temp will autamtically be
                        // recognized as + / - 

    for(int i = TEMP_LENGTH-1; i >= 0; i--) {
        value = value << 1;
        value += bits[i];
    }
    *temp = value;
}

void bits_to_rom(unsigned char bits[ROM_LENGTH], unsigned long long *rom){
    if (rom == NULL) {
        return;
    }
    *rom = 0;
    for(int i = ROM_LENGTH-1; i >= 0; i--) {
        *rom = *rom << 1;
        *rom += bits[i];
    }
}

// EOF