/**
* @file     bit_talk.c
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    Implements basic communication functions.
*           Like Sending and receiving bits and the reset operation
*/

#include "bit_talk.h"
#include "stm32f429xx.h"

#define OUTPUT  GPIOD->BSRR
#define PD0             0
#define PD1             1
#define SET_REGISTER    0
#define RESET_REGISTER  16

#define PD0_ON          0b00000001
#define PD1_ON          0b00000010


void init_bt() {
    GPIOD->OTYPER |= (1<< PD0);
    GPIOD->OTYPER |= (1<< PD1);
}

void open_drain() {
    GPIOD->BSRR = (1 << (PD1 + SET_REGISTER));
    OUTPUT = (1 << (PD0 + RESET_REGISTER));
}

void push_pull() {
    OUTPUT = (1 << (PD1 + SET_REGISTER));
    OUTPUT = (1 << (PD0 + SET_REGISTER));
}

void set_low(){
    open_drain();
}

void set_high(){
}

void send_1(){

}

void send_0(){

}

/**
* @brief    master sends read bit to slaves 
*/
void send_read();

/**
* @brief    checks information on bus returns whether bus is high or low
* 
* @return   bool true - bus is HIGH (1)
*                false - bus is LOW (0) 
*/
bool receive();

/**
* @brief    master sends reset signal to slaves (pulls line for 480 müs)
*/
void send_reset();


/**
* @brief    -
*
* @param    -
* 
* @return   -
*/