
/**
  * @file       interrupt.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Jan 2026
  * @brief      
  */

#ifndef INTERRUPT_H
#define INTERRUPT_H


#include <stdint.h>
#include "stdbool.h"

#define PORT_A  0x00
#define PORT_B  0x01
#define PORT_C  0x02
#define PORT_D  0x03 
#define PORT_E  0x04 
#define PORT_F  0x05
#define PORT_G  0x06 
#define PORT_H  0x07
#define PORT_I  0x08
#define PORT_J  0x09
#define PORT_K  0x0A


/**
  * @brief      sets up ab interrupt completely given a pin and port number.
  *             this includes setting up the clock, routing pins, setting
  *             triggers, unmasking the ISQ and setting the priority.
  *             this function will fail silently if the given parameters exceed
  *             the range that is predetermined by the hardware.
  * @param      pin/port index, ISQ priority, rising/falling trigger flags.
  */
void set_up_interrupt(uint16_t pin, uint16_t port, uint32_t priority, 
    bool rising_trigger, bool falling_trigger);

#endif

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */