/**
* @file RGB.h
* @brief LIB to control the RGB-LED on the ZLV-Mint Board
* @author Kenneth Mathis
* @version: 1.0
*
* *******************************
* Date      Vers.   Name            Comment/Change
* 17.09.19  1.0     Kenneth Mathis  Created
*
*/


#ifndef RGB_H
#define RGB_H
	//***INCLUDES***
	#include <avr/io.h>
	
	//***STRUCT DEFINITIONS***
	typedef struct{
		uint8_t r;
		uint8_t g;
		uint8_t b;
	} color;
		
	//***PROTOTYPES***
	/**
	* @brief Set the RGB-LED's color based on an color struct.
	* @param newColor Color struct to represent the led's color.
	*/
	void rgb(color newColor);

#endif