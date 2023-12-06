/*
 * Master.c
 *
 * Created: 10/30/2023 7:10:46 AM
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
void SPI_Master_Init(void)
{
	/* Set MOSI and SCK output, all others input */
	DDR_SPI |= (1<<DD_MOSI) | (1<<DD_SCK) | (1<<DD_SS);
	DDR_SPI &= ~(1<<DD_MISO);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR |= (1<<SPE) | (1<<MSTR) |(1<<SPR0);
}
unsigned char SPI_Master_Transmit(unsigned char data)
{
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while( !(SPSR & (1<<SPIF)) );
	
	return SPDR;
}
int main(void)
{
	/* Data to send output */ 
	unsigned char ch;
	/* PORTA is output */ 
	DDRA = 0xFF;
	SPI_Master_Init();
	
   for(ch = 0 ; ch <= 255; ch++)
   {
	   _delay_ms(1000);
	   /* Send data to Slave */
	   /* Show received data at PortA*/
	   PORTA = SPI_Master_Transmit(ch);
   }
}

