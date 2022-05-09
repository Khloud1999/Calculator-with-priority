/*
 * calc.c
 *
 *  Created on: 
 */

#include "STD_TYPES .h"
#include "BIT_MATH.h"
#include "App.h"
#define F_CPU 8000000UL
#include "util/delay.h"
#include <stdint.h>
#include <string.h>
#include "LCD_private.h"

s64 Result=0;
s64 Operands[MaxNumberOfOperands];
u8 Operations[MaxNumberOfOperations];
u8 Digit[MaxNumberOfDigit];

u8 OperandsCounter=0; 
u8 OperationsCounter=0; 
u8 DigitCounter=0;

s8 Sign =1;
u8 OtherNumberSign=false;

u8 ScanData ()
{
	u8 temp=0;
	temp =Kepad_u8CheckPress();
	while(temp!= '=')
	{
		
		if (temp == 'A')
		{
			Resetall();
			LCD_enuSendCommand(0x01);
		}
		
		//storing any thing the user input
		if((temp!=0) && (temp != 'A'))
		{
			
			Digit[DigitCounter]=temp;
			LCD_enuDisplayChar(Digit[DigitCounter]);
			DigitCounter++;
			_delay_ms(50);
			
		}
		temp=Kepad_u8CheckPress();
	
	}	
	Digit[DigitCounter]='=';
	LCD_enuDisplayChar(Digit[DigitCounter]);
	DigitCounter++;
	Digit[DigitCounter]='\0'; // to close array
	
	return AnalyzePoint; 
	
}

s32 ConvertToInt(u8 array[]){
	s32 num=0, sign=1, i=-1;

	if(array[0] == '-')    //check if the string is -ve
	{
		sign = -1;
		i = 0;           //skip the -ve sign to the number
	}

	while(array[++i] != 0)
	{
		num = (num * 10) + (array[i] - '0');
	}

	num *= sign;
	return num;
}

void InitArray(u8 array[]){
	u8 i =0;
	while(array[i] != '\0'){
		array[i]='\0';
		i++;
	}
}


u8 AnalyzeData()
{
	s8 TempArr[MaxNumberOfDigit]={0};
	u8 TempIndex=0;
	u8 index=0;
	
	Sign =1;
	OtherNumberSign =1;
	
	if (IsOperation(Digit[0]) && Digit[0]!= '-'&& Digit[0]!= '+') //input ex (*5)
	{
		LCD_voidSendString("Syntax error");
		_delay_ms(100);
		return Reset;
	}
	
	while(DigitCounter != 0)
	{
		if(((Digit[index]>='0') && (Digit[index]<='9')) || ((Digit[index]=='-') && (IsOperation(Digit[index-1])))/*||OtherNumberSign*/)
		{
			TempArr[TempIndex]=Digit[index];
			TempIndex++;

		}
		else if (((IsOperation(Digit[index]))||(Digit[index]== '=')))
		{
			Operations[OperationsCounter]=Digit[index];
			OperationsCounter++;
			Operands[OperandsCounter]= ConvertToInt(TempArr)/* Sign*/;
			OperandsCounter++;
			InitArray(TempArr);
			TempIndex=0;
		}
		index++;
		DigitCounter--;
	}
	return CalculatePoint;
}


void shift_s64array_left(u64* array ,u8 start_index){

	
	for(u8 i = start_index;1; i++) {
		
		array[i]=array[i+1];
		if(array[i] == '\0'){
			break;
		}
	}
}

void shift_u8array_left(u8 array[] ,u8 start_index){

	
	for(u8 i = start_index;1; i++) {
		
		array[i]=array[i+1];
		if(array[i] == '\0'){
			break;
		}
	}
}

s64 SubCalculate(s64 operand1,s64 operand2,u8 operation)
{
	s64 return_value = 0;
	if (operation != '=')
	{
		switch(operation)
		{
			case '+' :
			return_value = operand1+operand2;
			break;
			case '-' :
			return_value = operand1-operand2;
			break;
			case '*' :
			return_value = operand1*operand2;
			break;
			case '/' :
			return_value = operand1/operand2;
			break;
		}
		
		return return_value;
	}
	
	return 0;
}

u8 calculate(){
	u8 Operations_index=0 , Operands_index;
	
	while((Operations[Operations_index] != '=') && (Operations[Operations_index] != '\0') )
	{
		if (Operations[Operations_index] == '*')
		{
			Operands[Operations_index] = Operands[Operations_index] * Operands[Operations_index+1];
			shift_s64array_left((u64*)Operands,Operations_index+1);
			shift_u8array_left(Operations,Operations_index);

		}
		else if (Operations[Operations_index] == '/')
		{
			Operands[Operations_index] = Operands[Operations_index] / Operands[Operations_index+1];
			shift_s64array_left((u64*)Operands,Operations_index+1);
			shift_u8array_left(Operations,Operations_index);

		}
		else
		{
			Operations_index++;
		}	
	}
	
	Operations_index=0; Operands_index =1;
	Result = Operands[0];
	while((Operations[Operations_index] != '=') && (Operands[Operands_index] != '\0') )
	{
		Result =SubCalculate(Result,Operands[Operands_index],Operations[Operations_index]);
		Operations_index++;
		Operands_index++;
	}

	return DisplayPoint;
}

u8  display()
{

	LCD_voidSetPosition(LCD_ROW_2,LCD_COL_1);
	LCD_voidSendINTNum(Result);

	return Reset;
}

u8  Resetall()
{
	u8 index=0;
	for(index=0;index<MaxNumberOfDigit;index++)
	Digit[index]=0;
	for(index=0;index<MaxNumberOfOperands;index++)
	Operands[index]=0;
	for(index=0;index<MaxNumberOfOperations;index++)
	Operations[index]=0;
	OperandsCounter=0;
	OperationsCounter=0;
	DigitCounter=0;
	Result=0;

	return StartPoint;
}