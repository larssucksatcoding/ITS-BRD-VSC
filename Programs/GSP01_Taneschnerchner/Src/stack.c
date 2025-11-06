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

static int top_element_index = -1;  // index des obersten Elements
static int stack[MAX_SIZE];

int push(int v) {
    if((top_element_index + 1) == MAX_SIZE) {
        return STACK_OVERFLOW;
    }

    top_element_index++;

    stack[top_element_index] = v;
    return NO_ERROR;
}

int pop(int* v) {
    if(top_element_index == -1) {
        return STACK_UNDERFLOW;
    }

    *v = stack[top_element_index];

    top_element_index--;

    return NO_ERROR;
}

int swapStack() {
    if(top_element_index == -1 || top_element_index == 0) {
        return STACK_UNDERFLOW;
    }

    int v = stack[top_element_index];
    stack[top_element_index] = stack[top_element_index - 1];
    stack[top_element_index - 1] = v;

    return NO_ERROR;
}

int duplStack() {
    if(top_element_index == -1) {
        return STACK_UNDERFLOW;
    }

    int v = 0;
    getFirst(&v);
    return push(v);
}

void deleteStack() {
    for (int i = 0; i <= top_element_index; i++) {
        stack[i] = 0;
    }

    top_element_index = -1;
}

int getFirst(int* v) {
    if (top_element_index == -1) {
        return STACK_UNDERFLOW;
    }

    *v = stack[top_element_index];
    return NO_ERROR;
}

int peek(int* val, int field) {
    if (field >= MAX_SIZE) {
        return EMPTY_FIELD;
    }
    else if (field > top_element_index || field < 0) {
        return EMPTY_FIELD;
    }

    *val = stack[field];
    return NO_ERROR;
}

int getSize() {
    return top_element_index+1;
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