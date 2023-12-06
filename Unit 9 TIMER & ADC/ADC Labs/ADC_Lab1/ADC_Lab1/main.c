/*
 * ADC_Lab1.c
 *
 * Created: 10/24/2023 8:31:09 PM
 * Author : LEGION
 */ 


#define F_CPU 1000000UL
#include <avr/io.h>
#include "util/delay.h"
#include <avr/interrupt.h>

int main(void)
{
	DDRC = 0xFF; //make port C an output for 7seg
	DDRD = 0xFF; //make port D an output for 7seg
	DDRA = 0;	 //make port A input for ADC input
	
	//Internal 2.56V Voltage Reference with external capacitor at AREF pin and select channel 0
	ADMUX = ( (1<<REFS0) | (1<<REFS1) );  //ADMUX = 0b11 << 6;
	//ADC Prescaler ==> 128 and Enable ADC
	ADCSRA = ( (0b111 << 0) | (1<<ADEN) ); 
    /* Replace with your application code */
    while (1) 
    {
		//Start conversion
		ADCSRA |= (1<<ADSC);
		//wait for conversion to finish
		while( (ADCSRA & (1 << ADIF)) == 0); //ADC interrupt flag
		PORTD = ADCL;  // low byte  ==> PORTD
		PORTC = ADCH;  // high byte ==> PORTC
		 
    }
	
	return 0;
}

