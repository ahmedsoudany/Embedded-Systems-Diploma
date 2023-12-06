/*
 * Uart.c
 *
 * Created: 10/26/2023 2:05:39 PM
 *  Author: LEGION
 */ 

#include "Uart.h"

static unsigned char* TX_Str;
static unsigned char flag_send = 1;
static unsigned char* RX_Str;
static unsigned char flag_receive = 1;
void (*UART_RX_Fptr)(void);
void (*UART_TX_Fptr)(void);
void Uart_Init(void)
{
 
	//buad rate 9600
	UBRRL = 51;
	//Normal speed
	UCSRA &= ~(1<<U2X);
	
	//Frame
	//Default frame 8 data 1 stop parity
	
	//ENABLE
	UCSRB |= (1<<TXEN);
	UCSRB |= (1<<RXEN);
}

void Uart_Send(unsigned char data)
{
	
	while(!(UCSRA & (1<<UDRE)));
	 UDR = data;
}

unsigned char Uart_Receive()
{
	while(!(UCSRA & (1<<RXC)));
	return UDR;
}
void Uart_SendNumber(unsigned int num)
{
	//Uart_Send((unsigned char)num);
	//Uart_Send((unsigned char) (num>>8));
	//Uart_Send((unsigned char) (num>>16));
	//Uart_Send((unsigned char) (num>>24));
	unsigned char* ptr;
	ptr = &num;
	Uart_Send(ptr[0]);
	Uart_Send(ptr[1]);
	Uart_Send(ptr[2]);
	Uart_Send(ptr[3]);
	

}
unsigned int Uart_ReceiveNumber(void)
{
	//unsigned char b1 = Uart_Receive();
	//unsigned char b2 = Uart_Receive();
	//unsigned char b3 = Uart_Receive();
	//unsigned char b4 = Uart_Receive(); 
	//unsigned int num = 0;
	//num = b1 |(unsigned int) (b2<<8)|(unsigned int) (b2<<16)|(unsigned int) (b2<<24);
	unsigned int num;
	unsigned char *p = &num;
	p[0] = Uart_Receive();
	p[1] = Uart_Receive();
	p[2] = Uart_Receive();
	p[3] = Uart_Receive();
	
	return num;
	
}

void Send_Str(unsigned char* str)
{
	unsigned char i = 0;
	for(i = 0 ; i < str[i] ; i++)
	{
		Uart_Send(str[i]);
	}
	Uart_Send(DefaultStop); 
}

void Uart_RecStr(unsigned char* Buff)
{
	unsigned char i = 0;
	Buff[i] = Uart_Receive();
	while(Buff[i] != DefaultStop)
	{
		i++;
		Buff[i] = Uart_Receive();
	}
	Buff[i] = '\0';
}

unsigned char Uart_Receive_PerodicCheck(unsigned char* pdata)
{
	if(((UCSRA & (1<<RXC))) )
	{
		*pdata = UDR;
		return 1;
	}
	else
	{
		return 0;
	}
}

void Uart_SendNoBlock(unsigned char data)
{
	UDR = data;
}
unsigned char Uart_ReceiveNoBlock()
{
	return UDR;
}
void Uart_SendStrAsynch(unsigned char* str)
{ 
	if(flag_send == 1)
	{
		Uart_TX_InterruptEnbale();
		Uart_SendNoBlock(str[0]);
		TX_Str = str;
		flag_send = 0;
	}
}
void Uart_ReceStrAsynch(unsigned char* str)
{
	if(flag_receive == 1)
	{
		Uart_RX_InterruptEnbale();
		RX_Str	= str;
		*str = Uart_ReceiveNoBlock();

		flag_receive = 0;
	}

	
	
}
void Uart_RX_InterruptEnbale(void)
{
	UCSRB |= (1<<RXCIE);
}
void Uart_RX_InterruptDisable(void)
{
	UCSRB &= ~(1<<RXCIE);
}
void Uart_TX_InterruptEnbale(void)
{
	UCSRB |= (1<<TXCIE);
}
void Uart_TX_InterruptDisable(void)
{
	UCSRB &= ~(1<<TXCIE);
}
void Uart_RX_SetCallBack(void (*ptrfunc)(void))
{
	UART_RX_Fptr = ptrfunc;
}
void Uart_TX_SetCallBack(void (*ptrfunc)(void))
{
	UART_TX_Fptr = ptrfunc;
}
ISR(USART_TXC_vect)
{
	static unsigned char i	= 1 ;
	if(TX_Str[i] != 0)
	{
		Uart_SendNoBlock(TX_Str[i]);
		i++;	 
	 }
	 else
	 {
		 i = 1;
		 flag_send = 1;
	 }
}

ISR(USART_RXC_vect)
{
	//static unsigned char i	= 1 ;
	if(*RX_Str != 0)
	{
		RX_Str++;
		*RX_Str = Uart_ReceiveNoBlock();

	}

	else
	{
		*RX_Str = '\0';
		flag_receive = 1;
	}
	
}