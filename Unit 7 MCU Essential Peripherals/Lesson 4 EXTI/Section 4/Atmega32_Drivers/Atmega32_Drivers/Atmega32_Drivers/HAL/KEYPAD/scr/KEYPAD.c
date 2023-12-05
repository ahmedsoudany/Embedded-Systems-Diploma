/*
 * KEYPAD.c
 *
 * Created: 11/9/2023 9:21:54 PM
 *  Author: LEGION
 */ 

#include "KEYPAD.h"

int key_pad_Row[] = {R0, R1, R2, R3}; //Rows
int key_pad_Col[] = {C0, C1, C2, C3}; //Columns

void keypad_Init()
{
	/*Set upper part of the keypad as input
	  this will be required to scan rows*/
	MCAL_GPIO_SET_PIN_DIR(KeypadPORT,R0,Input);
	MCAL_GPIO_SET_PIN_DIR(KeypadPORT,R1,Input);
	MCAL_GPIO_SET_PIN_DIR(KeypadPORT,R2,Input);
	MCAL_GPIO_SET_PIN_DIR(KeypadPORT,R3,Input);
	/*Set lower part of the keypad as output
	the part of the keypad port where the columns are connected*/
	MCAL_GPIO_SET_PIN_DIR(KeypadPORT,C0,Output);
	MCAL_GPIO_SET_PIN_DIR(KeypadPORT,C1,Output);
	MCAL_GPIO_SET_PIN_DIR(KeypadPORT,C2,Output);
	MCAL_GPIO_SET_PIN_DIR(KeypadPORT,C3,Output);
	/* Activate PUR for input 
	Send high signal for output */
	MCAL_GPIO_SET_PORT_VAL(KeypadPORT,High);
}

uint8_t keypad_GetKey()
{
	int i , j;
	for(i = 0 ; i < 4; i++)
	{
		/* Source current*/
		MCAL_GPIO_SET_PIN_VAL(KeypadPORT,key_pad_Col[0],High);
		MCAL_GPIO_SET_PIN_VAL(KeypadPORT,key_pad_Col[1],High);
		MCAL_GPIO_SET_PIN_VAL(KeypadPORT,key_pad_Col[2],High);
		MCAL_GPIO_SET_PIN_VAL(KeypadPORT,key_pad_Col[3],High);
		/* Send low signal to particular row of the keypad (Sink current) */

		MCAL_GPIO_SET_PIN_VAL(KeypadPORT,key_pad_Col[i],Low);
		for(j = 0 ; j < 4; j++)
		{
			/* check if key is pressed */
			if(!GETBIT(KeypadPIN,key_pad_Row[j]))
			{
				/* Single press */
				while(!GETBIT(KeypadPIN,key_pad_Row[j]))
				switch(i)
				{
					case(0):
					{
						if(j == 0) return '7';
						else if(j == 1) return '4';
						else if(j == 2) return '1';
						else if(j == 3) return '?';
						break;
					}
					case(1):
					{
						if(j == 0) return '8';
						else if(j == 1) return '5';
						else if(j == 2) return '2';
						else if(j == 3) return '0';
						break;
					}
					case(2):
					{
						if(j == 0) return '9';
						else if(j == 1) return '6';
						else if(j == 2) return '3';
						else if(j == 3) return '=';
						break;
					}
					case(3):
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
	return 'A';//Return 'A' if no key is pressed.
}
