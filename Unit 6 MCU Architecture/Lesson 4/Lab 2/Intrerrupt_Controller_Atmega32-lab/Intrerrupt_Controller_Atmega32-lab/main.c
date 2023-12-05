/*
 * Intrerrupt_Controller_Atmega32-lab.c
 *
 * Created: 9/18/2023 7:33:24 PM
 * Author : LEGION
 */ 
#define F_CPU 8000000UL
//#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


typedef volatile unsigned int vuint32;


//Global Interrupt address
#define INT_SREG    *(vuint32 *)(0x3F)
#define GOIO_Base 0x20
//External interrupt addresses
#define INT_MCUCR   *(vuint32 *)(GOIO_Base + 0x35)
#define INT_MCUCSR  *(vuint32 *)(GOIO_Base + 0x34)
#define INT_GICR    *(vuint32 *)(GOIO_Base + 0x3B)
#define INT_GIFR    *(vuint32 *)(GOIO_Base + 0x3A)

//GPIO Addresses
#define GPIO_PORTD  *(vuint32 *)(GOIO_Base + 0x12)
#define GPIO_DDRD   *(vuint32 *)(GOIO_Base + 0x11)
#define GPIO_PORTB  *(vuint32 *)(GOIO_Base + 0x18)
#define GPIO_DDRB   *(vuint32 *)(GOIO_Base + 0x17)



void GPIOB_PB2_input_init() //INT2 (External Interrupt 2 Input)
{
	//DDRB is written logic zero, Pin is configured as an input pin
	GPIO_DDRB &= ~(1<<2);
}
void GPIOD_PD2_input_init() //INT0 (External Interrupt 0 Input)
{
	//DDRD is written logic zero, Pin is configured as an input pin
	GPIO_DDRD &= ~(1<<2);
}
void GPIOD_PD3_input_init() //INT1 (External Interrupt 1 Input)
{
	//DDRD is written logic zero, Pin is configured as an input pin
	GPIO_DDRD &= ~(1<<3);
	 
}
void GPIOD_PD5_output_init() //INT0 (External Interrupt 0 Input)
{
	//DDRD is written logic zero, Pin is configured as an input pin
	GPIO_DDRD |= (1<<5);
}
void GPIOD_PD6_output_init() //INT1 (External Interrupt 1 Input)
{
	//DDRD is written logic zero, Pin is configured as an input pin
	GPIO_DDRD |= (1<<6);
}
void GPIOD_PD7_output_init() //INT1 (External Interrupt 1 Input)
{
	//DDRD is written logic zero, Pin is configured as an input pin
	GPIO_DDRD |= (1<<7);
}

int main(void)
{
	
	//External Interrupt Request 0 Enable
	INT_GICR |= (1<<6);
	//External Interrupt Request 1 Enable
	INT_GICR |= (1<<7);
	//External Interrupt Request 2 Enable
	INT_GICR |= (1<<5);
	
	//Interrupt Sense Control 0 (any logic)
	INT_MCUCR |= (1<<0);
	//MCUCR & ~(1<<1);
	//Interrupt Sense Control 1(rising edge)
	INT_MCUCR |= (1<<2);
	INT_MCUCR |= (1<<3);
	//Interrupt Sense Control 2(falling edge)
	INT_MCUCSR &= ~(1<<6);
    
	GPIOB_PB2_input_init();
	GPIOD_PD2_input_init();
	GPIOD_PD3_input_init();
	GPIOD_PD5_output_init();
	GPIOD_PD6_output_init();
	GPIOD_PD7_output_init();
	
	//The Global Interrupt Enable bit must be set for the interrupts to be enabled
	//INT_SREG |= (1<<7);
    sei();
	while (1) 
    {
		GPIO_PORTD &= ~(1<<5);
		GPIO_PORTD &= ~(1<<6);
		GPIO_PORTD &= ~(1<<7);
    }
}

ISR (INT0_vect)
{
	GPIO_PORTD |= (1<<5);
	_delay_ms(1000);
	//Clearing the Interrupt 0 flag
	GIFR |= (1<<6);
}
ISR (INT1_vect)
{
	GPIO_PORTD |= (1<<6);
	_delay_ms(1000);
	//Clearing the Interrupt 1 flag
	GIFR |= (1<<7);
	}
ISR (INT2_vect)
{
	GPIO_PORTD |= (1<<7);
	_delay_ms(1000);
	//Clearing the Interrupt 2 flag
	GIFR |= (1<<5);
}