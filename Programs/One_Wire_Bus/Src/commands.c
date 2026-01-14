/**
* @file     commands.c
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    implements commands of the bus protocol
*/

#include "commands.h"
#include "crc.h"
#include "manager.h"
#include "time.h"
#include <stdbool.h>
#include "bit_talk.h"
#include "slaves.h"
#include "error_handler.h"

#define     SEARCH_ROM          0xf0
#define     READ_ROM            0x33
#define     MATCH_ROM           0x55
#define     CONVERT_T           0x44
#define     READ_SCRATCHPAD     0xbe

#define     COMMAND_LENGTH      8

#define     LAST_BIT_MASK       0x01


static char last_difference;
static bool spotted_diff;


/* ~ ~ ~ ~ ~   P R I V A T E - F U N C T I O N S   ~ ~ ~ ~ ~ */

/**
* @brief    sends the bits of the command code to the bus
*
* @param    code (int) - code for a command (e.g. 0xf0 for send_rom)
*/
void send_command(int code){
    unsigned char bit;
    for (int i = 0; i < COMMAND_LENGTH; i++) {
        bit = code >> i;
        bit &= LAST_BIT_MASK; // 
        if (bit == 0) {
            send_0();
        }
        else {
            send_1();
        }
    }
}

/**
* @brief    transmitts the rom Code to the slaves. For Match ROM
*
* @param    rom[] ROM Code of slave
*/
void send_rom(const unsigned char rom[]) {
    for (int i = 0; i < ROM_LENGTH; i ++) {
        if(rom[i] == 0) {
            send_0();
        }
        else{
            send_1();
        }
    }
}

/**
* @brief    receives bits from slaves and stores them in array.
*           The first received bit will be stored in array field 0.
*           So Bit 0 wil be in field 0
*           arr[0] - LSB  , arr[size] - MSB         
*
* @param    size - size of array/ length of incoming data
* 
* @param    arr - char array to store data
*/
void get_data(int size, unsigned char arr[size]){
    unsigned char bit;
    for (int i = 0; i < size; i++) {
        bit = receive();
        arr[i] = bit;
    }
}

/* ~ ~ ~ ~ ~   P U B L I C - F U N C T I O N S   ~ ~ ~ ~ ~ */

void init_cmds() {
    last_difference = 0;
    spotted_diff = false;
}

int search_ROM(){
    unsigned char rom[ROM_LENGTH];
    unsigned char bit;
    unsigned char inverse;
    int diff = -1;
    unsigned char start = 0;

    send_command(SEARCH_ROM);

    if (spotted_diff) {
        spotted_diff = false; 

        // get rom of last slave and take the same bits up to the difference.
        // while doing that check, if we receive the same bits this time.
        pslave last_slave = get_current_slave();
        unsigned char last_rom[ROM_LENGTH];
        copy_arr(ROM_LENGTH, last_slave->ROM, last_rom);
        for (int i = 0; i < last_difference; i++) {
            bit = receive();
            inverse = receive();
            if ((bit == 1) && (inverse == 1)) {
                return NO_SLAVE;
            }
            else if ((bit == 0) && (inverse == 0)){
                // Diff in den Roms 
                if ( last_rom[i] == 1) {
                    // Diff wurde schon abgehandelt.
                    send_1();
                }
                else {
                    send_0();
                    diff = i;
                }
            }
            else {
                if (bit == 0) {
                    send_0();
                }
                else { // bit == 1
                    send_1();
                }
                
            }
            rom[i] = last_rom[i]; // = bit
        }

        // choose 1 where last time we chose 1 (last_difference bit)
        bit = receive();
        inverse = receive();
        if (bit != inverse) {
            // this time no diff??
            return ROM_ERR;
        }
        else if (bit == 1) {
            // both are one -> Error
            return ROM_ERR;
        }
        rom[last_difference] = 1;
        send_1();

        start = last_difference + 1; 
    }

    // now continue (or start) as usual

    for (int i = start; i < ROM_LENGTH; i ++) {
        bit = receive();
        inverse = receive();
        if((bit == 1) &&  (inverse == 1)) {
            // bit + inverse is 1 -> ERROR (connection to slaves lost)
            return NO_SLAVE;
        }
        else {
            if (bit == 0) {
                send_0();
                if ( inverse == 0)  {
                    diff = i;
                }
            }
            else { // bit == 1
                send_1();
            }
        }
        rom[i] = bit;
    }

    bool passed_checksum;
    passed_checksum = checkCRC(ROM_LENGTH, rom);

    if(!passed_checksum) {
        return ROM_ERR;
    }

    if(diff != -1) {
        spotted_diff = true;
        last_difference = diff;
    }
    new_slave(rom);

    return EOK;
}

void match_ROM(){
    pslave slave = get_current_slave();
    send_command(MATCH_ROM);
    // wait ?
    send_rom(slave->ROM);
}

void convert_T(){
    send_command(CONVERT_T);
    // supply slave with power
    push_pull();
    wait(TEMP_MEASURE);
    open_drain();
}

int read_scratchpad(){
    pslave slave = get_current_slave();
    unsigned char scratchpad[SCRATCHPAD_LENGTH];

    send_command(READ_SCRATCHPAD);
    get_data(SCRATCHPAD_LENGTH, scratchpad);
    
    bool passed_checksum;
    passed_checksum = checkCRC(SCRATCHPAD_LENGTH, scratchpad);

    if(!passed_checksum) {
        return SCRATCHPAD_ERR;
    }
    save_scratchpad(scratchpad);
    return EOK;
}

int reset(){
    send_reset();
    bool high = receive_presence();

    if(high) {
        return NO_SLAVE; 
    }
    return EOK;
}


bool more_slaves(){
    return spotted_diff;
}

/**
* @brief    -
*
* @param    -
* 
* @return   -
*/