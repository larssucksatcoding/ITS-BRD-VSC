

#include "errno.h"
#include "stack.h"
#include "display.h"
#include "token.h"
#include "scanner.h"

/**
  * @brief      organizes the Error Output
  *
  * @param      int errorcode
  * 
  * @return     void
  */
void errorPrint (int error) {
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
		printStdout("\n\n\n  press C to reset");
	} 
}


void handle_error(int error) {
    if (error != NO_ERROR) {
        errorPrint(error);
        T_token reset;
        do {
            reset = nextToken();
        } while (reset.tok != CLEAR);
        deleteStack();
        setNormalMode();
    }	
}
