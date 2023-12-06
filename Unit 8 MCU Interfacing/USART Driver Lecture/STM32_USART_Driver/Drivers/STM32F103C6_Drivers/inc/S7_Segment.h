/*
 * S7_Segment.h
 *
 *  Created on: Nov 15, 2023
 *      Author: LEGION
 */

#ifndef INC_S7_SEGMENT_H_
#define INC_S7_SEGMENT_H_


//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6.h"
#include "STM32F103C6_GPIO_Drivers.h"

//-----------------------------
//Macros Configuration References
//-----------------------------

#define ZERO	0x01
#define ONE		0x79
#define TWO		0x24
#define THREE	0x30
#define FOUR	0x4C
#define FIVE	0x12
#define SIX		0x02
#define SEVEN	0x19
#define EIGHT	0x00
#define NINE	0x10


/*
* ===============================================
* APIs Supported by "HAL S7_SEGMENT DRIVER"
* ===============================================
*/
void S7_Segment_Init(void);

#endif /* INC_S7_SEGMENT_H_ */
