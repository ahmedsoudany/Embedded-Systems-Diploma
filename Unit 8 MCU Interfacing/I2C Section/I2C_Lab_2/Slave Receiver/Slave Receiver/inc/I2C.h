/*
 * I2C.h
 *
 * Created: 10/27/2023 9:56:36 AM
 *  Author: LEGION
 */ 


#ifndef I2C_H_
#define I2C_H_

/*************************************
*				INCLUDES			*
*************************************/
#include "avr/io.h"
/***************************************
*			CONFIGUARTIONS		       *
****************************************/
#undef F_CPU /*Remove previous definition*/
#define F_CPU 16000000UL/*16 MegaHz(16 Million)*/
#define PRESCALAR		1			/* 1 - 4 - 16 - 64 */

/************MASTER_SEND_STATUS_CODES********************/
#define MT_START					0x08
#define MT_R_START					0x10
#define MT_SLA_W_ACK				0x18
#define MT_SLA_W_NACK				0x20
#define MT_DATA_TRANS_ACK			0x28
#define MT_DATA_TRANS_NACK			0x30
#define MT_ARBIT_LOST   			0x38
/************SLAVE_RECEIVER_STATUS_CODES******************/
#define SR_SLA_W_ACK					0x60
#define SR_ARBIT_LOST 					0x68
#define SR_G_CALL_ACK					0x70
#define SR_SLA_W_NACK					0x78
#define SR_SLA_W_ACK_RET				0x80
#define SR_SLA_W_NACK_RET				0x88
/********************************************************/
/*						ENUMS		                    */
/********************************************************/
typedef enum
{
	PRESCALAR_1,
	PRESCALAR_4,
	PRESCALAR_16,
	PRESCALAR_64
}TWI_Prescaler;

typedef enum
{
	DISABLE,
	ENABLE
}TWI_Enable;

typedef enum
{
	OK,
	NOK
}ERROR_STATUS;
/********************************************************/
/*						STRUCT		                    */
/********************************************************/


/********************************************************/
/*						APIS		                    */
/********************************************************/

void TWI_Init(unsigned long SCL_F);
void TWI_Start(void);
void TWI_Write(unsigned char char_data);
void TWI_Stop(void);
void TWI_Set_Address(unsigned char address);
unsigned char TWI_Read(unsigned char ack);


#endif /* I2C_H_ */