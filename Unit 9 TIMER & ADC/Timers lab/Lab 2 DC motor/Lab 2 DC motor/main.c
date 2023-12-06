/*
 * Lab 2 DC motor.c
 *
 * Created: 10/25/2023 11:20:59 AM
 * Author : LEGION
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
	DDRD = 0x3;  //set bit 0 and bit 1
	
    /* Replace with your application code */
    while (1) 
    {
		PORTD |= (1<<0);	//motor rotation in clockwise direction
		_delay_ms(1000);
		
		PORTD &= ~(1<<0);	//motor stopped
		_delay_ms(100);
		
		PORTD |= (1<<1);	//motor rotation in anticlockwise direction
		_delay_ms(1000);
		
		PORTD &= ~(1<<1);	//motor stopped
		_delay_ms(100);
		
    }
}

