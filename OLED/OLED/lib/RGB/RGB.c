/**
* @file RGB.c
* @brief LIB to control the RGB-LED on the ZLV-Mint Board
*
* *******************************
* Date      Vers.   Name            Comment/Change
* 17.09.19  1.0     Kenneth Mathis  Created
* 30.09.19	1.1		Kenneth Mathis	Added PWM Support
*
* @author Kenneth Mathis
* @version 1.1
*/

#include "RGB.h"

// ***Init RGB PWM registers***
void rgb_init(void){
	OCR1A = 0; //RED led compare value
	OCR1B = 0; //Green led compare value
	OCR1C = 0; //Blue led compare value
	TCCR1A |= (1<<0); //Fast PWM, 8-Bit
	TCCR1B |= (1<<3);
	//Clear OC1A-C on compare match and set OC1A-C at BOTTOM (non-inverting mode)
	TCCR1A |= (1<<7)|(1<<5)|(1<<3);
	TCCR1B |= (1<<2); //256x Prescaling
}

// **Set the RGB LED's color**
void rgb(color newColor){
	//*Set the new compare match values*
	OCR1A = newColor.red;
	OCR1B = newColor.green;
	OCR1C = newColor.blue;
}