/**
* @file       angle.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Nov 2025
* @brief      reading input & writing output of GPIOs
*/

/*  Includes  -----------------------------*/

#include "encoder.h"
#include "time.h"
#include <stdint.h>

#define PHASESWITCHES_TURN  1200


static double angle;
static double angular_momentum;


void recalculate_angular_momentum(int *phase_count, uint32_t *timestamp) {
    double time_s = (double) ms_since_timewindow_start(*timestamp) / 1000.0;
    uint32_t window_phase_count = get_window_phase_count(phase_count);

    double prozentumdrehung = (double) window_phase_count / (double) PHASESWITCHES_TURN;
    angular_momentum = (prozentumdrehung * 360) / time_s;
}

void recalculate_angle(int *phase_count) {
    angle = 360 * ((double) *phase_count / (double) PHASESWITCHES_TURN);
}

double get_angle() {
    return angle;
}

double get_angular_momentum() {
    return angular_momentum;
}

// EOF