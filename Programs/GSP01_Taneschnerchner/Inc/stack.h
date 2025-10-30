/**
  * @file     stack.h
  * @author   Lars Müller-Stumpf, Noah Rajko
  * @date     Oct 2025
  * @brief    Header file of stack module 
  */

#ifndef STACK_H
#define STACK_H

/**
  * @brief      Speichert eine Nummer im Stack
  * 
  * @return     int Fehlercode
  */
int push(int v);

/**
  * @brief      Abrufen der obersten Zahl vom Stack 
  *
  * @param      int* Zielspeicherort der Variable
  * 
  * @return     int Fehlercode
  */
int pop(int* v);

 /**
  * @brief      vertauschen der oberen beiden Variablen auf dem Stack
  * 
  * @return     int Fehlercode
  */
int swapStack();

/**
  * @brief      dupliziere oberste Variable auf dem Stack
  * 
  * @return     int Fehlercode
  */
int duplStack();

/**
  * @brief      lösche alle Werte aus dem Stack
  * 
  * @return     void
  */
void deleteStack();

/**
  * @brief      gibt die oberste Zahl des Stack aus, ohne diese zu entfernen
  * 
  * @param      Zeiger auf Zeilspeicherort des Wertes
  * 
  * @return     int Fehlercode
  */
int getFirst(int* v);

/**
  * @brief      speichert den Wert 
  *
  * @param      int* val Zielspeicher des Wertes
  *
  * @param      int field Position im Stack
  * 
  * @return     Fehlercode 
  */
int peek(int* val, int field);

/**
  * @brief      Gibt aus, wie viele Elemente auf dem Stack liegen
  * 
  * @return     Größe des Stacks 
  */
int getSize();

/**
  * @brief      ~ ~ 
  *
  * @param      ~ ~
  * 
  * @return     ~ ~
  */
int popTopTwoElements(int* top, int* bottom);

#endif

// EOF
