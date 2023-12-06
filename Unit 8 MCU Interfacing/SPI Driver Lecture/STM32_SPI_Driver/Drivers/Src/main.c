/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
#include "STM32F103x6.h"
#include "STM32F103C6_GPIO_Drivers.h"
#include "STM32F103C6_EXTI_Drivers.h"
#include "STM32F103C6_USART_Drivers.h"
#include "STM32F103C6_SPI_Drivers.h"
#include "LCD.h"
#include "KEYPAD.h"


#define MCU_Act_As_Master
//#define MCU_Act_As_Slave

unsigned char ch;

void wait_ms(int time)
{
	uint32_t i,j;
	for(i = 0; i < time; i++)
		for(j = 0; i < 255; j++);
}

void clock_init()
{
	//IO port A clock enable
	RCC_GPIOA_CLK_EN();
	//IO port B clock enable
	RCC_GPIOB_CLK_EN();
	//IO port AFIO clock enable
	RCC_AFIO_CLK_EN();
}


void Ahmed_UART_IRQ_CallBack()
{
#ifdef MCU_Act_As_Master
	MCAL_UART_ReceiveData(USART1, &ch, Disable);
	MCAL_UART_SendData(USART1, &ch, Enable);
	//Send to SPI
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	MCAL_SPI_TX_RX(SPI1, &ch, PollingEnable);
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
#endif

}
void UART_Init()
{
	UART_Config uartCFG;
	uartCFG.BuadRate = UART_BaudRate_115200;
	uartCFG.HwFlowCtrl = UART_HwFlowCtrl_NONE;
	uartCFG.IRQ_Enable = UART_IRQ_Enable_RXNEIE;
	uartCFG.P_IRQ_CallBack = Ahmed_UART_IRQ_CallBack;
	uartCFG.Parity = UART_Parity__NONE;
	uartCFG.Payload_Length = UART_Payload_Length_8B;
	uartCFG.StopBits = UART_StopBits__1;
	uartCFG.UART_Mode = UART_Mode_TX_RX;

	MCAL_UART_Init(USART1, &uartCFG);
	MCAL_UART_GPIO_Set_Pins(USART1);

}

void SPI_Init()
{
	SPI_Config SPICFG;

	SPICFG.CLKPhase = SPI_Clock_Phase_2EDGE_first_data_capture_edge;
	SPICFG.CLKPolartity = SPI_CLKPolartity_HIGH_when_idle;
	SPICFG.DataSize = SPI_DataSize_8BIT;
	SPICFG.Frame_Formate = SPI_Frame_Format_MSB_transmitted_first;
	//Assume by default pclk2 = 8MHZ
	SPICFG.SPI_BAUDRATEPRESCALAR = SPI_BAUDRATEORESCALAR_8;
	SPICFG.Communication_Mode = SPI_DIRECTION_2LINES;

#ifdef MCU_Act_As_Master
	SPICFG.Device_Mode = SPI_Device_Mode_MASTER;
	SPICFG.IRQ_Enable = SPI_IRQ_Enable_NONE;
	SPICFG.P_IRQ_CallBack = NULL;
	SPICFG.NSS = SPI_NSS_Soft_NSSINternalSoft_Set;

#endif

	MCAL_SPI_Init(SPI1, &SPICFG);
	MCAL_SPI_GPIO_Set_Pins(SPI1);

	GPIO_PinConfig_t PINCFG;
	//Configure SS 	on PA.4 by GPIO
	PINCFG.GPIO_PinNumber = GPIO_PIN_4;
	PINCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PINCFG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &PINCFG);
	SPICFG.NSS = SPI_NSS_Soft_NSSINternalSoft_Set;

	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

	while(1)
				{

				}


}

int main(void)
{

	//clock_init();
	//UART_Init();
	//SPI_Init();

	//IO port A clock enable
		RCC_GPIOA_CLK_EN();
		//IO port B clock enable
		RCC_GPIOB_CLK_EN();
		//IO port AFIO clock enable
		RCC_AFIO_CLK_EN();

		UART_Config uartCFG;
			uartCFG.BuadRate = UART_BaudRate_115200;
			uartCFG.HwFlowCtrl = UART_HwFlowCtrl_NONE;
			uartCFG.IRQ_Enable = UART_IRQ_Enable_RXNEIE;
			uartCFG.P_IRQ_CallBack = Ahmed_UART_IRQ_CallBack;
			uartCFG.Parity = UART_Parity__NONE;
			uartCFG.Payload_Length = UART_Payload_Length_8B;
			uartCFG.StopBits = UART_StopBits__1;
			uartCFG.UART_Mode = UART_Mode_TX_RX;

			MCAL_UART_Init(USART1, &uartCFG);
			MCAL_UART_GPIO_Set_Pins(USART1);
#ifdef MCU_Act_As_Master
	MCAL_UART_ReceiveData(USART1, &ch, Disable);
	MCAL_UART_SendData(USART1, &ch, Enable);
	//Send to SPI
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	MCAL_SPI_TX_RX(SPI1, &ch, PollingEnable);
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
#endif

	SPI_Config SPICFG;

		SPICFG.CLKPhase = SPI_Clock_Phase_2EDGE_first_data_capture_edge;
		SPICFG.CLKPolartity = SPI_CLKPolartity_HIGH_when_idle;
		SPICFG.DataSize = SPI_DataSize_8BIT;
		SPICFG.Frame_Formate = SPI_Frame_Format_MSB_transmitted_first;
		//Assume by default pclk2 = 8MHZ
		SPICFG.SPI_BAUDRATEPRESCALAR = SPI_BAUDRATEORESCALAR_8;
		SPICFG.Communication_Mode = SPI_DIRECTION_2LINES;

	#ifdef MCU_Act_As_Master
		SPICFG.Device_Mode = SPI_Device_Mode_MASTER;
		SPICFG.IRQ_Enable = SPI_IRQ_Enable_NONE;
		SPICFG.P_IRQ_CallBack = NULL;
		SPICFG.NSS = SPI_NSS_Soft_NSSINternalSoft_Set;

	#endif

		MCAL_SPI_Init(SPI1, &SPICFG);
		MCAL_SPI_GPIO_Set_Pins(SPI1);

		GPIO_PinConfig_t PINCFG;
		//Configure SS 	on PA.4 by GPIO
		PINCFG.GPIO_PinNumber = GPIO_PIN_4;
		PINCFG.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		PINCFG.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &PINCFG);
		SPICFG.NSS = SPI_NSS_Soft_NSSINternalSoft_Set;

		MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

		while(1)
					{

					}



}