/*
 * FIFO.c
 *
 *  Created on: Oct 10, 2023
 *      Author: Ahmed Melik Alnasser
 */


#include "FIFO.h"


E_Buffer_status FIFO_init(FIFO_Buffer_t* fifo,element_type* buff,unsigned int buff_length)
{
	//check if buffer exists
	if(buff == NULL)
	{
		printf("Initialization for FIFO Buffer has Failed\n\n");
		return FIFO_null;
	}
	fifo->base = buff;
	fifo->head = fifo->base;
	fifo->tail = fifo->base;
	fifo->length = buff_length;
	fifo->count = 0;

	if(fifo->base && fifo->tail)
	{
		printf("Initialization for LIFO Buffer has Succeed\n\n");
		return FIFO_no_error;
	}

	return 0;

}


E_Buffer_status FIFO_enqueue(FIFO_Buffer_t * fifo,element_type *ENQ_Data)
{
	//check if FIFO exists
	if(!fifo->base || !fifo->head || !fifo->tail)
	{
		printf("FIFO Enqueue has Failed\n\n");
		return FIFO_null;
	}
	//check if FIFO is full
	if(FIFO_IS_BUFF_FULL (fifo) == FIFO_full)
	{
		printf("FIFO is FULL\n");
		return FIFO_full;
	}


	*(fifo->head) = *ENQ_Data;
	fifo->count++;

	//Circular FIFO
	if(fifo->head == (fifo->base + (fifo->length * sizeof(element_type))))
	{
		fifo->head = fifo->base;
	}
	else
	{
		fifo->head++;
	}

	return FIFO_no_error;

}


E_Buffer_status FIFO_dequeue(FIFO_Buffer_t * fifo,element_type* DEQ_Data)
{
	//check if FIFO exists
	if(!fifo->base || !fifo->head || !fifo->tail)
	{
		printf("FIFO Enqueue has Failed\n\n");
		return FIFO_null;
	}
	//check if FIFO is empty
	if(FIFO_IS_BUFF_EMPTY(fifo) == FIFO_empty)
	{
		printf("FIFO is empty \n");
		return FIFO_empty;
	}

	*DEQ_Data = *fifo->tail;
	fifo->count--;

	//Circular FIFO
	if(fifo->tail == (fifo->tail + (fifo->length * sizeof(element_type))))
	{
		fifo->tail = fifo->base;
	}
	else
	{
		fifo->tail++;

	}
	return FIFO_no_error;

}


E_Buffer_status FIFO_print(FIFO_Buffer_t* fifo)
{
	element_type* temp;
	int i;
	//check if FIFO is empty
	if(FIFO_IS_BUFF_EMPTY(fifo) == FIFO_empty)
	{
		printf("FIFO is empty\n");
		return FIFO_empty;
	}
	temp = fifo->tail;

	printf("\n==========FIFO_print=========\n");
	for(i = 0 ; i < fifo->count ; i++)
	{
		printf("\t %X \n",*temp);
		temp++;
	}

	printf("\n===============\n");

	return FIFO_no_error;

}
E_Buffer_status FIFO_IS_BUFF_FULL(FIFO_Buffer_t* fifo)
{
	//check if FIFO exists
	if(!fifo->base || !fifo->head || !fifo->tail)
	{
		printf("FIFO is FULL has failed\n");
		return FIFO_null;
	}
	if(fifo->count == fifo->length)
	{
		return FIFO_full;
	}


	return FIFO_no_error;

}
E_Buffer_status FIFO_IS_BUFF_EMPTY(FIFO_Buffer_t* fifo)
{
	//check if FIFO exists
	if(!fifo->base || !fifo->head || !fifo->tail)
	{
		printf("FIFO is EMPTY has failed\n");
		return FIFO_null;
	}
	if(fifo->count == 0)
	{

		return FIFO_empty;
	}


	return FIFO_no_error;
}
