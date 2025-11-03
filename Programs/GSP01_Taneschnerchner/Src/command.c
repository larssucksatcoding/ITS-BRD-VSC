/**
  * @file       command.c
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Oct 2025
  * @brief      functions to deal with any command
  */

#include "command.h"
#include "display.h"
#include "errno.h"
#include "stack.h"
#include "stdbool.h"
#include <stdlib.h>

/**
  * @brief      prints a number
  *
  * @param      int number (to be printed) 
  * 
  * @return     void
  */
void printNumber(int val);

/**
  * @brief      turns a number into a string 
  *
  * @param      char n[]: digits+1, 
  * @param      int v: number that is supposed to be a string
  * 
  * @return     number transformed to a string
  */
void numberToString(char n[], int v);

/**
  * @brief      counts the digits of a number 
  *
  * @param      int number which digits shall be known
  * 
  * @return     the amount of digits that have been counted
  */
int digitCount(int v);


/**

################ F U N C T I O N S ################
 
*/
void printCMD() {
    int val, error;
    error = getFirst(&val);
    
}

void printAllCMD() {
    int size = getSize();
    for (int i = 0; i < size; i++) {
        int val = 0;
        int error = peek(&val, i);
        if (error == NO_ERROR) {
            printNumber(val);
        }
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

void printNumber(int val) {
    int digits = digitCount(val);
    char vString[digits + 1];
    numberToString(vString, val);
    printStdout(vString);
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
