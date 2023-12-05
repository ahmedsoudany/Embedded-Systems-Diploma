/*
 * Atmega32_Drivers.c
 *
 * Created: 11/9/2023 12:45:58 PM
 * Author : LEGION
 */ 

#include "GPIO.h"
#include "KEYPAD.h"
#include "LCD.h"



int main(void)
{
  
    LCD_lcd_init();
    LCD_Send_A_String("Learn in Depth");
	/* Replace with your application code */
    while (1)
    {
	    
    }
    
}

