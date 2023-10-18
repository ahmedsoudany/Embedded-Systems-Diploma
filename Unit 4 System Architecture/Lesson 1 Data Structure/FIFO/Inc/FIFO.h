/*
 * FIFO.h
 *
 *  Created on: Oct 10, 2023
 *      Author: Ahmed Melik Alnasser
 */

#ifndef FIFO_H_
#define FIFO_H_
#include "stdio.h"
#include "stdint.h"


/*============================User configurations==============================*/
//Select the element type(uint8_t,uint16_t,uint32_t....)
#define element_type unsigned char

//Create buffer 1
#define width1 5
element_type uart_buffer [width1];

//Create buffer 2
#define width2 5
element_type buff [width2];
/*============================FIFO data types==================================*/
typedef struct
{
	unsigned int length;
	unsigned int count;
	element_type* base;
	element_type* head;
	element_type* tail;
}FIFO_Buffer_t;

typedef enum
{
	FIFO_no_error,
	FIFO_full,
	FIFO_empty,
	FIFO_null
}E_Buffer_status;

/*==============================================================================*/

/*==============================FIFO_APIs=======================================*/
E_Buffer_status FIFO_init(FIFO_Buffer_t* fifo,element_type* buff,unsigned int buff_length);
E_Buffer_status FIFO_enqueue(FIFO_Buffer_t* fifo,element_type* ENQ_Data);
E_Buffer_status FIFO_dequeue(FIFO_Buffer_t* fifo,element_type* DEQ_Data);
E_Buffer_status FIFO_IS_BUFF_FULL(FIFO_Buffer_t* fifo);
E_Buffer_status FIFO_IS_BUFF_EMPTY(FIFO_Buffer_t* fifo);
E_Buffer_status FIFO_print(FIFO_Buffer_t* fifo);

/*=============================================================================*/


#endif /* FIFO_H_ */
