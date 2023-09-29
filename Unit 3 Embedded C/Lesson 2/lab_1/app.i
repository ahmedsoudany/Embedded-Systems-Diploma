# 1 "app.c"
# 1 "<command-line>"
# 1 "app.c"




# 1 "uart.h" 1
# 6 "app.c" 2
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
# 7 "app.c" 2

unsigned char string_buffer[100] = "learn-in-depth:Ahmed" ;
unsigned char const string_buffer_2[100] = "learn-in-depth" ;

void main(void)
{
 Uart_Send_string(string_buffer);
}
