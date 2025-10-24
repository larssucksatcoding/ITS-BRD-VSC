/**
  * @file       command.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Oct 2025
  * @brief      header file of command module
  */

#ifndef COMMAND_H
#define COMMAND_H

/*
Die Funktion p druckt den obersten Wert des Stacks aus, ohne dass der Stack verändert wird.
Ø Die Funktion P druckt den gesamten Stack aus, ohne dass der Stack verändert wird.
Ø Die Funktion C löscht alle Einträge des Stacks.
Ø Die Funktion d dupliziert den obersten Eintrag des Stacks.
Ø Die Funktion r vertauscht die Reihenfolge der beiden obersten Einträge des Stacks.
*/


/**
  * @brief      prints the value of the topmost element on the stack
  */
void printTopOfStackCMD();

/**
  * @brief      prints the entire stack
  */
void printStackCMD();

/**
  * @brief      deletes all elements from the stack
  */
void deleteStackCMD();

/**
  * @brief      copies the topmost element of the stack and pushes
  *             that to the stack.
  * 
  * @return     returns STACK_UNDERFLOW when the stack is empty
  */
int duplicateTopOfStackCMD();

/**
  * @brief      reverses the order of the two topmost elements of
  *             the stack
  * 
  * @return     returns STACK_UNDERFLOW when the stack has fewer
  *             than two elements.
  */
int swapFristTwoEntriesCMD();

/**
  * @brief      counts the digits of a number 
  *
  * @param      int number which digits shall be known
  * 
  * @return     the amount of digits that have been counted
  */
int digitCount(int v);

/**
  * @brief      turns a number into a string 
  *
  * @param      char n[]: digits+1, 
  * @param      int v: number that is supposed to be a string
  * 
  * @return     number transformed to a string
  */
void numberToString(char n[], int v);



#endif
