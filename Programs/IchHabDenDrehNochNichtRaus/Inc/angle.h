/**
  * @file       angle.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Nov 2025
  * @brief      
  */

#ifndef ANGLE_H
#define ANGLE_H

extern double angle;
extern double angular_momentum;

/**
  * @brief      recalculates Values of angle and angular momentum
  */
void recalculate_angular_momentum();

/**
  * @brief      recalculates current angle 
  *
  * @param      -
  * 
  * @return     -
  */
void recalculate_angle();

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