/**
 * @file sevenSegDisp.c
 * @brief LIB to control the seven segment display.
 * @author Kenneth Mathis
 * @version 1.0
 *
 * ******************************
 * Date      Vers.   Name            Comment/Change
 * 09.09.19  1.0     Kenneth Mathis  Created
 */

//***INCLUDES***
#include <avr/io.h>
#include <math.h>
#include "sevenSegDisp.h"
#include "matrix.h"

//***DEFINES***
#define setSeg(bit) (PORTH |= (bit))
#define delSeg(bit) (PORTH &= (bit))

//***PROTOTYPES***
uint8_t numberToBitmask(uint8_t num, uint8_t dotted);

void updateSegment(unsigned int segNumber, uint8_t dotPos){
	static uint8_t segPos;
	
	segDisable;
	//**Select which segment is currently being displayed**
	switch(segPos){
		case 0:
			segSel0_off;
			segSel1_off;
			break;
		case 1:
			segSel0_on;
			segSel1_off;
			break;
		case 2:
			segSel0_off;
			segSel1_on;
			break;
		case 3:
			segSel0_on;
			segSel1_on;
			break;
		default:
			segSel0_off;
			segSel1_off;
			break;
	}
	
	//**Create the bitmask for the given number and set the PORT to it**
	uint8_t bitmask;
	if(segNumber == 0){
		bitmask = numberToBitmask(0, 0);
	}	//If the given number is zero, display it as such
	else{
		uint8_t segDigit;
		segDigit = ((uint8_t)(segNumber/pow(10, segPos)))%10;	//Get the digit at segPos from segNumber
		if(dotPos == segPos) //Determine if the current segment is dotted
			bitmask = numberToBitmask(segDigit, 1);
		else bitmask = numberToBitmask(segDigit, 0);
	}
	
	setSeg(bitmask);
	delSeg(bitmask);
	segEnable;
	
	if(segPos < 3) segPos++; //increment the segment position till the last segment
	else segPos = 0; //set the segment position to zero if its past the last one
}

/***NUMBER TO BITMASK***
 * @brief Turns a number into a seven segment bitmask
 * @param: num the number to turn into a 7-segment bitmask
 * @param: dotted If the wanted number should be dotted
 * @return: the bitmask of the given number
*/
uint8_t numberToBitmask(uint8_t num, uint8_t dotted){
	switch(num){
		case 0:
			return 0b00111111 | dotted<<7;
		case 1:
			return 0b00000110 | dotted<<7;
		case 2:
			return 0b01011011 | dotted<<7;
		case 3:
			return 0b01001111 | dotted<<7;
		case 4:
			return 0b01100110 | dotted<<7;
		case 5:
			return 0b01101101 | dotted<<7;
		case 6:
			return 0b01111101 | dotted<<7;
		case 7:
			return 0b00000111 | dotted<<7;
		case 8:
			return 0b01111111 | dotted<<7;
		case 9:
			return 0b01101111 | dotted<<7;
		default:
			return 0b01000000 | dotted<<7;
	}
}