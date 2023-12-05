/*
 * Task 2.c
 *
 * Created: 9/23/2023 10:26:47 PM
 * Author : LEGION
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000UL


int main(void)
{
	DDRA |= 0xFF;
	//DDRA = 0xff;
	uint8_t count = 0;
	DDRB = 0x0;
	PORTB |= (1<<0); //pull-up resistor is activated.
	
	/* Replace with your application code */
	while (1)
	{
		
		if ( ((PINB & 1) == 0) & (count == 0) )
		{
			PORTA |= (1<<0);
			count++;
			//_delay_ms(3000);
			while(  (PINB & 1) == 0   );
		}
		
		if( ((PINB & 1) == 0) & (count == 1) )
		{
			PORTA |= (1<<1);
			count = 2;
			//_delay_ms(5000);
			while( ((PINB & 1) == 0) );
		}
		
		if (((PINB & 1) == 0)  & (count == 2) )
		{
			PORTA |= (1<<2);
			count++;
	
			//_delay_ms(5000);
			while(  (PINB & 1) ==0   );
		}
		if ( ((PINB & 1) == 0) & (count == 3) )
		{
			PORTA |= (1<<3);
			count++;
			//_delay_ms(5000);
			while(  (PINB & 1) == 0 );
		}
		if ( ((PINB & 1) == 0) & (count == 4) )
		{
			PORTA |= (1<<4);
			count++;
			
			//_delay_ms(5000);
			while(  (PINB & 1) == 0   );
		}
		if  ( ((PINB & 1) == 0) & (count == 5) )
		{
			PORTA |= (1<<5);
			count++;
			//_delay_ms(5000);
			while(  (PINB & 1) == 0  );
		}
		if ( ((PINB & 1) == 0) & (count == 6) )
		{
			PORTA |= (1<<6);
			count++;
			//_delay_ms(5000);
			while(  (PINB & 1) == 0  );
		}
		if ( ((PINB & 1) == 0) & (count == 7) )
		{
			PORTA |= (1<<7);
			count++;
			//_delay_ms(5000);
			while(  (PINB & 1) == 0  );
		}
		
	}
		return 0;
}

