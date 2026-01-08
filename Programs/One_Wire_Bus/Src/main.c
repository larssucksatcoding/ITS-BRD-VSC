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
        error = reset();
        if (error == NO_SLAVE){
            handle_the_hand_the_error_EXCLAMATION_MARK_NOW(error);
        }
        wait(2 * ONE_SEC);
        reset_slaves();
        error = search_ROM();
        if ( error == NO_SLAVE) {
            handle_the_hand_the_error_EXCLAMATION_MARK_NOW(error);
            break;
        }
        write_info();

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