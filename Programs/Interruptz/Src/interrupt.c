
#include "interrupt.h"
#include "stm32f429xx.h"
#include "stm32f4xx.h"
#include <stdint.h>


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
    if (pin >  4) { return 0; }
    if (pin >  8) { return 1; }
    if (pin > 12) { return 2; }
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
  * @brief      route pins to their respective exti registers.
  * @param      pin index, port number.
  */
void route_interrupt_pins(uint16_t pin, uint16_t port) {
    uint32_t index = get_syscfg_exticr_index(pin);
	  SYSCFG->EXTICR[index] &= 0x00 << pin;	// remove old selection
	  SYSCFG->EXTICR[index] |= port << pin; 	// select port
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
  * @brief      unmask a given pin for interrupt use.
  * @param      pin index.
  */
void unmask_interrupt_pin(uint16_t pin) {
    EXTI->IMR  |= (1 << pin);
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

/**
  * @brief      ISR for pin 1. The name is hard-coded through the NVIC and
  *             cannot be changed by us.
  */
void EXTI1_IRQHandler (void) {
    // TODO: check if this function needs to be announced in the header or not.
    // Code for if pin 1 changes here
}

/**
  * @brief      ISR for pin 2. The name is hard-coded through the NVIC and
  *             cannot be changed by us.
  */
void EXTI2_IRQHandler (void) {
    // TODO: check if this function needs to be announced in the header or not.
    // Code for if pin 2 changes here
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

    enable_interrupt_clocks(port);
    route_interrupt_pins(pin, port);
    enable_interrupt_trigger(pin, rising_trigger, falling_trigger);
    unmask_interrupt_pin(pin);
    enable_interrupt(pin, port, priority);
}
