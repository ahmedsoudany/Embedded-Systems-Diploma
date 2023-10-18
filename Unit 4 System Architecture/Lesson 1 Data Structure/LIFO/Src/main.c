/*
 * main.c
 *
 *  Created on: Oct 10, 2023
 *      Author: Ahmed Melik Alnasser
 */


#include "LIFO.h"

#define LIFO_Buff_Length 5


int main()
{
	LIFO_BUF_st LIFO_Uart;
	element_datatype Uart_Buff[LIFO_Buff_Length];
	int i;
	element_datatype temp;

	LIFO_init(&LIFO_Uart,Uart_Buff,LIFO_Buff_Length);

	printf("===========LIFO_Pushing=============\n");
	for(i = 0 ; i < LIFO_Buff_Length ; i++)
	{
		if(LIF0_Push_Item(&LIFO_Uart,&i) == LIFO_no_error)
		{
			printf("LIFO Push %d --- Succeed\n",i);
		}
		else
		{
			printf("LIFO Push %d --- Failed\n",i);
		}
	}

	if(LIFO_print(&LIFO_Uart) == LIFO_no_error)
	{
		printf("=====Printing Succeed========\n");
	}
	else if(LIFO_print(&LIFO_Uart) == LIFO_empty)
	{
		printf("=====LIFO_IS_EMPTY============");
	}
	else
	{
		printf("=====Printing Failed========\n");
	}


	printf("===========LIFO_Poping=============\n");
	for(i = 0 ; i < LIFO_Buff_Length ; i++)
	{
		if(LIF0_Pop_Item(&LIFO_Uart,&temp) == LIFO_no_error)
		{
			printf("LIFO Pop %d --- Succeed\n",temp);
		}
		else
		{
			printf("LIFO Pop %d --- Failed\n",temp);
		}
	}

	if(LIFO_print(&LIFO_Uart) == LIFO_no_error)
	{
		printf("=====Printing Succeed========\n");
	}
	else
	{
		printf("=====Printing Failed========\n");
	}


}


