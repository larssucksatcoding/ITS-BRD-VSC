/**
  * @file       operator.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Oct 2025
  * @brief      header file of operator module
  */

#ifndef OPERATOR_H
#define OPERATOR_H


// Hallo lieber Lars, ich bin zu faul mir deinen Kot in der C Datei anzuschauen,
// deswegen bidde bidde kommentieren, habe schonmal Templates eingefügt. 
/**
  * @brief      adds the top two numbers from the stack defined in stack.h.
  *             performes arrithmetic overflow checks and returns an error
  *             in return value if applicable.          
  *
  * @param      int* call-by-reference that result will be written to.
  * 
  * @return     one of the error codes defined in errno.h
  */
int add(int* result);

/**
  * @brief      takes the top two numbers from the stack defined in stack.h
  *             and subtracts the upper from the lower one (2nd - 1st).
  *             performes arrithmetic overflow checks and returns an error
  *             in return value if applicable.   
  *
  * @param      int* call-by-reference that result will be written to.
  * 
  * @return     one of the error codes defined in errno.h
  */
int subtract(int* result);

/**
  * @brief      divides the top two numbers from the stack defined in stack.h
  *             and divides the upper from the lower one (2nd / 1st).
  *             performes arrithmetic overflow checks and returns an error
  *             in return value if applicable.   
  *
  * @param      int* call-by-reference that result will be written to.
  * 
  * @return     one of the error codes defined in errno.h
  */
int divide(int* result);

/**
  * @brief      multiplies the top two numbers from the stack defined in stack.h.
  *             performes arrithmetic overflow checks and returns an error
  *             in return value if applicable.   
  *
  * @param      int* call-by-reference that result will be written to.
  * 
  * @return     one of the error codes defined in errno.h
  */
int multiply(int* result);

#endif
