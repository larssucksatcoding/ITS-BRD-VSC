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
void printCMD();

/**
  * @brief      prints the entire stack
  */
void printAllCMD();

/**
  * @brief      deletes all elements from the stack
  */
void deleteCMD();

/**
  * @brief      copies the topmost element of the stack and pushes
  *             that to the stack.
  * 
  * @return     returns STACK_UNDERFLOW when the stack is empty
  */
int duplicateCMD();

/**
  * @brief      reverses the order of the two topmost elements of
  *             the stack
  * 
  * @return     returns STACK_UNDERFLOW when the stack has fewer
  *             than two elements.
  */
int swapCMD();







#endif
