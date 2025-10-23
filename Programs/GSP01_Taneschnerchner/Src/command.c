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
    int copyV = v;
    int digits = 0;
    // how to print?
    while (copyV % 10 != 0) {
        digits ++;
    }
    char str[digits + 1];
    str[digits] = '\0';
    for (int i = 0; i < 10; i++) {
        str[i] = v - v%10;
        digits++;
    }
}

void printStackCMD() {
    int size = getSize();
    int stackCopy[size];
}

void deleteStackCMD() {
    deleteStack();
}

int duplicateTopOfStackCMD() {
    duplStack();
}

int swapFristTwoEntriesCMD() {
    swapStack();
}

