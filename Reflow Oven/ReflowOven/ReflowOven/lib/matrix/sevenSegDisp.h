/**
 * @file sevenSegDisp.h
 * @brief LIB to control the seven segment display.
 * @author Kenneth Mathis
 * @version 1.0
 *
 * ******************************
 * Date      Vers.   Name            Comment/Change
 * 09.09.19  1.0     Kenneth Mathis  Created
 * 24.09.19  1.1     Kenneth Mathis  Added clearSeg
 */

#ifndef SEVENSEGDISP_H
#define SEVENSEGDISP_H

    #define colon_on	(PORTG |= (1<<4))
    #define colon_off	(PORTG &= ~(1<<4))
    #define apostrophe_on	(PORTG |= (1<<3))
    #define apostrophe_off	(PORTG &= ~(1<<3))

    #define segEnable (PORTG |= (1<<2))
    #define segDisable (PORTG &= ~(1<<2))
	
	#define clearSeg (PORTH = 0)
	
	/**
	* @brief Update the seven segment display with a number
	* Note: This function takes care of the incremeting
	* so no individual segment can be set.
	* @param segNumber The Number to display on the segment.
	* @param dotPos The position of the dot. Set it to 4 or higher for no dot.
	*/
    void updateSegment(unsigned int segNumber, uint8_t dotPos);

#endif