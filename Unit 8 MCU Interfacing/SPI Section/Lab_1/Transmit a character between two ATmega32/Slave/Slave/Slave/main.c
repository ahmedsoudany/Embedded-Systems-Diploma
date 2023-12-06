/*
 * Slave.c
 *
 * Created: 10/30/2023 7:24:51 AM
 * Author : LEGION
 */ 

#include <avr/io.h>
#define F_CPU		1000000UL
#include <util/delay.h>
#define DDR_SPI				DDRB
#define	DD_MOSI				5
#define	DD_SCK				7
#define	DD_SS				4
#define	DD_MISO				6
void SPI_SlaveInit(void)
{
	/* Set MISO output, all others input */
	DDR_SPI |= (1<<DD_MISO);
	DDR_SPI &= ~( (1<<DD_MISO) & (1<<DD_SCK) & (1<<DD_SS) );
	/* Enable SPI */
	SPCR |= (1<<SPE);
	/* Enable Slave mode */ 
	SPCR &= ~(1<<MSTR);
	
}
unsigned char SPI_SlaveReceive(unsigned char data)
{
	/* Start transmission */
	SPDR = data ;
	/* Wait for transmission complete */
	while( !(SPSR & (1<<SPIF)));

	return SPDR;
}
int main(void)
{
	/* Data to send output */ 
   	unsigned char ch;
	/* PORTA is output */ 
   	DDRA = 0xFF;
   	SPI_SlaveInit();
   	
   	for(ch = 255 ; ch > 0 ; ch--)
   	{
		/* Send data to Master */
		/* Show received data at PortA*/  
	   	PORTA = SPI_SlaveReceive(ch);
   	}
}

