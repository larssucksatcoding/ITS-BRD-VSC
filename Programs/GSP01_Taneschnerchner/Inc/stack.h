/**
  * @file     stack.h
  * @author   Lars Müller-Stumpf, Noah Rajko
  * @date     Oct 2025
  * @brief    Header file of stack module 
  */

#ifndef STACK_H
#define STACK_H

/**
  * @brief      pushes value onto the stack
  * 
  * @return     errorcode (NO_ERROR, STACK_OVERFLOW)
  */
int push(int v);

/**
  * @brief      pops and removes top element of stack 
  *
  * @param      int* val target memory for value
  * 
  * @return     errorcode (NO_ERROR, STACK_UNDERFLOW)
  */
int pop(int* v);

 /**
  * @brief      swaps top two elements of Stack
  * 
  * @return     errorcode (NO_ERROR, STACK_UNDERFLOW)
  */
int swapStack();

/**
  * @brief      duplicates top element
  * 
  * @return     errorcode (NO_ERROR, STACK_UNDERFLOW, STACK_OVERFLOW)
  */
int duplStack();

/**
  * @brief      deletes all elements
  * 
  * @return     void
  */
void deleteStack();

/**
  * @brief      returns top element without removing
  * 
  * @param      int* val target memory for value
  * 
  * @return     errorcode (NO_ERROR, STACK_UNDERFLOW) 
  */
int getFirst(int* v);

/**
  * @brief      gives value to index 
  *
  * @param      int* val target memory for value
  *
  * @param      int index - request for value at index
  * 
  * @return     errorcode (NO_ERROR, EMPTY_FIELD)
  */
int peek(int* val, int index);

/**
  * @brief      returns number of elements on the stack
  * 
  * @return     number of element
  */
int getSize();

/**
  * @brief      pops and removes the first two elements of the stack, writing
  *             them into the respective call-by-reference parameters.
  *
  * @param      int* top:    top element of stack will be written to this
  * @param      int* bottom: bottom element of stack will be written to this
  * 
  * @return     one of the error codes in errno.h can be NO_ERROR and 
  *             STACK_UNDERFLOW in case there are less than 2 elements on the stack.
  */
int popTopTwoElements(int* top, int* bottom);

#endif

// EOF
