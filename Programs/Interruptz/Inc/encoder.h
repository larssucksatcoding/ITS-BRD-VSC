/**
  * @file       encoder.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Nov 2025
  * @brief      
  */

#ifndef ENCODER_H
#define ENCODER_H

#include <stdbool.h>

#define PHASE_A 0
#define PHASE_B 1
#define PHASE_C 2
#define PHASE_D 3

#define DIR_NONE        0
#define DIR_FORWARDS    1
#define DIR_BACKWARDS   2


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