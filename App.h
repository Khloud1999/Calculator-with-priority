/*
 * calc.h
 *
 *  Created on: Apr 24, 2022
 *      Author:  
 */ 


#ifndef APP_H_
#define APP_H_



#define MaxNumberOfDigit 16
#define MaxNumberOfOperands 12	//including =
#define MaxNumberOfOperations MaxNumberOfOperands-1 //excluding =


//enum Flags{Reset=0,StartPoint,AnalyzePoint,CalculatePoint,DisplayPoint,ErrorPoint};
#define Reset			0
#define StartPoint		1
#define AnalyzePoint	2
#define CalculatePoint	3
#define DisplayPoint	    4

#define IsOperation(n) ((n=='*')||(n=='+')||(n=='-')||(n=='/'))

#define true 1
#define false 0


u8  ScanData (); //store any key pressed from user
s32 ConvertToInt(u8 array[]);//Convert ASCII to integer
void InitArray(u8 array[]);
u8  AnalyzeData();//differentiates between operands & operations, signed & unsigned 
void shift_s64array_left(u64* array ,u8 start_index);
void shift_u8array_left(u8 array[] ,u8 start_index);
s64 SubCalculate(s64 operand1,s64 operand2,u8 operation);
u8  calculate();
u8  display();
u8  Resetall();


#endif /* APP_H_ */