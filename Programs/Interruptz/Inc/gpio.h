/**
  * @file       gpio.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Nov 2025
  * @brief      
  */

#ifndef GPIO_H
#define GPIO_H

/*  Includes  ----------------------------------------*/
#include "stdbool.h"


#define AUX0_INPUT_MASK    0b00000001      // Maske für den Input 
#define AUX1_INPUT_MASK    0b00000010

#define INPUT               GPIOF
#define PHASE_COUNT_LEDS    GPIOD
#define STATUS_LEDS         GPIOE

#define RESET_REGISTER          16
#define SET_REGISTER            0

/**
  * @brief      initializes the module for first use, clears registers
  *
  * @param      a_on will be resetted (input pin0)
  *
  * @param      b_on will be resetted (input pin1) 
  *
  * @param      a_on_previous will be resetted (previous input pin0)
  *
  * @param      b_on_previous will be resetted (previous input pin1)
  */
void init_gpio(volatile bool *a_on, volatile bool *b_on, volatile bool *a_on_previous, volatile bool *b_on_previous);

void read_gpio_pins(volatile bool *a_on, volatile bool *b_on);

/**
  * @brief      checks whether reset button is pressed
  * 
  * @return     true (is pressed)/ false (is not pressed)
  */
bool is_reset_button_pressed();

/**
  * @brief      sets led to represent last measured direction of rotation:
  *             d23 on: clockwise, d22 on: counter clockwise
  */
void set_dir_led();

/**
  * @brief      turn dir led off and err led off
  */
void set_status_led_off();

/**
  * @brief      sets error led, in case something went wrong
  * 
  * @return     void
  */
void set_err_led_on();

/**
  * @brief      reveals total amount of phase shifts (subtract counterclockwise?)
  *
  * @param      int phase_count - Anzahl der insgesamten Phasenwechsel
  */
void set_phase_led(int *phase_count);

/**
  * @brief      turns off the phase leds
  */
void set_phase_led_off();

#endif

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */