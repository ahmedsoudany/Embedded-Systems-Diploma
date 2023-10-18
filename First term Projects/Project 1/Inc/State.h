/*
 * STATE.h
 *
 *  Created on: Oct 11, 2023
 *      Author: Ahmed Melik Alnasser 
 */

#ifndef STATE_H_
#define	STATE_H_

#include "Platform_Types.h"
#include "driver.h"


#define STATE_define(_stateFunc_) 		void ST_##_stateFunc_()
#define STATE(_stateFunc_)        		ST_##_stateFunc_

//States Connections
//Pressure Sensor ===> Main Algorithm
uint32_t set_pressure_val(void);
//Main Algorithm ===> Alarm Monitor
uint32_t HighPressure_detected(void);
//Alarm Monitor ===> Alarm Actuator
uint32_t AlarmStart(void);
//Alarm Monitor ===> Alarm Actuator
uint32_t AlarmStop(void);

#endif /* STATE_H_ */