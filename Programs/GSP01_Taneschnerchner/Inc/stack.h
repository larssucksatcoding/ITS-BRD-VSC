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
 int pop(int* x);

 /*
 ****************************************************************************************
 *  @brief      Abrufen der obersten beiden Zahlen vom Stack
 *
 *  @param      Zielspeicherort der Variable
 *
 *  @return     0 -> hat geklappt, 4 -> Stack Underflow
 ****************************************************************************************/
int pop(int* x, int* y);

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
 *  @return     
 ****************************************************************************************/
int clearStack();

/*
 ****************************************************************************************
 *  @brief      
 *
 *  @param      
 *
 *  @return     
 ****************************************************************************************/
int showNumbers();

#endif

// EOF