/*
 * Utils.h
 *
 * Created: 11/9/2023 9:11:48 PM
 *  Author: LEGION
 */ 


#ifndef UTILS_H_
#define UTILS_H_

#define SETBIT(REG,BIT)		(REG |= (1<<BIT))

#define CLRBIT(REG,BIT)		(REG &= ~(1<<BIT))

#define TOGBIT(REG,BIT)		(REG ^= (1<<BIT))

#define GETBIT(REG,BIT)		((REG>>BIT) & 1)  //(REG & (1<<BIT)




#endif /* UTILS_H_ */