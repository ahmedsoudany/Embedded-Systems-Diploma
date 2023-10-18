/*
 * LIFO.c
 *
 *  Created on: Oct 10, 2023
 *      Author: Ahmed Melik Alnasser
 */


#include "LIFO.h"

LIFO_BUF_Status LIFO_init(LIFO_BUF_st *lifo,element_datatype *buff,element_datatype buff_Lenght)
{

	if(!lifo || !buff || !buff_Lenght)
	{
		printf("Initialization for LIFO Buffer has Failed\n\n");
		return LIFO_null;
	}
	lifo->base = buff;
	lifo->head = lifo->base;
	lifo->length = buff_Lenght;
	lifo->count = 0;

	if(lifo->base || lifo->length)
	{
		printf("Initialization for LIFO Buffer has Succeed\n\n");
		return LIFO_no_error;
	}

	return LIFO_error;
}
LIFO_BUF_Status LIF0_Push_Item(LIFO_BUF_st* lifo,element_datatype* item)
{
	//check if pointer is valid
	if(LIF0_Is_Buff_Full(lifo)==LIFO_null || !item)
	{
		printf("LIFO push has Failed\n\n");
		return LIFO_null;
	}
	//check if buffer is full
	if(LIF0_Is_Buff_Full(lifo)==LIFO_full)
	{
		printf("LIFO Buffer is FULL\n\n");
		return LIFO_full;
	}
	*(lifo->head) = *item;
	lifo->head++;
	lifo->count++;

	return LIFO_no_error;
}
LIFO_BUF_Status LIF0_Pop_Item(LIFO_BUF_st* lifo,element_datatype* item)
{
	//check if pointer is valid
	if(LIF0_Is_Buff_EMPTY(lifo)==LIFO_null || !item)
	{
		printf("LIFO push has Failed\n\n");
		return LIFO_null;
	}

	//check if buffer is empty
	if(LIF0_Is_Buff_EMPTY(lifo)==LIFO_empty)
	{
		printf("LIFO Buffer is EMPTY\n\n");
		return LIFO_empty;
	}

	lifo->head--;
	*item = *(lifo->head);
	lifo->count--;

	return LIFO_no_error;
}
LIFO_BUF_Status LIF0_Is_Buff_Full(LIFO_BUF_st* lifo)
{
	//check if pointer is valid
	if(!lifo || !lifo->head || !lifo->base )
	{
		printf("LIFO is FULL has failed\n");
		return LIFO_null;
	}
	//check if buffer is empty
	if(lifo->count == lifo->length)
	{
		return LIFO_full;
	}

	return LIFO_not_full;
}
LIFO_BUF_Status LIF0_Is_Buff_EMPTY(LIFO_BUF_st* lifo)
{
	//check if pointer is valid
	if(!lifo || !lifo->head || !lifo->base )
	{
		printf("LIFO is EMPTY has failed\n");
		return LIFO_null;
	}
	//check if buffer is empty
	if(lifo->head == lifo->base)
	{
		return LIFO_empty;
	}

	return LIFO_not_empty;
}
LIFO_BUF_Status LIFO_print(LIFO_BUF_st *lifo)
{
	element_datatype *p_item;
	int i;
	p_item = lifo->base;
	if(!lifo || !lifo->base || !lifo->head)
	{
		printf("LIFO print has Failed\n\n");
		return LIFO_null;
	}

	//check if buffer is empty
	if(LIF0_Is_Buff_EMPTY(lifo)==LIFO_empty)
	{
		printf("LIFO Buffer is EMPTY\n\n");
		return LIFO_empty;
	}

	printf("=======Printing LIFO Buffer=======\n");
	for(i = 0 ; i < lifo->count ; i++,p_item++)
	{
		printf("%d \n",*p_item);

	}


	return LIFO_no_error;
}
