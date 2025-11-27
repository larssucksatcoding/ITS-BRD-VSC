/**
* @file       angle.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Nov 2025
* @brief      reading input & writing output of GPIOs
*/

/*  Includes  -----------------------------*/

#include "encoder.h"
#include "time.h"
#include "encoder.h"

#define PHASESWITCHES_TURN  1200


double angle;
double angular_momentum;


void recalculate_angular_momentum() {
    int phase_count = get_window_phase_count();
    int time_ms = ms_since_timewindow_start();

    double prozentumdrehung = (double) phase_count / (double) PHASESWITCHES_TURN;
    double angular_momentum = time_ms * prozentumdrehung;
}

void recalculate_angle() {
    int total_phase_count = get_total_phase_count();
    angle = 360 * ((double) total_phase_count / (double) PHASESWITCHES_TURN);
}

double get_angle() {
    return angle;
}

double get_angular_momentum() {
    return angular_momentum;
}

// EOF