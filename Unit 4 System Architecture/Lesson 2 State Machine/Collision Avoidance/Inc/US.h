/*
 * CA.h
 *
 *  Created on: Sep 6, 2023
 *      Author: Ahmed Melik Alnasser
 */

#ifndef US_H_
#define US_H_

#include "State.h"


//Define States
enum
{
	US_busy
}US_state_id;


//Ultra-sonic prototypes
void US_init();
STATE_define(US_busy);
int US_Get_distance_random(int l, int r, int count);
//global to pointer
extern void (*US_state)();

#endif /* US_H_ */


