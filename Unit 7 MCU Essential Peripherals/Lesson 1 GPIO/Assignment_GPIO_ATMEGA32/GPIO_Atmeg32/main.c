/*
 * GPIO_Atmeg32.c
 *
 * Created: 9/22/2023 11:03:21 AM
 * Author : LEGION
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL

void delay(unsigned int time)
{
	unsigned int i , j;
	for(i = 0 ; i < time ; i++)
	 for(j = 0 ; j < 1000 ; j++);
	
}
int main(void)
{
	DDRA |= (1<<0) | (1<<1) | (1<<2) | (1<<3);
	
    /* Replace with your application code */
    while (1) 
	{
		
		PORTA ^= (1<<0);
		delay(500);
		PORTA ^= (1<<1);
		delay(500);
		PORTA ^= (1<<2); 
		delay(500);
		PORTA ^= (1<<3);
		delay(1000);
		
		
    }
}

