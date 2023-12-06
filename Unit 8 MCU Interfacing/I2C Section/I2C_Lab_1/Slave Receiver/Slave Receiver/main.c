/*
 * Slave Receiver.c
 *
 * Created: 10/28/2023 2:05:10 PM
 * Author : LEGION
 */ 

#include <avr/io.h>


int main(void)
{
	DDRA = 0xFF;
	TWI_Set_Address(0b11010000);
    /* Replace with your application code */
    while (1) 
    {
		PORTA = TWI_Read(1);
    }
	return 0;
}

