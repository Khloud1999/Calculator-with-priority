/*
 * LCD_program.c
 *
 *  Created on: Oct 29, 2021
 *      Author: taqwa
 */

#include "STD_TYPES .h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"

#define F_CPU 8000000UL
#include "util/delay.h"

GPIO_ErrorStatus LCD_enuInit(void)
{
	GPIO_ErrorStatus LOC_enumState = GPIO_OK ;

	GPIO_voidSetPinDDR(RS_PORT	, RS_PIN , OUTPUT);
	GPIO_voidSetPinDDR(RW_PORT	, RW_PIN , OUTPUT);
	GPIO_voidSetPinDDR(EN_PORT	, EN_PIN , OUTPUT);

	GPIO_voidSetPinDDR(D7_PORT, D7_PIN, OUTPUT);
	GPIO_voidSetPinDDR(D6_PORT, D6_PIN, OUTPUT);
	GPIO_voidSetPinDDR(D5_PORT, D5_PIN, OUTPUT);
	GPIO_voidSetPinDDR(D4_PORT, D4_PIN, OUTPUT);

	_delay_ms(50);

#if LCD_MODE == EIGHT_BIT
	GPIO_voidSetPinDDR(D3_PORT, D3_PIN, OUTPUT);
	GPIO_voidSetPinDDR(D2_PORT, D2_PIN, OUTPUT);
	GPIO_voidSetPinDDR(D1_PORT, D1_PIN, OUTPUT);
	GPIO_voidSetPinDDR(D0_PORT, D0_PIN, OUTPUT);

	// function set
	LCD_invidSendCommend(0x38);

#elif  LCD_MODE ==FOUR_BIT
	// function set
	LCD_invidSendCommend(0x28);
#endif

	_delay_ms(1);
	//Display on off
	LCD_invidSendCommend(0x0C);
	_delay_ms(1);
	//clear display
	LCD_invidSendCommend(0x01);
	_delay_ms(2);
	//entry mode
	LCD_invidSendCommend(0x06);

	return LOC_enumState;
}


GPIO_ErrorStatus LCD_enuDisplayChar(u8 Copy_u8Data)
{

	GPIO_ErrorStatus LOC_enumState=GPIO_OK;
	//set RS as Data
	GPIO_voidWritePin(RS_PORT ,RS_PIN ,HIGH);
	LCD_voidLatch( Copy_u8Data);

	return LOC_enumState;
}


GPIO_ErrorStatus LCD_enuSendCommand(u8 Copy_u8Command)
{
	GPIO_ErrorStatus LOC_enumState=GPIO_OK;
	//set RS as command
	GPIO_voidWritePin(RS_PORT ,RS_PIN ,LOW);
	LCD_voidLatch( Copy_u8Command);

	return LOC_enumState;
}

void LCD_voidSendString  ( const u8* Copy_u8ptrString )
{

	u8 LOC_u8Iterator=0;

	while(Copy_u8ptrString[LOC_u8Iterator]!= '\0')
	{
		LCD_enuDisplayChar(Copy_u8ptrString[LOC_u8Iterator]);
		LOC_u8Iterator++;

	}

}


void LCD_voidSetPosition ( u8 Copy_u8Row , u8 Copy_u8Col )
{

	if(Copy_u8Row==LCD_ROW_1)
	{
		LCD_invidSendCommend((0x80) + ( Copy_u8Col - 1 ));
	}

	else if(Copy_u8Row==LCD_ROW_2)
	{
		LCD_invidSendCommend((0x80)+64 + ( Copy_u8Col - 1 ));

	}

}


void LCD_voidSendINTNum(s64 copy_u32Num)
{
	
	s64 LOC_u32Reversed = 1 ;
	
	if( copy_u32Num == 0 ){ LCD_enuDisplayChar('0'); }
	
	else{
		if (copy_u32Num < 0)
		{
			LCD_enuDisplayChar('-');
			copy_u32Num *=-1;
		}
		while ( copy_u32Num != 0 ){
			
			LOC_u32Reversed = ( LOC_u32Reversed * 10 ) + ( copy_u32Num % 10 );
			copy_u32Num /= 10 ;
			
		}
		
		while ( LOC_u32Reversed != 1 ){
			GPIO_voidWritePin(RS_PORT,RS_PIN,HIGH);
			LCD_voidLatch( ( LOC_u32Reversed % 10 ) + 48 );
			LOC_u32Reversed /= 10 ;
			
		}
	}
}




void LCD_voidSendExtraChar(u8 *copy_u8Parr,u8 copy_u8CharNum,u8 copy_u8position,u8 copy_u8EntryMode)
{
	u8 LOC_u8Iterator = 0 ;
	//Go To CGRAM
	LCD_invidSendCommend(0b01000000);
	// set RS as data
	GPIO_voidWritePin(RS_PORT, RS_PIN,HIGH);
	//Draw Character
	for(LOC_u8Iterator=0;LOC_u8Iterator<(copy_u8CharNum*8);LOC_u8Iterator++)
	{
		LCD_voidLatch(copy_u8Parr[LOC_u8Iterator]);
	}
	if(copy_u8EntryMode==0x04)
	{
		//return to DDRAM
		LCD_invidSendCommend(copy_u8position);
		LCD_invidSendCommend(copy_u8EntryMode);


	}
	//send address
	for(LOC_u8Iterator=0;LOC_u8Iterator<copy_u8CharNum;LOC_u8Iterator++)
	{
		GPIO_voidWritePin(RS_PORT, RS_PIN,HIGH);
		LCD_voidLatch(LOC_u8Iterator);


	}

}


void LCD_voidSendFloatNumber(f64 Copy_f64Number)
{


	// send int num
	LCD_voidSendINTNum((u64)Copy_f64Number );
	// Send decimal point
	LCD_enuDisplayChar('.');

	// Multiply the Float Number by 10^6 so the decimal number becomes part number
	u64 Local_u64tempNumber = Copy_f64Number*1000000;

	if( Local_u64tempNumber%10 >=5 )
	{

		LCD_voidSendINTNum((u64)((( Local_u64tempNumber/10)+1) % 100000));
	}
	else
	{

		// Display the number
		LCD_voidSendINTNum((u64)(( Local_u64tempNumber/10) % 100000));

	}


}

static inline void LCD_invidSendCommend(u8 Copy_u8Command)
{
	//set RS as command
	GPIO_voidWritePin(RS_PORT ,RS_PIN ,LOW);

	// set RW as  write operation,EN LOW
	GPIO_voidWritePin(RW_PORT, RW_PIN,LOW);
	GPIO_voidWritePin(EN_PORT, EN_PIN,LOW);

	//write data
	GPIO_voidWritePin(D7_PORT, D7_PIN,GET_BIT(Copy_u8Command,7) );
	GPIO_voidWritePin(D6_PORT, D6_PIN, GET_BIT(Copy_u8Command,6) );
	GPIO_voidWritePin(D5_PORT, D5_PIN, GET_BIT(Copy_u8Command,5)  );
	GPIO_voidWritePin(D4_PORT, D4_PIN, GET_BIT(Copy_u8Command,4)  );

#if LCD_MODE==EIGHT_BIT

	GPIO_voidWritePin(D3_PORT, D3_PIN,GET_BIT(Copy_u8Command,3) );
	GPIO_voidWritePin(D2_PORT, D2_PIN, GET_BIT(Copy_u8Command,2) );
	GPIO_voidWritePin(D1_PORT, D1_PIN, GET_BIT(Copy_u8Command,1) );
	GPIO_voidWritePin(D0_PORT, D0_PIN, GET_BIT(Copy_u8Command,0) );

#elif LCD_MODE == FOUR_BIT
	if(Copy_u8Command=0x28)
	{
		// falling edge
		GPIO_voidWritePin(EN_PORT, EN_PIN,HIGH);
		_delay_ms(10);
		GPIO_voidWritePin(EN_PORT, EN_PIN,LOW);
		_delay_ms(10);
		GPIO_voidWritePin(D7_PORT, D7_PIN,GET_BIT(Copy_u8Command,7) );
		GPIO_voidWritePin(D6_PORT, D6_PIN, GET_BIT(Copy_u8Command,6) );
		GPIO_voidWritePin(D5_PORT, D5_PIN, GET_BIT(Copy_u8Command,5)  );
		GPIO_voidWritePin(D4_PORT, D4_PIN, GET_BIT(Copy_u8Command,4)  );
	}


	// falling edge
	GPIO_voidWritePin(EN_PORT, EN_PIN,HIGH);
	_delay_ms(10);
	GPIO_voidWritePin(EN_PORT, EN_PIN,LOW);
	_delay_ms(10);

	GPIO_voidWritePin(D3_PORT, D3_PIN,GET_BIT(Copy_u8Command,3) );
	GPIO_voidWritePin(D2_PORT, D2_PIN, GET_BIT(Copy_u8Command,2) );
	GPIO_voidWritePin(D1_PORT, D1_PIN, GET_BIT(Copy_u8Command,1) );
	GPIO_voidWritePin(D0_PORT, D0_PIN, GET_BIT(Copy_u8Command,0) );


#else
#error Wrong Selection


#endif

	// falling edge
	GPIO_voidWritePin(EN_PORT, EN_PIN,HIGH);
	_delay_ms(10);
	GPIO_voidWritePin(EN_PORT, EN_PIN,LOW);
	_delay_ms(10);

}





static void LCD_voidLatch(u8 copy_u8Data)
{

	// set RW as  write operation,EN LOW
	GPIO_voidWritePin(RW_PORT, RW_PIN,LOW);
	GPIO_voidWritePin(EN_PORT, EN_PIN,LOW);

	//write data
	GPIO_voidWritePin(D7_PORT, D7_PIN,GET_BIT (copy_u8Data,7) );
	GPIO_voidWritePin(D6_PORT, D6_PIN, GET_BIT(copy_u8Data,6) );
	GPIO_voidWritePin(D5_PORT, D5_PIN, GET_BIT(copy_u8Data,5)  );
	GPIO_voidWritePin(D4_PORT, D4_PIN, GET_BIT(copy_u8Data,4)  );

#if LCD_MODE==EIGHT_BIT

	GPIO_voidWritePin(D3_PORT, D3_PIN,GET_BIT (copy_u8Data,3) );
	GPIO_voidWritePin(D2_PORT, D2_PIN, GET_BIT(copy_u8Data,2) );
	GPIO_voidWritePin(D1_PORT, D1_PIN, GET_BIT(copy_u8Data,1) );
	GPIO_voidWritePin(D0_PORT, D0_PIN, GET_BIT(copy_u8Data,0) );

#elif LCD_MODE == FOUR_BIT
	if(Copy_u8Command =0x28)
	{
		// falling edge
		GPIO_voidWritePin(EN_PORT, EN_PIN,HIGH);
		_delay_ms(10);
		GPIO_voidWritePin(EN_PORT, EN_PIN,LOW);
		_delay_ms(10);
		GPIO_voidWritePin(D7_PORT, D7_PIN,GET_BIT( copy_u8Data,7) );
		GPIO_voidWritePin(D6_PORT, D6_PIN, GET_BIT(copy_u8Data,6) );
		GPIO_voidWritePin(D5_PORT, D5_PIN, GET_BIT(copy_u8Data,5)  );
		GPIO_voidWritePin(D4_PORT, D4_PIN, GET_BIT(copy_u8Data,4)  );
	}


	// falling edge
	GPIO_voidWritePin(EN_PORT, EN_PIN,HIGH);
	_delay_ms(10);
	GPIO_voidWritePin(EN_PORT, EN_PIN,LOW);
	_delay_ms(10);

	GPIO_voidWritePin(D3_PORT, D3_PIN,GET_BIT (copy_u8Data,3) );
	GPIO_voidWritePin(D2_PORT, D2_PIN, GET_BIT(copy_u8Data,2) );
	GPIO_voidWritePin(D1_PORT, D1_PIN, GET_BIT(copy_u8Data,1) );
	GPIO_voidWritePin(D0_PORT, D0_PIN, GET_BIT(copy_u8Data,0) );


#else
#error "Wrong Selection"


#endif

	// falling edge
	GPIO_voidWritePin(EN_PORT, EN_PIN,HIGH);
	_delay_ms(10);
	GPIO_voidWritePin(EN_PORT, EN_PIN,LOW);
	_delay_ms(10);



}
















