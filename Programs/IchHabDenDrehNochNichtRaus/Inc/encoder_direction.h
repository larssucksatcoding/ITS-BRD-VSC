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


extern int direction;


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
int refresh_direction();


#endif

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */