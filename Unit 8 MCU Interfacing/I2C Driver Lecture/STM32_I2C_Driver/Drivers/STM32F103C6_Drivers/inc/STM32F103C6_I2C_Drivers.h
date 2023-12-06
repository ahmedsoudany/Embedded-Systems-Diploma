/*
 * STM32F103C6_I2C_Drivers.h
 *
 *  Created on: Nov 19, 2023
 *      Author: LEGION
 */

#ifndef INC_STM32F103C6_I2C_DRIVERS_H_
#define INC_STM32F103C6_I2C_DRIVERS_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6.h"
#include "STM32F103C6_GPIO_Drivers.h"
#include "STM32F103C6_RCC_Drivers.h"


//-----------------------------
//User type definitions (structures)
//-----------------------------

struct S_I2C_Slave_Device_Address
{
	uint16_t Enable_Dual_ADD;//1-Enable  0-Disable
	uint16_t Primary_slave_address;
	uint16_t Secondary_slave_address;
	uint32_t I2C_Addressing_Slave_Mode; // @ref I2C_Addressing_Slave_
};

typedef enum
{
	I2C_EV_STOP,
	I2C_ERROR_AF,
	I2C_EV_ADDR_Matched,
	I2C_EV_Data_REQ,	//The APP Layer should sent the data (I2C_SlaveSendData) in this state
	I2C_EV_Data_RCV		//The APP Layer should sent the data (I2C_SlaveReceiveData) in this state
}Slave_State;
typedef struct
{
	uint32_t								I2C_ClockSpeed;						/*!< Specifies the clock frequency.
														 	 	 	 	 	 	 	 This parameter must be set @ref 12c_SCLK_ */

	uint32_t 								Stretch_Mode;						//@ref I2C_StretchMode_


	uint32_t								I2C_Mode;							/*!< Specifies the I2C Mode.
														 	 	 	 	 	 	 	 This parameter must be set @ref I2C_Mode_ */


	struct S_I2C_Slave_Device_Address		I2C_Slave_Address;


	uint32_t								I2C_ACK_Control;					/*!< Enables or Disables the acknowledgement.
														 	 	 	 	 	 	 	 This parameter must be set @ref I2C_ACK_ */


	uint32_t								General_Call_Address_Detection;		/*!< Specifies the I2C General call.
														 	 	 	 	 	 	 	 This parameter must be set @ref I2C_ENGC */

	void(*P_Slave_Event_CallBack)(Slave_State state);							//Set the C Function() which will be called once the IRQ Happen



}I2C_InitTypedef;




// *================================================================================
// Reference Macros
// *================================================================================

//@ref 12c_SCLK_
//Supports different communication speeds:
//– Standard Speed (up to 100 kHz)
//– Fast Speed (up to 400 kHz)
//-to configure Clock before enable the peripheral
//–-- I2C_CR2.FREQ[5:0]: Peripheral clock frequency
//• Configure the clock control registers
//		Thigh = CCR * TPCLK1
// 		SM or FM
//• Configure the rise time register I2C_TRISE register

#define I2C_SCLK_SM_50K				(0x50000U)
#define I2C_SCLK_SM_100K			(100000U)
#define I2C_SCLK_SM_200K			(200000U) //Fast Mode Not Supported yet
#define I2C_SCLK_SM_400K			(400000U) //Fast Mode Not Supported yet

//@ref I2C_StretchMode_
//I2C_CR1
//Bit 7 NOSTRETCH: Clock stretching disable (Slave mode)
//0: Clock stretching enabled
//1: Clock stretching disabled

#define I2C_StretchMode_Enable				0x00000000U
#define I2C_StretchMode_Disable				I2C_CR1_NOSTRETCH



//@ref I2C_Mode_
//I2C_CR1
//Bit 1 SMBUS: SMBus mode
//0: I2C mode
//1: SMBus mode
#define I2C_Mode_I2C			0
#define I2C_Mode_SMBus			I2C_CR1_SMBUS


// @ref I2C_Addressing_Slave_
//I2C_OAR1.ADDMODE
//Bit 15 ADDMODE Addressing mode (slave mode)
//0: 7-bit slave address (10-bit address not acknowledged)
//1: 10-bit slave address (7-bit address not acknowledged)
#define I2C_Addressing_Slave_mode_7Bit			0x00000000U
#define I2C_Addressing_Slave_mode_8Bit			(uint16_t)(1U<<15)

//@ref I2C_ACK_
//Bit 10 ACK: Acknowledge enable
//This bit is set and cleared by software and cleared by hardware when PE=0.
//0: No acknowledge returned
//1: Acknowledge returned after a byte is received (matched address or data

#define I2C_ACK_Enable					(I2C_CR1_ACK)
#define I2C_ACK_Disable					((uint16_t)0x0000)

//@ref I2C_ENGC
//I2C_CR1
//Bit 6 ENGC: General call enable
//0: General call disabled. Address 00h is NACKed.
//1: General call enabled. Address 00h is ACKed.
#define I2C_ENGC_Enable 				(I2C_CR1_ENGC)
#define I2C_ENGC_Disable				(0x00000000U)


// * ===================================================================================

typedef enum
{
	With_Stop,
	Without_Stop
}Stop_Condition;

typedef enum
{
	Start,
	Repeated_start
}Repeated_Start;


typedef enum
{ DISABLE = 0 , ENABLE = 1}FunctionalState;
typedef enum{ RESET = 0 , SET = 1}FlagStatus;
typedef enum{I2C_Direction_Transmitter = 0 , I2C_Direction_Receiver = 1}I2C_Direction;

#define I2C_EVENT_MASTER_BYTE_TRANSMITTING			((uint32_t)0x00070080) /* TRA, BUSY, MSL, TXE flags */
typedef enum
{
	I2C_FLAG_BUSY = 0,
	EV5, 				// EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	EV6,			 	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2
	EV8,				//EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
	EV8_1,				//EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
	EV7,				//EV7: RxNE = 1cleared by reading DR register
	MASTER_BYTE_TRANSMITTING = ((uint32_t)0x00070080)					/* TRA, BUSY, MSL, TXE flags */
}Status;

/*
 * ==================================================================
 *				 APIs Supported by "MCAL I2C DRIVER"
 * ==================================================================
 */

void MCAL_I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypedef* I2C_InitStruct);
void MCAL_I2C_DeInit(I2C_TypeDef* I2Cx);

void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef* I2Cx);


//Master Polling Mechanism
void MCAL_I2C_Master_TX (I2C_TypeDef* I2Cx, uint16_t devAddr, uint8_t* dataout,uint32_t datalen, Stop_Condition Stop, Repeated_Start Start);
void MCAL_I2C_Master_RX (I2C_TypeDef* I2Cx, uint16_t devAddr, uint8_t* dataout,uint32_t datalen, Stop_Condition Stop, Repeated_Start Start);

//Slave Interrupt Mechanism
void MCAL_I2C_SlaveSendData(I2C_TypeDef* I2Cx, uint8_t data);
uint8_t MCAL_I2C_SlaveReceiveData(I2C_TypeDef* I2Cx);

//Generic APIS
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState, Repeated_Start Start);
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState);
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, Status Flag);
void I2C_SendAddres(I2C_TypeDef* I2Cx, uint16_t Address, I2C_Direction Direction);
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState);
void Slave_States(I2C_TypeDef* I2Cx, Slave_State State);



#endif /* INC_STM32F103C6_I2C_DRIVERS_H_ */
