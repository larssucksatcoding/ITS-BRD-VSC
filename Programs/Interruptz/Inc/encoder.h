/**
  * @file       encoder.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Nov 2025
  * @brief      
  */

#ifndef ENCODER_H
#define ENCODER_H

#include <stdbool.h>

#define DIR_NONE        0
#define DIR_FORWARDS    1
#define DIR_BACKWARDS   2


/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */
void init_encoder();

/**
  * @brief      checks in which direction the encoder is spinning 
  *
  * @param      a_on (pointer) refers to current status of pin0
  *
  * @param      b_on (pointer) refers to current status of pin1
  *
  * @param      a_on_previous (pointer) refers to previous status of pin0
  *
  * @param      b_on_previous (pointer) refers to previous status of pin1
  */
void check_direction(volatile bool *a_on, volatile bool *b_on, volatile bool *a_on_previous, volatile bool *b_on_previous);



// getter
int get_direction();
int get_total_phase_count();
int get_window_phase_count();

// setter
/**
  * @brief      increment phase count by one.
  *
  * @param      direction: the encoder spin direction.
  */
void increment_phase_count();

/**
  * @brief      resets the window_phase_count to 0.
  */
void reset_window_phase_count();



#endif

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */