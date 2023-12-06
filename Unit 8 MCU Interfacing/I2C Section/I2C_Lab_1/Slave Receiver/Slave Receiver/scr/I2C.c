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

ERROR_STATUS TWI_Init(unsigned long SCL_F)
{
	if(1 == PRESCALAR)
	{
		TWSR |= (0<<0);
	}
	else if(4 == PRESCALAR)
	{
		TWSR |= (1<<0);
	}
	else if(16 == PRESCALAR)
	{
		TWSR |= (2<<0);
	}
	else if(64 == PRESCALAR)
	{
		TWSR |= (3<<0);
	}
	
	TWBR = (unsigned char) (((F_CPU / SCL_F) - 16) / (2 * PRESCALAR));
}
ERROR_STATUS TWI_Start(void)
{
	/* Send START condition and set the TWINT to clear flag */
	TWCR = ( (1<<TWINT)| (1<<TWEN) | (1<<TWSTA) );
	/* Wait: Start Condition has been transmitted(TWINT Flag in TWCR is set) */
	while( !(TWCR & (1 << TWINT)) );
	// Check TWSR is == START condition
	while((TWSR & 0xF8) != MT_START);

}
ERROR_STATUS TWI_Write(unsigned char char_data)
{
	//Load SLA_W into TWDR Register.
	TWDR = char_data;
	//Clear TWINT bit in TWCR to start transmission of address
	TWCR = (1<<TWINT) | (1<<TWEN);
	// Wait: SLA+W has been transmitted(TWINT Flag in TWCR is set)
	while(! (TWCR & (1 << TWINT)) );
	// Check TWSR is updated
	while((TWCR & 0xF8) != SR_SLA_W_ACK_RET);

}
ERROR_STATUS TWI_Stop(void)
{
	// Transmit Stop Condition
	TWCR = ( (1<<TWINT)| (1<<TWEN) | (1<<TWSTO) );
}

ERROR_STATUS TWI_Set_Address(unsigned char address)
{
	/* Sending Slave address */
	TWAR = address;
}
unsigned char TWI_Read(unsigned char ack)
{
	/* TWEN must be written to one to enable the TWI */
	/* The TWEA bit must be written to one to enable	the ack of the device’s own slave address or the general call address */
	TWCR = ( (1<<TWINT) | (1<<TWEN) | (ack<<TWEA) );
	/* TWSTA and TWSTO must be written to zero */
	TWCR &= ( ~(1<<TWSTA) | ~(1<<TWSTO));
	/* Wait until TWINT Flag is set */
	while( !(TWCR & (1<<TWINT)) );
	/* Wait valid for status code can be read from TWSR */
	while((TWSR & 0xF8) != SR_SLA_W_ACK);
	//while((TWSR ) != SR_SLA_W_ACK);
	TWCR = ( (1<<TWINT) | (1<<TWEN) | (ack<<TWEA) );
	/* TWSTA and TWSTO must be written to zero */
	TWCR &= ( ~(1<<TWSTA) | ~(1<<TWSTO));
	/* Wait until TWINT Flag is set */
	while( !(TWCR & (1<<TWINT)) );
	/* Wait valid for status code can be read from TWSR */
	while((TWSR & 0xF8) != SR_SLA_W_ACK_RET);
	//while((TWSR ) != SR_SLA_W_ACK_RET);
	return TWDR;
	
}