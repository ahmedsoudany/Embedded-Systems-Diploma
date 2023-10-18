/*
 * CA.c
 *
 *  Created on: Sep 6, 2023
 *      Author: Ahmed Melik Alnasser
 */


#include "US.h"

//Global variables

int US_distance = 0;

void (*US_state)();

void US_init()
{
	//Ultrasonic sensor initilization
	//Call the U	S drivers
	printf("Ultrasonic init \n");

}

int US_Get_distance_random(int l, int r, int count)
{
	//This function will generate random number in range l and r
	int  i, rand_num;
	for(i = 0; i < count; i++)

		rand_num = ((rand() % (r - l + 1)) + l);

	return  rand_num;
}

STATE_define(US_busy)
{

	//state action
	US_state_id = US_busy;
	//take reading from sensor
	US_distance = US_Get_distance_random(45, 55, 1);

	printf("US_busy_state: distance=%d \n",US_distance);
    //Send reading to CA module
	US_distance_set(US_distance);
	//return to busy state
	US_state = STATE(US_busy);

}
