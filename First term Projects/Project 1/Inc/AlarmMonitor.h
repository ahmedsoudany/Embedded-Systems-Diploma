/*
 * AlarmMonitor.h
 *
 *  Created on: Oct 11, 2023
 *      Author: Ahmed Melik Alnasser 
 */

#ifndef ALARMMONITOR_H_
#define	ALARMMONITOR_H_

#include "State.h"


//Define States
enum
{
	AlarmMonitor_Off,
	AlarmMonitor_On,
	AlarmMonitor_waiting
}AlarmMonitor_stateid;

//prototypes
STATE_define(AlarmMonitor_Off);
STATE_define(AlarmMonitor_On);
STATE_define(AlarmMonitor_waiting);

//global pointer to function
extern void (*Alarmmonitor_state)(void);

#endif /* ALARMMONITOR */
