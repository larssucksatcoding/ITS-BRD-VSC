/**
  * @file       stack.c
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Oct 2025
  * @brief      implements the stack + functions to operate
  *             on the stack
  * Note: we don't reset non used indexes to zero.
  * The stack itself takes care that these indexes cannot be accessed
  * (Yes, the magic does it)
  */

#include "stack.h"
#include "errno.h"


#define MAX_SIZE 8

static int top_element_index = -1;  // index des obersten Elements
static int stack[MAX_SIZE];

int push(int v) {
    if(getSize() >= MAX_SIZE) {
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
    if(top_element_index < 1) {
        // not enough elements to perform task
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
    top_element_index = -1;
}

int getFirst(int* v) {
    if (top_element_index == -1) {
        return STACK_UNDERFLOW;
    }

    *v = stack[top_element_index];
    return NO_ERROR;
}

int peek(int* val, int index) {
    if (index >= MAX_SIZE || index < 0) {
        // index doesn't exist in stack
        return EMPTY_FIELD;
    }
    else if (index > top_element_index) {
        // no value at index
        return EMPTY_FIELD;
    }

    *val = stack[index];
    return NO_ERROR;
}

int getSize() {
    return top_element_index + 1;
}

int popTopTwoElements(int* top, int* bottom) {
    /* if (getSize() < 2) {
        // check if there are enough elements
        // to perform task
       return STACK_UNDERFLOW;
    }

    pop (top);
    pop (bottom); */

    // geändert, damit es doch nicht komplett dumm ist in der
    // pop Funktion einen error zu returnen

    int error = NO_ERROR;
    error = pop(top);
    if ( error != NO_ERROR) {
        return error;
    }
    error = pop(bottom);
    if (error != NO_ERROR) {
        // müssten hier nicht pushen, Stack wird bei error eh gelöscht
        push(*top);
        return error;
    }

    return NO_ERROR;
}

//EOF