//@ learn-in-depth.com
//Mastering Embedded Systems
// Ahmed Melik Alnasser

#include "uart.h"
#include "Platform_Types.h"

unsigned char string_buffer[100] = "learn-in-depth:Ahmed" ;
unsigned char const string_buffer_2[100] = "learn-in-depth" ;

void main(void)
{
	Uart_Send_string(string_buffer);
}	