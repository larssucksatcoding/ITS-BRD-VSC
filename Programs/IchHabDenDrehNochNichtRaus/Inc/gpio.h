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
void set_dir_led(int dir);


/**
  * @brief      reveals total amount of phase shifts (subtract counterclockwise?)
  *
  * @param      int phase_count - Anzahl der insgesamten Phasenwechsel
  */
void set_phase_led(int phase_count);




/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */
void write_gpiod_led(int mask);

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */
void write_gpioe_led(int mask);

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */
void get_gpiof_state();


#endif

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */