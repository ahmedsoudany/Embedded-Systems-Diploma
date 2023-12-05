/*
 * LCD.c
 *
 *  Created on: Nov 15, 2023
 *      Author: LEGION
 */


#include "LCD.h"

static void delay_ms(uint32_t time)
{
	uint32_t i , j ;
	for(i = 0 ; i < time ; i++)
	{
		for(j = 0 ; j < 255  ; j++);
	}
}

/* ========================================== */
/*			 Functions Definitions 			  */
/* ========================================== */

void LCD_GPIO_Init(LCD_Config *LCD_Config)
{

	/* ===========Set Control PINS to OUTPUT=========== */

	/* RS PIN config ==> OUTPUT */
	PinCfg.GPIO_PinNumber = LCD_Config->Ctrl.RSPIN;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_Config->Ctrl.GPIOx, &PinCfg);

	/* RW PIN config ==> OUTPUT */
	PinCfg.GPIO_PinNumber = LCD_Config->Ctrl.RWPIN;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_Config->Ctrl.GPIOx, &PinCfg);

	/* EN PIN config ==> OUTPUT */
	PinCfg.GPIO_PinNumber = LCD_Config->Ctrl.ENPIN;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_Config->Ctrl.GPIOx, &PinCfg);

	/* ===========Set LCD PORT PINS to OUTPUT=========== */
	uint8_t i;
#ifdef EIGHT_BIT_MODE

	for (i = 0 ; i < 8 ; i++)
	{
		PinCfg.GPIO_PinNumber = LCD_Config->Data.DATAPINS << i;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
		MCAL_GPIO_Init(LCD_Config->Data.GPIOx, &PinCfg);
	}

#endif

#ifdef FOUR_BIT_MODE

	for (i = 4 ; i < 8 ; i++)
		{
			PinCfg.GPIO_PinNumber = LCD_Config->Data.DATAPINS << i;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(LCD_Config->Data.GPIOx, &PinCfg);
		}

//	PinCfg.GPIO_PinNumber = GPIO_PIN_4;
//	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
//	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
//	MCAL_GPIO_Init(LCD_Config->Data.GPIOx, &PinCfg);
//
//	PinCfg.GPIO_PinNumber = GPIO_PIN_5;
//	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
//	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
//	MCAL_GPIO_Init(LCD_Config->Data.GPIOx, &PinCfg);
//
//	PinCfg.GPIO_PinNumber = GPIO_PIN_6;
//	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
//	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
//	MCAL_GPIO_Init(LCD_Config->Data.GPIOx, &PinCfg);
//
//	PinCfg.GPIO_PinNumber = GPIO_PIN_7;
//	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
//	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
//	MCAL_GPIO_Init(LCD_Config->Data.GPIOx, &PinCfg);



#endif

	/* Set Control signal to Low (Sink current) */
	MCAL_GPIO_WritePin(LCD_Config->Ctrl.GPIOx, LCD_Config->Ctrl.ENPIN, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_Config->Ctrl.GPIOx, LCD_Config->Ctrl.RSPIN, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_Config->Ctrl.GPIOx, LCD_Config->Ctrl.RWPIN, GPIO_PIN_RESET);

}

void LCD_Init(LCD_Config *LCD_Config)
{
	delay_ms(20);
	LCD_GPIO_Init(LCD_Config);
	delay_ms(15);

	LCD_Clear_Screen(LCD_Config);


#ifdef EIGHT_BIT_MODE
	LCD_Write_Command(LCD_Config,LCD_FUNCTION_8BIT_4LINES);
#endif

#ifdef FOUR_BIT_MODE
	LCD_Write_Command(LCD_Config,0x02);
	LCD_Write_Command(LCD_Config,LCD_FUNCTION_4BIT_2LINES);
#endif

	LCD_Write_Command(LCD_Config,LCD_ENTRY_MODE);
	LCD_Write_Command(LCD_Config,LCD_BEGIN_AT_FIRST_ROW);
	LCD_Write_Command(LCD_Config,LCD_DISP_ON_CURSOR_BLINK);


}
void LCD_Write_Command(LCD_Config *LCD_Config,uint8_t cmd)
{
#ifdef EIGHT_BIT_MODE
	MCAL_GPIO_WritePort(LCD_Config->Data.GPIOx, cmd);
	/* Set as Write MODE ==> 0 */
	MCAL_GPIO_WritePin(LCD_Config->Ctrl.GPIOx, LCD_Config->Ctrl.RWPIN, GPIO_PIN_RESET);
	/* Set as Command MODE ==> 0 */
	MCAL_GPIO_WritePin(LCD_Config->Ctrl.GPIOx, LCD_Config->Ctrl.RSPIN, GPIO_PIN_RESET);
	delay_ms(1);
	LCD_Lcd_kick(LCD_Config);
#endif

#ifdef FOUR_BIT_MODE

	// Send last four bits of command
	uint8_t temp_cmd;
	temp_cmd = (cmd & 0xF0);
	MCAL_GPIO_WritePort(LCD_Config->Ctrl.GPIOx, temp_cmd);
	MCAL_GPIO_WritePin(LCD_Config->Ctrl.GPIOx, LCD_Config->Ctrl.RWPIN, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_Config->Ctrl.GPIOx, LCD_Config->Ctrl.RSPIN, GPIO_PIN_RESET);
	delay_ms(1);
	LCD_Lcd_kick(LCD_Config);

	temp_cmd = (cmd << 4);
	MCAL_GPIO_WritePort(LCD_Config->Ctrl.GPIOx, temp_cmd);
	MCAL_GPIO_WritePin(LCD_Config->Ctrl.GPIOx, LCD_Config->Ctrl.RWPIN, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_Config->Ctrl.GPIOx, LCD_Config->Ctrl.RSPIN, GPIO_PIN_RESET);
	delay_ms(1);
	LCD_Lcd_kick(LCD_Config);

#endif

}
void LCD_Write_Char(LCD_Config *LCD_Config,uint8_t ch)
{

#ifdef EIGHT_BIT_MODE

	MCAL_GPIO_WritePort(LCD_Config->Data.GPIOx,ch);
	/* Set Write MODE ==> 0 */
	MCAL_GPIO_WritePin(LCD_Config->Ctrl.GPIOx, LCD_Config->Ctrl.RWPIN, GPIO_PIN_RESET);
	/* Set as Data MODE ==> 1 */
	MCAL_GPIO_WritePin(LCD_Config->Ctrl.GPIOx, LCD_Config->Ctrl.RSPIN, GPIO_PIN_SET);

	delay_ms(1);
	LCD_Lcd_kick(LCD_Config);
#endif
#ifdef FOUR_BIT_MODE

	/* ====== LCD is in 4 bit Mode ====== */

	// Send last four bits of command
	uint8_t temp_cmd;
	temp_cmd = (ch & 0xF0);
	MCAL_GPIO_WritePort(LCD_Config->Data.GPIOx, temp_cmd);
	MCAL_GPIO_WritePin(LCD_Config->Ctrl.GPIOx, LCD_Config->Ctrl.RSPIN, GPIO_PIN_SET);
	MCAL_GPIO_WritePin(LCD_Config->Ctrl.GPIOx, LCD_Config->Ctrl.RWPIN, GPIO_PIN_RESET);
	delay_ms(1);
	LCD_Lcd_kick(LCD_Config);


	// Send first four bits of command
	temp_cmd = (ch << 4);
	MCAL_GPIO_WritePort(LCD_Config->Data.GPIOx, temp_cmd);
	MCAL_GPIO_WritePin(LCD_Config->Ctrl.GPIOx, LCD_Config->Ctrl.RSPIN, GPIO_PIN_SET);
	MCAL_GPIO_WritePin(LCD_Config->Ctrl.GPIOx, LCD_Config->Ctrl.RWPIN, GPIO_PIN_RESET);
	delay_ms(1);
	LCD_Lcd_kick(LCD_Config);

#endif
}

void LCD_Check_LCD_IsBusy(LCD_Config *LCD_Config)
{

	uint8_t i;
	/* ===========Set LCD PORT PINS to INPUT=========== */

#ifdef EIGHT_BIT_MODE

	for (i = 0 ; i < 8 ; i++)
	{
		PinCfg.GPIO_PinNumber = LCD_Config->Data.DATAPINS << i;
		PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
		MCAL_GPIO_Init(LCD_Config->Data.GPIOx, &PinCfg);
	}

#endif

#ifdef FOUR_BIT_MODE

	for (i = 4 ; i < 8 ; i++)
		{
			PinCfg.GPIO_PinNumber = LCD_Config->Data.DATAPINS << i;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(LCD_Config->Data.GPIOx, &PinCfg);
		}
//		PinCfg.GPIO_PinNumber = GPIO_PIN_4;
//		PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
//		MCAL_GPIO_Init(LCD_Config->Data.GPIOx, &PinCfg);
//
//		PinCfg.GPIO_PinNumber = GPIO_PIN_5;
//		PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
//		MCAL_GPIO_Init(LCD_Config->Data.GPIOx, &PinCfg);
//
//		PinCfg.GPIO_PinNumber = GPIO_PIN_6;
//		PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
//		MCAL_GPIO_Init(LCD_Config->Data.GPIOx, &PinCfg);
//
//		PinCfg.GPIO_PinNumber = GPIO_PIN_7;
//		PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
//		MCAL_GPIO_Init(LCD_Config->Data.GPIOx, &PinCfg);


#endif



	/* Set Read MODE ==> 1 */
	MCAL_GPIO_WritePin(LCD_Config->Ctrl.GPIOx, LCD_Config->Ctrl.RWPIN, GPIO_PIN_SET);
	/* Set as Command MODE ==> 0 */
	MCAL_GPIO_WritePin(LCD_Config->Ctrl.GPIOx, LCD_Config->Ctrl.RSPIN, GPIO_PIN_RESET);

	LCD_Lcd_kick(LCD_Config);

	/* Set Port as Output */
	//MCAL_GPIO_WritePort(LCD_CTRL,GPIO_PIN_SET);

	/* Set as Write MODE ==> 0 */
	MCAL_GPIO_WritePin(LCD_Config->Ctrl.GPIOx, LCD_Config->Ctrl.RWPIN, GPIO_PIN_RESET);

}
void LCD_Lcd_kick(LCD_Config *LCD_Config)
{
	MCAL_GPIO_WritePin(LCD_Config->Ctrl.GPIOx, LCD_Config->Ctrl.ENPIN, GPIO_PIN_SET);
	delay_ms(50);
	MCAL_GPIO_WritePin(LCD_Config->Ctrl.GPIOx, LCD_Config->Ctrl.ENPIN, GPIO_PIN_RESET);

}
void LCD_Clear_Screen(LCD_Config *LCD_Config)
{
	LCD_Write_Command(LCD_Config,LCD_CLEAR_SCREEN);
}
void LCD_GOTO_XY(LCD_Config *LCD_Config,uint8_t line,uint8_t position)
{
	if(line == 1)
	{
		if(position < 16 && position >= 0)
		{
			LCD_Write_Command(LCD_Config,LCD_BEGIN_AT_FIRST_ROW + position);
		}
	}
	if(line == 2)
	{
		if(position < 16 && position >= 0)
		{
			LCD_Write_Command(LCD_Config,LCD_BEGIN_AT_SECOND_ROW + position);
		}
	}
	if(line == 3)
	{
		if(position < 16 && position >= 0)
		{
			LCD_Write_Command(LCD_Config,LCD_BEGIN_AT_THIRD_ROW + position);
		}
	}
	if(line == 4)
	{
		if(position < 16 && position >= 0)
		{
			LCD_Write_Command(LCD_Config,LCD_BEGIN_AT_FOURTH_ROW + position);
		}
	}


}

void LCD_Write_Str(LCD_Config *LCD_Config,uint8_t *st)
{
	int count = 0;

	while(*st > 0)
	{
		count++;
		LCD_Write_Char(LCD_Config,*st++);

		if(count == 16)
		{
			LCD_GOTO_XY(LCD_Config,2, 0);

		}
		else if (count == 32)
		{
			LCD_GOTO_XY(LCD_Config,3, 0);
		}
		else if (count == 48)
		{

			LCD_GOTO_XY(LCD_Config,4, 0);

		}
		else if (count == 64)
		{
			LCD_Clear_Screen(LCD_Config);
			LCD_GOTO_XY(LCD_Config,1, 0);
			count = 0;
		}


	}
}

void LCD_display_number (LCD_Config *LCD_Config,uint32_t Number)
{
	char str[7];

	sprintf(str,"%d",Number);

	LCD_Write_Str(LCD_Config,str);
}
