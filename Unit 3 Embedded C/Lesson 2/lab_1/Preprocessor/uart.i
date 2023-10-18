# 1 "uart.c"
# 1 "<command-line>"
# 1 "uart.c"



# 1 "uart.h" 1
# 5 "uart.c" 2
# 1 "Platform_Types.h" 1




typedef _Bool boolean;
# 18 "Platform_Types.h"
typedef signed char sint8_t;
typedef unsigned char uint8_t;

typedef signed short sint16_t;
typedef unsigned short uint16_t;

typedef signed int sint32_t;
typedef unsigned int uint32_t;


typedef signed long long sint64_t;
typedef unsigned long long uint64_t;

typedef float float32;
typedef double float64;

typedef volatile signed char vsint8_t;
typedef volatile unsigned char vuint8_t;

typedef volatile signed short vsint16_t;
typedef volatile unsigned short vuint16_t;

typedef volatile signed int vsint32_t;
typedef volatile unsigned int vuint32_t;


typedef volatile signed long long vsint64_t;
typedef volatile unsigned long long vuint64_t;
# 6 "uart.c" 2


void Uart_Send_string(uint8_t *P_tx_string)
{
 while(*P_tx_string != '\0')
 {

  *((vuint32_t* const)((uint32_t *)0x101f1000)) = (uint32_t)(*P_tx_string);

  P_tx_string++;
 }
}
