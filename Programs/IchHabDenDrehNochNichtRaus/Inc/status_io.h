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
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */
bool is_reset_button_pressed();


/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */
void set_dir_led(int dir);


/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */
void set_phase_led(int phase_transition_count);

#endif
