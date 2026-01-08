/**
* @file     main.c
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    it's the main duh
*/

#include <stdbool.h>
#include "commands.h"
#include "display.h"
#include "slaves.h"
#include "time.h"
#include "manager.h"
#include "error_handler.h"
#include "bit_talk.h"



int main(void) {
	init();
    int error = EOK;
    
    while(true) {
        init_display();
        error = detect_slaves();
        if( error != EOK) {
            handle_the_hand_the_error_EXCLAMATION_MARK_NOW(error);
        }
        int slave_count = get_slave_count();
        for (int i = 0; i < slave_count; i++) {
            measure_temperature();
            calculate_temperature();
            write_info();
            wait(ONE_SEC);
            next_slave();
        }
        wait(2*ONE_SEC);
    }
    /*
    while(true) {
        error = detect_slaves();
        handle_the_hand_the_error_EXCLAMATION_MARK_NOW(error);
        if (error == EOK){
            write_rom();
        }
        wait(ONE_SEC);
    } */

    

    return 0;

}