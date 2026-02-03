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


static int last_total_phase_count; //!< total_phase_count after finished time window

int get_window_phase_count(int *total_phase_count) {
    return *total_phase_count - last_total_phase_count;
}

void save_last_total_phase_count(int *phase_count) {
    last_total_phase_count = *phase_count;
}
