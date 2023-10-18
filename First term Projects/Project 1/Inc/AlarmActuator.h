/*
 * AlarmActuator.h
 *
 *  Created on: Oct 11, 2023
 *      Author: Ahmed Melik Alnasser 
 */

#ifndef ALARMACTUATOR_H_
#define	ALARMACTUATOR_H_

#include "State.h"

//Define States
enum
{
	AlarmActuator_init,
	AlarmActuator_waiting,
	AlarmActuator_On,
	AlarmActuator_Off
}AlarmActuator_stateid;

//prototypes
STATE_define(AlarmActuator_init);
STATE_define(AlarmActuator_waiting); 	 	 
STATE_define(AlarmActuator_On);
STATE_define(AlarmActuator_Off);

//global pointer to function
extern void(*AlarmActuator_state)();

#endif /* ALARMACTUATOR_H_ */