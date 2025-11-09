

#include "tests.h"
#include "display.h"
#include "errno.h"
#include "stack.h"
#include "token.h"
#include "parser.h"
#include <limits.h>
#include <stdio.h>


#define TEST_PASSED 0
#define TEST_FAILED 1

#define ERROR_STR_LEN 200


/**
  * @brief      takes a list of token inputs and saves the first occuring error as well
  *             the top value of the stack after processing the list. these are then
  *             compared to an expected result and error afterwards.
  *             if the expectations don't match, print error message on screen.
  *
  * @param      input: the input token list to test.
  *             test_name: name for the test. used for printed error message.
  *             expected_result: the expected result for this token list.
  *             expected_error: the expected error for this token list.
  * 
  * @return     either TEST_PASSED or TEST_FAILED.
  */
int test_input(T_token* input, char* test_name, int expected_result, int expected_error) {
    deleteStack();

    int error = NO_ERROR;
    int result = 0;

    int index = 0;

    // loop through test input. the ENTER token is used as a signal that dsignates
    // the end of the test input.
    while (input[index].tok != ENTER) {
        error = parse_token(input[index], &result);

        if (error != NO_ERROR) {
            break;
        }

        index++;
    }

    // fetch result from top of stack and reset the stack
    getFirst(&result);
    deleteStack();

    // check if our test yielded the expected error. if not, print error message.
    if (error != expected_error) {
        setErrMode();

        char error_msg[ERROR_STR_LEN];
        sprintf(error_msg, "err: %i, expected %i\n", error, expected_error);

        printStdout(test_name);
        printStdout("\n");
        printStdout(error_msg);

        return TEST_FAILED;
    }

    // check if our test yielded the expected result. if not, print error message.
    // we only need to check for the results if we expected no error, since the
    // result does not matter in case we were just checking for an error.
    if ((result != expected_result) && (expected_error == NO_ERROR)) {
        setErrMode();

        char error_msg[ERROR_STR_LEN];
        sprintf(error_msg, "result: %i, expected %i\n", result, expected_result);

        printStdout(test_name);
        printStdout("\n");
        printStdout(error_msg);

        return TEST_FAILED;
    }

    // the test is passed if it yielded both the expected result and error.
    return TEST_PASSED;
}

// =============
// GENERAL TESTS
// =============

int test1() {
    char* test_name = "test1";
    int expected_error = NO_ERROR;
    int expected_result = 3;

    T_token input[] = {
        {.tok = NUMBER, .val = 25},
        {.tok = NUMBER, .val = 8},
        {.tok = NUMBER, .val = 67},
        {.tok = PLUS,   .val = 0},
        {.tok = SWAP,   .val = 0},
        {.tok = DIV,    .val = 0},
        {.tok = ENTER,  .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

int test2() {
    char* test_name = "test2";
    int expected_error = NO_ERROR;
    int expected_result = 0;

    T_token input[] = {
        {.tok = NUMBER, .val = INT_MAX},
        {.tok = NUMBER, .val = INT_MIN},
        {.tok = DIV,    .val = 0},
        {.tok = ENTER, .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

int test3() {
    char* test_name = "test3";
    int expected_error = NO_ERROR;
    int expected_result = -12;

    T_token input[] = {
        {.tok = NUMBER, .val = 2},
        {.tok = NUMBER, .val = 3},
        {.tok = NUMBER, .val = 4},
        {.tok = NUMBER, .val = 5},
        {.tok = PLUS,   .val = 0},
        {.tok = MINUS,  .val = 0},
        {.tok = MULT,   .val = 0},
        {.tok = ENTER,  .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

int test4() {
    char* test_name = "test4";
    int expected_error = DIVISION_BY_ZERO;
    int expected_result = 0;

    T_token input[] = {
        {.tok = NUMBER, .val = 3},
        {.tok = NUMBER, .val = 0},
        {.tok = DIV, .val = 0},
        {.tok = ENTER,  .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

int test5() {
    char* test_name = "test5";
    int expected_error = NO_ERROR;
    int expected_result = 0;

    T_token input[] = {
        {.tok = NUMBER, .val = 0},
        {.tok = NUMBER, .val = 3},
        {.tok = DIV, .val = 0},
        {.tok = ENTER,  .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

// ========================================
// TESTS FOR ARITHMETIC OVERFLOW (ADDITION)
// ========================================

int test6() {
    char* test_name = "test6";
    int expected_error = ARITHMETIC_OVERFLOW;
    int expected_result = 0;

    T_token input[] = {
        {.tok = NUMBER, .val = INT_MAX},
        {.tok = NUMBER, .val = 1},
        {.tok = PLUS,   .val = 0},
        {.tok = ENTER,  .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

int test7() {
    char* test_name = "test7";
    int expected_error = NO_ERROR;
    int expected_result = INT_MAX;

    T_token input[] = {
        {.tok = NUMBER, .val = INT_MAX},
        {.tok = NUMBER, .val = 0},
        {.tok = PLUS,   .val = 0},
        {.tok = ENTER,  .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

int test8() {
    char* test_name = "test8";
    int expected_error = ARITHMETIC_OVERFLOW;
    int expected_result = 0;

    T_token input[] = {
        {.tok = NUMBER, .val = INT_MIN},
        {.tok = NUMBER, .val = -1},
        {.tok = PLUS,   .val = 0},
        {.tok = ENTER,  .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

int test11() {
    char* test_name = "test11";
    int expected_error = NO_ERROR;
    int expected_result = INT_MIN;

    T_token input[] = {
        {.tok = NUMBER, .val = INT_MIN},
        {.tok = NUMBER, .val = 0},
        {.tok = PLUS,   .val = 0},
        {.tok = ENTER,  .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

// ==========================================
// TESTS FOR ARITHMETIC OVERFLOW (SUBTRACTION)
// ==========================================

int test12() {
    char* test_name = "test12";
    int expected_error = ARITHMETIC_OVERFLOW;
    int expected_result = 0;

    T_token input[] = {
        {.tok = NUMBER, .val = INT_MIN},
        {.tok = NUMBER, .val = 1},
        {.tok = MINUS,  .val = 0},
        {.tok = ENTER,  .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

int test13() {
    char* test_name = "test13";
    int expected_error = NO_ERROR;
    int expected_result = INT_MIN;

    T_token input[] = {
        {.tok = NUMBER, .val = INT_MIN},
        {.tok = NUMBER, .val = 0},
        {.tok = MINUS,  .val = 0},
        {.tok = ENTER,  .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

int test14() {
    char* test_name = "test14";
    int expected_error = ARITHMETIC_OVERFLOW;
    int expected_result = 0;

    T_token input[] = {
        {.tok = NUMBER, .val = 0},
        {.tok = NUMBER, .val = INT_MIN},
        {.tok = MINUS,  .val = 0},
        {.tok = ENTER,  .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

int test15() {
    char* test_name = "test15";
    int expected_error = ARITHMETIC_OVERFLOW;
    int expected_result = 0;

    T_token input[] = {
        {.tok = NUMBER, .val = INT_MAX},
        {.tok = NUMBER, .val = -1},
        {.tok = MINUS,  .val = 0},
        {.tok = ENTER,  .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

// ==============================================
// TESTS FOR ARITHMETIC OVERFLOW (MULTIPLICATION)
// ==============================================

int test16() {
    char* test_name = "test16";
    int expected_error = NO_ERROR;
    int expected_result = INT_MAX;

    T_token input[] = {
        {.tok = NUMBER, .val = INT_MAX},
        {.tok = NUMBER, .val = 0},
        {.tok = MINUS,  .val = 0},
        {.tok = ENTER,  .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

int test17() {
    char* test_name = "test17";
    int expected_error = ARITHMETIC_OVERFLOW;
    int expected_result = 0;

    T_token input[] = {
        {.tok = NUMBER, .val = INT_MIN},
        {.tok = NUMBER, .val = -1},
        {.tok = MULT,   .val = 0},
        {.tok = ENTER,  .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

int test18() {
    char* test_name = "test18";
    int expected_error = NO_ERROR;
    int expected_result = -INT_MAX;

    T_token input[] = {
        {.tok = NUMBER, .val = INT_MAX},
        {.tok = NUMBER, .val = -1},
        {.tok = MULT,   .val = 0},
        {.tok = ENTER,  .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

// ========================
// TESTS FOR STACK OVERFLOW
// ========================

int test19() {
    char* test_name = "test19";
    int expected_error = STACK_OVERFLOW;
    int expected_result = 0;

    T_token input[] = {
        {.tok = NUMBER, .val = 1},
        {.tok = NUMBER, .val = 2},
        {.tok = NUMBER, .val = 3},
        {.tok = NUMBER, .val = 4},
        {.tok = NUMBER, .val = 5},
        {.tok = NUMBER, .val = 6},
        {.tok = NUMBER, .val = 7},
        {.tok = NUMBER, .val = 8},
        {.tok = NUMBER, .val = 9},
        {.tok = ENTER,  .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

int test20() {
    char* test_name = "test20";
    int expected_error = STACK_OVERFLOW;
    int expected_result = 0;

    T_token input[] = {
        {.tok = NUMBER, .val = 1},
        {.tok = DOUBLE, .val = 2},
        {.tok = DOUBLE, .val = 3},
        {.tok = DOUBLE, .val = 4},
        {.tok = DOUBLE, .val = 5},
        {.tok = DOUBLE, .val = 6},
        {.tok = DOUBLE, .val = 7},
        {.tok = DOUBLE, .val = 8},
        {.tok = DOUBLE, .val = 9},
        {.tok = ENTER,  .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

int test21() {
    char* test_name = "test21";
    int expected_error = NO_ERROR;
    int expected_result = 9;

    T_token input[] = {
        {.tok = NUMBER, .val = 1},
        {.tok = NUMBER, .val = 2},
        {.tok = NUMBER, .val = 3},
        {.tok = CLEAR,  .val = 0},
        {.tok = NUMBER, .val = 4},
        {.tok = NUMBER, .val = 5},
        {.tok = NUMBER, .val = 6},
        {.tok = NUMBER, .val = 7},
        {.tok = NUMBER, .val = 8},
        {.tok = NUMBER, .val = 9},
        {.tok = ENTER, .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

// =========================
// TESTS FOR STACK UNDERFLOW
// =========================

int test22() {
    char* test_name = "test22";
    int expected_error = STACK_UNDERFLOW;
    int expected_result = 0;

    T_token input[] = {
        {.tok = SWAP,  .val = 0},
        {.tok = ENTER, .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

int test23() {
    char* test_name = "test23";
    int expected_error = STACK_UNDERFLOW;
    int expected_result = 0;

    T_token input[] = {
        {.tok = NUMBER, .val = 1},
        {.tok = SWAP,   .val = 0},
        {.tok = ENTER,  .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

int test24() {
    char* test_name = "test24";
    int expected_error = NO_ERROR;
    int expected_result = 1;

    T_token input[] = {
        {.tok = NUMBER, .val = 1},
        {.tok = NUMBER, .val = 2},
        {.tok = SWAP,   .val = 0},
        {.tok = ENTER,  .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

int test25() {
    char* test_name = "test25";
    int expected_error = NO_ERROR;
    int expected_result = 1;

    T_token input[] = {
        {.tok = NUMBER, .val = 1},
        {.tok = DOUBLE, .val = 0},
        {.tok = SWAP,   .val = 0},
        {.tok = ENTER,  .val = 0}
    };

    int test_result = test_input(
        input, test_name, expected_result, expected_error
    );

    return test_result;
}

// ===============
// OTHER TEST CODE
// ===============

void run_tests() {
    clearStdout();
    setNormalMode();

    // run through all handwritten tests. abort if one of the tests failed
    // to avoid having the screen cluttered in the case that more tests fail.
    if (test1() == TEST_FAILED) return;
    if (test2() == TEST_FAILED) return;
    if (test3() == TEST_FAILED) return;
    if (test4() == TEST_FAILED) return;
    if (test5() == TEST_FAILED) return;
    if (test6() == TEST_FAILED) return;
    if (test7() == TEST_FAILED) return;
    if (test8() == TEST_FAILED) return;
    if (test11() == TEST_FAILED) return;
    if (test12() == TEST_FAILED) return;
    if (test13() == TEST_FAILED) return;
    if (test14() == TEST_FAILED) return;
    if (test15() == TEST_FAILED) return;
    if (test16() == TEST_FAILED) return;
    if (test17() == TEST_FAILED) return;
    if (test18() == TEST_FAILED) return;
    if (test19() == TEST_FAILED) return;
    if (test20() == TEST_FAILED) return;
    if (test21() == TEST_FAILED) return;
    if (test22() == TEST_FAILED) return;
    if (test23() == TEST_FAILED) return;
    if (test24() == TEST_FAILED) return;
    if (test25() == TEST_FAILED) return;

    // if all tests pass, print that on the screen
    printStdout("all tests passed :)\nhave a slightly\nabove average day!\n");
}
