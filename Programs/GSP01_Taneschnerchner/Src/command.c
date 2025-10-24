/**
  * @file command.h
  * @author Der Stumpfe Kommandeur Lars 
  * @date gestern
  * @brief C file of the commander 
  */

#include "command.h"
#include "stack.h"

void printTopOfStackCMD() {
    int v = getFirst();
    int digits = digitCount(v);

    char vString[digits + 1];
    numberToString(vString, v);

}

void printStackCMD() {
    int size = getSize();
    int stackCopy[size];
}

void deleteStackCMD() {
    deleteStack();
}

int duplicateTopOfStackCMD() {
    int error = duplStack();
    return error;
}

int swapFristTwoEntriesCMD() {
    int error = swapStack();
    return error;
}

int digitCount(int v) {
    int digits = 0;
    while (v % 10 != 0) {
        digits ++;
    }
    return digits;
}

void numberToString(char *vString, int v) {
    int digits = digitCount(v);
    vString[digits] = '\0';
    for (int i = digits-1; i>= 0; i--) {
        int z = v;
        v = v%10;
        vString[i] = z - (v*10);
    }
}

