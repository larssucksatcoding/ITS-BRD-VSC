/**
  * @file       encoder_direction.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Nov 2025
  * @brief      
  */

#ifndef ENCODER_DIRECTION_H
#define ENCODER_DIRECTION_H


#define DIR_NONE        0
#define DIR_FORWARDS    1
#define DIR_BACKWARDS   2
#define DIR_ERROR       3


/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */
void init_encoder_direction();

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */
int get_direction();


#endif
