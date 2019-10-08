/**
* @file RGB.c
* @brief LIB to control the RGB-LED on the ZLV-Mint Board
* @author Kenneth Mathis
* @version 1.0
* 
* *******************************
* Date      Vers.   Name            Comment/Change
* 17.09.19  1.0     Kenneth Mathis  Created
*
*/

#include "RGB.h"

// ***RGB LED***
void rgb(color newColor){
	PORTB |= (newColor.r<<5)|(newColor.g<<6)|(newColor.b<<7);
	
	//Because a 0 turns anything off with an "and-set", its necessary to set every bit outside of
	//the RGB bits to 1. Thats why there is a |0x8f (|0b1000 1111) at the end.
	PORTB &= (newColor.r<<5)|(newColor.g<<6)|(newColor.b<<7)|0x1f;
}