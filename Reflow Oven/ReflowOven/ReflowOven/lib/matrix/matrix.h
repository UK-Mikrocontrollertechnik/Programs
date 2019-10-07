/**
 * @file matrix.h
 * @brief LIB to control the mux and enable signal to the seven segment display and keypad.
 * @author Kenneth Mathis
 * @version 1.0
 *
 * ******************************
 * Date      Vers.   Name            Comment/Change
 * 09.09.19  1.0     Kenneth Mathis  Created
 */

#ifndef MATRIX_H
#define MATRIX_H

    //Enable and Disable the segment and keypad
    #define mtxEnable (PORTG |= (1<<2))
    #define mtxDisable (PORTG &= ~(1<<2))

    //Mux signals for selecting a segment/keypad row
    #define segSel0_off (PORTG &= ~(1<<0))
    #define segSel1_off (PORTG &= ~(1<<1))
    #define segSel0_on (PORTG |= (1<<0))
    #define segSel1_on (PORTG |= (1<<1))

    //***PROTOTYPES***
	/**
	* @brief Preps the seven segment display and keypad for use.
	* @param Void
	*/
    void matrix_init(void);
	
#endif