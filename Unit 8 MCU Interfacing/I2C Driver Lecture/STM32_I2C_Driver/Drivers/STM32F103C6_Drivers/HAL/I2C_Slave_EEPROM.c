/*
 * I2C_Slave_EEPROM.c
 *
 *  Created on: Nov 19, 2023
 *      Author: LEGION
 */

#include "I2C_Slave_EEPROM.h"

void EEPROM_Init(void)
{

	//====================I2C_INIT===========================
	//		PB6 : I2C1_SCL
	//		PB7 : I2C_SDA
	I2C_InitTypedef I2CICFG ;

	//I2C Controller act as a Master

	I2CICFG.General_Call_Address_Detection = I2C_ENGC_Enable ;
	I2CICFG.I2C_ACK_Control = I2C_ACK_Enable;
	I2CICFG.I2C_ClockSpeed = I2C_SCLK_SM_100K;
	I2CICFG.I2C_Mode = I2C_Mode_I2C;
	I2CICFG.P_Slave_Event_CallBack = NULL;
	I2CICFG.Stretch_Mode = I2C_StretchMode_Enable;

	MCAL_I2C_GPIO_Set_Pins(I2C1);
	MCAL_I2C_Init(I2C1, &I2CICFG);

}
uint8_t EEPROM_Write_NBytes(uint32_t Memory_Address , uint8_t* Bytes, uint8_t Data_Length)
{
	uint8_t i = 0;
	//MISRA C++ 2008, 18-4-1 - Dynamic heap memory allocation should not be used
	//Violate MISRA Rule
	//(unsigned char*)malloc(Data_Length+2) ;

	uint8_t buffer[256];

	buffer[0] = (uint8_t)(Memory_Address >> 8 ); // Upper byte Memory address
	buffer[1] = (uint8_t)(Memory_Address      ); // Lower byte Memory address

	for(i = 2 ; i < (Data_Length+2) ; i++ )
	{
		buffer[i] = Bytes[i-2];
	}

	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_Address, buffer, (Data_Length+2), With_Stop, Start);

	return 0;

}
uint8_t EEPROM_Read_NBytes(uint32_t Memory_Address, uint8_t* DataOut, uint8_t Data_Length)
{
	uint8_t buffer[2];

	buffer[0] = (uint8_t)(Memory_Address >> 8 ); // Upper byte Memory address
	buffer[1] = (uint8_t)(Memory_Address      ); // Lower byte Memory address

	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_Address, buffer, 2, Without_Stop, Start); //Write Address Only
	MCAL_I2C_Master_RX(I2C1, EEPROM_Slave_Address, DataOut, Data_Length, With_Stop, Repeated_start); //Write Address Only

	return 0;
}
