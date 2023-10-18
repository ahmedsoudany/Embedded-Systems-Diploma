/*
 * LIFO.h
 *
 *  Created on: Oct 10, 2023
 *      Author: Ahmed Melik Alnasser
 */

#ifndef LIFO_H_
#define LIFO_H_

//Includes

#include "stdio.h"
#include "stdlib.h"

//Data type for buffer
#define element_datatype uint32_t

//Typedef
typedef unsigned char uint8_t;
typedef unsigned int  uint32_t;

typedef struct
{
	element_datatype* base;
	element_datatype* head;
	unsigned int length;
	unsigned int count;
}LIFO_BUF_st;



typedef enum
{
	LIFO_null,
	LIFO_error,
	LIFO_no_error,
	LIFO_full,
	LIFO_not_full,
	LIFO_empty,
	LIFO_not_empty
}LIFO_BUF_Status;


//=================================================================
//APIs

LIFO_BUF_Status LIFO_init(LIFO_BUF_st *lifo,element_datatype *buff,element_datatype buff_Lenght);
LIFO_BUF_Status LIF0_Push_Item(LIFO_BUF_st* lifo,element_datatype* item);
LIFO_BUF_Status LIF0_Pop_Item(LIFO_BUF_st* lifo,element_datatype* item);
LIFO_BUF_Status LIF0_Is_Buff_Full(LIFO_BUF_st* lifo);
LIFO_BUF_Status LIF0_Is_Buff_EMPTY(LIFO_BUF_st* lifo);
LIFO_BUF_Status LIFO_print(LIFO_BUF_st *lifo);

#endif /* LIFO_H_ */
