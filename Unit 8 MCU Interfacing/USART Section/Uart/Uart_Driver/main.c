/*
 * Uart_Driver.c
 *
 * Created: 10/26/2023 2:05:09 PM
 * Author : LEGION
 */ 


#include "Uart.h"
#include "LCD.h"

unsigned char x = 0 , y = 0;


int main(void)
{
	sei(); 
	unsigned char str[100];
	LCD_lcd_init();
	Uart_Init();
	
	LCD_GotoXY(0,0);
	LCD_Send_A_String("UART TR");
	/* Try send string */
	
	//Send_Str("Ahmed");
	//Uart_Send('A');
	//Uart_Send('H');
	//Uart_Send('M');
	//Uart_Send('E');
	//Uart_Send('D');
	//unsigned int num = 300;
	//Uart_SendNumber(num);
	
	
	Uart_SendStrAsynch("Ansam");
    /* Replace with your application code */
    while (1) 
    {
			
		LCD_GotoXY(1,0);
		
		x = Uart_Receive();
		LCD_Send_A_Character(x);
		
		
			/************************1******************
			Uart_RecStr(str);
		
			LCD_GotoXY(1,0);
			
			LCD_Send_A_String(str);
			
			LCD_Send_A_String("						");
			
			LCD_GotoXY(0,0);
			LCD_display_number(x);
			x++;
			if(x == 10)
			{
				x = 0;
			}
			_delay_ms(200);
			*/
			
			/*********************2************
			if(Uart_Receive_PerodicCheck(&y))
			{
				LCD_GotoXY(0,0);
				LCD_clear_screen();
				LCD_Send_A_Character(y);
			}
			
			LCD_GotoXY(1,0);
			LCD_display_number(x);
			x++;
			if(x == 10)
			{
				x = 0;
			}
			_delay_ms(1000);
			*/
			
			/*********************3************
			LCD_GotoXY(0,0);
			Uart_ReceStrAsynch(&y);
			if(y != 0)
			LCD_Send_A_Character(y);
			
		//	LCD_Send_A_String("				");
			LCD_GotoXY(1,0);
			LCD_display_number(x);
			x++;
			if(x == 10)
			{
				x = 0;
			}
			_delay_ms(300);
			*/
    }
	return 0;
}

