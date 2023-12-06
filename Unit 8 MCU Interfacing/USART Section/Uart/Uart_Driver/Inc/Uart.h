/*
 * Uart.h
 *
 * Created: 10/26/2023 2:06:01 PM
 *  Author: LEGION
 */ 


#ifndef UART_H_
#define UART_H_
typedef unsigned int uint32_t;
#include <avr/io.h>
#include <avr/interrupt.h>
#define DefaultStop '\r'

void Uart_Init(void);
void Uart_Send(unsigned char data);
unsigned char Uart_Receive();
void Uart_SendNumber(unsigned int num);
unsigned int Uart_ReceiveNumber(void);
void Send_Str(unsigned char* str);
void Uart_RecStr(unsigned char* Buff);
unsigned char Uart_Receive_PerodicCheck(unsigned char* pdata);
void Uart_RX_InterruptEnbale(void);
void Uart_RX_InterruptDisable(void);
void Uart_TX_InterruptEnbale(void);
void Uart_TX_InterruptDisable(void);
void Uart_RX_SetCallBack(void (*ptrfunc)(void));
void Uart_TX_SetCallBack(void (*ptrfunc)(void));
void Uart_SendNoBlock(unsigned char data);
unsigned char Uart_ReceiveNoBlock();
void Uart_SendStrAsynch(unsigned char* str);
void Uart_ReceStrAsynch(unsigned char* str);

#endif /* UART_H_ */