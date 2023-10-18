/*
 * MainAlgorithm.c
 *
 *  Created on: Oct 11, 2023
 *      Author: Ahmed Melik Alnasser 
 */
 
#include "MainAlgorithm.h"


static  uint32_t MainAlgo_pVal = 0;
static  uint32_t threshold = 20;

STATE_define(MainAlgo_HighPressure)
{	
	//State id
	MainAlgo_stateid = MainAlgo_HighPressure;
	
	//taking reading from presuure sensor 
	MainAlgo_pVal = set_pressure_val(); 
	
	//update next state
	MainAlgo_state = STATE(MainAlgo_HighPressure);
}

//Send 1 to alarm mointor if high pressure detected
uint32_t HighPressure_detected(void)
{
	//Checking if pressure sensor exceeded the threshold 
	return (MainAlgo_pVal > threshold) ? 1 : 0;
}