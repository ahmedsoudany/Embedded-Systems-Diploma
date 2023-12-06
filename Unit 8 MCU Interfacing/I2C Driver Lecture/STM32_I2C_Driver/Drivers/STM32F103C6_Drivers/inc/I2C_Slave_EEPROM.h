/*
 * I2C_Slave_EEPROM.h
 *
 *  Created on: Nov 19, 2023
 *      Author: LEGION
 */

#ifndef INC_I2C_SLAVE_EEPROM_H_
#define INC_I2C_SLAVE_EEPROM_H_

#include "STM32F103x6.h"
#include "STM32F103C6_I2C_Drivers.h"

//E2PROM is an I2C SLAVE
// Idle Mode: device is in high-impedance state and waits for data
//Master Receive Mode: the device receives data from a slave transmitter

#define EEPROM_Slave_Address		0x2A

void EEPROM_Init(void);
uint8_t EEPROM_Write_NBytes(uint32_t Memory_Address, uint8_t* Bytes, uint8_t Data_Length);
uint8_t EEPROM_Read_NBytes(uint32_t Memory_Address, uint8_t* DataOut, uint8_t Data_Length);

#endif /* INC_I2C_SLAVE_EEPROM_H_ */
