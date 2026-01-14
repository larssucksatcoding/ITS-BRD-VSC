/**
* @file     commands.h
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    implements commands of the bus protocol
*/

#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdbool.h>

/**
* @brief    initializes the module (resets field variables)
*/
void init_cmds();

/**
* @brief    executes search_ROM once. Gets ROM for one slave. 
*           stores Information in slave struct [] 
*           Code: F0h
*/
int search_ROM();

/**
* @brief    sends match ROM signal followed by ROM of current slave
*           Code: 55h
*/
void match_ROM();

/**
* @brief    sends conver_T signal to slave(s)
*           switches power mode to pull up for sufficient power supply
*           [PD0 and PD1 to 1]
*           Code: 44h
*/
void convert_T();

/**
* @brief    reads scratchpad from current slave
*           saves scratchpad data in struct
*           Code: BEh
*/
void read_scratchpad();

/**
* @brief    executes reset command
* 
* @return   error code (everything alright/ no slave detected)
*/
int reset();

/**
* @brief    returns whether we KNOW are slaves whose ROM Code hasn't
*           been saved by now
*           if we never executed Search_ROM succesfully WE DO NOT KNOW!
* 
* @return   true if there must be more ROM Codes we did not fully detect yet
*/
bool more_slaves();


#endif


