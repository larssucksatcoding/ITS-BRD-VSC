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
  * @brief      initalizes the encoder module: resets direction and total phase count
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



/**
  * @brief      returns spinning direction of encoder    
  */
int get_direction();

/**
  * @brief      calculates diff between total_phase_count and last_total_phase_count
  */
int get_window_phase_count(int *total_phase_count);

/**
  * @brief      saves current total_phase_count so it can be used later to calculate window_phase_count 
  */
void save_last_total_phase_count(int *phase_count);



#endif

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */