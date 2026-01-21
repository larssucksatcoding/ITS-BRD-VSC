/**
* @file       error_handler.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Nov 2025
* @brief      
*/


#include "error_handler.h"
#include "gpio.h"
#include "main.h"
#include "display.h"


void show_error() {
    // setErrMode();
    print_error("Deine Oma liebt dich nicht");

    while(!is_reset_button_pressed()) {
        // just wait :3
    }

    // setNormalMode();
    reset_state();
}
