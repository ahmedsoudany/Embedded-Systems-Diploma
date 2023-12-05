/*
 * KEYPAD.h
 *
 * Created: 11/9/2023 9:21:43 PM
 *  Author: LEGION
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "DataTypes.h"
#include "MemoryMap.h"
#include "Utils.h"
#include "GPIO.h"


#define R0		PIN0
#define R1		PIN1
#define R2		PIN2
#define R3		PIN3
#define C0		PIN4
#define C1		PIN5
#define C2		PIN6
#define C3		PIN7

#define KeypadPORT	PortD
#define KeypadPIN	PIND
#define KeypadDDR	DDRD

void keypad_Init();
uint8_t keypad_GetKey();


#endif /* KEYPAD_H_ */