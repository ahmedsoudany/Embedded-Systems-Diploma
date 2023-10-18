/*
 * CA.h
 *
 *  Created on: Sep 6, 2023
 *      Author: Ahmed Melik Alnasser
 */

#ifndef DC_H_
#define DC_H_




#include "State.h"

//Define States

enum{
	DC_idle,
	DC_busy
}DC_state_id;

//DC prototypes
void DC_init();
STATE_define(DC_idle);
STATE_define(DC_busy);

extern void (*DC_state)();


#endif /* DC_H_ */
