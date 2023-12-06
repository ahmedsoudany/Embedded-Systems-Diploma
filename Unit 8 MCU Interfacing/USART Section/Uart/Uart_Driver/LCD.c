/*
 * LCD.c
 *
 * Created: 9/25/2023 7:28:27 PM
 *  Author: LEGION
 */ 
#include "LCD.h"

void LCD_Send_A_Command(unsigned char command)
{
	#ifdef EIGHT_BIT_MODE
	LCD_check_lcd_isbusy();
	
	LCD_Port = command;
	LCD_Ctrl &= ~((1<<RW) | (1<<RS));
	LCD_lcd_kick();
	
	#endif
	
	#ifdef FOR_BIT_MODE
	LCD_check_lcd_isbusy();
	LCD_Port = (LCD_Port & 0x0F) | (command & 0xF0);
	LCD_Ctrl &= ~((1<<RW) | (1<<RS));
	LCD_lcd_kick();
	LCD_Port = (LCD_Port & 0x0F) | (command << 4);
	#endif
}

void LCD_clear_screen ()
{
	LCD_Send_A_Command(LCD_CLEAR_SCREEN);
}

void LCD_check_lcd_isbusy(void)
{
	Datadir_LCD_Port &= ~(0xff<<DATA_shift);
	LCD_Ctrl |= (1<<RW); //read mode
	LCD_Ctrl &= ~(1<<RS); //command mode
	LCD_lcd_kick();
	Datadir_LCD_Port = 0xff; //port is set as output
	LCD_Ctrl &= ~(1<<RW); //write mode
	
}
void LCD_lcd_kick (void)
{
	LCD_Ctrl &= ~(1<<EN);
	//asm volatile ("nop");
	//asm volatile ("nop");
	_delay_ms(50);
	LCD_Ctrl |= (1<<EN);
}

void LCD_Send_A_Character(unsigned char character)
{
	#ifdef EIGHT_BIT_MODE
	LCD_check_lcd_isbusy();
	
	LCD_Ctrl |= 1<<RS; //Set for data mode
	LCD_Port = ((character) << DATA_shift);
	LCD_Ctrl |= 1<<RS; //Set for data mode
	LCD_Ctrl &= ~(1<<RW);
	
	LCD_lcd_kick();
	
	#endif
	
	#ifdef FOUR_BIT_MODE
	LCD_Port = (LCD_Port & 0x0F) | (character & 0xF0);
	LCD_Ctrl |= 1<<RS;
	LCD_Ctrl &= ~(1<<RW);
	LCD_lcd_kick();
	LCD_Port = (LCD_Port & 0x0F) | (character << 4);
	LCD_Ctrl |= 1<<RS;
	LCD_Ctrl &= ~(1<<RW);
	LCD_lcd_kick();
	#endif
}
void LCD_Send_A_String(char *string)
{
	int count = 0; //To count how much char on the line
	while(*string > 0)
	{
		
		count++;
		LCD_Send_A_Character(*string++);
		if(count == 16)//go to second line
		{
			LCD_GotoXY(1,0); //line 1 position 0
		}
		else if(count == 32 || count == 33)//go to second line
		{
			LCD_clear_screen();
			LCD_GotoXY(0,0); //line 0 position 0
			count = 0;
		}
		
	}
	
}
void LCD_lcd_init(void)
{
	_delay_ms(20);
	
	Datadir_LCD_Ctrl |= (1<<EN) | (1<<RS) | (1<<RW);
	LCD_Ctrl &= ~((1<<EN) | (1<<RS) | (1<<RW));
	
	Datadir_LCD_Port = 0xFF;
	_delay_ms(15);
	
	LCD_clear_screen();
	
	#ifdef EIGHT_BIT_MODE
	LCD_Send_A_Command(LCD_FUNCTION_8BIT_2LINES);
	
	#endif
	
	#ifdef FOUR_BIT_MODE
	LCD_Send_A_Command(0x02);
	
	LCD_Send_A_Command(LCD_FUNCTION_4BIT_2LINES);
	
	#endif
	
	LCD_Send_A_Command(LCD_ENTRY_MODE);
	LCD_Send_A_Command(LCD_BEGIN_AT_FIRST_RAW);
	LCD_Send_A_Command(LCD_DISP_ON_CURSOR_BLINK);
}

void LCD_GotoXY(unsigned char line, unsigned char position )
{
	if(line == 0)
	{
		if(position < 16 && position >= 0)
		{
			LCD_Send_A_Command(LCD_BEGIN_AT_FIRST_RAW + position);
		}
		
	}
	else if (line == 1)
	{
		if(position < 16 && position >= 0)
		{
			LCD_Send_A_Command(LCD_BEGIN_AT_SECOND_RAW + position);
		}
	}
}
void LCD_display_number (int Number)
{
	char str[7];
	
	sprintf(str,"%d",Number);
	
	LCD_Send_A_String(str);
}
void LCD_display_real_number (double  Number)
{
	char str[7];
	
	char *tmpSign = (Number < 0) ? "-" : "";
	float tmpVal = (Number < 0) ? -Number : Number;
	
	int tmpInt1 = tmpVal; //Get the integer (678)
	float tmpFrac = tmpVal - tmpInt1; //Get fraction (0.0123)
	int tmpInt2 = tmpFrac * 10000;  //Turn into integer
	
	sprintf(str,"%s%d.%04d",tmpSign,tmpInt1,tmpInt2);
	
	LCD_Send_A_String(str);
}