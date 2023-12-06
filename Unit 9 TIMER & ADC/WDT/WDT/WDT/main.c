/*
 * WDT.c
 *
 * Created: 10/22/2023 7:58:12 PM
 * Author : LEGION
 */ 

//WDT


#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


#define SET_BIT(PORT,BIT)  (PORT |=  (1<<BIT))
#define CLR_BIT(PORT,BIT)  (PORT &= ~(1<<BIT))
#define TOG_BIT(PORT,BIT)  (PORT ^=  (1<<BIT))
#define GET_BIT(PORT,BIT)  (PORT &   (1<<BIT))

#define LED_DDR      DDRC
#define LED_PORT 	PORTC

void WDT_OFF()
{
	//Watchdog Enable: write a logic one to WDTOE and WDE
	WDTCR |= (1<<WDE) | (1<<WDTOE);

	//Wait for four clock cycles


	//write a logic 0 to WDE. This disables the Watchdog
	WDTCR = 0x00;
}

void WDT_ON()
{
	//Watchdog Enable When the WDE is written to logic one, the Watchdog Timer is enabled
	WDTCR |= (1<<WDE);
	//The WDP2, WDP1, and WDP0 bits determine the Watchdog Timer prescaling when the Watchdog Timer is enabled

	CLR_BIT(WDTCR,WDP0);
	WDTCR |= (1<<WDP2) | (1<<WDP1);

}

int main()
{
	SET_BIT(LED_DDR,0);

	while(1)
	{
		WDT_ON();
		TOG_BIT(LED_PORT,0);
		_delay_ms(1020);
		WDT_OFF();
	}
}

