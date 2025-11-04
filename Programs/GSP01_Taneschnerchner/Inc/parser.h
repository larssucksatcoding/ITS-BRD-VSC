/**
  * @file       parser.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Oct 2025
  * @brief      
  */

#ifndef PARSER_H
#define PARSER_H

#include "token.h"

/**
  * @brief      maps user input tokens to module functions.
  *
  * @param      T_token input: user input token
  *             int* result:   when add/sub/div/mul was pressed will contain the
  *                            result of that operation.
  * 
  * @return     an error code as defined in errno.h
  */
int parse_token(T_token input, int* result);

#endif
