/**
* @file       main.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Nov 2025
* @brief      
*/


/* Includes ------------------------------------------------------------------*/

#include "display.h"
#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"

#include "gpio.h"
#include "encoder.h"
#include "angle.h"
#include "error_handler.h"
#include "time.h"
#include "timer.h"
#include <stdint.h>


#define PIN4	0b00010000


/* Variables ------------------------------------------------------------------*/

// Timestamps

          
volatile uint32_t last_phase_transition_timestamp;
volatile bool a_on_previous;
volatile bool b_on_previous;
volatile bool a_on;
volatile bool b_on;
volatile int total_phase_count;





/* Functions ------------------------------------------------------------------*/

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */
void init_modules() {
	// initialize board, display and imported modules
	initITSboard();
	GUI_init(DEFAULT_BRIGHTNESS);
	TP_Init(false);

	// init self-written modules
	init_display();

	init_gpio(&a_on, &b_on, &a_on_previous, &b_on_previous);
	init_time(&last_phase_transition_timestamp);
	init_encoder();
}

/**
  * @brief      - iiii dddd kkkk 
  *
  * @param      -
  * 
  * @return     -
  */
void reset_state() {
	init_encoder(); // badly named, sets phase_count to 0
	reset_display();

	refresh_input_state(&a_on, &b_on, &a_on_previous, &b_on_previous);
	update_current();

	check_direction(&a_on, &b_on, &a_on_previous, &b_on_previous);

	set_dir_led_off();
	set_phase_led();

	start_first_timewindow();
}

/**
  * @brief      checks, if we could save data without being interrupted
  *
  * @return 	true, if interrrupted, false, if not interrupted
  */
bool check_for_interruption(bool *a, bool *b, bool *a_previous, bool *b_previous, 
	uint32_t *isr_timestamp, int *phase_count) 
{
	*a = a_on;
	*b = b_on;
	*a_previous = a_on_previous;
	*b_previous = b_on_previous;
	*isr_timestamp = last_phase_transition_timestamp;
	*phase_count = total_phase_count;

	bool a2 = a_on;
	bool b2 = b_on;
	bool a_previous2 = a_on_previous;
	bool b_previous2 = b_on_previous;
	uint32_t isr_timestamp2 = last_phase_transition_timestamp;
	int phase_count2 = total_phase_count;

	bool no_interruption = ((*a == a2) && (*b == b2) && (*a_previous == a_previous2) &&
		(*b_previous == b_previous2) && (*isr_timestamp == isr_timestamp2) && 
		(*phase_count == phase_count2));
	
	return !no_interruption;
}


int main(void) {
	init_modules();

	int encoder_direction = DIR_NONE;
	int total_phase_transition_count = 0;

	// read all inputs once right before superloop to avoid
	// immediate DIR_ERROR after the superloop starts
	reset_state();

	// while(1) {
	// 	lcd_shit();
	// 	HAL_Delay(20);
	// }

	bool toggle = false;

	while(1) {

		if (toggle) {
			GPIOE->BSRR = PIN4 << SET_REGISTER;
		} else {
			GPIOE->BSRR = PIN4 << RESET_REGISTER;
		}
		toggle = !toggle;


		// ===============
		// HARDWARE INPUTS
		// ===============

		refresh_input_state(&a_on, &b_on, &a_on_previous, &b_on_previous);
		update_current();

		// ============
		// CALCULATIONS
		// ============

		if(is_timewindow_over(&isr_timestamp)) {

			recalculate_angle(&phase_count);
			recalculate_angular_momentum(&phase_count, &isr_timestamp);

			// fetch new values
			check_display_data();

			// new time window
			start_new_timewindow();
			reset_window_phase_count(); // does this belong here or inside the function above?
		}

		// ======
		// OUTPUT
		// ======
		
		// --- BLINKY BLINK ---

		set_dir_led();
		set_phase_led();

		// --- DISPLAY ---

		// displays new values on the display, if any 
		// new have been set by recalcuate_display()
		update_display();

		
	}

}

// EOF
