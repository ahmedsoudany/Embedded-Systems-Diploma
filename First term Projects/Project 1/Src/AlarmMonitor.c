/*
 * Alarmmonitor.c
 *
 *  Created on: Oct 11, 2023
 *      Author: Ahmed Melik Alnasser 
 */
 
#include "AlarmMonitor.h"

uint32_t On_Off = 0;
//uint32_t Off = 0;

STATE_define(AlarmMonitor_Off)
{
	//State id
	AlarmMonitor_stateid = AlarmMonitor_Off;
	
	//Send signal to Alarm Actuator (Stop alarm) 
	 On_Off = 0;
	
	// check if true then update next state
	if(HighPressure_detected() == TRUE)
	{
		Alarmmonitor_state = STATE(AlarmMonitor_On);
	}
}

STATE_define(AlarmMonitor_On)
{
	//State id
	AlarmMonitor_stateid = AlarmMonitor_On;
	//Send signal to actuator (start alarm)
	On_Off = 1;

	//update next state
	Alarmmonitor_state = STATE(AlarmMonitor_waiting);
}

STATE_define(AlarmMonitor_waiting)
{

	//State id
	AlarmMonitor_stateid = AlarmMonitor_waiting;
	
	//delay 
	Delay(6000);
	
	//update next state
	Alarmmonitor_state = STATE(AlarmMonitor_Off);
}



//Alarm Monitor ===> Alarm Actuator
uint32_t AlarmStart(void)
{
	return On_Off;
}
//Alarm Monitor ===> Alarm Actuator
uint32_t AlarmStop(void)
{
	return On_Off;
}



