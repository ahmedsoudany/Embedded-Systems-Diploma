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
#include "LCD.h"
#include "KEYPAD.h"


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

void UART_Init_test1()
{
	UART_Config uartCFG;
	uartCFG.BuadRate = UART_BaudRate_115200;
	uartCFG.HwFlowCtrl = UART_HwFlowCtrl_NONE;
	uartCFG.IRQ_Enable = UART_IRQ_Enable_NONE;
	uartCFG.P_IRQ_CallBack = NULL;
	uartCFG.Parity = UART_Parity__NONE;
	uartCFG.Payload_Length = UART_Payload_Length_8B;
	uartCFG.StopBits = UART_StopBits__1;
	uartCFG.UART_Mode = UART_Mode_TX_RX;

	MCAL_UART_Init(USART1, &uartCFG);
	MCAL_UART_GPIO_Set_Pins(USART1);

	while(1)
	{
		MCAL_UART_ReceiveData(USART1, &ch, Enable);
		MCAL_UART_SendData(USART1, &ch, Enable);
	}

}
void Ahmed_UART_IRQ_CallBack()
{
	MCAL_UART_ReceiveData(USART1, &ch, Disable);
	MCAL_UART_SendData(USART1, &ch, Enable);

}
void UART_Init_test2()
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

int main(void)
{

	clock_init();
	//UART_Init_test1();
	UART_Init_test2();

    /* Loop forever */
	while(1)
	{
	}
}