/**
* @file RGB.h
* @brief LIB to control the RGB-LED on the ZLV-Mint Board
* @author Kenneth Mathis
* @version 1.0
*
* *******************************
* Date      Vers.   Name            Comment/Change
* 17.09.19  1.0     Kenneth Mathis  Created
* 30.09.19	1.1		Kenneth Mathis	Added PWM Support
*
*/


#ifndef RGB_H
#define RGB_H
	//***INCLUDES***
	#include <avr/io.h>
	
	//***STRUCT DEFINITIONS***
	typedef struct{
		uint8_t red;
		uint8_t green;
		uint8_t blue;
	} color;

	//***PROTOTYPES***
	/**
	* @brief Initialize all the registers for the RGB-LED's pwm color.
	* @param void
	*/
	void rgb_init(void);
	/**
	* @brief Set the RGB-LED's color based on an color struct.
	* @param newColor Color struct to represent the led's color.
	*/
	void rgb(color newColor);

#endif /* RGB_H_ */