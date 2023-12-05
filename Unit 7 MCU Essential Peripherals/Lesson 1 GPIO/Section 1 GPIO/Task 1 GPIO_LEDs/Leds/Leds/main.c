/*
 * Leds.c
 *
 * Created: 9/23/2023 10:33:00 PM
 * Author : LEGION
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000UL

void delay(unsigned int time)
{
	unsigned int i , j;
	for(int i = 0 ; i < time ; i++)
	for(int j = 0 ; j < 255 ; j++);
	
}
int main(void)
{
	DDRA = 0xFF;
	
	/* Replace with your application code */
	while (1)
	{
		PORTA |= (1<<0);
		_delay_ms(6000);
		PORTA |= (1<<1);
		_delay_ms(6000);
		PORTA |= (1<<2);
		_delay_ms(6000);
		PORTA |= (1<<3);
		_delay_ms(6000);
		PORTA |= (1<<4);
		_delay_ms(6000);
		PORTA |= (1<<5);
		_delay_ms(6000);
		PORTA |= (1<<6);
		_delay_ms(6000);
		PORTA |= (1<<7);
		_delay_ms(6000);
		PORTA &= ~(1<<7);
		_delay_ms(6000);
		PORTA &= ~(1<<6);
		_delay_ms(6000);
		PORTA &= ~(1<<5);
		_delay_ms(6000);
		PORTA &= ~(1<<4);
		_delay_ms(6000);
		PORTA &= ~(1<<3);
		_delay_ms(6000);
		PORTA &= ~(1<<2);
		_delay_ms(6000);
		PORTA &= ~(1<<1);
		_delay_ms(6000);
		PORTA &= ~(1<<0);
	}
}

