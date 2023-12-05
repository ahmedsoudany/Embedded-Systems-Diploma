/*
 * DataTypes.h
 *
 * Created: 11/9/2023 1:05:52 PM
 *  Author: LEGION
 */ 


#ifndef DATATYPES_H_
#define DATATYPES_H_



typedef _Bool					boolean;

#ifndef FALSE
#define FALSE (boolean)false
#endif

#ifndef TRUE
#define TRUE (boolean)true
#endif



typedef unsigned char			uint8_t;
typedef   signed char			sint8_t;
typedef unsigned int			uint16_t;
typedef   signed int			sint16_t;
typedef unsigned int			uint32_t;
typedef   signed int			sint32_t;
typedef unsigned int			uint32_t;
typedef   signed int			sint32_t;
typedef unsigned long long		uint64_t;
typedef   signed long long		sint64_t;
typedef	float					float32;
typedef double					float64;



typedef volatile unsigned char			vuint8_t;
typedef volatile   signed char			vsint8_t;
typedef volatile unsigned int			vuint16_t;
typedef volatile   signed int			vsint16_t;
typedef volatile unsigned int			vuint32_t;
typedef volatile   signed int			vsint32_t;
typedef volatile unsigned int			vuint32_t;
typedef volatile   signed int			vsint32_t;
typedef volatile unsigned long long		vuint64_t;
typedef volatile   signed long long		vsint64_t;




#endif /* DATATYPES_H_ */