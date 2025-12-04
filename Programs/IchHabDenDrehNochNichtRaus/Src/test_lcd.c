/**
* @file       test_lcd.c
* @author     Lars Müller-Stumpf, Noah Rajko
* @date       Nov 2025
* @brief      Test duration of lcd output
*/

#include "test_lcd.h"
#include "display.h"
#include "timer.h"
#include "time.h"


void lcd_shit(){
    GPIOE->ODR = 0b10000000;
    // update(12.34, 56.78);
    GPIOE->ODR = 0b00000000;
}