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
  *
  * @param      double angle - recently calculated angle
  * @param      double angular_momentum
  */
void update(double angle, double angular_momentum);


void print_error(char *e);

void init_Display(void);

void setErrMode(void);

void setNormalMode(void);

#endif

/**
  * @brief      -
  *
  * @param      -
  * 
  * @return     -
  */