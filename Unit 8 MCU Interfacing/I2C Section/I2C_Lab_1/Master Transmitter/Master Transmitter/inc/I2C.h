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
#include "util/delay.h"
/*********************************************************
*						CONFIGUARTIONS					*
*********************************************************/
#undef F_CPU
#define F_CPU							8000000UL
#define PRESCALAR						4			/* 1 - 4 - 16 - 64 */
/************MASTER_SEND_STATUS_CODES********************/
#define MT_START						(unsigned char)0x08
#define MT_R_START						(unsigned char)0x10
#define MT_SLA_W_ACK					(unsigned char)0x18
#define MT_SLA_W_NACK					(unsigned char)0x20
#define MT_DATA_TRANS_ACK				(unsigned char)0x28
#define MT_DATA_TRANS_NACK				(unsigned char)0x30
#define MT_ARBIT_LOST   				(unsigned char)0x38
/************SLAVE_RECEIVER_STATUS_CODES******************/
#define SR_SLA_W_ACK					(unsigned char)0x60
#define SR_ARBIT_LOST 					(unsigned char)0x68
#define SR_G_CALL_ACK					(unsigned char)0x70
#define SR_G_ARBIT_LOST					(unsigned char)0x78
#define SR_SLA_W_ACK_RET				(unsigned char)0x80
#define SR_SLA_W_NACK_RET				(unsigned char)0x88
/********************************************************/
/*						ENUMS		                    */
/********************************************************/
typedef enum
{
	OK,
	NOK
}ERROR_STATUS;

/********************************************************/
/*						APIS		                    */
/********************************************************/

ERROR_STATUS TWI_Init(unsigned long SCL_F);
ERROR_STATUS TWI_Start(void);
ERROR_STATUS TWI_Write(unsigned char char_data);
ERROR_STATUS TWI_Stop(void);
ERROR_STATUS TWI_Set_Address(unsigned char address);
unsigned char TWI_Read(unsigned char ack);

#endif /* I2C_H_ */