/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"

#include "input.h"
#include "BMP_types.h"
#include "errorhandler.h"
#include "headers.h"
#include "MS_basetypes.h"

#include "writer.h"
#include "button.h"


int main(void) {

	// init
	initITSboard();    // Initialisierung des ITS Boards
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	initInput();

	while (true) {
		load_picture();
		draw_picture();

		wait_until_button_pressed();
	}
}

// EOF
