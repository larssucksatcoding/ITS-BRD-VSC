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
#define SHIFT_PD0     0
#define SHIFT_PD1     1
#define SET_REGISTER    0
#define RESET_REGISTER  16

#define STATUS_LEDS         GPIOE

/*  Output  ------------------------------------------*/

#define FORWARDS_LED_MASK       0b10000000


void init_bt() {
    GPIOD->MODER &= ~0x0000000F;
    GPIOD->MODER |= 0x00000005; //1010 Pin 0 und 1 auf gpom
}

void open_drain() {
    GPIOD->BSRR = (1 << (SHIFT_PD1 + SET_REGISTER));
    OUTPUT = (1 << (SHIFT_PD0 + RESET_REGISTER));
}

void push_pull() {
    OUTPUT = (1 << (SHIFT_PD1 + SET_REGISTER));
    OUTPUT = (1 << (SHIFT_PD0 + SET_REGISTER));
}

void set_low(){
    open_drain();
}

void set_high(){
    
    STATUS_LEDS->ODR = FORWARDS_LED_MASK;

    GPIOD -> BSRR = 0b11111111;
    int gpiod = GPIOD -> IDR;
    GPIOD -> BSRR = 0b11111111 << RESET_REGISTER;
    gpiod = GPIOD -> IDR;
    GPIOD -> BSRR = 0b00001000;
    gpiod = GPIOD -> IDR;
    GPIOD -> ODR = 0b00000110;
    gpiod = GPIOD -> IDR;

    int gpiof = GPIOF -> IDR;
    gpiof = GPIOF -> IDR;
    gpiof = GPIOF -> IDR;
    gpiof = GPIOF -> IDR;
    gpiof = GPIOF -> IDR;
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