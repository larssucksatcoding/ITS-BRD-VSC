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

#define     SENSOR_B        0x28
#define     SENSOR_S        0x10

slave current_slave;
int c_s_index;
slave slaves[MAX_SLAVE];
uint8_t slave_count; 


int rom_detected(char rom[ROM_LENGTH]){
    char check_rom[ROM_LENGTH];
    bool no_diff = true;
    for(int i = 0; i < slave_count; i++) {
        check_rom = slaves[i]->rom;
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

/*
* @brief        this method sums up data of a char[] into one number. 
*               arr[0]=LSB & arr[size]=MSB
* 
* @param        size number of elements in char[]
*
* @param        arr array which contains 1 and 0 and should be converted into a single number
*
* @param        *number pointer dereferencing the destination 
*/
void char_arr_to_nr(int size, char arr[size], int *number) {
    if (number == NULL) {
        return;
    }
    *number = 0;
    for(int i = size-1; i >= 0; i--) {
        *number = *number << 1;
        *number += arr[i];
    }
}

double calculate_temperature(){
    // extract important info from scratchpad
    // last 2 bytes
    char scratchpad[SCRATCHPAD_LENGTH] = current_slave->scratchpad;
    char temp[TEMP_LENGTH];
    int temp_int = 0;
    double temp = 0;

    for (int i = 0; i < TEMP_LENGTH; i++) {
        temp[i] = scratchpad [i];
    }
    char_arr_to_nr(TEMP_LENGTH, temp, &temp_int);

    if(current_slave->family_code == B_FAM) {
        temp = temp_int /16;
    }
    else {
        temp = temp_int /2;
    }
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

void save_scratchpad(char scratchpad_data[SCRATCHPAD_LENGTH]){
    current_slave->scratchpad = scratchpad_data;
}

void new_slave(char rom_data[ROM_LENGTH]){
    if (rom_detected == ROM_ERR) {
        return;
    }
    slave_count++;
    int fam = 0;
    char fam_code[FAM_LENGTH];

    for (int i = 0; i < FAM_LENGTH; i++){
        fam_code[i] = rom_data[i];
    }
    char_arr_to_nr(FAM_LENGTH, fam_code, &fam);

    slave new_slave;
    new_slave.rom = rom_data;
    if(fam_code == B_FAM){
        new_slave.fam = B_FAM;
    }
    else {
        new_slave.fam = S_FAM;
    }
    c_s_index = slave_count -1;
    slaves[c_s_index] = new_slave;
}

void reset_slaves(){
    slave_count = 0;
    c_s_index = -1;
}


/**
* @brief    -
*
* @param    -
* 
* @return   -
*/