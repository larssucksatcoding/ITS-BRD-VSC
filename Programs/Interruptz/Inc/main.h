/**
* @file       main.h
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Jan 2026
* @brief      
*/

#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stdbool.h>

/* Variables ------------------------------------------------------------------*/

volatile extern uint32_t last_phase_transition_timestamp;

volatile extern bool a_on_previous;
volatile extern bool b_on_previous;
volatile extern bool a_on;
volatile extern bool b_on;
volatile extern int total_phase_count;

/**
*  @brief       resets the state of all modules to reset/ initalize values
*/
void reset_state();

#endif
