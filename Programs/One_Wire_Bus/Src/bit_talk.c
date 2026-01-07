/**
* @file     bit_talk.c
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    Implements basic communication functions.
*           Like Sending and receiving bits and the reset operation
*/

#include "bit_talk.h"
#include "stm32f429xx.h"
#include "time.h"

#define OUTPUT          GPIOD->BSRR
#define TYPE            GPIOD->OTYPER
#define MODE            GPIOD->MODER

#define INPUT_MASK      0xFFF0  // 00 input mode
#define OUTPUT_MASK     0x0005  // 01 gpom

#define PIN_MASK        0x0001

#define PD0             0
#define PD1             1
#define SET_REGISTER    0
#define RESET_REGISTER  16


/* ~ ~ ~ ~ ~   P R I V A T E - F U N C T I O N S   ~ ~ ~ ~ ~ */

/**
* @brief    sets bus to 1 in open drain
*/
void set_high(){
    OUTPUT = (1 << (PD0 + SET_REGISTER));
}

/**
* @brief    sets bus to 0 in open drain
*/
void set_low(){
    OUTPUT = (1 << (PD0 + RESET_REGISTER));
}

/**
* @brief    master sends read bit to slaves 
*/
void send_read(){
    set_low();
    wait(SEND_READ_BIT);
    set_high();
}

/* ~ ~ ~ ~ ~   P U B L I C - F U N C T I O N S   ~ ~ ~ ~ ~ */

void init_gpio() {
    MODE &= INPUT_MASK;
    MODE |= OUTPUT_MASK;
    
    TYPE |= (1 << PD0);     // pd0 in open-drain
    TYPE &= ~(1 << PD1);    // pd1 in push-pull
    OUTPUT = (1 << (PD0 + SET_REGISTER));
    OUTPUT = (1 << (PD1 + SET_REGISTER));
}

void open_drain() {
    TYPE |= (1 << PD0);
    OUTPUT = (1 << (PD0 + SET_REGISTER));
}

void push_pull() {
    TYPE &= ~(1 << PD0);
    OUTPUT = (1 << (PD0 + SET_REGISTER));
}

void send_1(){
    set_low();
    wait(SEND_1);
    set_high();
}

void send_0(){
    set_low();
    wait(SEND_0);
    set_high();
}

char receive(){
    char high = 1;
    send_read();
    
    wait(WAIT_FOR_BIT);
    int t;
    for (t = 0; t < 55; t ++) {
        int input = GPIOD->IDR;
        input &= PIN_MASK;
        if (input == 0) {
            high = 0;
            break;
        }
        wait(1);
    }
    // MODE |= OUTPUT_MASK;
    wait(END_READ-t);
    return high;
}

char receive_presence(){
    char high = 1;
    wait(15);
    int t = 0;
    for ( ; t < 100; t++) {
        wait(1);
        int input = GPIOD->IDR;
        input &= PIN_MASK;
        if (input == 0) {
            high = 0;
            break;
        }
    }
    wait(END_PRESENCE);
    return high;

}

void send_reset(){
    set_low();
    wait(SEND_RESET);
    set_high();
}


/**
* @brief    -
*
* @param    -
* 
* @return   -
*/