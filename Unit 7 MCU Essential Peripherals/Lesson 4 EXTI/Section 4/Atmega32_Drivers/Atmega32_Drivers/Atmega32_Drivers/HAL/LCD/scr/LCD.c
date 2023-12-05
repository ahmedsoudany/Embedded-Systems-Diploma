/*
 * LCD.c
 *
 * Created: 11/9/2023 12:58:46 PM
 *  Author: LEGION
 */ 

#include "LCD.h"

void LCD_Send_A_Command(unsigned char command)
{
	#ifdef EIGHT_BIT_MODE
	LCD_check_lcd_isbusy();
	
	PORTA = command;
	MCAL_GPIO_SET_PIN_VAL(LCD_Ctrl,RW,Low);
	MCAL_GPIO_SET_PIN_VAL(LCD_Ctrl,RS,Low);
	LCD_lcd_kick();
	
	#endif
	
	#ifdef FOR_BIT_MODE
	LCD_check_lcd_isbusy();
	PORTA = (PORTA & 0x0F) | (command & 0xF0);
	MCAL_GPIO_SET_PIN_VAL(LCD_Ctrl,RW,Low);
	MCAL_GPIO_SET_PIN_VAL(LCD_Ctrl,RS,Low);
	LCD_lcd_kick();
	PORTA = (PORTA & 0x0F) | (command << 4);
	#endif
}

void LCD_clear_screen ()
{
	LCD_Send_A_Command(LCD_CLEAR_SCREEN);
}

void LCD_check_lcd_isbusy(void)
{
	Datadir_LCD_Port &= ~(0xff<<DATA_shift);
	
	MCAL_GPIO_SET_PIN_VAL(LCD_Ctrl,RW,High);
	
	MCAL_GPIO_SET_PIN_VAL(LCD_Ctrl,RS,Low);
	LCD_lcd_kick();
	Datadir_LCD_Port |= (0xff<<DATA_shift);
	//MCAL_GPIO_SET_PORT_DIR(LCD_Port,High);
	MCAL_GPIO_SET_PIN_VAL(LCD_Ctrl,RW,Low);
	
}
void LCD_lcd_kick (void)
{
	MCAL_GPIO_SET_PIN_VAL(LCD_Ctrl,EN,Low);
	//asm volatile ("nop");
	//asm volatile ("nop");
	_delay_ms(50);
	MCAL_GPIO_SET_PIN_VAL(LCD_Ctrl,EN,High);
}

void LCD_Send_A_Character(unsigned char character)
{
	#ifdef EIGHT_BIT_MODE
	LCD_check_lcd_isbusy();
	MCAL_GPIO_SET_PIN_VAL(LCD_Ctrl,RS,High);
	PORTA	= ((character) << DATA_shift);
	MCAL_GPIO_SET_PIN_VAL(LCD_Ctrl,RS,High);
	MCAL_GPIO_SET_PIN_VAL(LCD_Ctrl,RW,Low);
	LCD_lcd_kick();
	
	#endif
	
	#ifdef FOUR_BIT_MODE
	PORTA = (PORTA & 0x0F) | (character & 0xF0);
	MCAL_GPIO_SET_PIN_VAL(LCD_Ctrl,RS,High);
	MCAL_GPIO_SET_PIN_VAL(LCD_Ctrl,RW,Low);
	LCD_lcd_kick();
	PORTA = (PORTA & 0x0F) | (character << 4 );
	MCAL_GPIO_SET_PIN_VAL(LCD_Ctrl,RS,High);
	MCAL_GPIO_SET_PIN_VAL(LCD_Ctrl,RW,Low);
	LCD_lcd_kick();
	#endif
}
void LCD_Send_A_String(uint8_t *string)
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
	
	MCAL_GPIO_SET_PIN_DIR(LCD_Ctrl,EN,Output);
	MCAL_GPIO_SET_PIN_DIR(LCD_Ctrl,RS,Output);
	MCAL_GPIO_SET_PIN_DIR(LCD_Ctrl,RW,Output);
	MCAL_GPIO_SET_PIN_VAL(LCD_Ctrl,EN,Low);
	MCAL_GPIO_SET_PIN_VAL(LCD_Ctrl,RS,Low);
	MCAL_GPIO_SET_PIN_VAL(LCD_Ctrl,RW,Low);
	
	MCAL_GPIO_SET_PORT_DIR(Datadir_LCD_Port,Output);
	_delay_ms(15);
	
	LCD_clear_screen();
	
	#ifdef EIGHT_BIT_MODE
	LCD_Send_A_Command(LCD_FUNCTION_8BIT_2LINES);
	
	#endif
	
	#ifdef FOUR_BIT_MODE
	/* Set for 4 bit initialization */
	LCD_Send_A_Command(0x02);
	LCD_Send_A_Command(LCD_FUNCTION_4BIT_2LINES);
	#endif
	
	LCD_Send_A_Command(LCD_ENTRY_MODE);
	LCD_Send_A_Command(LCD_BEGIN_AT_FIRST_RAW);
	LCD_Send_A_Command(LCD_DISP_ON_CURSOR_BLINK);
}

void LCD_GotoXY(uint8_t line, uint8_t position )
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
void LCD_display_number (uint32_t Number)
{
	char str[7];
	
	sprintf(str,"%d",Number);
	
	LCD_Send_A_String(str);
}
void LCD_display_real_number (float64  Number)
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