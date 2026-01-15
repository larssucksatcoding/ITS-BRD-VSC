/**
* @file       gpio.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Nov 2025
* @brief      reading input & writing output of GPIOs
*/

#include "gpio.h"
#include "encoder.h"
#include <stdbool.h>
#include <stdlib.h>
#include "stm32f4xx.h"
#include "math.h"

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
#define RESETTED                0x00

/*  Input  -------------------------------------------*/

#define ERROR_BUTTON_MASK       (1<<6)     
#define ENCODER_A_INPUT_MASK    0b00000010      // Maske für den Input 
#define ENCODER_B_INPUT_MASK    0b00000001

static int current_status;
static int current_phase_count;
static int input;

bool a_on_previous;
bool b_on_previous;
bool a_on;
bool b_on;

void init_gpio(){
    // set GPIO registers to zero 
    PHASE_COUNT_LEDS->BSRR = RESET_MASK << RESET_REGISTER;
    STATUS_LEDS->BSRR = RESET_MASK << RESET_REGISTER;

    current_status = RESETTED;
    current_phase_count = RESETTED;
    input = RESETTED;

    a_on_previous = false;
    b_on_previous = false;
    a_on = false;
    b_on = false;
}

bool is_reset_button_pressed(){
    int input = ~INPUT->IDR;
    return (input & ERROR_BUTTON_MASK) != 0;
}

void set_dir_led() {
    int dir = get_direction();

    switch (dir) {
        case DIR_FORWARDS: {
            if(current_status != FORWARDS_LED_MASK) {
                // Forwards LED is not on
                STATUS_LEDS->BSRR = FORWARDS_LED_MASK << SET_REGISTER;
                current_status &= FORWARDS_LED_MASK;
            }
            break;
        }
        case DIR_BACKWARDS: {
            if(current_status != BACKWARDS_LED_MASK) {
                // Backwards LED is not on
                STATUS_LEDS->BSRR = BACKWARDS_LED_MASK << SET_REGISTER;
                current_status &= BACKWARDS_LED_MASK;
            }
            break;
        }
    }
}

void set_dir_led_off() {
    STATUS_LEDS->BSRR = RESET_MASK << RESET;
    current_status = RESET_MASK;
}

void set_err_led_on() {
    STATUS_LEDS->BSRR = ERROR_LED_MASK << SET_REGISTER;
    current_status = ERROR_LED_MASK;
}

void set_err_led_off() {
    STATUS_LEDS->BSRR = RESET_MASK << RESET_REGISTER;
    current_status = RESETTED;
}

void set_phase_led() {
    int phase_count = abs(get_total_phase_count());
    current_phase_count = phase_count & PHASE_COUNT_LED_MASK;
    PHASE_COUNT_LEDS->BSRR = current_phase_count << SET_REGISTER;
}

void refresh_input_state() {
    a_on_previous = a_on;
    b_on_previous = b_on;
    input = (~INPUT->IDR);
    a_on = (input & ENCODER_A_INPUT_MASK) != 0;
    b_on = (input & ENCODER_B_INPUT_MASK) != 0;
}


// EOF