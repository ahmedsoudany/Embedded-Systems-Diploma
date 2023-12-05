/*
 * KEYPAD.c
 *
 *  Created on: Nov 15, 2023
 *      Author: LEGION
 */


#include "KEYPAD.h"


//-----------------------------
//Global Variables
//-----------------------------

int Keypad_Row[] = {R0 , R1 , R2 , R3};
int Keypad_Col[] = {C0 , C1 , C2 , C3};



/* ========================================== */
/*			 Functions Definitions 			  */
/* ========================================== */

void keypad_Init()
{
	GPIO_PinConfig_t PinCfg;


	/* All Rows and Columns are OUTPUT */
	PinCfg.GPIO_PinNumber = R0;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KeypadPORT, &PinCfg);

	PinCfg.GPIO_PinNumber = R1;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KeypadPORT, &PinCfg);

	PinCfg.GPIO_PinNumber = R2;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KeypadPORT, &PinCfg);

	PinCfg.GPIO_PinNumber = R3;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KeypadPORT, &PinCfg);

	PinCfg.GPIO_PinNumber = C0;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KeypadPORT, &PinCfg);

	PinCfg.GPIO_PinNumber = C1;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KeypadPORT, &PinCfg);

	PinCfg.GPIO_PinNumber = C2;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KeypadPORT, &PinCfg);

	PinCfg.GPIO_PinNumber = C3;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KeypadPORT, &PinCfg);

	/* Activate PUR for input
	   Send high signal for output */
	MCAL_GPIO_WritePort(KeypadPORT, 0xFF);

}
char keypad_GetKey()
{
	int i , j;

	/* loop ==> to find the Column */
	for(i = 0 ; i < 4 ; i++)
	{
		/* All Column PINS are SET to 1 */
		MCAL_GPIO_WritePin(KeypadPORT, Keypad_Col[0], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KeypadPORT, Keypad_Col[1], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KeypadPORT, Keypad_Col[2], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KeypadPORT, Keypad_Col[3], GPIO_PIN_SET);


		/* ONLY ONE Column is SET to 0 */
		/* To Check if pin is pressed */
		MCAL_GPIO_WritePin(KeypadPORT, Keypad_Col[i], GPIO_PIN_RESET);


		/* loop ==> to find the Row */
		for(j = 0 ; j < 4 ; j++)
		{

			if((MCAL_GPIO_ReadPin(KeypadPORT,Keypad_Row[j])) == 0)
			{
				/* Single pressed */
				while((MCAL_GPIO_ReadPin(KeypadPORT,Keypad_Row[j])) == 0);

				switch(i)
				{
					case 0:
					{
						     if(j == 0) return '7';
						else if(j == 1) return '4';
						else if(j == 2) return '1';
						else if(j == 3) return '?';
						break;
					}
					case 1:
					{
						     if(j == 0) return '8';
						else if(j == 1) return '5';
						else if(j == 2) return '2';
						else if(j == 3) return '0';
						break;
					}

					case 2:
					{
						     if(j == 0) return '9';
						else if(j == 1) return '6';
						else if(j == 2) return '3';
						else if(j == 3) return '=';
						break;
					}

					case 3:
					{
						     if(j == 0) return '/';
						else if(j == 1) return '*';
						else if(j == 2) return '-';
						else if(j == 3) return '+';
						break;
					}

				}

			}
		}
	}
	return 'A'; // Return 'A' if no key is pressed

}


