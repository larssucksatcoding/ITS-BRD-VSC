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
	init_gpio();
	init_time();
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
	refresh_input_state();
	refresh_timer();

	start_new_timewindow();
}


int main(void) {
	init_modules();

	int encoder_direction = DIR_NONE;
	int total_phase_transition_count = 0;

	// read all inputs once right before superloop to avoid
	// immediate DIR_ERROR after the superloop starts
	reset_state();

	while(1) {

		// ===============
		// HARDWARE INPUTS
		// ===============

		refresh_input_state();
		refresh_timer();

		// ============
		// CALCULATIONS
		// ============

		// --- ENCODER ENSHMODER ---

		recalculate_encoder();
		encoder_direction = get_direction();
		total_phase_transition_count = get_total_phase_count();

		if (encoder_direction == DIR_ERROR) {
			handle_error(DIR_ERROR);
			continue;
		}

		if (encoder_direction != DIR_NONE) {
			save_timestamp();
			increment_window_phase_count();
		}

		// ======
		// OUTPUT
		// ======

		// --- BLINKY BLINK ---

		set_dir_led(encoder_direction);
		set_phase_led(total_phase_transition_count);

		// --- DISPLAY ---

		if(is_timewindow_over()) {
			update_total_phase_count();

			// ankle only after updating total phase count yes yes
			recalculate_angle();
			recalculate_angular_momentum();

			// display this shit
			update();

			// new time window
			start_new_timewindow();
			reset_window_phase_count(); // does this belong here or inside the function above?
		}
	}
}

// EOF
