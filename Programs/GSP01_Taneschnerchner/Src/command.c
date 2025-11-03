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
#include <stdio.h>
#include <stdlib.h>
#include "limits.h"

#define MAX_LENGTH 12 
// längste Zahle ist -2^31 10 Stellen + Nullterminater + Minuszeichen

/**

################ V A R I A B L E ################

*/

static char numberCharArray[MAX_LENGTH];

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
void numberToString(int val);

/**
  * @brief      counts the digits of a number 
  *
  * @param      int number which digits shall be known
  * 
  * @return     the amount of digits that have been counted
  */
int digitCount(int val);


/**

################ F U N C T I O N S ################
 
*/
void printCMD() {
    clearStdout();
    int val, error;
    error = getFirst(&val);
    if(error == NO_ERROR) {
        numberToString(val);
        printStdout(numberCharArray);
        printStdout("\n");
    }
}

void printAllCMD() {
    clearStdout();
    int elements = getSize();

    for (int i = 0; i<elements; i++) {
        int val;
        int errrror = peek(&val, i);

        if(errrror == NO_ERROR) {
            numberToString(val);
            printStdout(numberCharArray);
            printStdout("\n");
        }
    }
}

void deleteCMD() {
    deleteStack();
}

int duplicateCMD() {
    int error = duplStack();
    return error;
}

int swapCMD() {
    int error = swapStack();
    return error;
}

int digitCount(int v) {
    int digits = 0;
    do {
        digits ++;
        v /= 10;
    } while (v != 0);
    return digits;
}

void numberToString(int val) {
    bool is_negative = val < 0;  
    int digits = digitCount(val);

    if (is_negative) {
        numberCharArray[0] = '-';
        digits += 1;
    }

    numberCharArray[digits] = '\0';
    int current_index = digits - 1;

    // do while because loop needs to run at least once, even if val == 0
    do {
        int last_digit = abs(val % 10);
        val /= 10;

        numberCharArray[current_index] = last_digit + '0';
        current_index -= 1;
    } while (val != 0);
}