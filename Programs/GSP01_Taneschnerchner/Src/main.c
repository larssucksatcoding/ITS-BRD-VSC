/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Main von unserem Taneschnerchner
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "errno.h"
#include "init.h"
#include "scanner.h"
#include "display.h"
#include "tests.h"
#include "parser.h"


int main(void) {
	initITSboard();
	initDisplay();

	// running tests will print stuff on the screen, so don't run this if you don't have to
	// run_tests();

	T_token input;
	int error, result;

	while(1) {
		input = nextToken();

		// parser checks input, if thrown returns error
		error = parse_token(input, &result);
		// let error handler check the errorcode (/ no_errorcode)
		handle_error(error);
	}
}

// EOF
