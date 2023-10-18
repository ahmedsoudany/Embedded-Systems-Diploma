/*
 * PRESSURESENSOR.h
 *
 *  Created on: Oct 11, 2023
 *      Author: Ahmed Melik Alnasser 
 */
 
#ifndef PRESSURESENSOR_H_
#define	PRESSURESENSOR_H_

#include "State.h"

//Define States
enum
{
	PS_init,
	PS_reading,
	PS_waiting
}PS_stateid;


//prototypes
STATE_define(PS_init);
STATE_define(PS_reading);
STATE_define(PS_waiting);

//global pointer to function
extern void (*PS_state)();

#endif /* PRESSURESENSOR_H_ */