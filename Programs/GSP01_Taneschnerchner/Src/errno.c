

#include "errno.h"
#include "stack.h"
#include "display.h"
#include "token.h"
#include "scanner.h"

/**
  * @brief      organizes the Error Output, sets Error Mode 
  *  			and displays error message
  *
  * @param      int errorcode
  * 
  * @return     void
  */
void errorPrint (int error) {
	setErrMode();
	switch(error) {
		case DIVISION_BY_ZERO: {
			printStdout(" nicht durch 0 teilen\n Grundschulschwaenzer!"
				"\n    error:\n  DIVSION BY ZERO");
			break;
		}
		case ARITHMETIC_OVERFLOW: {
			printStdout(" so weit kann ich\n nicht zaehlen.\n"
				"\n    error:\n  ARITHMETIC OVERFLOW");
			break;
		}
		case STACK_OVERFLOW: {
			printStdout(" Ich bin voll,\n ich kann nicht mehr.\n"
				"\n    error:\n  STACK OVERFLOW");
			break;
		}
		case STACK_UNDERFLOW: {
			printStdout(" Was willst du?\n Ich bin leer.\n"
				"\n    error:\n  STACK UNDERFLOW");
			break;
		}
		// last two errors will never be displayed
		case NEGATIVE_INPUT: {
			printStdout(" 5 aepfel kannst du mir geben, aber -5?!\n"
				"\n    error:\n  NEGATIVE INPUT");
			break;
		}
		case EMPTY_FIELD: {
			printStdout(" what would java say?\n INDEX OUT OF BOUNDS\n"
				"\n    error:\n  EMPTY FIELD");
			break;
		}
	}
	printStdout("\n\n\n  press C to reset");
}


void handle_error(int error) {
    if (error != NO_ERROR) {
        errorPrint(error);
		// wait for CLEAR token, to reset calculator
        T_token reset;
        do {
            reset = nextToken();
        } while (reset.tok != CLEAR);
		// reset Calculator
        deleteStack();
        setNormalMode();
    }	
}
