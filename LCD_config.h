/*
 * LCD_config.h
 *
 *  Created on: Oct 29, 2021
 *      Author: taqwa
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/*			LCD_MODE		*/
#define LCD_MODE		EIGHT_BIT

/*			Control Pins	*/
#define RS_PORT		GPIOB
#define RS_PIN		0

#define RW_PORT		GPIOB
#define RW_PIN		1

#define EN_PORT		GPIOB
#define EN_PIN		2

/*			Data Pins		*/
#define D7_PORT		GPIOA
#define D7_PIN		7

#define D6_PORT		GPIOA
#define D6_PIN		6

#define D5_PORT		GPIOA
#define D5_PIN		5

#define D4_PORT		GPIOA
#define D4_PIN		4

#define D3_PORT		GPIOA
#define D3_PIN		3

#define D2_PORT		GPIOA
#define D2_PIN		2

#define D1_PORT		GPIOA
#define D1_PIN		1

#define D0_PORT		GPIOA
#define D0_PIN		0



#endif /* LCD_CONFIG_H_ */
