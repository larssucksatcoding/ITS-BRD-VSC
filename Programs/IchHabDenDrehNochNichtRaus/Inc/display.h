/**
  * @file       display.h
  * @author     Lars Müller-Stumpf, Noah Rajko
  * @date       Nov 2025
  * @brief      displaying Encoder Information
  */

#ifndef DISPLAY_H
#define DISPLAY_H

/**
  * @brief      initializes the display for output with start values and descriptions
  */
void init_display();

/**
  * @brief      updates the display (only changed values)
  */
void update();

/**
  * @brief      prints an error message to the display
  *
  * @param      char *e - String, error message
  * 
  * @return     void
  */
void print_error(char *e);

/**
  * @brief      initializes display
  * 
  * @return     void
  */
void init_Display(void);

/**
  * @brief      sets the Display to Error Mode (changes background color) 
  *             + clears Output
  * 
  * @return     void
  */
void setErrMode(void);

/**
  * @brief      sets the Display to Normal Mode(changes background color)
  *             + clears Output
  * 
  * @return     void
  */
void setNormalMode(void);

#endif

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */