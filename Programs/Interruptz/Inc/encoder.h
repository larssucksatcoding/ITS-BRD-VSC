/**
  * @file       encoder.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Nov 2025
  * @brief      
  */

#ifndef ENCODER_H
#define ENCODER_H

#include <stdbool.h>
#include "error_handler.h"

#define DIR_NONE        0
#define DIR_FORWARDS    1
#define DIR_BACKWARDS   2

#define PHASE_A 0
#define PHASE_B 1
#define PHASE_C 2
#define PHASE_D 3


/**
  * @brief      initalizes the encoder module: resets direction and total phase count
  */
void init_encoder();

/**
  * @brief      calculates phase we're in, in your phase. based. on hardware input.
  *
  * @param      a Hardware Input pin0
  * @param      b Hardware Input pin1
  * 
  * @return     returns the current phase the encoder is in.
  */
static inline int get_phase(volatile bool *a, volatile bool *b) {
    if (*a) {
        if (*b) { return PHASE_C; }
        else    { return PHASE_B; }
    } else {
        if (*b) { return PHASE_D; }
        else    { return PHASE_A; }
    }
}

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
static inline int check_direction(volatile bool *a_on, volatile bool *b_on, volatile bool *a_on_previous, volatile bool *b_on_previous){
    int last_phase = get_phase(a_on_previous, b_on_previous);
    int curr_phase = get_phase(a_on, b_on);
    int direction;
    
    switch (last_phase) {
        case PHASE_A: {
            switch (curr_phase) {
                case PHASE_A: { direction = DIR_NONE; break; }
                case PHASE_B: { direction = DIR_FORWARDS; break; }
                case PHASE_C: { direction = DIR_ERROR; break; }
                case PHASE_D: { direction = DIR_BACKWARDS; break; }
            }
            break;
        }
        case PHASE_B: {
            switch (curr_phase) {
                case PHASE_A: { direction = DIR_BACKWARDS; break; }
                case PHASE_B: { direction = DIR_NONE; break; }
                case PHASE_C: { direction = DIR_FORWARDS; break; }
                case PHASE_D: { direction = DIR_ERROR; break; }
            }
            break;
        }
        case PHASE_C: {
            switch (curr_phase) {
                case PHASE_A: { direction = DIR_ERROR; break; }
                case PHASE_B: { direction = DIR_BACKWARDS; break; }
                case PHASE_C: { direction = DIR_NONE; break; }
                case PHASE_D: { direction = DIR_FORWARDS; break; }
            }
            break;
        }
        case PHASE_D: {
            switch (curr_phase) {
                case PHASE_A: { direction = DIR_FORWARDS; break; }
                case PHASE_B: { direction = DIR_ERROR; break; }
                case PHASE_C: { direction = DIR_BACKWARDS; break; }
                case PHASE_D: { direction = DIR_NONE; break; }
            }
            break;
        }
    }

    return direction;
}

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