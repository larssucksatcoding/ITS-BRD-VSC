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

extern bool a_on_previous;
extern bool b_on_previous;
extern bool a_on;
extern bool b_on;

/**
  * @brief      initializes the module for first use, clears registers
  */
void init_gpio();

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
  * @brief      updates value of the intern Input Variables
  * 
  * @return     void
  */
void refresh_input_state();


#endif

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */