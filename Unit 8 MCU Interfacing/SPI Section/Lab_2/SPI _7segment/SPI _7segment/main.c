/*
 * SPI _7segment.c
 *
 * Created: 10/30/2023 8:58:48 AM
 * Author : LEGION
 */ 

#include <avr/io.h>
#define F_CPU		1000000UL
#include <util/delay.h>
#define MOSI		5
#define SCK			7
#define SS			4

void execute(unsigned char cmd,unsigned char data)
{
	/* PULL SS to Low */
	PORTB &= ~(1<<SS);
	/* Set cmd transmission */
	SPDR = cmd;
	/* Wait for cmd transmission */
	while( !(SPSR & (1<<SPIF)) );
	/* Set data transmission */
	SPDR = data;
	/* Wait for data transmission */
	while( !(SPSR & (1<<SPIF)) );
	/* Terminate the packet by pulling SS high */
	PORTB |= (1<<SS);
	
}
int main(void)
{
    unsigned char counter = 0;
	unsigned int index_display = 1;
	
	/* Set MOSI and SCK and SS output*/
	DDRB |= ( (1<<MOSI) | (1<<SCK) | (1<<SS) );
	/* Enable SPI as Master, SCK = Focs/16 */
	SPCR = ( (1<<SPE) | (1<<MSTR) | (1<<SPR0) );
	/* Decode all displays  ==> 1111111 */
	execute(0x09,0xFF);
	/* Set scan limit (digit 0 to digit 7) */
	execute(0x0B,0x07);
	/* Set Max intensity */
	execute(0x0A,0x0F);
	/* Turn display On */
	execute(0x0C,0x01); 
	while(1)
	{
		for(index_display = 1 ; index_display < 9 ; index_display++)
		{
			execute(index_display,counter++);
			
		}
		_delay_ms(1000);
	}
	return 0;
}

