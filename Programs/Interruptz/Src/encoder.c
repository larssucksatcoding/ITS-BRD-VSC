/**
* @file       main.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Nov 2025
* @brief      
*/


/* Includes ------------------------------------------------------------------*/
#include "encoder.h"
#include "gpio.h"
#include "error_handler.h"
#include "stdbool.h"


#define PHASE_A 0
#define PHASE_B 1
#define PHASE_C 2
#define PHASE_D 3


int direction;

int total_phase_count;
int window_phase_count;

// ===============
// PRIVATE METHODS
// ===============

/**
  * @brief      gets the phase, in your phase. based. on hardware input.
  *
  * @param      a Hardware Input pin0
  * @param      b Hardware Input pin1
  * 
  * @return     returns the current phase the encoder is in.
  */
int get_phase(volatile bool *a, volatile bool *b) {
    if (*a) {
        if (*b)  { return PHASE_C; }
        else    { return PHASE_B; }
    } else {
        if (*b)  { return PHASE_D; }
        else    { return PHASE_A; }
    }
}

// ==============
// PUBLIC METHODS
// ==============


void init_encoder() {
    direction = DIR_NONE;

    total_phase_count = 0;
    window_phase_count = 0;
}


void recalculate_encoder() {
    int last_phase = get_phase(&a_on_previous, &b_on_previous);
    int curr_phase = get_phase(&a_on, &b_on);

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
}


int get_direction() {
    return direction;
}

int get_total_phase_count() {
    return total_phase_count;
}

int get_window_phase_count() {
    return window_phase_count;
}

void increment_phase_count() {
    if (direction == DIR_FORWARDS) {
        window_phase_count++;
        total_phase_count++;
    }

    if (direction == DIR_BACKWARDS) {
        window_phase_count--;
        total_phase_count--;
    }
}

void reset_window_phase_count() {
    window_phase_count = 0;
}
