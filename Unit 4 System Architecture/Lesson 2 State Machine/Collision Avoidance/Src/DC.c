/*
 * CA.c
 *
 *  Created on: Sep 6, 2023
 *      Author: Ahmed Melik Alnasser
 */


#include "DC.h"
//Global variables
int DC_speed = 0;

void (*DC_state)();

void DC_init()
{
	//DC motor initilization
	//Call DC drivers
	printf("DC init\n");
}

DC_motor(int s)
{
	DC_speed = s;

	DC_state = STATE(DC_busy);

	printf(" CA------speed=%d------->\n",DC_speed);
}

STATE_define(DC_idle)
{
	//state action
	DC_state_id = DC_idle;
	//Call PWM to make speed = DC_speed
	DC_state= STATE(DC_idle);

	printf("DC_ideal_state: speed=%d \n \n \n",DC_speed);

}
STATE_define(DC_busy)
{
	//state action
	DC_state_id = DC_busy;

	printf("DC_busy_state: speed=%d \n \n \n",DC_speed);

	//Call DC-Driver
	DC_state= STATE(DC_idle);
	

}
