/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Ahmed Melik Alnasser
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

typedef volatile unsigned int vuint32_t;

#define RCC_BASE       0x40021000
#define GPIO_PA_Base   0x40010800
#define RCC_APB2ENR    *(volatile unsigned int *)(RCC_BASE   +   0x18)
#define GPIO_PA_CRH    *(volatile unsigned int *)(GPIO_PA_Base + 0x04)
#define GPIO_PA_ODR    *(volatile unsigned int *)(GPIO_PA_Base + 0x0C)

#define RCC_IOPAEN     (1<<2)

typedef union
{
	vuint32_t All_Bits;
	struct{
		vuint32_t reserved:13;
		vuint32_t P_13:1;

	}Pins;
}R_ODR_t;

volatile R_ODR_t* R_ODR = (volatile R_ODR_t*) (0x4001080C);

int main(void)
{
	volatile int delay;

	RCC_APB2ENR |= RCC_IOPAEN;
	GPIO_PA_CRH &= 0XFF0FFFFF;
    GPIO_PA_CRH |= 0X00200000;

	while(1)
	{
		R_ODR->Pins.P_13 = 1;
	for(delay = 0 ; delay < 10000 ; delay++);
	  R_ODR->Pins.P_13 = 0;
    for(delay = 0 ; delay < 10000 ; delay++);
	}

	return 0;
}
