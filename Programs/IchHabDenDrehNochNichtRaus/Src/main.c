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

bool a_on;
bool b_on;

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */
void init_modules() {
	init_gpio();
	init_encoder();
	init_display();
}

/**
  * @brief      - iiii dddd kkkk 
  *
  * @param      -
  * 
  * @return     -
  */
void reset_state() {
	start_new_timewindow();
	refresh_input_state();
}


int main(void) {

	// initialize board, display and imported modules
	initITSboard();
	GUI_init(DEFAULT_BRIGHTNESS);
	TP_Init(false);
	init_modules();

	int encoder_direction = DIR_NONE;
	int total_phase_transition_count = 0;

	// read all inputs once right before superloop to avoid
	// immediate DIR_ERROR after the superloop starts
	refresh_input_state();
	start_new_timewindow(); // this should be in a reset function!   ?

	while(1) {

		// ===============
		// HARDWARE INPUTS
		// ===============

		refresh_input_state();
		refresh_timer();

		// -----------------------------------
		// refresh input state 2* bei phase total count = 1
		// (um dirr err zu vermeiden, weil am Anfang alles au ffalse ist)
		// -------------------------------------------------

		// ============
		// CALCULATIONS
		// ============

		// --- ENCODER ENSHMODER ---

		recalculate_encoder();
		encoder_direction = get_direction();
		total_phase_transition_count = get_total_phase_count();

		if (encoder_direction == DIR_ERROR) {
			handle_error(DIR_ERROR);
			// reset
			// - maybe extract reset to own function?
			// - maybe have reset instead of init method in modules?
			// thsi should also just be in the handle_error method
			init_modules();
			refresh_input_state();
			continue;
		}

		if (encoder_direction != DIR_NONE) {
			save_timestamp();
			increment_window_phase_count(encoder_direction);
		}

		// --- ANKLE ---

		recalculate_angle();
		recalculate_angular_momentum();

		// ======
		// OUTPUT
		// ======

		// --- BLINKY BLINK ---

		set_dir_led(encoder_direction);
		set_phase_led(total_phase_transition_count);

		// --- DISPLAY ---

		if(is_timewindow_over()) {
			update_total_phase_count();

			// display this shit
			// this still needs to be written.
			// update(double angle, double angular_momentum);

			// new time window
			start_new_timewindow();
			reset_window_phase_count(); // does this belong here or inside the function above?
		}
	}
}

// EOF
