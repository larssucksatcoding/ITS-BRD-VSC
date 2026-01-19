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

 
#define RESET_REGISTER          16
#define SET_REGISTER            0


/**
  * @brief      initializes the module for first use, clears registers
  *
  * @param      a_on will get the new input at pin0
  *
  * @param      b_on will get the new input at pin1
  *
  * @param      a_on_previous will get value that was at a_on before
  *
  * @param      b_on_previous will get value that was at b_on before
  */
void init_gpio(volatile bool *a_on, volatile bool *b_on, volatile bool *a_on_previous, volatile bool *b_on_previous);

/**
  * @brief      checks whether reset button is pressed
  * 
  * @return     true / false
  */
bool is_reset_button_pressed();

/**
  * @brief      sets led to represent last measured direction of rotation:
  *             d23 on: clockwise, d22 on: counter clockwise
  *
  * @param      integer dir - contains information of rotation direction
  * 
  * @return     void
  */
void set_dir_led();

/**
  * @brief      turn dir led off :c
  */
void set_dir_led_off();

/**
  * @brief      sets error led, in case something went wrong
  * 
  * @return     void
  */
void set_err_led_on();

/**
  * @brief      turns error led off, after error has been handled
  * 
  * @return     void
  */
void set_err_led_off();


/**
  * @brief      reveals total amount of phase shifts (subtract counterclockwise?)
  *
  * @param      int phase_count - Anzahl der insgesamten Phasenwechsel
  */
void set_phase_led();

/**
  * @brief      updates current input status
  *
  * @param      a_on will get the new input at pin0
  *
  * @param      b_on will get the new input at pin1
  *
  * @param      a_on_previous will get value that was at a_on before
  *
  * @param      b_on_previous will get value that was at b_on before
  */
void refresh_input_state(volatile bool *a_on, volatile bool *b_on, volatile bool *a_on_previous, volatile bool *b_on_previous);

#endif

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */