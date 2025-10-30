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
  * @brief      füllt ein übergebens Array mit den Werten im Stack 
  *
  * @param      int[] Array der Größe MAX_SIZE oder getSize() des Stacks
  * 
  * @return     void
  */
void getCopyOfStack(int copy[]);

/**
  * @brief      Gibt aus, wie viele Elemente auf dem Stack liegen
  * 
  * @return     Anzahl der Elemente auf dem Stack
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
