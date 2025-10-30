/**
  * @file       errno.h 
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Oct 2025
  * @brief      Definition der Error Codes
  */

#ifndef ERRNO_h
#define ERRNO_h

#define NO_ERROR            0       // kein Fehler
#define DIVISION_BY_ZERO    -1      // Bei Division: teiler == 0
#define ARITHMETIC_OVERFLOW -2      // Bereichsüberschreitung (Add, Mul, Sub)
#define STACK_OVERFLOW      -3      // Stack voll
#define STACK_UNDERFLOW     -4      // Stack leer
#define NEGATIVE_INPUT      -5      // negative Zahl wurde eingegeben
#define EMPTY_FIELD         -6      // Feld im Stack nicht belegt

#endif