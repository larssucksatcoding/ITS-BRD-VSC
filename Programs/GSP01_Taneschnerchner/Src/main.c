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
		int result = 0;
		bool arithmeticOperation = false;
		switch(input.tok) {
			case NUMBER: {
				push(input.val);
			}
			case PLUS: {
				error = add(&result);
				arithmeticOperation = true;
			}
			case MINUS: {
				error = subtract(&result);
				arithmeticOperation = true;
			} 
			case MULT: {
				error = multiply(&result);
				arithmeticOperation = true;
			}
			case DIV: {
				error = divide(&result);
				arithmeticOperation = true;
			}
			case PRT: {
				error = printCMD();
			}
			case SWAP: {
				error = swapCMD();
			}
			case PRT_ALL: {
				error = printAllCMD()
			}
			case CLEAR: {
				error = deleteCMD()
			}
			case DOUBLE: {
				error = duplicateCMD()
			}
			case ENTER: {
				// mal schauen
			}
			case UNEXPECTED: {
				// gar kein plan 
			}
			case OVERFLOW: {
				// miste kagge
			}
			
			 

		}
		if (error != NO_ERROR) {
			// Fehlerverarbeitung
		}
		else if (arithmeticOperation) {
			push(result);
			// print result
		}


			
	}
}

void errorPrint (int e) {

}

// EOF
