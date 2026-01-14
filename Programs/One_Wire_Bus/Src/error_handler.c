/**
* @file     error.h
* @author   Lars Müller-Stumpf, Noah Rajko
* @date     Jan 2025
* @brief    error module
*/

#include "error_handler.h"
#include "LCD_GUI.h"
#include "LCD_general.h"
#include "fonts.h"
#include "commands.h"
#include "display.h"


static Coordinate c = {50, 150};
static const char *no_slave = "WO SIND MEINE SKLAVEN"; 
static Coordinate c2 = {120, 180};
static const char *dampfwalze = "ich brauche eine wilesco d 366";

void handle_the_hand_the_error_EXCLAMATION_MARK_NOW(int error){
    if (error == NO_SLAVE) {
        GUI_clear(GRED);
        GUI_disStr(c, no_slave, &Font24, GRED, RED);
        GUI_disStr(c2, dampfwalze, &Font12, GRED, BLUE);
        while (reset() == NO_SLAVE); // wir warten bis wir auf reset eine Nachricht bekommen.
        init_display();
        return;
    }
}

//EOF