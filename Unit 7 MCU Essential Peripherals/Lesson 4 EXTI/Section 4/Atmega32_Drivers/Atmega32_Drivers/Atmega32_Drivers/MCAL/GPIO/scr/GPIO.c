/*
 * GPIO.c
 *
 * Created: 11/9/2023 12:56:31 PM
 *  Author: LEGION
 */ 


#include "GPIO.h"


void MCAL_GPIO_SET_PIN_DIR(GPIO_Port_t Port,PIN_No_t Pin,PIN_Dir_t Dir)
{
	if(Dir == Output)
	{
		switch(Port)
		{
			case PortA:
			SETBIT(DDRA,Pin);
			break;
			case PortB:
			SETBIT(DDRB,Pin);
			break;
			case PortC:
			SETBIT(DDRC,Pin);
			break;
			case PortD:
			SETBIT(DDRD,Pin);
			break;
		}
	}
	else if(Dir == Input)
	{
		switch(Port)
		{
			case PortA:
			CLRBIT(DDRA,Pin);
			break;
			case PortB:
			CLRBIT(DDRB,Pin);
			break;
			case PortC:
			CLRBIT(DDRC,Pin);
			break;
			case PortD:
			CLRBIT(DDRD,Pin);
			break;
		}
		
	}
}
void MCAL_GPIO_SET_PORT_DIR(GPIO_Port_t Port,PIN_Dir_t Dir)
{
	if(Dir == Output)
	{
		switch(Port)
		{
			case PortA:
			DDRA = 0xFF;
			break;
			case PortB:
			DDRB = 0xFF;
			break;
			case PortC:
			DDRC = 0xFF;
			break;
			case PortD:
			DDRD = 0xFF;
			break;
		}
	}
	else if(Dir == Input)
	{
		switch(Port)
		{
			case PortA:
			DDRA = 0x00;
			break;
			case PortB:
			DDRB = 0x00;
			break;
			case PortC:
			DDRC = 0x00;
			break;
			case PortD:
			DDRD = 0x00;
			break;
		}
	}
}
void MCAL_GPIO_SET_PIN_VAL(GPIO_Port_t Port,PIN_No_t Pin,PIN_Value_t Val)
{
	if(Val == High)
	{
		switch(Port)
		{
			case PortA:
			SETBIT(PORTA,Pin);
			break;
			case PortB:
			SETBIT(PORTB,Pin);
			break;
			case PortC:
			SETBIT(PORTC,Pin);
			break;
			case PortD:
			SETBIT(PORTD,Pin);
			break;
		}
	}
	else if(Val == Low)
	{
		switch(Port)
		{
			case PortA:
			CLRBIT(PORTA,Pin);
			break;
			case PortB:
			CLRBIT(PORTB,Pin);
			break;
			case PortC:
			CLRBIT(PORTC,Pin);
			break;
			case PortD:
			CLRBIT(PORTD,Pin);
			break;
		}
		
	}
}
void MCAL_GPIO_SET_PORT_VAL(GPIO_Port_t Port,PIN_Value_t Val)
{
	if(Val == High)
	{
		switch(Port)
		{
			case PortA:
			PORTA = 0xFF;
			break;
			case PortB:
			PORTB = 0xFF;
			break;
			case PortC:
			PORTC = 0xFF;
			break;
			case PortD:
			PORTD = 0xFF;
			break;
		}
	}
	else if(Val == Input)
	{
		switch(Port)
		{
			case PortA:
			PORTA = 0x00;
			break;
			case PortB:
			PORTB = 0x00;
			break;
			case PortC:
			PORTC = 0x00;
			break;
			case PortD:
			PORTD = 0x00;
			break;
		}
	}
}
void MCAL_GPIO_GET_PIN_VAL(GPIO_Port_t Port,PIN_No_t Pin,PIN_Value_t* Val)
{
	
		switch(Port)
		{
			case PortA:
			*Val = GETBIT(PINA,Pin);
			break;
			case PortB:
			*Val = GETBIT(PINB,Pin);
			break;
			case PortC:
			*Val = GETBIT(PINC,Pin);
			break;
			case PortD:
			*Val = GETBIT(PIND,Pin);
			break;
		}
	

}
void MCAL_GPIO_GET_PORT_VAL(GPIO_Port_t Port,PIN_Value_t* Val)
{
		switch(Port)
		{
			case PortA:
			*Val = PINA;
			break;
			case PortB:
			*Val = PINB;
			break;
			case PortC:
			*Val = PINC;
			break;
			case PortD:
			*Val = PIND;
			break;
		}
}
void MCAL_GPIO_TOG_PIN(GPIO_Port_t Port,PIN_No_t Pin)
{
			switch(Port)
			{
				case PortA:
				TOGBIT(PORTA,Pin);
				break;
				case PortB:
				TOGBIT(PORTB,Pin);
				break;
				case PortC:
				TOGBIT(PORTC,Pin);
				break;
				case PortD:
				TOGBIT(PORTD,Pin);
				break;
			}
}
void MCAL_GPIO_TOG_PORT(GPIO_Port_t Port)
{
	switch(Port)
	{
		case PortA:
		PORTA = ~PORTA;
		break;
		case PortB:
		PORTB = ~PORTB;
		break;
		case PortC:
		PORTC = ~PORTC;
		break;
		case PortD:
		PORTD = ~PORTD;
		break;
	}
}