/**
* @file     error.h
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    error module
*/

#include "error_handler.h"


void handle_the_hand_the_error_EXCLAMATION_MARK_NOW(int error){
    if (error == EOK) {
        return;
    }
    else if (error == NO_SLAVE){
        // print error message, that we need slaves to work for us
        return;
    }
    else if (error == ROM_ERR){
        // ask the slaves for ROM again. I feel like the error
        // handler will never have to handle this
    }
    else { // error == SCRATCHPAD_ERR
        // same as ROM_ERR just read duh
    }
}