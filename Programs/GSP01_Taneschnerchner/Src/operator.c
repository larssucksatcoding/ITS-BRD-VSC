
#include "operator.h"
#include "stack.h"
#include "errno.h"
#include "stdbool.h"


int add(int* result) {
    int error, top_number, second_number;

    error = popTopTwoElements(&top_number, &second_number);

    if (error != NO_ERROR) {
        return error;
    }

    // TODO: check for arithmetic overflow
    *result = top_number + second_number;
    return NO_ERROR;
}

int subtract(int* result) {

}

int divide(int* result);

int multiply(int* result);