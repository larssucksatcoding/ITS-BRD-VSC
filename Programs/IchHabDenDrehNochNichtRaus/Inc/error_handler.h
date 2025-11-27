/**
  * @file       error_handler.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Nov 2025
  * @brief      contains Error Code definition and error handler
  */

#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

/*  ERROR CODES ------------------------------------*/
#define   NO_ERROR      0         // no error occurred
#define   DIR_ERROR     -1        // phase has been skipped


/**
  * @brief      deals with errors, outputs messages on display, returns to normal mode, when finished
  *
  * @param      integer error - Errorcode, der gecheckt werden soll
  */
void handle_error(int error);

#endif

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */