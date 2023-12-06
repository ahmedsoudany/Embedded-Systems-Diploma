/*
 * I2C.c
 *
 * Created: 10/27/2023 9:56:22 AM
 *  Author: LEGION
 */ 
/********************************************************/
/*						INCLUDE		                    */
/********************************************************/

#include "I2C.h"

/********************************************************/
/*						GLOABLS		                    */
/********************************************************/


/********************************************************/
/*					APIS_IMPLEMENTAIONS	                */
/********************************************************/

void TWI_Init(unsigned long SCL_F)
{
	TWBR = (unsigned char) (((F_CPU / SCL_F) - 16) / (2 * PRESCALAR));
	
	if(1 == PRESCALAR)
	{
		TWSR = 0;
	}
	else if(4 == PRESCALAR)
	{
		TWSR = 1;
	}
	else if(16 == PRESCALAR)
	{
		TWSR = 2;
	}
	else if(64 == PRESCALAR)
	{
		TWSR = 3;
	}
	
	
}
void TWI_Start(void)
{
	TWCR |= ( (1<<TWINT)| (1<<TWSTA) | (1<<TWEN)  );
	while( (TWCR & (1 << 7)) == 0 );
	while((TWSR ) != 0x08);
}
void TWI_Write(unsigned char char_data)
{
	TWDR = char_data;
	TWCR |= (1<<TWINT) | (1<<TWEN) ;
	while((TWCR & 0x80) == 0);
}
void TWI_Stop(void)
{
	TWCR = ( (1<<TWINT)| (1<<TWSTO) | (1<<TWEN) );
}

void TWI_Set_Address(unsigned char address)
{
	/* Sending Slave address */
	TWAR = address;
}
unsigned char TWI_Read(unsigned char ack)
{
	//unsigned char x;
	
	
	TWCR = ( (1<<TWINT) | (1<<TWEN) | (ack<<TWEA) );
	//while( (TWCR & (1<<7)) == 0);
	//while((TWSR ) != 0x60)
	//x = TWSR;
	//TWCR = ( (1<<TWINT) | (1<<TWEN) | (1<<TWEA) );
	//while( (TWCR & (1<<7)) == 0);
	while((TWCR & 0x80) == 0);
	//x = TWSR;
	
	//return TWDR;
	
}