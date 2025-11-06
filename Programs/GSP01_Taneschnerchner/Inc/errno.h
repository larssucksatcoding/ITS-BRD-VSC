/**
  * @file       errno.h 
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Oct 2025
  * @brief      Definition der Error Codes
  */

#ifndef ERRNO_H
#define ERRNO_H

#define NO_ERROR             0      // kein Fehler
#define DIVISION_BY_ZERO    -1      // Bei Division: teiler == 0
#define ARITHMETIC_OVERFLOW -2      // Bereichsüberschreitung (Add, Mul, Sub)
#define STACK_OVERFLOW      -3      // Stack voll
#define STACK_UNDERFLOW     -4      // Stack leer
#define NEGATIVE_INPUT      -5      // negative Zahl wurde eingegeben
#define EMPTY_FIELD         -6      // Stackfeld nicht belegt oder nicht vorhanden


/**
  * @brief      if the error code indicates an error call function
  *             which deals with error display and wait until user inputs
  *             the clear command.
  *
  * @param      int error: the error message to handle
  * 
  * @return     void
  */
void handle_error(int error);


#endif