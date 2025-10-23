/**
  * @file stack.h
  * @author Noah Rajko
  * @date Oct 2025
  * @brief Header file of stack module
  */

#ifndef STACK_H
#define STACK_H

// Größe des Stacks = 8


/*
 ****************************************************************************************
 *  @brief      Speichert eine Nummer im Stack
 *
 *  @param      
 *
 *  @return     0 -> hat geklappt, 3 -> Stack Overflow
 ****************************************************************************************/
int push(int v);

/*
 ****************************************************************************************
 *  @brief      Abrufen der obersten Zahl vom Stack
 *
 *  @param      Zielspeicherort der Variable
 *
 *  @return     0 -> hat geklappt, 4 -> Stack Underflow
 ****************************************************************************************/
int pop(int* v);

 
/*
 ****************************************************************************************
 *  @brief      vertauschen der oberen beiden Variablen auf dem Stack
 *
 *  @return     0 -> hat geklappt, 4 -> Stack Underflow
 ****************************************************************************************/
int swapStack();


/*
 ****************************************************************************************
 *  @brief      dupliziere oberste Variable auf dem Stack
 *
 *  @return     0 -> hat geklappt, 3 -> Stack Overflow, 4 -> Stack Underflow
 ****************************************************************************************/
int duplStack();


/*
 ****************************************************************************************
 *  @brief      lösche alle Werte aus dem Stack
 *
 *  @return     nüchts
 ****************************************************************************************/
void clearStack();

/*
 ****************************************************************************************
 *  @brief     gibt die oberste Zahl des Stack aus, ohne diese zu entfernen 
 *
 *  @return    oberste Zahl des Stacks
 ****************************************************************************************/
int getFirst();

/*
 ****************************************************************************************
 *  @brief      füllt ein übergebens Array mit den Werten im Stack
 *
 *  @param      Array der Größe MAX_SIZE oder getSize() des Stacks
 *
 *  @return     
 ****************************************************************************************/
void getCopyOfStack(int copy[]);

/*
 ****************************************************************************************
 *  @brief      Gibt aus, wie viele Elemente auf dem Stack liegen
 *
 *  @return     Anzahl der Elemente auf dem Stack
 ****************************************************************************************/
int getSize();


int popTopTwoElements(int* top, int* bottom);

#endif

// EOF
