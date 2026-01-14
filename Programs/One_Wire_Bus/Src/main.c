/**
* @file     main.c
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    it's the main duh
*/

#include <stdbool.h>
#include "display.h"
#include "slaves.h"
#include "time.h"
#include "manager.h"
#include "error_handler.h"

void aufgabe_1() {
    init();
    int error = EOK;
    init_display();
    while(true) {
        error = detect_slaves();
        if( error == NO_SLAVE) {
            handle_the_hand_the_error_EXCLAMATION_MARK_NOW(error);
        }
        write_info();
    }
}


int main(void) {
	init();
    int error = EOK;
    init_display();
    int slave_count = 0;
    
    
    while(true) {
        error = detect_slaves();
        if( error != EOK) {
            handle_the_hand_the_error_EXCLAMATION_MARK_NOW(error);
        }
        int new_slave_count = get_slave_count();
        if (new_slave_count != slave_count){
            if (new_slave_count < slave_count) {
                clear_sensor_pdrom();
            }
            slave_count = new_slave_count;
        }        
        clear_temp();
        for (int i = 0; i < slave_count; i++) {
            measure_temperature();
            calculate_temperature();
            write_info();
            wait(ONE_SEC);
            next_slave();
        }
        wait(2*ONE_SEC);
    }

    return 0;
}

//EOF