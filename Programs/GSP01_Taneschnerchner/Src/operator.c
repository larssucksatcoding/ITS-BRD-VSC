/**
  * @file       operator.c
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Oct 2025
  * @brief      functions to deal with mul div sub add
  */
#include "operator.h"
#include "stack.h"
#include "errno.h"
#include "stdbool.h"
#include "limits.h"


int add(int* result) {
    int error, top_number, second_number;

    error = popTopTwoElements(&top_number, &second_number);

    if (error != NO_ERROR) {
        return error;
    }

    // arithmetic overflow can not happen for adding numbers
    // when one number is positive and one negative, because even
    // if one number is INT_MAX, the other number is negative, and
    // if one number is INT_MIN, the other number is positive, so
    // adding these two numbers will always result in a number that is
    // closer to zero.
    *result = top_number + second_number;
    bool both_positive = (top_number > 0) && (second_number > 0);
    bool both_negative = (top_number < 0) && (second_number < 0);

    // to check for overflow when both are positive:
    // top_number + second_number > INT_MAX        | - second_number
    // top_number > INT_MAX - second_number
    if (both_positive) {
        if (top_number > (INT_MAX - second_number)) {
            return ARITHMETIC_OVERFLOW;
        }
    }

    // to check for underflow when both are negative:
    // top_number + second_number < INT_MIN         | - second_number
    // top_number < INT_MIN - second_number
    if (both_negative) {
        if (top_number < (INT_MIN - second_number)) {
            return ARITHMETIC_OVERFLOW;
        }
    }

    return NO_ERROR;
}

int subtract(int* result) {
    int error, top_number, second_number;

    error = popTopTwoElements(&top_number, &second_number);

    if (error != NO_ERROR) {
        return error;
    }

    // arithmetic overflow cannot happen for subtraction when the numbers are
    // both either positive or negative. When both are positive, subtracting
    // them cannot lead to underflow, and when both are negative, subtracting
    // them cannot lead to overflow.
    *result = second_number - top_number;
    bool can_overflow  = (second_number > 0) && (top_number < 0);
    bool can_underflow = (second_number < 0) && (top_number > 0);
    
    // special case: 0 - INT_MIN will overflow.
    if ((second_number == 0) && (top_number == INT_MIN)) {
        return ARITHMETIC_OVERFLOW;
    }

    // check for overflow:
    // second_number - top_number > INT_MAX         | + top_number
    // second_number > INT_MAX + top_number
    if (can_overflow) {
        if (second_number > (INT_MAX + top_number)) {
            return ARITHMETIC_OVERFLOW;
        }
    }

    // check for underflow:
    // second_number - top_number < INT_MIN         | + top_number
    // second_number < INT_MIN + top_number
    if (can_underflow) {
        if (second_number < (INT_MIN + top_number)) {
            return ARITHMETIC_OVERFLOW;
        }
    }

    return NO_ERROR;
}

int divide(int* result) {
    int error, top_number, second_number;

    error = popTopTwoElements(&top_number, &second_number);

    if (error != NO_ERROR) {
        return error;
    }

    // only possble error when dividing is divison by zero
    // arithmetic over-/ underflow not possible
    if (top_number == 0) {
        return DIVISION_BY_ZERO;
    }

    *result = second_number / top_number;
    return NO_ERROR;
}

int multiply(int* result) {
    int error, top_number, second_number;

    error = popTopTwoElements(&top_number, &second_number);

    if (error != NO_ERROR) {
        return error;
    }

    bool result_zero = (top_number == 0) || (second_number == 0);
    bool result_negative =
        ((top_number > 0) && (second_number < 0)) ||
        ((top_number < 0) && (second_number > 0));

    if (result_zero) {
        return NO_ERROR;
    }

    // special case: -1 * INT_MIN will overflow
    if ((top_number == -1) && (second_number == INT_MIN)) return ARITHMETIC_OVERFLOW;
    if ((top_number == INT_MIN) && (second_number == -1)) return ARITHMETIC_OVERFLOW;

    // checking for underflow if result is negative:
    // top * bottom < INT_MIN           | /bottom
    // top < INT_MIN / bottom       (if bottom is positive)
    // top > INT_MIN / bottom       (if bottom is negative)
    if (result_negative) {
        if (second_number > 0) {
            if (top_number < (INT_MIN / second_number)) {
                return ARITHMETIC_OVERFLOW;
            }
        } else {
            if (top_number > (INT_MIN / second_number)) {
                return ARITHMETIC_OVERFLOW;
            }
        }
    }

    // checking for overflow if result is positive:
    // top * bottom > MAX_INT           | /bottom
    // top > MAX_INT / bottom       (if bottom positive)
    // top < MAX_INT / bottom       (if bottom negative)
    if (!result_negative) {
        if (second_number > 0) {
            if (top_number > (INT_MAX / second_number)) {
                return ARITHMETIC_OVERFLOW;
            }
        } else {
            if (top_number < (INT_MAX / second_number)) {
                return ARITHMETIC_OVERFLOW;
            }
        }
    }

    *result = top_number * second_number;
    return NO_ERROR;
}

