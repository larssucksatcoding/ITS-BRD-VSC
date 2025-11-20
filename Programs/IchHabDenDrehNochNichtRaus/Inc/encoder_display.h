/**
  * @file       encoder_display.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Nov 2025
  * @brief      displaying Encoder Information
  */

#ifndef ENCODER_DISPLAY_H
#define ENCODER_DISPLAY_H

/**
  * @brief      initializes the display for output with stat values and descriptions
  *
  * @param      -
  * 
  * @return     void
  */
void init_encoder_display();

/**
  * @brief      updates the display (only changed values)
  *
  * @param      double angle - recently calculated angle
  * @param      double angular_momentum
  * 
  * @return     -
  */
void update(double angle, double angular_momentum);


#endif
