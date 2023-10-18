//@ learn-in-depth.com
//Mastering Embedded Systems
//Ahmed Melik Alnasser
#include "uart.h"
#include "Platform_Types.h"
//Uart resgister
#define UART0DR *((vuint32_t* const)((uint32_t *)0x101f1000))
void Uart_Send_string(uint8_t *P_tx_string)
{
	while(*P_tx_string != '\0')
	{
		//Send char
		UART0DR = (uint32_t)(*P_tx_string);
		//point to next char
		P_tx_string++;
	}
}