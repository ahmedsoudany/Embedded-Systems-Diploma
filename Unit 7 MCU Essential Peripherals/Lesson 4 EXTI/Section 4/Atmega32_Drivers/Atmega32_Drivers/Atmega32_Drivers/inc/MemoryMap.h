/*
 * MemoryMap.h
 *
 * Created: 11/9/2023 1:00:45 PM
 *  Author: LEGION
 */ 


#ifndef MEMORYMAP_H_
#define MEMORYMAP_H_


#include "DataTypes.h"

#define PORTA			*(vsint8_t *)(0x3B)
#define DDRA			*(vsint8_t *)(0x3A)
#define PINA			*(vsint8_t *)(0x39)
#define PORTB			*(vsint8_t *)(0x38)
#define DDRB			*(vsint8_t *)(0x37)
#define PINB			*(vsint8_t *)(0x36)
#define PORTC			*(vsint8_t *)(0x35)
#define DDRC			*(vsint8_t *)(0x34)
#define PINC			*(vsint8_t *)(0x33)
#define PORTD			*(vsint8_t *)(0x32)
#define DDRD			*(vsint8_t *)(0x31)
#define PIND			*(vsint8_t *)(0x30)



#endif /* MEMORYMAP_H_ */