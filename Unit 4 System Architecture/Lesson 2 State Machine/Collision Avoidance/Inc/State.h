/*
 * State.h
 *
 *  Created on: Sep 6, 2023
 *      Author: Ahmed Melik Alnasser
 */

#ifndef STATE_H_
#define STATE_H_

#include "stdio.h"
#include "stdlib.h"


//Automatic STATE Function generation
#define STATE_define(_stateFunc_) void ST_##_stateFunc_()
#define STATE(_stateFunc_)  ST_##_stateFunc_


//states connection
void US_distance_set(int d);
void DC_motor(int s);



#endif /* STATE_H_ */
