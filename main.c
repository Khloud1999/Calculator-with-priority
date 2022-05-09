/*
 * main.c
 *
 * Created: 4/21/2022 2:45:49 PM
 *  Author: khloud & yasmeen
 */ 


#include "STD_TYPES .h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "Keypad_INT.h"
#include "LCD_interface.h"
#include "App.h"

#define F_CPU 8000000UL
#include "util/delay.h"

int main(void)
{
	 Keypad_voidInit();
	 LCD_enuInit();
	u8 Flag;
		
	while(1)
	{
	
				Flag=StartPoint;
				while(Flag==StartPoint)		{   Flag=ScanData();	  }
				while(Flag==AnalyzePoint)	{   Flag=AnalyzeData();	  }
				while(Flag==CalculatePoint)	{   Flag=calculate();     }
				while(Flag==DisplayPoint)	{   Flag=display();	      }
				while(Flag==Reset)			{   Flag=Resetall();      }
			
				while(Kepad_u8CheckPress()!='A'){}
				LCD_enuSendCommand(0X01);
	}
 return 0;
}
