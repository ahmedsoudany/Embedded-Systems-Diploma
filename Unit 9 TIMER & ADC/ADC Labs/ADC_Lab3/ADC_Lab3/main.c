/*
 * ADC_Lab3.c
 *
 * Created: 10/24/2023 10:47:12 PM
 * Author : LEGION
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include "util/delay.h"
#include <avr/interrupt.h>


ISR(ADC_vect)
{
	PORTD = ADCH;  // low byte  ==> PORTD
	//Start conversion
	ADCSRA |= (1<<ADSC);
}
int main(void)
{
	DDRD = 0xFF; //make port D an output for 7seg
	DDRA = 0;	 //make port A input for ADC input
	sei();		//Enable global interrupt
	//Internal 2.56V Voltage Reference with external capacitor at AREF pin and select channel 0
	ADMUX = ( (1<<REFS0) | (1<<REFS1) | (1<<ADLAR));  //ADMUX = 0b11 << 6;
	//ADC Prescaler ==> 128 and Enable ADC and Enable interrupt
	ADCSRA = ( (0b111 << 0) | (1<<ADEN) | (1<<ADIE) );
	
	//Start conversion
	ADCSRA |= (1<<ADSC);
	while (1);
	return 0;
}


