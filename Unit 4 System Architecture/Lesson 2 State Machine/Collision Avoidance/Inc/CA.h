/*
 * CA.h
 *
 *  Created on: Sep 6, 2023
 *      Author: Ahmed Melik Alnasser
 */

#ifndef CA_H_
#define CA_H_
#include "State.h"


//Define States

enum{
	CA_waiting,
	CA_driving
}CA_state_id;

//Declare states functions CA
STATE_define(CA_waiting);
STATE_define(CA_driving);


extern void (*CA_state)();


#endif /* CA_H_ */
