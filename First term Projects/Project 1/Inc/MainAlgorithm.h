/*
 * MainAlgo.h
 *
 *  Created on: Oct 11, 2023
 *      Author: Ahmed Melik Alnasser 
 */
 
#ifndef MAINALGORITHM_H_
#define	MAINALGORITHM_H_

#include "State.h"


//Define States
enum
{
	MainAlgo_HighPressure
}MainAlgo_stateid;

//prototype
STATE_define(MainAlgo_HighPressure);

//global pointer to function
extern void(*MainAlgo_state)();

#endif /* MAINALGORITHM_H_ */