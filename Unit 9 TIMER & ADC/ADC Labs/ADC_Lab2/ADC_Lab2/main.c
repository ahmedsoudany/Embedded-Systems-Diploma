/*
 * ADC_Lab2.c
 *
 * Created: 10/24/2023 9:51:03 PM
 * Author : LEGION
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include "util/delay.h"
#include <avr/interrupt.h>

#define ACD_Converted_Data (*(volatile uint16_t *)(0x24)) //uint16_t* pointer to point on two bytes L & H

ISR(ADC_vect)
{
	PORTD = ACD_Converted_Data;  // low byte  ==> PORTD
	PORTC = ACD_Converted_Data >> 8;  // high byte ==> PORTC
	//Start conversion
	ADCSRA |= (1<<ADSC);
}
int main(void)
{
	DDRC = 0xFF; //make port C an output for 7seg
	DDRD = 0xFF; //make port D an output for 7seg
	DDRA = 0;	 //make port A input for ADC input
	sei();		//Enable global interrupt
	//Internal 2.56V Voltage Reference with external capacitor at AREF pin and select channel 0
	ADMUX = ( (1<<REFS0) | (1<<REFS1) );  //ADMUX = 0b11 << 6;
	//ADC Prescaler ==> 128 and Enable ADC and Enable interrupt
	ADCSRA = ( (0b111 << 0) | (1<<ADEN) | (1<<ADIE) );
	
	//Start conversion
	ADCSRA |= (1<<ADSC);
	while (1);	
	return 0;
}


