/**
* @file       angle.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Nov 2025
* @brief      reading input & writing output of GPIOs
*/

#define PHASESWITCHES_TURN  1200


double angle;
double angular_momentum;


void recalculate_angular_momentum(int phase_count, int time_ms) {
    double prozentumdrehung = phase_count/PHASESWITCHES_TURN;
    double angular_momentum = time_ms*prozentumdrehung;
}

void recalculate_angle() {
    
}

// EOF