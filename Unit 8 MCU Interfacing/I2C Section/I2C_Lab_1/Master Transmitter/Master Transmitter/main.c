/*
 * Master Transmitter.c
 *
 * Created: 10/28/2023 2:02:46 PM
 * Author : LEGION
 */ 

#include "I2C.h"


int main(void)
{
	unsigned ch = 0;
	
	TWI_Init(0x48);
    /* Replace with your application code */
    while (1) 
    {
		
		_delay_ms(2500);
		TWI_Start();
		TWI_Write(0b11010000+0);
		while( (TWSR & (0xF8)) !=  MT_SLA_W_ACK);
		TWI_Write(ch++);
		while( (TWSR & (0xF8)) !=  MT_DATA_TRANS_ACK);
		TWI_Stop();
		
		
		
    }
	return 0;
}

