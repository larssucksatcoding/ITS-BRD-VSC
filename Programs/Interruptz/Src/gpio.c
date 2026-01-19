/**
* @file       gpio.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Nov 2025
* @brief      reading input & writing output of GPIOs
*/

#include "gpio.h"
#include "encoder.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "stm32f429xx.h"
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

/*  Interrupt  ---------------------------------------*/

#define PORT_RESET      0x00
#define PORT_G          0x06

#define EXTI_BIT_WIDTH  4
#define PIN_1           (EXTI_BIT_WIDTH * 1)
#define PIN_2           (EXTI_BIT_WIDTH * 2)

static int current_status;
static int current_phase_count;
static int input;

bool a_on_previous;
bool b_on_previous;
bool a_on;
bool b_on;

unsigned long get_clock_enable_mask(uint16_t port) {
    /* definitions for clock enables:
    #define RCC_AHB1ENR_GPIOAEN_Pos     (0U)                                
    #define RCC_AHB1ENR_GPIOAEN_Msk     (0x1UL << RCC_AHB1ENR_GPIOAEN_Pos)
    #define RCC_AHB1ENR_GPIOAEN         RCC_AHB1ENR_GPIOAEN_Msk 
    so its just 0x1UL shifted to the right by the port index. */
    return 0x1UL << port;
}

uint32_t get_syscfg_exticr_register(uint16_t pin) {
    if (pin >  4) { return SYSCFG->EXTICR[0]; }
    if (pin >  8) { return SYSCFG->EXTICR[1]; }
    if (pin > 12) { return SYSCFG->EXTICR[2]; }
    return SYSCFG->EXTICR[3];
}

void enable_interrupt_clocks(uint16_t port) {
    unsigned long clock_enable_mask = get_clock_enable_mask(port);
    RCC->AHB1ENR |= clock_enable_mask;      // clock for port
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;   // enable system conf. clock
}

void route_interrupt_pins(uint16_t pin, uint16_t port) {
    uint32_t syscfg_exti_register = get_syscfg_exticr_register(pin);
	syscfg_exti_register &= 0x00 << pin;	// remove old selection
	syscfg_exti_register |= port << pin; 	// select port
}

void enable_interrupt_trigger(uint16_t pin, bool rising, bool falling) {
    if (rising)  { EXTI->RTSR |= (1 << pin); }
    if (falling) { EXTI->FTSR |= (1 << pin); }
}

void unmask_interrupt_pin(uint16_t pin) {
    EXTI->IMR  |= (1 << pin);
}

void enable_interrupt(uint16_t pin, uint16_t port, uint32_t priority) {
    int exti_irqn = EXTI0_IRQn + pin;

    // interrupt enable works differently for pins 5-15
    // EXTI4_IRQn is for pin 5
    if (exti_irqn > EXTI4_IRQn) {
        // have not looked into how to change this
    }

    NVIC_SetPriority(exti_irqn, priority);  // set priority
    NVIC_EnableIRQ(exti_irqn);              // enable interrupt
}

void set_up_interrupt(uint16_t pin, uint16_t port, uint32_t priority, 
    bool rising_trigger, bool falling_trigger) 
{
    enable_interrupt_clocks(port);
    route_interrupt_pins(pin, port);
    enable_interrupt_trigger(pin, rising_trigger, falling_trigger);
    unmask_interrupt_pin(pin);
    enable_interrupt(pin, port, priority);
}

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
    set_up_interrupt(1, 0x06, 0, true, true);
    set_up_interrupt(2, 0x06, 0, true, true);
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