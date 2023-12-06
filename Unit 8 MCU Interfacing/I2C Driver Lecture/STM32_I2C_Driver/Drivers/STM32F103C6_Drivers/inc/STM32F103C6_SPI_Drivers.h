/*
 * STM32F103C6_SPI_Drivers.h
 *
 *  Created on: Nov 16, 2023
 *      Author: LEGION
 */

#ifndef INC_STM32F103C6_SPI_DRIVERS_H_
#define INC_STM32F103C6_SPI_DRIVERS_H_


#include "STM32F103x6.h"
#include "STM32F103C6_GPIO_Drivers.h"
#include "STM32F103C6_RCC_Drivers.h"


struct S_IRQ_SRC
{
	uint8_t TXE:1;	//TX buffer empty interrupt
	uint8_t RXNE:1; //RX buffer not empty interrupt
	uint8_t ERRI:1; //Error interrupt
	uint8_t Reserved:5;
};


typedef struct
{
	uint16_t	Device_Mode;			//Specifies the SPI operating mode @ref SPI_Device_Mode
	uint16_t	Communication_Mode;		//Specifies the SPI bidirectional mode state @ref SPI_Communication_Mode
	uint16_t 	Frame_Formate;			//Specifies the LSB or MSB @ref SPI_Frame_Format
	uint16_t 	DataSize;				//Specifies @ref SPI_DataSize
	uint16_t	CLKPolartity;			//@ref SPI_CLKPolartity
	uint16_t 	CLKPhase;				//@ref SPI_CLKPhase
	uint16_t 	NSS;				    //Specifies whether the NSS signal is managed by
	//hardware (NSS pin) or by Software using the SSI bitenable @ref SPI_NSS
	uint16_t	SPI_BAUDRATEPRESCALAR;	//Specifies the Baud Rate prescalar value which will be used to
	//Configure the transmit and receive SCK clock
	//This parameter can be a value of @ref SPI_BAUDRATEORESCALAR
	//@note The communication clock is derived from the master clock.
	//The slave cloxk does not need to be set
	//Take care you have to configure RCC to enter the correct clock to APB2 >>> to SPI1 , APB1 >>> to SPI2
	uint16_t	IRQ_Enable;				//@ref SPI_IRQ_Enable
	void(* P_IRQ_CallBack)(struct S_IRQ_SRC irq_src);			//Set the C function() which will be called once the IRQ Happen

}SPI_Config;

// *================================================================================
// Reference Macros
// *================================================================================

//@ref SPI_Device_Mode
#define SPI_Device_Mode_SLAVE						(0x00000000U)
#define SPI_Device_Mode_MASTER						(0x1U << 2) //CR1.MSTR :1: Master configuation
//@ref SPI_Communication_Mode
#define SPI_DIRECTION_2LINES						(0x00000000U)
#define SPI_DIRECTION_2LINES_RXONLY					(0x1U << 10)				//CR1. Bit 10 RXONLY: Receive only

#define SPI_DIRECTION_1LINES_receive_only			(0x1U << 15)				//CR1. Bit 15 BIDIMODE: Bidirectional data mode enable
#define SPI_DIRECTION_2LINES_transmit_only			(0x1U << 15) | (0x1U << 14) //CR1. Bit 15 BIDIMODE: Bidirectional data mode enable & Bit 14 BIDIOE: Output enable in bidirectional mode
//@ref SPI_Frame_Format
#define SPI_Frame_Format_MSB_transmitted_first		(0x00000000U)
#define SPI_Frame_Format_LSB_transmitted_first		(0x1U << 7) 	//Bit 7 LSBFIRST: frame format
//@ref SPI_DataSize
#define SPI_DataSize_8BIT						(0x00000000U)
#define SPI_DataSize_16BIT						(0x1U << 11)	//CR1. Bit 11 DFF: Data frame format
//@ref SPI_CLKPolartity
#define SPI_CLKPolartity_LOW_when_idle				(0x00000000U)
#define SPI_CLKPolartity_HIGH_when_idle				(0x1U << 1)		//Bit1 CPOL: Clock polarity
//@ref SPI_CLKPhase
#define SPI_Clock_Phase_1EDGE_first_data_capture_edge	(0x00000000U)
#define SPI_Clock_Phase_2EDGE_first_data_capture_edge	(0x1U << 0) //Bit 0 CPHA: Clock Phase
//@ref SPI_NSS	SPI Slave Select Management
// =================================================
//Hardware
#define SPI_NSS_Hard_Slave 							(0x00000000U)
#define SPI_NSS_Hard_Master_SS_output_enable 		(0x1U<<2)		//SPI_CR2 Bit 2 SSOE:SS output enable
#define SPI_NSS_Hard_Master_SS_output_disable		~(0x1U<<2)		//SPI_CR2 Bit 2 SSOE:SS output disable

//NSS is driven By SW (Master or Slave)
#define SPI_NSS_Soft_NSSINternalSoft_Reset			(0x1U<<9)
#define SPI_NSS_Soft_NSSINternalSoft_Set			((0x1U<<9) | (0x1U<<8)) //For master and slave
//==================================================

//@ref SPI_BAUDRATEORESCALAR
#define SPI_BAUDRATEORESCALAR_2						(0x00000000U)
#define SPI_BAUDRATEORESCALAR_4						(0b001U << 3)
#define SPI_BAUDRATEORESCALAR_8						(0b010U << 3)
#define SPI_BAUDRATEORESCALAR_16					(0b011U << 3)
#define SPI_BAUDRATEORESCALAR_32					(0b100U << 3)
#define SPI_BAUDRATEORESCALAR_64					(0b101U << 3)
#define SPI_BAUDRATEORESCALAR_128					(0b110U << 3)
#define SPI_BAUDRATEORESCALAR_256					(0b111U << 3)

//@ref SPI_IRQ_Enable
#define SPI_IRQ_Enable_NONE							(uint32_t)(0)
#define SPI_IRQ_Enable_TXEIE						(uint32_t)(1<<7)	//SPI_CR2 Bit 7 TXEIE:  TX buffer empty interrupt enable
#define SPI_IRQ_Enable_RXNEIE						(uint32_t)(1<<6)	//SPI_CR2 Bit 7 RXNEIE: RX buffer not empty interrupt enable
#define SPI_IRQ_Enable_ERRIE						(uint32_t)(1<<5)	//SPI_CR2 Bit 5 ERRIE:  Error interrupt enable


enum Polling_mechanism
{
	PollingEnable,
	PollingDisable
};

/*
 * ==================================================================
 *				 APIs Supported by "MCAL USART DRIVER"
 * ==================================================================
 */

void MCAL_SPI_Init(SPI_TypeDef* SPIx,SPI_Config* SPI_Config);
void MCAL_SPI_DeInit(SPI_TypeDef* SPIx);

void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef* SPIx);

void MCAL_SPI_SendData(SPI_TypeDef *SPIx, uint16_t *pTxBuffer, enum Polling_mechanism PollingEn);
void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx, uint16_t *pRxBuffer, enum Polling_mechanism PollingEn);
void MCAL_SPI_TX_RX(SPI_TypeDef *SPIx, uint16_t *pRxBuffer, enum Polling_mechanism PollingEn);


#endif /* INC_STM32F103C6_SPI_DRIVERS_H_ */
