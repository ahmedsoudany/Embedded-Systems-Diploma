/*
 * AlarmActuator.c
 *
 *  Created on: Oct 11, 2023
 *      Author: Ahmed Melik Alnasser 
 */

#include "AlarmActuator.h"


STATE_define(AlarmActuator_init)
{
	//State id
	AlarmActuator_stateid = AlarmActuator_init;
	
	//update state
	AlarmActuator_state = STATE(AlarmActuator_waiting);
}
STATE_define(AlarmActuator_waiting)
{
	//State id
	AlarmActuator_stateid = AlarmActuator_waiting;
	
	
	if(AlarmStart() == TRUE)
	{
		AlarmActuator_state = STATE(AlarmActuator_On);
	}
	
	else if(AlarmStop() == FALSE)
	{
		AlarmActuator_state = STATE(AlarmActuator_Off);
	}
	else
	{
		AlarmActuator_stateid = AlarmActuator_waiting;
	}
	
	
}
STATE_define(AlarmActuator_On)
{
	//State id
	AlarmActuator_stateid = AlarmActuator_On;
	
	//Actuator On
	Set_Alarm_actuator(TRUE);
	
	//update state
	AlarmActuator_state = STATE(AlarmActuator_waiting);
}
STATE_define(AlarmActuator_Off)
{
	//State id
	AlarmActuator_stateid = AlarmActuator_Off;
	
	//Actuator Off
	Set_Alarm_actuator(FALSE);
	
	//update state
	AlarmActuator_state = STATE(AlarmActuator_waiting);
}

