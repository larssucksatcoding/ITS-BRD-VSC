/**
* @file     commands.h
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    implements commands of the bus protocol
*/

#ifndef COMMANDS_H
#define COMMANDS_H

/**
* @brief    executes search_ROM once. Gets ROM for one slave. 
*           stores Information in slave struct [] 
*           Code: F0h
*/
void search_ROM();

/**
* @brief    if only 1 slave on bus -> slave sends ROM
*           Code: 33h
*/
void read_ROM();

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


#endif


