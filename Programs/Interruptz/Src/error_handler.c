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


void show_error(char* str) {

	mask_interrupt_pin(0);
	mask_interrupt_pin(1);

    set_err_led_on();

    setErrMode();
    print_error(str);

	unmask_interrupt_pin(0);
	unmask_interrupt_pin(1);


    while(!is_reset_button_pressed()) {
        // just wait :3
    }

	mask_interrupt_pin(0);
	mask_interrupt_pin(1);

    setNormalMode();

    set_err_led_off();

	unmask_interrupt_pin(0);
	unmask_interrupt_pin(1);
}
