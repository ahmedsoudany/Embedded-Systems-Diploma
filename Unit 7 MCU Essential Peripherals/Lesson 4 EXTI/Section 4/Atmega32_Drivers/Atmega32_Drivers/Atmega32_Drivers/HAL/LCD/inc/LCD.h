/*
 * LCD.h
 *
 * Created: 11/9/2023 12:58:28 PM
 *  Author: LEGION
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "DataTypes.h"
#include "MemoryMap.h"
#include "Utils.h"
#include "GPIO.h"
#define F_CPU 8000000UL
#include <util/delay.h>

#define LCD_Port PortA
#define Datadir_LCD_Port DDRA
#define DATA_shift 4 //0: 8bit data mode | 4:4bit data mode
#define LCD_Ctrl PortB
#define Datadir_LCD_Ctrl DDRB
#define RS 1
#define RW 2
#define EN 3



//#define EIGHT_BIT_MODE
#define FOUR_BIT_MODE



#define LCD_REGISTER_SELECT_PIN						(0)
#define LCD_READ_WRITE_PIN							(1)
#define LCD_ENABLE_PIN								(2)
#define LCD_REGISTER_SELECT_ENABLE					(1)
#define LCD_REGISTER_SELECT_DISABLE					(0)
#define READ_FROM_LCD								(1)
#define WRITE_TO_LCD								(0)
#define LCD_ENABLE									(1)
#define LCD_DISABLE									(0)
#define LCD_FIRST_LINE								(0)
#define LCD_SECOND_LINE								(1)
#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
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
#define LCD_BEGIN_AT_FIRST_RAW						(0x80)
#define LCD_BEGIN_AT_SECOND_RAW						(0xC0)
#define LCD_CLEAR_SCREEN						    (0x01)
#define LCD_ENTRY_MODE								(0x06)



void LCD_check_lcd_isbusy(void);
void LCD_lcd_kick (void);
void LCD_Send_A_Command(uint8_t command);
void LCD_Send_A_Character(uint8_t character);
void LCD_Send_A_String(uint8_t *string);
void LCD_lcd_init(void);
void LCD_clear_screen(void);
void LCD_GotoXY(uint8_t line, uint8_t position);
void LCD_display_number (uint32_t Number);
void LCD_display_real_number (float64  Number);	



#endif /* LCD_H_ */