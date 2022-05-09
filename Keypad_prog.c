/*
 * Keypad_prog.c
 *
 * Created: 9/13/2021 7:46:34 PM
 *  Author: Yasmeen
 */ 

 #include "STD_TYPES .h"
 #include "BIT_MATH.h"

 #include "GPIO_interface.h"

 #include "Keypad_INT.h"
 #include "Keypad_CONFG.h"

 #define  F_CPU  8000000UL
 #include "util/delay.h"



u8 Keypad [4][4] = { 	{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'A', '0','=','+'}};

void Keypad_voidInit ()
{
	
	GPIO_voidSetPinDDR(KEYPADPORT ,R0 ,INPUT);
	GPIO_voidSetPinDDR(KEYPADPORT ,R1 ,INPUT);
	GPIO_voidSetPinDDR(KEYPADPORT ,R2 ,INPUT);
	GPIO_voidSetPinDDR(KEYPADPORT ,R3 ,INPUT);
							
	GPIO_voidSetPinDDR(KEYPADPORT ,C0 ,OUTPUT);
	GPIO_voidSetPinDDR(KEYPADPORT ,C1 ,OUTPUT);
	GPIO_voidSetPinDDR(KEYPADPORT ,C2 ,OUTPUT);
	GPIO_voidSetPinDDR(KEYPADPORT ,C3 ,OUTPUT);

	//write in input 1 & output pull up (write in pin 1)
	GPIO_voidWritePort(KEYPADPORT ,0xFF);
}

u8 Kepad_u8CheckPress()
{
	u8 Row , Column , Return  , Value = NOTPRESSED;
    while(Value ==NOTPRESSED){
		for (Column = 0 ; Column <4 ; Column++)
		{
			//Activate column
			GPIO_voidWritePin(KEYPADPORT , (Column+4) , LOW );

			for (Row = 0 ; Row <4 ; Row++ )
			{
				Return=GPIO_u8ReadPin(KEYPADPORT , Row );

				if (Return == 0 )
				{
					Value = Keypad [Row][Column];
					_delay_ms(30);
					break;
				}
			}
			//Deactivate COl
			GPIO_voidWritePin(KEYPADPORT , (Column+4) , HIGH);
		}
	}
	return Value ;
}


 
