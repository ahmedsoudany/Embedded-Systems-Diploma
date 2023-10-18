/*
 * Psensor.c
 *
 *  Created on: Oct 11, 2023
 *      Author: Ahmed Melik Alnasser 
 */
 
#include "PressureSensor.h"

static uint32_t PS_Val;

STATE_define(PS_init)
{
	//init sensor
	PS_stateid = PS_init;
	
	//update state
	PS_state = STATE(PS_reading);
}
STATE_define(PS_reading)
{
	//State id
	PS_stateid = PS_reading;
	//take reading from sensors and save it in pVal
	PS_Val = getPressureVal();
	
	//wait for timer to finish 
	PS_state = STATE(PS_waiting);

}
STATE_define(PS_waiting)
{
	//State id
	PS_stateid = PS_waiting;

	//Set timer for next value reading 
	Delay(1000);
	
	//Update state
	PS_state = STATE(PS_reading);
}

//Send pressure value to main algorithm
uint32_t set_pressure_val(void)
{
	return PS_Val;
}
