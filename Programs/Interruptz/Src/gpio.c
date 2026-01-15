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
#define RESET_MASK              0x00            // Maske um 16-Bit-Register auf 0 zu setzen. 

/*  Input  -------------------------------------------*/

#define ERROR_BUTTON_MASK       (1<<6)     
#define ENCODER_A_INPUT_MASK    0b00000010     // Maske für den Input 
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
    PHASE_COUNT_LEDS->ODR = PHASE_COUNT_LEDS->ODR & RESET_MASK;
    STATUS_LEDS->ODR = STATUS_LEDS->ODR & RESET_MASK;

    current_status = RESET_MASK;
    current_phase_count = RESET_MASK;
    input = RESET_MASK;

    a_on_previous = false;
    b_on_previous = false;
    a_on = false;
    b_on = false;

    // configure interrupts

    // TODO: clean this up with sensible defines?
    // i just copied this from the lecture slides, don't really understand whats happening.
    // might be wrong.

    // Enable clocks
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;	// Clock for GPIO Port G
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; 	// System conf. Clock enable

    // Route Pin 1 of Port G -> EXTI2
	SYSCFG->EXTICR[0] &= (0x0f << (4 * 1));	// Remove old selection
	SYSCFG->EXTICR[0] |=  0x06 << (4 * 1); 	// Select Port G
    
    // Route Pin 2 of Port G -> EXTI2
	SYSCFG->EXTICR[0] &= (0x0f << (4 * 2));	// Remove old selection
	SYSCFG->EXTICR[0] |=  0x06 << (4 * 2); 	// Select Port G

    // Configure Pin 1
    EXTI->RTSR |= (1 << 2); // select rising trigger for INT2
    EXTI->FTSR |= (1 << 2); // select falling trigger for INT2
    EXTI->IMR  |= (1 << 2); // unmask INT2
}

bool is_reset_button_pressed(){
    return ((~INPUT->IDR) & ERROR_BUTTON_MASK) != 0;
}

void set_dir_led() {
    int dir = get_direction();

    // was ist Während eines Fehlers? werden dann richtungen noch geupdated? 
    switch (dir) {
        case DIR_FORWARDS: {
            if(current_status != FORWARDS_LED_MASK) {
                // Forwards LED is not on
                STATUS_LEDS->ODR = FORWARDS_LED_MASK;
                current_status = FORWARDS_LED_MASK;
            }
            break;
        }
        case DIR_BACKWARDS: {
            if(current_status != BACKWARDS_LED_MASK) {
                // Backwards LED is not on
                STATUS_LEDS->ODR = BACKWARDS_LED_MASK;
                current_status = BACKWARDS_LED_MASK;
            }
            break;
        }
    }
}

void set_dir_led_off() {
    STATUS_LEDS->ODR = RESET_MASK;
    current_status = RESET_MASK;
}

void set_err_led_on() {
    STATUS_LEDS->ODR = ERROR_LED_MASK;
    current_status = ERROR_LED_MASK;
}

void set_err_led_off() {
    STATUS_LEDS->ODR = RESET_MASK;
    current_status = 0;
}

void set_phase_led() {
    int phase_count = abs(get_total_phase_count());
    current_phase_count = phase_count & PHASE_COUNT_LED_MASK;
    PHASE_COUNT_LEDS->ODR = current_phase_count;
}

void refresh_input_state() {
    a_on_previous = a_on;
    b_on_previous = b_on;
    input = (~INPUT->IDR);
    a_on = (input & ENCODER_A_INPUT_MASK) != 0;
    b_on = (input & ENCODER_B_INPUT_MASK) != 0;
}


// EOF