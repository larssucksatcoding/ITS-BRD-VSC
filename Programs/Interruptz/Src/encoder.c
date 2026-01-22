/**
* @file       main.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Nov 2025
* @brief      
*/


/* Includes ------------------------------------------------------------------*/
#include "encoder.h"
#include "error_handler.h"
#include "stdbool.h"





static int direction;

static int last_total_phase_count; //!< total_phase_count after finished time window

// ===============
// PRIVATE METHODS
// ===============



// ==============
// PUBLIC METHODS
// ==============


void init_encoder() {
    direction = DIR_NONE;
}




int get_direction() {
    return direction;
}

int get_window_phase_count(int *total_phase_count) {
    return *total_phase_count - last_total_phase_count;
}

void save_last_total_phase_count(int *phase_count) {
    last_total_phase_count = *phase_count;
}
