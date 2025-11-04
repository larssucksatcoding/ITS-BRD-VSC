

#include "tests.h"
#include "display.h"
#include "errno.h"
#include "stack.h"
#include "operator.h"
#include "token.h"
#include "parser.h"
#include <stdio.h>


#define TEST_PASSED 0
#define TEST_FAILED 1

#define ERROR_STR_LEN 200


int test_input(T_token* input, int input_size, int expected_result, int expected_error) {
    deleteStack();

    int error = NO_ERROR;
    int result = 0;

    for (int i = 0; i < input_size; i++) {
        error = parse_token(input[i], &result);

        if (error != NO_ERROR) {
            break;
        }
    }

    deleteStack();

    if (error != expected_error) {
        setErrMode();

        char error_msg[ERROR_STR_LEN];
        sprintf(error_msg, "err: %i, expected %i\n", error, expected_error);
        printStdout(error_msg);

        return TEST_FAILED;
    }

    if (result != expected_result) {
        setErrMode();

        char error_msg[ERROR_STR_LEN];
        sprintf(error_msg, "result: %i, expected %i\n", result, expected_result);
        printStdout(error_msg);

        return TEST_FAILED;
    }

    return TEST_PASSED;
}


void run_tests() {
    clearStdout();
    setNormalMode();

    int input_size, test_result, expected_error, expected_result;

    // test 1

    T_token input[] = {
        {.tok = NUMBER, .val = 25},
        {.tok = NUMBER, .val = 8},
        {.tok = NUMBER, .val = 6},
        {.tok = NUMBER, .val = 7},
        {.tok = PLUS,   .val = 0},
        {.tok = SWAP,   .val = 0},
        {.tok = DIV,    .val = 0},
        {.tok = PRT,    .val = 0},
    };

    input_size = 8;
    expected_error = NO_ERROR;
    expected_result = 3;

    // TODO: as of now, somehow gives "err: 0, expected 3"
    test_result = test_input(
        input, input_size, expected_error, expected_result
    );

    if (test_result == TEST_FAILED) {
        return;
    } 
}

/*
`25 8 6 7 + r / p` gibt den Wert 3 aus.
`INT_MAX INT_MIN /` gibt den Wert 0 aus.
`1 2 3 4 5  + - * / p` gibt den Wert -3 aus.

### Division durch Null

`3 0 /` sollte DIVISION_BY_ZERO error werfen.
`0 3 /` sollte NO_ERROR zurückgeben und 0 schreiben.

### Bereichsüberschreitung

**Addition:**

`INT_MAX  1 +` sollte ARITHMETIC_OVERFLOW werfen.
`INT_MAX  0 +` sollte NO_ERROR zurückgeben und INT_MAX schreiben.

`INT_MIN -1 +` sollte ARITHMETIC_OVERFLOW werfen
`INT_MIN  0 +` sollte NO_ERROR zurückgeben und INT_MIN schreiben.

**Subtraktion:**

`INT_MIN 1 -` sollte ARITHMETIC_OVERFLOW werfen.
`INT_MIN 0 -` sollte NO_ERROR zurückgeben und INT_MIN schreiben.

`0 INT_MIN -`  sollte ARITHMETIC_OVERFLOW werfen.
`INT_MAX -1 -` sollte ARITHMETIC_OVERFLOW werfen.
`INT_MAX  0 -` sollte NO_ERROR zurückgeben und INT_MAX schreiben.

**Multiplikation:**

`INT_MIN -1 *` sollte ARITHMETIC_OVERFLOW werfen.
`INT_MAX -1 *` sollte NO_ERROR und -INT_MAX zurückgeben.

### STACK_OVERFLOW

`1 2 3 4 5 6 7 8 9` sollte STACK_OVERFLOW werfen (bei MAX_SIZE = 8).
`1 d d d d d d d d` sollte STACK_OVERFLOW werfen.
`1 2 3 C 1 2 3 4 5` sollte NO_ERROR zurückgeben.

### STACK_UNDERFLOW

`r` sollte STACK_UNDERFLOW werfen.
`1 r` sollte STACK_UNDERFLOW werfen.
`1 2 r` sollte NO_ERROR zurückgeben.
`1 d r` sollte NO_ERROR zurückgeben. (setzt `d` size korrect?)

`p` sollte STACK_UNDERFLOW werfen.
`1 p 2 p p` sollte STACK_UNDERFLOW werfen. (wird size korrekt gesetzt?)
`1 2 3 4 C 1 p p` sollte STACK_UNDERFLOW werfen. (wird size zurückgesetzt?)

`d` sollte STACK_OVERFLOW werfen.
`1 d` sollte NO_ERROR zurückgeben.
*/