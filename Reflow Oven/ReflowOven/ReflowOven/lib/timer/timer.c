/**
* @file timer.c
* @brief LIB to control the timer0 on the ZLV-Mint Board
* @author Kenneth Mathis
* @version: 1.0
*
* *******************************
* Date      Vers.   Name            Comment/Change
* 23.09.19  1.0     Kenneth Mathis  Created
*
*/

#include "timer.h"

// ***INIT TIMER2***
void timer2_init(void){
	TCCR2B |= (1<<3); //64x Prescaling (1.02mS till Overflow)
	TIMSK2 |= (1<<0); //Enable oveflow interrupt
}