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


/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */
void reset_encoder();

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */
void refresh_encoder();


// getter
int get_direction();
int get_total_phase_count();
int get_window_phase_count();

// setter
/**
  * @brief      increment window phase count by one.
  *
  * @param      direction: the encoder spin direction.
  */
void increment_window_phase_count(int direction);

/**
  * @brief      increase the total_time_window by the amount that is currently
  *             in window_phase_count. resets the window_phase_count to 0.
  */
void update_total_phase_count();



#endif

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */