/**
  * @file       stack.c
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Oct 2025
  * @brief      implements the stack + functions to operate
  *             on the stack
  */

#include "stack.h"
#include "errno.h"
#include "stdbool.h"

#define MAX_SIZE 8

static int size = 0; // aktuelle Anzahl der Elemente
static int stack[MAX_SIZE];

int push(int v) {
    if(size == MAX_SIZE) {
        return STACK_OVERFLOW;
    }
    stack[size] = v;
    size++;
    return NO_ERROR;
}

int pop(int* v) {
    if(size == 0) {
        return STACK_UNDERFLOW;
    }
    *v = stack[size];
    stack[size] = 0;
    size--;
    return NO_ERROR;
}

int swapStack() {
    if(size == 0 || size == 1) {
        return STACK_UNDERFLOW;
    }
    int v = stack[size];
    stack[size] = stack[size-1];
    stack[size-1] = v;
    return NO_ERROR;
}

int duplStack() {
    if(size == 0) {
        return STACK_UNDERFLOW;
    }
    int v = 0;
    pop(&v);
    push(v);
    return NO_ERROR;
}

void deleteStack() {
    for (int i = 0; i < size; i++) {
        stack[i] = 0;
    }
    size = 0;
}

int getFirst(int* v) {
    if (size == 0) {
        return STACK_UNDERFLOW;
    }
    *v = stack[size];
    return NO_ERROR;
}

void getCopyOfStack(int copy[]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (i < size) {
            copy[i] = stack[i];
        }
        else {
            copy[i] = 0;
        }
    }
}

int getSize() {
    return size;
}

int popTopTwoElements(int* top, int* bottom) {
    bool stackSizeSufficient = (getSize() >= 2);

    if (!stackSizeSufficient) {
        return STACK_UNDERFLOW;
    }

    int error;

    error = pop(top);
    if (error != NO_ERROR) {
        return error;
    }

    error = pop(bottom);
    if (error != NO_ERROR) {
        return error;
    }

    return NO_ERROR;
}

//EOF