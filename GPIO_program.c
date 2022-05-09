/*******************************************************/
/* Author   : Khloud Khaled                            */
/* Date     : 10 OCT 2020                              */
/* File     : GPIO_program                             */
/* Version  : V 1.0                                    */
/* LOG      : 1- Add Port set Direction                */
/*				 Add Write On Port                     
			  2- Add Nibble set Direction              
				 Add
			 3- Toggle port                           */
/*******************************************************/


/* LIB include */
#include "STD_TYPES .h"
#include "BIT_MATH.h"

/* Driver Include */
#include "GPIO_interface.h"
#include "GPIO_private.h"

void GPIO_voidSetPinDDR(u8 copy_u8Port	,u8 copy_u8Pin ,u8 copy_u8direction)
{
	switch(copy_u8Port)
	{
		case GPIOA:
			if(copy_u8direction == OUTPUT)
			{
				SET_BIT(DDRA,copy_u8Pin);
			}
			else
			{
				CLR_BIT(DDRA,copy_u8Pin);
			}
			break;
		case GPIOB:
			if(copy_u8direction == OUTPUT)
			{
				SET_BIT(DDRB,copy_u8Pin);
			}
			else
			{
				CLR_BIT(DDRB,copy_u8Pin);
			}
			break;
		case GPIOC:
			if(copy_u8direction == OUTPUT)
			{
				SET_BIT(DDRC,copy_u8Pin);
			}
			else
			{
				CLR_BIT(DDRC,copy_u8Pin);
			}
			break;
		case GPIOD:
			if(copy_u8direction == OUTPUT)
			{
				SET_BIT(DDRD,copy_u8Pin);
			}
			else
			{
				CLR_BIT(DDRD,copy_u8Pin);
			}
			break;
		default :
			break;
	}
}

void GPIO_voidWritePin(u8 copy_u8Port	,u8 copy_u8Pin ,u8 copy_u8Value)
{
	switch(copy_u8Port)
	{
		case(GPIOA):
			if(copy_u8Value == HIGH)
			{
				SET_BIT(PORTA,copy_u8Pin);
			}
			else
			{
				CLR_BIT(PORTA,copy_u8Pin);
			}
			break;
		case(GPIOB):
			if(copy_u8Value == HIGH)
			{
				SET_BIT(PORTB,copy_u8Pin);
			}
			else
			{
				CLR_BIT(PORTB,copy_u8Pin);
			}
			break;
		case(GPIOC):
			if(copy_u8Value == HIGH)
			{
				SET_BIT(PORTC,copy_u8Pin);
			}
			else
			{
				CLR_BIT(PORTC,copy_u8Pin);
			}
			break;
		case(GPIOD):
			if(copy_u8Value == HIGH)
			{
				SET_BIT(PORTD,copy_u8Pin);
			}
			else
			{
				CLR_BIT(PORTD,copy_u8Pin);
			}
		    break;
		default :
			break;
	}
}


u8 GPIO_u8ReadPin(u8 copy_u8Port ,u8 copy_u8Pin )
{
	u8 Local_u8Value=0;
	switch(copy_u8Port)
	{
		case GPIOA :
			Local_u8Value = GET_BIT(PINA,copy_u8Pin);
			break;
		case GPIOB :
			Local_u8Value = GET_BIT(PINB,copy_u8Pin);
			break;
		case GPIOC :
			Local_u8Value = GET_BIT(PINC,copy_u8Pin);
			break;
		case GPIOD :
			Local_u8Value = GET_BIT(PIND,copy_u8Pin);
			break;
		default :
			break;
	}
	return Local_u8Value;

}

void GPIO_voidTogglePin(u8 copy_u8Port	,u8 copy_u8Pin )
{
	switch(copy_u8Port){

		case GPIOA:
            TOG_BIT(PORTA,copy_u8Pin);
			break;

	    case GPIOB:
            TOG_BIT(PORTB,copy_u8Pin);
			break;

	    case GPIOC:
            TOG_BIT(PORTC,copy_u8Pin);
			break;

		case GPIOD:
            TOG_BIT(PORTD,copy_u8Pin);
			break;
}
}


void GPIO_voidSetPortDDR(u8 copy_u8Port ,u8 copy_u8direction)
{
	switch(copy_u8Port)
	{
		case GPIOA :
			if(copy_u8direction == OUTPUT)
			{
				DDRA = 0xff;
			}
			else
			{
				DDRA = 0x00;
			}
			break;
		case GPIOB :
			if(copy_u8direction == OUTPUT)
			{
				DDRB = 0xff;
			}
			else
			{
				DDRB = 0x00;
			}
			break;
		case GPIOC :
			if(copy_u8direction == OUTPUT)
			{
				DDRC = 0xff;
			}
			else
			{
				DDRC = 0x00;
			}
			break;
		case GPIOD :
			if(copy_u8direction == OUTPUT)
			{
				DDRD = 0xff;
			}
			else
			{
				DDRD = 0x00;
			}
			break;
		default:
			break;
	}
}

void GPIO_voidWritePort(u8 copy_u8Port ,u8 copy_u8Value)
{
	switch(copy_u8Port)
	{
	case GPIOA :
		PORTA = copy_u8Value;
	    break;
	case GPIOB :
		PORTB = copy_u8Value;
		break;
	case GPIOC :
		PORTC = copy_u8Value;
		break;
	case GPIOD :
		PORTD = copy_u8Value;
	    break;
	default    :
		 break;
	}
}


u8 GPIO_u8ReadPort(u8 copy_u8Port)
{
	u8 Local_u8Value =0;
	switch(copy_u8Port)
	{
	case GPIOA :
		Local_u8Value =PINA;
	    break;
	case GPIOB :
		Local_u8Value =PINB;
		break;
	case GPIOC :
		Local_u8Value =PINC;
		break;
	case GPIOD :
		Local_u8Value=PIND;
	    break;
	default    :
		 break;
	}
	return Local_u8Value;
}


void GPIO_u8TogglePort(u8 copy_u8Port)
{
	switch(copy_u8Port)
	{
	case GPIOA :
	//PORTA =PORTA^0XFF
		PORTA=~PORTA;
	    break;
	case GPIOB :
		PORTB=~PORTB;
		break;
	case GPIOC :
		PORTC=~PORTC;
		break;
	case GPIOD :
		PORTD=~PORTD;
	    break;
	default    :
		 break;
	}
}


void GPIO_voidSetLowNibbleDDR(u8 copy_u8Port, u8 copy_u8direction)
{
	for (u8 i=0;i<=3 ;i++){
		GPIO_voidSetPinDDR(copy_u8Port	,i , copy_u8direction);
	}
}

void GPIO_voidSetHighNibbleDDR(u8 copy_u8Port,u8 copy_u8direction)
{
	for (u8 i=4;i<=7 ;i++){
		GPIO_voidSetPinDDR(  copy_u8Port,i,copy_u8direction);
	}
}

void GPIO_voidWriteLowNibble(u8 copy_u8Port ,u8 copy_u8Value)
{

	copy_u8Value&=0x0f; ////to save four low bites make most =0
	switch (copy_u8Port)
	{
		case GPIOA :
			PORTA&=0xf0;
			PORTA|=copy_u8Value;
			break;

		case GPIOB :
			PORTB&=0xf0;
			PORTB|=copy_u8Value;
			break;
		case GPIOC:
			PORTC&=0xf0;
			PORTC|=copy_u8Value;
			break;
		case GPIOD :
			PORTD&=0xf0;
			PORTD|=copy_u8Value;
			break;
		default :
		   break;
	}
}

void GPIO_voidWritHighNibble(u8 copy_u8Port ,u8 copy_u8Value)
{
	copy_u8Value&=0xf0; //to save four most bites make low =0
	switch (copy_u8Port)
	{
		case GPIOA :
			PORTA&=0x0f;
			PORTA|=copy_u8Value;
			break;

		case GPIOB :
			PORTB&=0x0f;
			PORTB|=copy_u8Value;
			break;
		case GPIOC:
			PORTC&=0x0f;
			PORTC|=copy_u8Value;
			break;
		case GPIOD :
			PORTD&=0x0f;
			PORTD|=copy_u8Value;
			break;
		default :
		   break;
	}
}


