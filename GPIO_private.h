/*******************************************************/
/* Author   : Khloud Khaled                            */
/* Date     : 10 OCT 2020                              */
/* File     : GPIO_private                             */
/* Version  : V 1.0                                    */
/* LOG      :                                          */
/*******************************************************/

#ifndef  GPIO_PRIVATE_H
#define  GPIO_PRIVATE_H

/* Register Definition */
    /*cast adress as u8(reg/8bits) pointer & save it from optimizer(volatile)
	(adress)from register samery >>memorry mab*/
	#define   DDRA    *((volatile u8*)0x3A) 
	#define   PORTA   *((volatile u8*)0x3B)
	#define   PINA    *((volatile u8*)0x39)
	
	#define   DDRB    *((volatile u8*)0x37) 
	#define   PORTB   *((volatile u8*)0x38)
	#define   PINB    *((volatile u8*)0x36)
	
	#define   DDRC    *((volatile u8*)0x34) 
	#define   PORTC   *((volatile u8*)0x35)
	#define   PINC    *((volatile u8*)0x33)
	
	#define   DDRD    *((volatile u8*)0x31) 
	#define   PORTD   *((volatile u8*)0x32)
	#define   PIND    *((volatile u8*)0x30)
	
#endif