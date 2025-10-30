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
		bool pushVal = input.val != 0;
		bool arithmeticOperation = false;
		switch(input.tok) {
			case NUMBER: {
				push(input.val);
			}
			case PLUS: {
				// habe ich input.val? ja - push auf stack
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
				printCMD();
			}
			case SWAP: {
				error = swapCMD();
			}
			case PRT_ALL: {
				printAllCMD();
			}
			case CLEAR: {
				deleteCMD();
			}
			case DOUBLE: {
				error = duplicateCMD();
			}
			case ENTER: {
				// check number
				if (input.val != 0) {
					// store number in stack
					push(input.val);
				}
			}
			case UNEXPECTED: {
				// default token, wir warten bis wir was 
			}
			case OVERFLOW: {
				// - Zahl wurde eingegeben setze alles zurück
				// wir müssen damit nicht umgehen, tun wir trotzdem
				error = NEGATIVE_INPUT;
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
