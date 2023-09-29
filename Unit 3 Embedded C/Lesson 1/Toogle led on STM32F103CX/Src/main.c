/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Ahmed Melik Alnasser Said Ahmed
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

#include "stdio.h"


typedef volatile unsigned int vuint32_t;

#define RCC_BASE 		0x40021000
#define RCC_APB2ENR    *(vuint32_t *)(RCC_BASE   +   0x18)
#define RCC_IOPAEN      (1<<2)

#define GPIO_BASE		0x40010800
#define GPIO_PA_CRH    *(vuint32_t *)(GPIO_BASE + 0x04)
#define GPIO_PA_ODR    *(vuint32_t *)(GPIO_BASE + 0x0C)

typedef union
{
	vuint32_t all_fields;
	struct
	{
		vuint32_t reserved:13;
		vuint32_t P_13:1;
	}Pins;
}R_ODR_t;

volatile R_ODR_t *R_ODR = (volatile R_ODR_t *) (0x4001080C);
int main(void)
{
	vuint32_t delay;

	RCC_APB2ENR |= RCC_IOPAEN;

	GPIO_PA_CRH &= 0xFF0FFFFF;
	GPIO_PA_CRH |= 0x00200000;

	while(1)
	{
		R_ODR->Pins.P_13 = 1;
		for(delay = 0 ; delay < 10000 ; delay++);
		R_ODR->Pins.P_13 = 0;
		for(delay = 0 ; delay < 10000 ; delay++);
	}

	return 0;
}
