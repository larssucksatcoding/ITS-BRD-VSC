/**
* @file       gpio.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Nov 2025
* @brief      reading input & writing output of GPIOs
*/

#include "gpio.h"
#include "encoder.h"
#include <stdbool.h>
#include "stm32f429xx.h"
#include "interrupt.h"

/*  Register  ----------------------------------------*/

#define INPUT               GPIOF
#define PHASE_COUNT_LEDS    GPIOD
#define STATUS_LEDS         GPIOE

/*  Output  ------------------------------------------*/

#define FORWARDS_LED_MASK       0b10000000
#define BACKWARDS_LED_MASK      0b01000000
#define ERROR_LED_MASK          0b00100000
#define PHASE_COUNT_LED_MASK    0x00FF          // Maske für die Anzeige des Phasen Counts
#define RESET_MASK              0xFF            // Maske um 16-Bit-Register auf 0 zu setzen.

/*  Input  -------------------------------------------*/

#define ERROR_BUTTON_MASK       (1<<6)     
#define ENCODER_A_INPUT_MASK    0b00000010      // Maske für den Input 
#define ENCODER_B_INPUT_MASK    0b00000001

static bool forwards_on;
static bool backwards_on;


void init_gpio(volatile bool *a_on, volatile bool *b_on, volatile bool *a_on_previous, volatile bool *b_on_previous){
    // set GPIO registers to zero 
    set_phase_led_off();

    a_on_previous = false;
    b_on_previous = false;
    a_on = false;
    b_on = false;

    // configure interrupts
    set_up_interrupt(1, PORT_G, 0, true, true);
    set_up_interrupt(2, PORT_G, 0, true, true);
}

bool is_reset_button_pressed(){
    int input = ~INPUT->IDR;
    return (input & ERROR_BUTTON_MASK) != 0;
}

void set_dir_led() {
    int dir = get_direction();

    switch (dir) {
        case DIR_FORWARDS: {
            if(!forwards_on) {
                // Forwards LED is not on
                STATUS_LEDS->BSRR = FORWARDS_LED_MASK << SET_REGISTER;
                forwards_on = true;
            }
            break;
        }
        case DIR_BACKWARDS: {
            if(!backwards_on) {
                // Backwards LED is not on
                STATUS_LEDS->BSRR = BACKWARDS_LED_MASK << SET_REGISTER;
                backwards_on = true;
            }
            break;
        }
    }
}

void set_status_led_off() {
    STATUS_LEDS->BSRR = RESET_MASK << RESET_REGISTER;
}

void set_err_led_on() {
    STATUS_LEDS->BSRR = ERROR_LED_MASK << SET_REGISTER;
}

void set_err_led_off() {
    STATUS_LEDS->BSRR = RESET_MASK << RESET_REGISTER;
}

void set_phase_led(int *phase_count) {
    int current_phase_count = *phase_count & PHASE_COUNT_LED_MASK;
    PHASE_COUNT_LEDS->BSRR = current_phase_count << SET_REGISTER;
}

void refresh_input_state(volatile bool *a_on, volatile bool *b_on, volatile bool *a_on_previous, volatile bool *b_on_previous) {
    *a_on_previous = *a_on;
    *b_on_previous = *b_on;
    int input = (~INPUT->IDR);
    *a_on = (input & ENCODER_A_INPUT_MASK) != 0;
    *b_on = (input & ENCODER_B_INPUT_MASK) != 0;
}


// EOF