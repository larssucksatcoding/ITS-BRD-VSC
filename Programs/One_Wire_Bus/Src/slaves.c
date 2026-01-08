/**
* @file     slaves.c
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    implements struct, stores information bout slaves
*           and implements slave specific functions
*/

#include "slaves.h"
#include <stdint.h>
#include <stdbool.h>
#include "error_handler.h"
#include "manager.h"

#define     SENSOR_B        0x28
#define     SENSOR_S        0x10

slave current_slave;
int c_s_index;
slave slaves[MAX_SLAVE];
uint8_t slave_count; 

/* ~ ~ ~ ~ ~   P R I V A T E - F U N C T I O N S   ~ ~ ~ ~ ~ */

int rom_detected(unsigned char rom[ROM_LENGTH]){
    unsigned char check_rom[ROM_LENGTH];
    bool no_diff = true;
    for(int i = 0; i < slave_count; i++) {
    copy_arr(ROM_LENGTH, slaves[i].ROM, check_rom);
        bool same_rom = true; // assume they have the same rom - if one number is different - not the same
        for (int j = 0; (j < ROM_LENGTH) && same_rom; j++) {
            if(check_rom[j] != rom[j]) {
                same_rom = false;
            }
        }
        if (same_rom == true) {
            // we just found a slave with the same rom
            return ROM_ERR;
        }
    }
    return EOK;
}

/* ~ ~ ~ ~ ~   P U B L I C - F U N C T I O N S   ~ ~ ~ ~ ~ */

void calculate_temperature(){
    // extract important info from scratchpad
    // last 2 bytes
    unsigned char temp_arr[TEMP_LENGTH];
    int temp_int = 0;
    double temp = 0;

    copy_arr(TEMP_LENGTH, current_slave.scratchpad, temp_arr);
    bits_to_temp(temp_arr, &temp_int);

    if(current_slave.family_code == B_FAM) {
        temp = (double) temp_int / 16.0;
    }
    else {
        temp = (double) temp_int /2.0;
    }
    current_slave.temperature = temp;
}

void next_slave(){
    if(c_s_index+1 == slave_count) {
        c_s_index = 0;
    }
    else {
        c_s_index++;
    }
    current_slave = slaves[c_s_index];
}

pslave get_current_slave(){
    return &current_slave;
}

void save_scratchpad(unsigned char scratchpad_data[SCRATCHPAD_LENGTH]){
    copy_arr(SCRATCHPAD_LENGTH, scratchpad_data, current_slave.scratchpad);
}

void new_slave(unsigned char rom_data[ROM_LENGTH]){
    if (rom_detected(rom_data) == ROM_ERR) {
        return;
    }
    slave_count++;
    unsigned int fam = 0;
    unsigned char fam_code[FAM_LENGTH];

    copy_arr(FAM_LENGTH, rom_data, fam_code);
    bits_to_fam(fam_code, &fam);

    slave new_slave;
    copy_arr(ROM_LENGTH, rom_data, new_slave.ROM);
    if(fam == B_FAM){
        new_slave.family_code = B_FAM;
    }
    else {
        new_slave.family_code = S_FAM;
    }
    c_s_index = slave_count -1;
    slaves[c_s_index] = new_slave;
    current_slave = new_slave;
}

void reset_slaves(){
    slave_count = 0;
    c_s_index = -1;
}

char get_slave_count() {
    return slave_count;
}

char get_current_slave_number() {
    return c_s_index + 1;
}


/**
* @brief    -
*
* @param    -
* 
* @return   -
*/