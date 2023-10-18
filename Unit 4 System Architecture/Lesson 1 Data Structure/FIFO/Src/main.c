/*
 * main.c
 *
 *  Created on: Oct 10, 2023
 *      Author: Ahmed Melik Alnasser
 */


#include "FIFO.h"

void main()
{
	FIFO_Buffer_t FIFO_UART;
	element_type i , temp = 0;

	FIFO_init(&FIFO_UART,uart_buffer,width1);


	for (i = 0 ; i < 7 ; i++)
	{
		printf("FIFO Enqueue (%x) \n",i);
		if(FIFO_enqueue(&FIFO_UART,&i)== FIFO_no_error)
		{
			printf("FIFO Enqueue (%x) --------Done--------\n",i);
		}
		else
		{
			printf("FIFO Enqueue (%x) -------Failed-------\n",i);
		}

	}
	FIFO_print(&FIFO_UART);

	FIFO_dequeue(&FIFO_UART,&temp);
	printf("FIFO Dequeue: Data=%X \n",temp);

	FIFO_dequeue(&FIFO_UART,&temp);
	printf("FIFO Dequeue: Data=%X \n",temp);


	for (i = 0 ; i < 2 ; i++)
	{
		printf("FIFO Enqueue (%x) \n",i);
		if(FIFO_enqueue(&FIFO_UART,&i)== FIFO_no_error)
		{
			printf("FIFO Enqueue (%x) --------Done--------\n",i);
		}
		else
		{
			printf("FIFO Enqueue (%x) -------Failed-------\n",i);
		}

	}
	FIFO_print(&FIFO_UART);



}
