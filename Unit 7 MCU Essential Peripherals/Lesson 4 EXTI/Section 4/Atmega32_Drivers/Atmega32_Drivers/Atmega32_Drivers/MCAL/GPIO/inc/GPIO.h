/*
 * GPIO.h
 *
 * Created: 11/9/2023 12:56:18 PM
 *  Author: LEGION
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include "DataTypes.h"
#include "MemoryMap.h"
#include "Utils.h"

typedef enum
{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7
}PIN_No_t;

typedef enum
{
	Input,
	Output
}PIN_Dir_t;

typedef enum
{
	High,
	Low
}PIN_Value_t;

typedef enum
{
	Output_status,
	Input_status
}PIN_Status_t;

typedef enum
{
	PortA,
	PortB,
	PortC,
	PortD
}GPIO_Port_t;


void MCAL_GPIO_SET_PIN_DIR(GPIO_Port_t Port,PIN_No_t Pin,PIN_Dir_t Dir);
void MCAL_GPIO_SET_PORT_DIR(GPIO_Port_t Port,PIN_Dir_t Dir);
void MCAL_GPIO_SET_PIN_VAL(GPIO_Port_t Port,PIN_No_t Pin,PIN_Value_t Val);
void MCAL_GPIO_SET_PORT_VAL(GPIO_Port_t Port,PIN_Value_t Val);
void MCAL_GPIO_GET_PIN_VAL(GPIO_Port_t Port,PIN_No_t Pin,PIN_Value_t* Val);
void MCAL_GPIO_GET_PORT_VAL(GPIO_Port_t Port,PIN_Value_t* Val);
void MCAL_GPIO_TOG_PIN(GPIO_Port_t Port,PIN_No_t Pin);
void MCAL_GPIO_TOG_PORT(GPIO_Port_t Port);


#endif /* GPIO_H_ */