/**
* @file       gpio.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Nov 2025
* @brief      reading input & writing output of GPIOs
*/

#include "gpio.h"
#include "encoder_direction.h"
#include <stdbool.h>
#include "stm32f4xx.h"

#define INPUT               GPIOF
#define PHASE_COUNT_LEDS    GPIOD
#define STATUS_LEDS         GPIOE

/*  Output  ------------------------------------------*/

#define FORWARDS_LED            23
#define BACKWARDS_LED           22
#define ERROR_LED               21
#define PHASE_COUNT_LED_MASK    0x00FF    // Maske für die Anzeige des Phasen Counts
#define RESET_MASK              0x0000    // Maske um Register auf 0 zu setzen. 

/*  Input  -------------------------------------------*/

#define ERROR_BUTTON_MASK       (1<<6)     
#define ENCODER_A_INPUT_MASK    0b0000 0001     // Maske für den Input 
#define ENCODER_B_INPUT_MASK    0b0000 0010



void init_gpio(){
    // set GPIO registers to zero 
    PHASE_COUNT_LEDS->ODR = PHASE_COUNT_LEDS->ODR & RESET_MASK;
    STATUS_LEDS->ODR = STATUS_LEDS->ODR & RESET_MASK;
}

bool is_reset_button_pressed(){
    return (INPUT->IDR & ERROR_BUTTON_MASK) != 0;
}

void set_dir_led(int dir) {
    switch (dir) {
        case DIR_FORWARDS: {
            // set Forwards LED
        }
        case DIR_BACKWARDS: {
            // set Backwards LED
        }
    }
}

/**
  * @brief      reads and save current gpio save. **all read functions in this module
  *             will only return what was saved by this function.**
  * 
  * @return     int - 
  */
int read_gpio_state();
