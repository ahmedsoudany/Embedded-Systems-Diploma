/*
 * Lab 1 Test servo motor.c
 *
 * Created: 10/25/2023 10:50:30 AM
 * Author : LEGION
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
	DDRC = 0x01;
	PORTC = 0X00;
	
    /* Replace with your application code */
    while (1) 
    {
		//Rotate Motor to 0 degree
		PORTC |= (1<<0);
		_delay_ms(1);		//1ms
		PORTC &= ~(1<<0);
		
		_delay_ms(2000);		//20ms
		
		//Rotate Motor to 90 degree
		PORTC |= (1<<0);
		_delay_ms(1.5);		//1.5ms
		PORTC &= ~(1<<0);
		
		_delay_ms(2000);		//20ms
		
		//Rotate Motor to 180 degree
		PORTC |= (1<<0);
		_delay_ms(2.1);		//2ms
		PORTC &= ~(1<<0);
		
		_delay_ms(2000);		//20ms
    }
}

