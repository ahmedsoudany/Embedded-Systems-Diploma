/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Ahmed Melik Alnasser
 * @brief          : Main program body
 */

#include "Platform_Types.h"

#define SYSCTL_BASE 0x400FE000
#define GPIO_F_BASE 0x40025000

#define SYSCTL_RCGC2_R *((vuint32_t*)(0x400FE108))
#define GPIO_PF_DIR_R  *((vuint32_t*)(0x40025400))
#define GPIO_PF_DEN_R  *((vuint32_t*)(0x4002551C))
#define GPIO_PF_DATA_R *((vuint32_t*)(0x400253FC))
#define Bit_3 (1<<3)

int main()
{
	vuint32_t delay;
	SYSCTL_RCGC2_R = 1<<5;
	for(delay = 0 ; delay < 10000; delay++);
	GPIO_PF_DIR_R |= 1<<3;
    GPIO_PF_DEN_R |= 1<<3;

    while(1)
    {
    	GPIO_PF_DATA_R |= 1<<3;
    	for(delay = 0 ; delay < 100000; delay++);
    	GPIO_PF_DATA_R &= ~(1<<3);
    	for(delay = 0 ; delay < 100000; delay++);

    }

	return 0;
}
