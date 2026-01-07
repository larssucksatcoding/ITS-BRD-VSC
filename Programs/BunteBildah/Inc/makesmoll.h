/**
* @file       makesmoll.h
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Dec 2025
* @brief      makes a big picture small
*/

#ifndef MAKESMOLL_H
#define MAKESMOLL_H

#include "LCD_general.h"
#include "stdbool.h"

#define MAX_COMPRESSION_RATIO 5

int check_image_scaling_possible(bool* scale);

bool should_image_be_scaled();

int get_compression_ratio();

COLOR* get_compressed_line(COLOR* line);

/**
* @brief      -
*
* @param      -
* 
* @return     -
*/

#endif
