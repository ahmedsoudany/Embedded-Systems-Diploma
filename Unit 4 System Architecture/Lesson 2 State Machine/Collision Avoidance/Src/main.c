/*
 * MAIN.C
 *
 *  Created on: Sep 6, 2023
 *      Author: Ahmed Melik Alnasser
 */


#include "CA.h"
#include "US.h"
#include "DC.h"

void setup()
{
	//init all drivers
	//init IRQ
	//init HAL US_Driver DC_Driver
	//init block
	//Set states pointers for each block
	US_init();
	DC_init();
	//Set States pointers for each block
	US_state = STATE(US_busy);
	DC_state = STATE(DC_idle);
}


void main()
{
	setup();

	while(1)
	{
		US_state();
		CA_state();
		DC_state();
	}

}
