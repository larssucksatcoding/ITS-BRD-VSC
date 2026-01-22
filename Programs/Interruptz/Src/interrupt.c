
#include "interrupt.h"
#include "encoder.h"
#include "error_handler.h"
#include "stm32f429xx.h"
#include "stm32f4xx.h"
#include <stdint.h>
#include "main.h"
#include "gpio.h"
#include "time.h"
#include "timer.h"

// uncommint this define for oscilloscope measurement
// connect the oscilloscope to the INTERRUPT_MEASURE_LED below
#define MEASURE_INTERRUPT_TIME
#define INTERRUPT_MEASURE_LED 0b00010000

uint32_t biggest_diff = 0;

static bool aux0_state_previous;
static bool aux1_state_previous;
static bool aux0_state;
static bool aux1_state;

/*  Private Methods  ----------------------------------------*/

/**
  * @brief      get the clock enable mask given a port number.
  *             (equivalent to e.g. RCC_AHB1ENR_GPIOAEN, RCC_AHB1ENR_GPIOBEN and so on)
  * @param      port number.
  * @return     clock enable mask
  */
unsigned long get_clock_enable_mask(uint16_t port) {
    /* definitions for clock enables:
    #define RCC_AHB1ENR_GPIOAEN_Pos     (0U)                                
    #define RCC_AHB1ENR_GPIOAEN_Msk     (0x1UL << RCC_AHB1ENR_GPIOAEN_Pos)
    #define RCC_AHB1ENR_GPIOAEN         RCC_AHB1ENR_GPIOAEN_Msk 
    so its just 0x1UL shifted to the right by the port index. */
    return 0x1UL << port;
}

/**
  * @brief      get the syscfg exticr register given a pin index.
  *             (equivalent to SYSCFG->EXTICR[0], SYSCFG->EXTICR[1] and so on).
  * @param      pin index.
  * @return     syscfg exticr register.
  */
uint32_t get_syscfg_exticr_index(uint16_t pin) {
    if (pin <  4) { return 0; }
    if (pin <  8) { return 1; }
    if (pin < 12) { return 2; }
    return 3;
}

/**
  * @brief      enable clocks needed by interrupts. will enable clock for passed
  *             port as well as general system conf. clock (whatever that is).
  */
void enable_interrupt_clocks(uint16_t port) {
    unsigned long clock_enable_mask = get_clock_enable_mask(port);
    RCC->AHB1ENR |= clock_enable_mask;      // clock for port
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;   // enable system conf. clock
}

/**
  * @brief      route pins to their respective EXTICRs.
  * @param      pin index, port number.
  */
void route_interrupt_pins(uint16_t pin, uint16_t port) {
    uint32_t index = get_syscfg_exticr_index(pin);
	  SYSCFG->EXTICR[index] &= ~(0x0f << (pin*4));	// remove old selection
	  SYSCFG->EXTICR[index] |= (port << (pin*4)); 	// select port
}

/**
  * @brief      enable triggers for given pin. you can seperately enable
  *             rising and falling triggers
  * @param      pin index, rising and falling flags.
  */
void enable_interrupt_trigger(uint16_t pin, bool rising, bool falling) {
    if (rising)  { EXTI->RTSR |= (1 << pin); }
    if (falling) { EXTI->FTSR |= (1 << pin); }
}

/**
  * @brief      enable interrupt given a pin and port number.
  * @param      pin index, port number, interrupt priority.
  */
void enable_interrupt(uint16_t pin, uint16_t port, uint32_t priority) {
    // the first four interrupt lines are just increasing integers, starting
    // with EXTI0_IRQn.
    int exti_irqn = EXTI0_IRQn + pin;

    // however, interrupt enable works differently for pins 5-15
    // after EXTI4_IRQn, there only is EXTI9_5_IRQn and EXTI15_10_IRQn
    if (pin > 5) {
        // TODO:
        // use EXTI9_5_IRQn for pins 5 to 9 and EXTI15_10_IRQn for pins 10 to 15.
        // i don't really know if anything else needs to change other than that.
        // maybe we can also just ignore this case because we already know that
        // we do not use such high pin numbers.
    }

    NVIC_SetPriority(exti_irqn, priority);  // set priority
    NVIC_EnableIRQ(exti_irqn);              // enable interrupt
}

/*  Interrupt Service Routines  ----------------------------------------*/

/*
#define RESET_REGISTER          16
#define SET_REGISTER            0
#define ERROR_LED_MASK          0b00100000

void set_err_led_on() {
    STATUS_LEDS->BSRR = ERROR_LED_MASK << SET_REGISTER;
}

void set_err_led_off() {
    STATUS_LEDS->BSRR = RESET_MASK << RESET_REGISTER;
}
*/

/**
  * @brief      calculates phase we're in, in your phase. based. on hardware input.
  *
  * @param      a Hardware Input pin0
  * @param      b Hardware Input pin1
  * 
  * @return     returns the current phase the encoder is in.
  */
static inline int get_phase(volatile bool a, volatile bool b) {
    if (a) {
        if (b)  { return PHASE_C; }
        else    { return PHASE_B; }
    } else {
        if (b)  { return PHASE_D; }
        else    { return PHASE_A; }
    }
}

static inline void check_direction(volatile int *direction) {
    int last_phase = get_phase(aux0_state_previous, aux1_state_previous);
    int curr_phase = get_phase(aux0_state, aux1_state);

    switch (last_phase) {
        case PHASE_A: {
            switch (curr_phase) {
                case PHASE_A: { *direction = DIR_NONE; break; }
                case PHASE_B: { *direction = DIR_FORWARDS; break; }
                case PHASE_C: { *direction = DIR_ERROR; break; }
                case PHASE_D: { *direction = DIR_BACKWARDS; break; }
            }
            break;
        }
        case PHASE_B: {
            switch (curr_phase) {
                case PHASE_A: { *direction = DIR_BACKWARDS; break; }
                case PHASE_B: { *direction = DIR_NONE; break; }
                case PHASE_C: { *direction = DIR_FORWARDS; break; }
                case PHASE_D: { *direction = DIR_ERROR; break; }
            }
            break;
        }
        case PHASE_C: {
            switch (curr_phase) {
                case PHASE_A: { *direction = DIR_ERROR; break; }
                case PHASE_B: { *direction = DIR_BACKWARDS; break; }
                case PHASE_C: { *direction = DIR_NONE; break; }
                case PHASE_D: { *direction = DIR_FORWARDS; break; }
            }
            break;
        }
        case PHASE_D: {
            switch (curr_phase) {
                case PHASE_A: { *direction = DIR_FORWARDS; break; }
                case PHASE_B: { *direction = DIR_ERROR; break; }
                case PHASE_C: { *direction = DIR_BACKWARDS; break; }
                case PHASE_D: { *direction = DIR_NONE; break; }
            }
            break;
        }
    }
}

static inline void isr_handler(uint16_t pin) {

    // -- clear interrupt flag --
    // the source of all my agony ;-;

    EXTI->PR = (1 << pin);


    #ifdef MEASURE_INTERRUPT_TIME
    STATUS_LEDS->BSRR = INTERRUPT_MEASURE_LED << SET_REGISTER;
    #endif

    // -- input --

    last_phase_transition_timestamp = getTimeStamp(); // should be first thing in isr
    uint32_t input = (~GPIOG->IDR) & 0x3;

    // -- output --

    aux0_state_previous = aux0_state;
    aux0_state = (input & AUX0_INPUT_MASK) != 0;

    aux1_state_previous = aux1_state;
    aux1_state = (input & AUX1_INPUT_MASK) != 0;

    if( (aux0_state != aux0_state_previous) && (aux1_state != aux1_state_previous)) {
      error = DIR_ERROR;
    }
    
    check_direction(&direction);
    switch (direction) {
      case DIR_FORWARDS:  { total_phase_count++; break; }
      case DIR_BACKWARDS: { total_phase_count--; break; }
      /* case DIR_ERROR: { error = DIR_ERROR; break; } */
    }

    #ifdef MEASURE_INTERRUPT_TIME
    STATUS_LEDS->BSRR = INTERRUPT_MEASURE_LED << RESET_REGISTER;
    #endif

    // uint32_t isr_end_timestamp = getTimeStamp();
    // uint32_t diff = (isr_end_timestamp - last_phase_transition_timestamp);
    // if (diff > biggest_diff) {
    //     biggest_diff = diff;
    // }
}


/**
  * @brief      ISR for pin 0 (AUX0). The name is hard-coded through the NVIC and
  *             cannot be changed by us.
  */
void EXTI0_IRQHandler (void) {
  isr_handler(0);
}

/**
  * @brief      ISR for pin 1 (AUX1). The name is hard-coded through the NVIC and
  *             cannot be changed by us.
  */
void EXTI1_IRQHandler (void) {
  isr_handler(1);
}

/*  Public Methods  ----------------------------------------*/

void set_up_interrupt(uint16_t pin, uint16_t port, uint32_t priority, 
    bool rising_trigger, bool falling_trigger) 
{
    // don't change anything if parameters suck.
    if (pin > 15)                               { return; } // pin index exceeded
    if (port > PORT_K)                          { return; } // port number exceeded
    if (!rising_trigger && !falling_trigger)    { return; } // no trigger selected
    if (priority > 15)                          { return; } // priority exceeded

    // set pins as input, hardcoded for now
    GPIOG->MODER &= ~(0x00 << (2 * pin));

    enable_interrupt_clocks(port);
    route_interrupt_pins(pin, port);
    enable_interrupt_trigger(pin, rising_trigger, falling_trigger);
    unmask_interrupt_pin(pin);
    enable_interrupt(pin, port, priority);
}

void unmask_interrupt_pin(uint16_t pin) {
    EXTI->IMR  |= (1 << pin);
}

void mask_interrupt_pin(uint16_t pin) {
    EXTI->IMR  &= ~(1 << pin);
}

void read_gpio_pins() {
    uint32_t input = (~GPIOG->IDR) & 0x3;

    aux0_state = (input & AUX0_INPUT_MASK) != 0;
    aux1_state = (input & AUX1_INPUT_MASK) != 0;
}

void init_interrupt() {
    aux0_state_previous= false;
    aux1_state_previous = false;
    aux0_state = false;
    aux1_state = false;

    // configure interrupts
    set_up_interrupt(0, PORT_G, 0, true, true); // AUX0
    set_up_interrupt(1, PORT_G, 0, true, true); // AUX1
}