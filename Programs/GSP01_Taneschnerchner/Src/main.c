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


int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch

  // Begruessungstext	
	lcdPrintlnS("Hallo liebes TI-Labor (c-project)");
	
	// Test in Endlosschleife
	while(1) {
		// HAL_Delay(10000);
		T_token input = nextToken();
		int error = NO_ERROR;
		switch(input.tok) {
			case NUMBER: {
				push(input.val);
			}
			case PLUS: {
				int result = 0;
				error = add(&result);
				if (error == NO_ERROR) {
					push(result);
				}
				// ergebnis anzeigen lassen?
			}
			case MINUS: {

			} 
			case MULT: {

			}
			case DIV: {

			}
			case PRT: {

			}
			case SWAP: {

			}
			case PRT_ALL: {

			}
			case CLEAR: {

			}
			case DOUBLE: {

			}
			case ENTER: {

			}
			case UNEXPECTED: {

			}
			case OVERFLOW: {

			}

		}

			
	}
}

void errorPrint (int e) {

}

// EOF
