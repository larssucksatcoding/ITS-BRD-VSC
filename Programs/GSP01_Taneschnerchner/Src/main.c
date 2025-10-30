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


int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	initDisplay();
	// GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	// TP_Init(false);                 // Initialisierung des LCD Boards mit Touch

	// makeKeyPad();

	// std out:   big green box at the top
	// echo line: small thingy at the bottom

	// printToEchoLine('c'); 
	// printStdout("Hallo");

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
				break;
			}
			case PLUS: {
				// habe ich input.val? ja - push auf stack
				error = add(&result);
				arithmeticOperation = true;
				break;
			}
			case MINUS: {
				error = subtract(&result);
				arithmeticOperation = true;
				break;
			} 
			case MULT: {
				error = multiply(&result);
				arithmeticOperation = true;
				break;
			}
			case DIV: {
				error = divide(&result);
				arithmeticOperation = true;
				break;
			}
			case PRT: {
				printCMD();
				break;
			}
			case SWAP: {
				error = swapCMD();
				break;
			}
			case PRT_ALL: {
				printAllCMD();
				break;
			}
			case CLEAR: {
				deleteCMD();
				break;
			}
			case DOUBLE: {
				// error = duplicateCMD();
				break;
			}
			case ENTER: {
				// check number
				if (input.val != 0) {
					// store number in stack
					push(input.val);
				}
				break;
			}
			case UNEXPECTED: {
				// default token, wir warten bis wir was 
				break;
			}
			case OVERFLOW: {
				// - Zahl wurde eingegeben setze alles zurück
				// wir müssen damit nicht umgehen, tun wir trotzdem
				error = NEGATIVE_INPUT;
				break;
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
