/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Main von unserem Taneschnerchner
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "errno.h"
#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#include "scanner.h"
#include "stack.h"
#include "operator.h"
#include "command.h"
#include "stdbool.h"
#include "keypad.h"
#include "display.h"
#include <stdio.h>
#include "tests.h"
#include "parser.h"


int main(void) {
	initITSboard();
	initDisplay();

	// in case a test fails, the program halts.
	// run_tests();

	while(1) {
		T_token input = nextToken();

		int error = NO_ERROR;
		int result = 0;

		error = parse_token(input, &result);
		handle_error(error);
	}
}

// EOF
