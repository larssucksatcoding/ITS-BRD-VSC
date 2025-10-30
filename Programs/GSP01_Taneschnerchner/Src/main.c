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
			
			case ENTER: case UNEXPECTED: {
				break;
			}
			case NUMBER: {
				push(input.val);
				break;
			}
			case PLUS: {
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
			case OVERFLOW: {
				// - Zahl wurde eingegeben setze alles zurück
				// wir müssen damit nicht umgehen, tun wir trotzdem
				error = NEGATIVE_INPUT;
				break;
			}
		}
		if (error != NO_ERROR) {
			errorPrint(error);
			do {
				T_token reset = nextToken();
			} while (reset.tok != CLEAR)
			setNormalMode();
		}
		else if (arithmeticOperation) {
			// kein Fehler + arithmetic Operation
			push(result);
		}		
	}
}

void errorPrint (int e) {
	setErrMode();
	switch(error) {
		case DIVISION_BY_ZERO: {
			printStdout("nicht durch 0 teilen du Idiot!\n"
				"error: DIVSION BY ZERO");
			break;
		}
		case ARITHMETIC_OVERFLOW: {
			printStdout("so weit kann ich nicht Zählen.\n"
				"error: ARITHMETIC OVERFLOW");
			break;
		}
		case STACK_OVERFLOW: {
			printStdout("Ich bin voll, ich kann nicht mehr.\n"
				"error: STACK OVERFLOW");
			break;
		}
		case STACK_UNDERFLOW: {
			printStdout("Was willst du? ich kann dir nichts geben.\n"
				"error: STACK UNDERFLOW");
			break;
		}
		case NEGATIVE_INPUT: {
			printStdout("5 Äpfel kannst du mir geben, aber -5?!\n"
				"error: NEGATIVE INPUT");
			break;
		}
		printStdout("\n\n\n  press C to reset")
	} 
}

// EOF
