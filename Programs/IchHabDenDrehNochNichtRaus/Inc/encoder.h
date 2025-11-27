/**
  * @file       encoder.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Nov 2025
  * @brief      
  */

#ifndef ENCODER_H
#define ENCODER_H


#define DIR_NONE        0
#define DIR_FORWARDS    1
#define DIR_BACKWARDS   2


extern int direction;

extern int total_phase_count;
extern int window_phase_count;


/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */
void init_encoder();

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */
int refresh_encoder();


#endif

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */