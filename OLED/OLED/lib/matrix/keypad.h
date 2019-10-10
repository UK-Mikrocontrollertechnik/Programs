/**

 * @file keypad.h
 * @brief LIB to control the keypad
 * @author Kenneth Mathis
 * @version 1.0
 *
 * ******************************
 * Date      Vers.   Name            Comment/Change
 * 09.09.19  1.0     Kenneth Mathis  Created
 */


#ifndef KEYPAD_H
#define KEYPAD_H


/**
* @brief Read the keypad for any pin changes
* @param keypad A struct array of the keypad.
*/
void keypad_read(uint8_t *pad[]);

#endif /* KEYPAD_H_ */