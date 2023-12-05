/*
 * LCD.h
 *
 *  Created on: Nov 15, 2023
 *      Author: LEGION
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_



//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6.h"
#include "STM32F103C6_GPIO_Drivers.h"

//-----------------------------
//Macros Configuration References
//-----------------------------
typedef struct
{
	GPIO_TypeDef     *GPIOx;
	uint16_t 		  RSPIN;
	uint16_t 		  RWPIN;
	uint16_t 		  ENPIN;
}LCD_CTRLPINS;

typedef struct
{
	GPIO_TypeDef *GPIOx;
	uint16_t 	DATAPINS;
}LCD_DATAPINS;


typedef struct
{
	LCD_CTRLPINS	Ctrl;
	LCD_DATAPINS	Data;
}LCD_Config;

/*	LCD Mode  */
//#define EIGHT_BIT_MODE
#define FOUR_BIT_MODE

/*	LCD_Commands */
#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_8BIT_4LINES   					(0x3C)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
#define LCD_FUNCTION_4BIT_4LINES   					(0x2C)
#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF   								(0x08)
#define LCD_DISP_ON_CURSOR   						(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_INC_   							(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_BEGIN_AT_FIRST_ROW						(0x80)
#define LCD_BEGIN_AT_SECOND_ROW						(0xC0)
#define LCD_BEGIN_AT_THIRD_ROW						(0x90)
#define LCD_BEGIN_AT_FOURTH_ROW						(0xD0)
#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_ENTRY_MODE								(0x06)




//-----------------------------
//Global Variables
//-----------------------------


GPIO_PinConfig_t PinCfg;



/*
* ===============================================
* APIs Supported by "LCD DRIVER"
* ===============================================
*/

void LCD_Init(LCD_Config *LCD_Config);
void LCD_Write_Command(LCD_Config *LCD_Config,uint8_t cmd);
void LCD_Write_Char(LCD_Config *LCD_Config,uint8_t ch);
void LCD_Write_Str(LCD_Config *LCD_Config,uint8_t* st);
void LCD_Check_LCD_IsBusy(LCD_Config *LCD_Config);
void LCD_Lcd_kick(LCD_Config *LCD_Config);
void LCD_Clear_Screen(LCD_Config *LCD_Config);
void LCD_GOTO_XY(LCD_Config *LCD_Config,uint8_t line,uint8_t position);
void LCD_display_number (LCD_Config *LCD_Config,uint32_t Number);

#endif /* INC_LCD_H_ */
