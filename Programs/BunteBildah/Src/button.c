#include "button.h"
#include "stm32f4xx_hal.h"

/**
* @brief Returns true if any button is pressed.
*/
bool button_pressed() {
	return (~GPIOF->IDR) != 0;
}

void wait_until_button_pressed() {
	while (button_pressed()) {};
}
