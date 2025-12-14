#include "button.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>

/**
* @brief Returns true if any button is pressed.
*/
bool button_pressed() {
	uint32_t pressed_button_mask = ~(GPIOF->IDR) & 0xFF;
	return pressed_button_mask != 0;
}

void wait_until_button_pressed() {
	while (!button_pressed()) {};
}
