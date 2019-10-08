/**
* @file timer.h
* @brief LIB to control the timer0 on the ZLV-Mint Board
* @author Kenneth Mathis
* @version: 1.0
*
* *******************************
* Date      Vers.   Name            Comment/Change
* 23.09.19  1.0     Kenneth Mathis  Created
*
*/

#ifndef TIMER_H
#define TIMER_H
	#include <avr/io.h>

	/**
	* @brief Initialize the timer0
	* @param void
	*/
	void timer2_init(void);
	
#endif