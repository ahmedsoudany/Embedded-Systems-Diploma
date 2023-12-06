/*
 * Master Transmitter.c
 *
 * Created: 10/28/2023 2:02:46 PM
 * Author : LEGION
 */ 

#include "I2C.h"


int main(void)
{
	unsigned char ch = 0;
	DDRA = 0xFF;
	TWI_Init(0x48);
	
    /* Replace with your application code */
    while (1) 
    {
		_delay_ms(3000);
			TWI_Start();
			TWI_Write(0b11010000+1); // transmit SLA+Write(0)
			ch = TWI_Read(0);
			TWI_Stop();
			PORTA = ch;
    }
	
	return 0;
}

