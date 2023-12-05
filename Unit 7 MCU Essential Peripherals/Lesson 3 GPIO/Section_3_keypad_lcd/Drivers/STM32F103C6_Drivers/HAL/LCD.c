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

void LCD_GPIO_Init()
{

	/* ===========Set Control PINS to OUTPUT=========== */

	/* RS PIN config ==> OUTPUT */
	PinCfg.GPIO_PinNumber = RS_SWITCH;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	/* RW PIN config ==> OUTPUT */
	PinCfg.GPIO_PinNumber = RW_SWITCH;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	/* EN PIN config ==> OUTPUT */
	PinCfg.GPIO_PinNumber = EN_SWITCH;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	/* ===========Set LCD PORT PINS to OUTPUT=========== */

	PinCfg.GPIO_PinNumber = GPIO_PIN_0;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_1;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_2;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_3;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_4;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_5;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_6;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_7;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	/* Set Control signal to Low (Sink current) */
	MCAL_GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);

}

void LCD_Init(void)
{
	delay_ms(20);
	LCD_GPIO_Init();
	delay_ms(15);

	LCD_Clear_Screen();


	#ifdef EIGHT_BIT_MODE
	LCD_Write_Command(LCD_FUNCTION_8BIT_2LINES);
	#endif

	#ifdef FOUR_BIT_MODE
	LCD_Write_Command(0x02);
	LCD_Write_Command(LCD_FUNCTION_8BIT_2LINES);
	#endif

	LCD_Write_Command(LCD_ENTRY_MODE);
	LCD_Write_Command(LCD_BEGIN_AT_FIRST_ROW);
	LCD_Write_Command(LCD_DISP_ON_CURSOR_BLINK);


}
void LCD_Write_Command(uint8_t cmd)
{
	#ifdef EIGHT_BIT_MODE
	//LCD_Check_LCD_IsBusy();
	MCAL_GPIO_WritePort(LCD_CTRL, cmd);
	/* Set as Write MODE ==> 0 */
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	/* Set as Command MODE ==> 0 */
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
	delay_ms(1);
	LCD_Lcd_kick();
	#endif

	#ifdef FOUR_BIT_MODE
	uint8_t temp_cmd;
	temp_cmd = (cmd & 0xF0);
	MCAL_GPIO_WritePort(LCD_CTRL, cmd);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
	delay_ms(1);
	LCD_Lcd_kick();
	
	temp_cmd = (cmd << 4);
	MCAL_GPIO_WritePort(LCD_CTRL, cmd);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
	delay_ms(1);
	LCD_Lcd_kick();
	#endif

}
void LCD_Write_Char(uint8_t ch)
{

	#ifdef EIGHT_BIT_MODE
	
	//LCD_Check_LCD_IsBusy();
	MCAL_GPIO_WritePort(LCD_CTRL,ch);
	/* Set Write MODE ==> 0 */
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	/* Set as Data MODE ==> 1 */
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET);
	delay_ms(1);
	LCD_Lcd_kick();
	#endif

	#ifdef FOUR_BIT_MODE
	uint8_t temp_cmd;
	temp_cmd = (ch & 0xF0);
	MCAL_GPIO_WritePort(LCD_CTRL, cmd);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET);
	delay_ms(1);
	LCD_Lcd_kick();
	
	temp_cmd = (ch << 4);
	MCAL_GPIO_WritePort(LCD_CTRL, cmd);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET);
	delay_ms(1);
	LCD_Lcd_kick();
	#endif
}
void LCD_Write_Str(uint8_t *st)
{
	int count = 0;

	while(*st > 0)
	{
		count++;
		LCD_Write_Char(*st++);
		if(count == 16)
		{
			LCD_GOTO_XY(2, 0);
		}
		else if (count == 32)
		{
			LCD_Clear_Screen();
			LCD_GOTO_XY(1, 0);
			count = 0;
		}
	}
}
void LCD_Check_LCD_IsBusy(void)
{

	/* ===========Set LCD PORT PINS to INPUT=========== */


	/* Set Data as Input */
	PinCfg.GPIO_PinNumber = GPIO_PIN_0;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_1;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_2;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_3;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_4;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_5;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_6;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_7;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	/* Set Read MODE ==> 1 */
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_SET);
	/* Set as Command MODE ==> 0 */
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);

	LCD_Lcd_kick();

	/* Set Port as Output */
	//MCAL_GPIO_WritePort(LCD_CTRL,GPIO_PIN_SET);

	/* Set as Write MODE ==> 0 */
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);

}
void LCD_Lcd_kick(void)
{
	MCAL_GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_SET);
	delay_ms(50);
	MCAL_GPIO_WritePin(LCD_CTRL, EN_SWITCH, GPIO_PIN_RESET);

}
void LCD_Clear_Screen(void)
{
	LCD_Write_Command(LCD_CLEAR_SCREEN);
}
void LCD_GOTO_XY(uint8_t line,uint8_t position)
{
	if(line == 1)
	{
		if(position < 16 && position >= 0)
		{
			LCD_Write_Command(LCD_BEGIN_AT_FIRST_ROW + position);
		}
	}
	if(line == 2)
	{
		if(position < 16 && position >= 0)
		{
			LCD_Write_Command(LCD_BEGIN_AT_SECOND_ROW + position);
		}
	}
}
