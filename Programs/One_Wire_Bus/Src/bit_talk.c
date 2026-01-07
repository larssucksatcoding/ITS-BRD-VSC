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

#define INPUT_MASK      0xFFF0
#define OUTPUT_MASK     0x0005

#define PIN_MASK        0x0003

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

void open_drain() {
    TYPE |= (1 << PD0);
    TYPE &= ~(1 << PD1); // always keep pd1 in push-pull
    OUTPUT = (1 << (PD0 + SET_REGISTER));
    OUTPUT = (1 << (PD1 + SET_REGISTER));
}

void push_pull() {
    TYPE &= ~(1 << PD0);
    TYPE &= ~(1 << PD1);
    OUTPUT = (1 << (PD0 + SET_REGISTER));
    OUTPUT = (1 << (PD1 + SET_REGISTER));
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

    // switch to Input mode (both pins?)
    MODE &= INPUT_MASK;
    int input = GPIOD->IDR;
    input &= PIN_MASK;
    if (input == 0) {
        high = 0;
    }
    MODE |= OUTPUT_MASK;
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