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
#include "interrupt.h"


void show_error() {
	mask_interrupt_pin(0);
	mask_interrupt_pin(1);

    setErrMode();
    print_error("Deine Oma liebt dich nicht");

    while(!is_reset_button_pressed()) {
        // just wait :3
    }

    setNormalMode();
    reset_state();

    error = NO_ERROR;

	unmask_interrupt_pin(0);
	unmask_interrupt_pin(1);
}
