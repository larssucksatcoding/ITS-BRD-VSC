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

#define ONE_SEC 1000

int main(void) {
	init();
    int error = EOK;
    
    while(true) {
        reset();
        wait(2 * ONE_SEC);
        reset_slaves();
        search_ROM();
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