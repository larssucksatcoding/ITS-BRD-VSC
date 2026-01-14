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
* @brief    tells slave to start measuring temperature
*           provides power + waits for slave 
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
* @return   error code 0 if no error, else 
*/
int reset();

/**
* @brief    checks if we there are ROM Codes on the bus, we did not save yet
* 
* @return   true if there, false if we detected all
*/
bool more_slaves();

#endif

//EOF