/**
  * @file       gpio.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Nov 2025
  * @brief      
  */

#ifndef GPIO_H
#define GPIO_H

/**
  * @brief      initializes the module for first use. always call this before
  *             doing anything else.
  *
  * @param      -
  * 
  * @return     -
  */
void init_gpio();

/**
  * @brief      reads and save current gpio save. **all read functions in this module
  *             will only return what was saved by this function.**
  *
  * @param      -
  * 
  * @return     -
  */
int read_gpio_state();

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
