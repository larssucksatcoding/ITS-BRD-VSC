/**
  * @file       angle.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Nov 2025
  * @brief      
  */

#ifndef ANGLE_H
#define ANGLE_H

#include <stdint.h>

extern double angle;
extern double angular_momentum;

/**
  * @brief      recalculates Value of angular momentum
  *
  * @param      phase_count (pointer) total_phase_count at time af calculation
  * 
  * @param      timestamp (pointer) timestamp at time of calculation
  */
void recalculate_angular_momentum(int *phase_count, uint32_t *timestamp);

/**
  * @brief      recalculates current angle 
  *
  * @param      phase_count total phase count at time of calculation
  */
void recalculate_angle(int *phase_count);

/**
  * @brief      returns value of angle
  * 
  * @return     double angle
  */
double get_angle();

/**
  * @brief      returns value of angular momentum
  * 
  * @return     double angular momentum
  */
double get_angular_momentum();

#endif

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */