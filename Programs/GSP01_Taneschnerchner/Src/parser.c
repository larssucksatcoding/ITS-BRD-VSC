

#include "parser.h"
#include "errno.h"
#include "token.h"
#include "stack.h"
#include "operator.h"
#include "command.h"


int parse_token(T_token input, int* result) {
	int error = NO_ERROR;

	switch(input.tok) {
		case ENTER: case UNEXPECTED: {
			break;
		}
		case NUMBER: {
			error = push(input.val);
			break;
		}
		case PLUS: {
			error = add(result);
			push(*result);
			break;
		}
		case MINUS: {
			error = subtract(result);
			push(*result);
			break;
		}
		case MULT: {
			error = multiply(result);
			push(*result);
			break;
		}
		case DIV: {
			error = divide(result);
			push(*result);
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
			error = duplCMD();
			break;
		}
		case OVERFLOW: {
			// - Zahl wurde eingegeben setze alles zurück
			// wir müssen damit nicht umgehen, tun wir trotzdem
			error = NEGATIVE_INPUT;
			break;
		}
	}

	return error;
}