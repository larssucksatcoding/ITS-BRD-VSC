/**
* @file       main.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Nov 2025
* @brief      
*/


/* Includes ------------------------------------------------------------------*/

#include "display.h"
#include "interrupt.h"
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

volatile uint32_t last_phase_transition_timestamp;
volatile bool aux0_state_previous;
volatile bool aux1_state_previous;
volatile bool aux0_state;
volatile bool aux1_state;
volatile int total_phase_count;
volatile int direction;


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
	init_time(&last_phase_transition_timestamp);
	init_gpio(&aux0_state, &aux1_state, 
		&aux0_state_previous, &aux1_state_previous);
}

/**
  * @brief      resets state of modules and reads input for first time
  */
void reset_state() {
	mask_interrupt_pin(0);
	mask_interrupt_pin(1);

	reset_display();

	set_status_led_off();
	set_phase_led_off();

	start_first_timewindow();
	read_gpio_pins(&aux0_state, &aux1_state);

	total_phase_count = 0;
	direction = DIR_NONE;

	unmask_interrupt_pin(0);
	unmask_interrupt_pin(1);
}

/**
  * @brief      save data into passed parameters and checks if we were
  *				interrupted by the isr in the process.
  * @return 	true, if interrrupted, false, if not interrupted
  */
bool check_for_interruption(bool *a, bool *b, bool *a_previous, bool *b_previous, 
	uint32_t *isr_timestamp, int *phase_count, int *dir) 
{
	// state 1
	*a = aux0_state;
	*b = aux1_state;
	*a_previous = aux0_state_previous;
	*b_previous = aux1_state_previous;
	*isr_timestamp = last_phase_transition_timestamp;
	*phase_count = total_phase_count;
	*dir = direction;

	// state 2
	bool a2 = aux0_state;
	bool b2 = aux1_state;
	bool a_previous2 = aux0_state_previous;
	bool b_previous2 = aux1_state_previous;
	uint32_t isr_timestamp2 = last_phase_transition_timestamp;
	int phase_count2 = total_phase_count;
	int dir2 = direction;

	// true if state1 == state2
	bool no_interruption = (
		(*a == a2) && (*b == b2) && 
		(*a_previous == a_previous2) && (*b_previous == b_previous2) && 
		(*isr_timestamp == isr_timestamp2) && 
		(*phase_count == phase_count2) &&
		(*dir == dir2)
	);
	
	return !no_interruption;
}


int main(void) {
	init_modules();

	int encoder_direction = DIR_NONE;

	// while(1) {
	// 	lcd_shit();
	// 	HAL_Delay(20);
	// }

	// bool toggle = false;

	// ===============
	// VARIABLE DEFINITIONS
	// ===============

	// values filled in by ddr
	bool aux0_state_copy, aux1_state_copy; 
	bool aux0_state_previous_copy, aux1_state_previous_copy;
	uint32_t isr_timestamp, loop_timestamp;
	int phase_count;
	int direction_copy;

	// values used for check_for_interruption loop
	bool interrupted = false;
	int iteration = 0;

	// read all inputs once right before superloop to avoid
	// immediate DIR_ERROR after the superloop starts
	reset_state();

	while(1) {

		// if (toggle) {
		// 	GPIOE->BSRR = PIN4 << SET_REGISTER;
		// } else {
		// 	GPIOE->BSRR = PIN4 << RESET_REGISTER;
		// }
		// toggle = !toggle;

		// ===============
		// HARDWARE INPUTS
		// ===============

		loop_timestamp = getTimeStamp();

		iteration = 0;
		do {
			bool interrupted = check_for_interruption(
				&aux0_state_copy, &aux1_state_copy, 
				&aux0_state_previous_copy, &aux1_state_previous_copy,
				&isr_timestamp, &phase_count, &direction_copy
			);
			iteration++;
		} while ((iteration < 10) && interrupted);

		// we tried saving data 10 times, and we always got interrupted. 
		// The decoder is spinning to fast. ERRROOORR!!
		if(interrupted) {
			show_error();
		}

		// ============
		// CALCULATIONS
		// ============

		if(is_timewindow_over(loop_timestamp, isr_timestamp)) {

			recalculate_angle(&phase_count);
			recalculate_angular_momentum(&phase_count, &isr_timestamp);

			// fetch new values
			check_display_data();

			// new time window
			// edge case (maybe?):
			// if first time window passes before encoder spins, the
			// start_new_timewindow(&isr_timestamp); method will use
			// isr_timestamp, which is at that point unitialized as
			// the new start for the time window. this will mess up
			// the next time window calculation, which could result
			// in a time window of up to 40s, halting the program.
			if (phase_count == 0) {
				start_new_timewindow(&loop_timestamp);
			} else {
				start_new_timewindow(&isr_timestamp);
			}
			
			save_last_total_phase_count(&phase_count);

			// blinky blink
			set_dir_led(&direction_copy);
			set_phase_led(&phase_count);
		}

		// --- DISPLAY ---

		// displays new values on the display, if any 
		// new have been set by recalcuate_display()
		update_display();
	}

}

// EOF
