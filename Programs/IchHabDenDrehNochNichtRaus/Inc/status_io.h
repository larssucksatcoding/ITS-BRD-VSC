/**
  * @file       status_io.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Nov 2025
  * @brief      
  */

#ifndef STATUS_IO_H
#define STATUS_IO_H

#include "stdbool.h"

/**
  * @brief      checks whether reset button is pressed
  *
  * @param      -
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
  * @param      -
  * 
  * @return     -
  */
void set_phase_led(int phase_transition_count);

#endif
