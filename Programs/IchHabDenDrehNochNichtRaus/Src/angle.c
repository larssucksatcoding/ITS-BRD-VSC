/**
* @file       angle.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Nov 2025
* @brief      reading input & writing output of GPIOs
*/

/*  Includes  -----------------------------*/

#include "encoder.h"
#include "time.h"

#define PHASESWITCHES_TURN  1200


double angle;
double angular_momentum;


void recalculate_angular_momentum() {
    int phase_count = 0;
    // get (window_phase_count)
    int time_ms = 0;
    // get timeframe
    double prozentumdrehung = phase_count/PHASESWITCHES_TURN;
    double angular_momentum = time_ms*prozentumdrehung;
}

void recalculate_angle() {
    int total_phase_count = 0;
    // get_total_phase_count
    angle = 360 * (total_phase_count/PHASESWITCHES_TURN);
}

double get_angle() {
    return angle;
}

double get_angular_momentum() {
    return angular_momentum;
}

// EOF