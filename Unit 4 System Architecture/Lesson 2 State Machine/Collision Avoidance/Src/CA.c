/*
 * CA.c
 *
 *  Created on: Sep 6, 2023
 *      Author: Ahmed Melik Alnasser
 */


#include "CA.h"

//Global variables
unsigned int CA_speed = 0  , CA_distance = 0 , CA_threshold = 50;

//State pointer to function
void (*CA_state)();

STATE_define(CA_waiting)
{
	CA_state_id = CA_waiting;
	printf("Waiting state: speed = %d distance = %d \n",CA_speed,CA_distance);
	//state action
	CA_speed= 0;
	//DC_motor(speed);
	DC_motor(CA_speed);
	//Take reading from sensor


	//US_Get_distance(CA_distance)
	///Event_Check

}
STATE_define(CA_driving)
{
	//State_Name
	CA_state_id = CA_driving;
	printf("Driving state: speed = %d distance = %d \n",CA_speed,CA_distance);

	//state action
	CA_speed = 30;
	//DC_Motor(CA_speed)
	DC_motor(CA_speed);


	//US_Get_distance(CA_distance)

	///Event_Check
}


US_distance_set( int d)
{
	CA_distance = d;
	(CA_distance <= CA_threshold) ? (CA_state = STATE(CA_waiting)) : (CA_state = STATE(CA_driving)) ;
	printf("US-----distance=%d----> CA \n",CA_distance);

}
