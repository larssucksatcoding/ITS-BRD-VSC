/**
* @file       main.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Nov 2025
* @brief      
*/


/* Includes ------------------------------------------------------------------*/
#include "encoder_direction.h"
#include "gpio.h"
#include "error_handler.h"


#define PHASE_A 0
#define PHASE_B 1
#define PHASE_C 2
#define PHASE_D 3

int direction;


int coole_methode(bool a, bool b) {
    if (a) {
        if (b)  { return PHASE_C; }
        else    { return PHASE_B; }
    } else {
        if (b)  { return PHASE_D; }
        else    { return PHASE_A; }
    }
}


void init_encoder_direction() {

}


int refresh_direction() {
    int last_phase = coole_methode(a_on_previous, b_on_previous);
    int curr_phase = coole_methode(a_on, b_on);

    switch (last_phase) {
        case PHASE_A: {
            switch (curr_phase) {
                case PHASE_A: { return DIR_NONE; }
                case PHASE_B: { return DIR_FORWARDS; }
                case PHASE_C: { return DIR_ERROR; }
                case PHASE_D: { return DIR_BACKWARDS; }
            }
        }
        case PHASE_B: {
            switch (curr_phase) {
                case PHASE_A: { return DIR_BACKWARDS; }
                case PHASE_B: { return DIR_NONE; }
                case PHASE_C: { return DIR_FORWARDS; }
                case PHASE_D: { return DIR_ERROR; }
            }
        }
        case PHASE_C: {
            switch (curr_phase) {
                case PHASE_A: { return DIR_ERROR; }
                case PHASE_B: { return DIR_BACKWARDS; }
                case PHASE_C: { return DIR_NONE; }
                case PHASE_D: { return DIR_FORWARDS; }
            }
        }
        case PHASE_D: {
            switch (curr_phase) {
                case PHASE_A: { return DIR_FORWARDS; }
                case PHASE_B: { return DIR_ERROR; }
                case PHASE_C: { return DIR_BACKWARDS; }
                case PHASE_D: { return DIR_NONE; }
            }
        }
    }

    return DIR_ERROR;
}
