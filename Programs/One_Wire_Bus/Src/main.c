/**
* @file     main.c
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    it's the main duh
*/


#include "bit_talk.h"
#include "time.h"
#include "manager.h"

#define ONE_SEC 1000

int main(void) {
	init();

    while(true) {
        open_drain();
        wait(2*ONE_SEC);
        set_high();                     // PD0 stays off
        wait(2*ONE_SEC);
        set_low();


        push_pull();
        wait(2*ONE_SEC);
        set_high();                     // PD0 goes on (slaves high current)
        wait(2*ONE_SEC);
        set_low();

        open_drain();
        wait(2*ONE_SEC);
        set_high_1();                   // PD1 stays off
        wait(2*ONE_SEC);
        set_low_1();


        push_pull();
        wait(2*ONE_SEC);
        set_high_1();                   // PD1 goes on but slaves don't get no current
        wait(2*ONE_SEC);
        set_low_1();

        open_drain();
        wait(2*ONE_SEC);
        set_high_1();                   // PD1 stays off
        wait(2*ONE_SEC);
        set_high();                     // PD0 and PD1 go on slaves get current (low)
        wait(2*ONE_SEC);
        set_low();                      // both off
        wait(2*ONE_SEC);
        set_low_1();


        push_pull();
        wait(2*ONE_SEC);
        set_high_1();                   // PD1 on slave low (no?) current
        wait(2*ONE_SEC);
        set_high();                     // both on slave high current
        wait(2*ONE_SEC);
        set_low();
        wait(2*ONE_SEC);
        set_low_1();
    }

}

/*  SUMMARY
Open-Drain:     the Bus is high, if PD1 and PD0 are high.
*               one goes low - Bus goes low/zero

Push-Pull:      the Bus is very high, if PD0 is on. 
*               PD1 does not seem to make any difference 
*               BEWARE: task says we're supposed to leave PD1 on in Push-Pull Mode
*               (Reason for that is that else the current will be to high,
*               since the resistor can be avoided)
*/

/**
* @brief    -
*
* @param    -
* 
* @return   -
*/