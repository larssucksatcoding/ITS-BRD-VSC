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
#include "timer.h"

#include "gpio.h"
#include "encoder_direction.h"
#include "encoder_angle.h"
#include "error_handler.h"
#include "status_io.h"
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
	init_encoder_direction();
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
	int phase_transition_count = 0;

	double time_s = 0.0;
	double angle = 0.0;
	double angular_momentum = 0.0;

	// read all inputs once right before superloop to avoid
	// immediate DIR_ERROR after the superloop starts
	refresh_input_state();
	start_new_timewindow(); // this should be in a reset function!   ?

	while(1) {

		// read all inputs (including timer?)
		refresh_input_state();

		// process inputs
		encoder_direction = get_direction();
		// DIR_ERROR in der Error Datei definiert (Änderung durch Noah)
		switch (encoder_direction) {
			case DIR_ERROR: {
				handle_error(DIR_ERROR);
				// reset
				// - maybe extract reset to own function?
				// - maybe have reset instead of init method in modules?
				// thsi should also just be in the handle_error method
				init_modules();
				refresh_input_state();
				continue;
			}
			case DIR_FORWARDS: {
				phase_transition_count++;
				save_timestamp();
				time_s = duration_timewindow();
			}			
			case DIR_BACKWARDS: {
				phase_transition_count--;
				save_timestamp();
				time_s = duration_timewindow();
			}
		}

		if (encoder_direction != DIR_NONE) {
			// update status LEDs
			set_dir_led(encoder_direction);
			set_phase_led(phase_transition_count);
		}



		// calculate angle and angular momentum
		// kind of weird, since a new timestamp will only be set when 
		time_s = 

		angle = get_angle(phase_transition_count);
		angular_momentum = get_angular_momentum(angle, time_s);


		// output

		HAL_Delay(10000);
	}
}

// EOF
