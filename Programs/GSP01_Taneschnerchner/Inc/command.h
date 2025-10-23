/**
  * @file command.h
  * @author Der Stumpfe Kommandeur Lars 
  * @date gestern
  * @brief Header file of the commander 
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


/*
 **************************************************************
 * @brief: prints the value of the topmost element on the stack
 *************************************************************/
void printTopOfStackCMD();

/*
 **************************************************************
 * @brief: prints the entire stack
 *************************************************************/
void printStackCMD();

/*
 **************************************************************
 * @brief: deletes all elements from the stack
 *************************************************************/
void deleteStackCMD();

/*
 **************************************************************
 * @brief: copies the topmost element of the stack and pushes
 * that to the stack.
 * @return: returns STACK_UNDERFLOW when the stack is empty
 *************************************************************/
int duplicateTopOfStackCMD();

/*
 **************************************************************
 * @brief: reverses the order of the two topmost elements of
 * the stack
 * @return: returns STACK_UNDERFLOW when the stack has fewer
 * than two elements.
 *************************************************************/
int swapFristTwoEntriesCMD();

#endif
