/**
* @file matrix.c
* @brief LIB to control the mux and enable signal to the seven segment display and keypad.
* @author Kenneth Mathis
* @version 1.0
*
* ******************************
* Date      Vers.   Name            Comment/Change
* 09.09.19  1.0     Kenneth Mathis  Created
*/

#include <avr/io.h>
#include "matrix.h"

void matrix_init(void){
    //**Data Direction Registers**
	//*1=Output*
	DDRH = 0xff; //DDR of the individual segments
    DDRG |= 0x1f; //DDR of the multiplexing/control signals
    DDRD &= 0x70; //DDR of the keypad read pins
    mtxEnable; //Enable the matrix
}
