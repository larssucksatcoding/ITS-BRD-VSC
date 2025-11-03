/**
  * @file       command.c
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Oct 2025
  * @brief      functions to deal with any command
  */

#include "command.h"
#include "stack.h"
#include "stdbool.h"
#include <stdlib.h>

void printCMD() {
    int v, error;
    error = getFirst(&v);
    int digits = digitCount(v);

    char vString[digits + 1];
    numberToString(vString, v);
}

void printAllCMD() {
    int size = getSize();
    for (int i = 0; i < size; i++) {
        int val = 0;
        int error = peek(&val, i);
        // print val
    }
}

void deleteCMD() {
    deleteStack();
}

int duplCMD() {
    int error = duplStack();
    return error;
}

int swapCMD() {
    int error = swapStack();
    return error;
}

int digitCount(int v) {
    int digits = 0;
    while (v != 0) {
        digits ++;
        v /= 10;
    }
    return digits;
}

void numberToString(char *vString, int v) {
    bool is_negative = v < 0;  
    int digits = digitCount(v);

    if (is_negative) {
        vString[0] = '-';
        digits += 1;
    }

    vString[digits] = '\0';
    int current_index = digits - 1;

    while (v != 0) {
        int last_digit = abs(v % 10);
        v /= 10;

        vString[current_index] = last_digit;
        current_index += 1;
    }
}

