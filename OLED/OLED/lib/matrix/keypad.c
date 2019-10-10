/**
 * @file keypad.c
 * @brief LIB to control the keypad
 * @author Kenneth Mathis
 * @version 1.0
 *
 * ******************************
 * Date      Vers.   Name            Comment/Change
 * 09.09.19  1.0     Kenneth Mathis  Created
 */

void keypad_read(uint8_t *keypad[]){
	//Read keys 10, 0, 11
	uint8_t pinjCurrent = PIND;
	static uint8_t old1;
	segSel0_off;
	segSel1_off;
	keypad[10] = (pinjCurrent & ~old1) & 0x08;
	keypad[0] = (pinjCurrent & ~old1) & 0x10;
	keypad[11] = (pinjCurrent & ~old1) & 0x20;
	old1 = pinjCurrent;
	
	pinjCurrent = PIND;
	static uint8_t old2;
	segSel0_on;
	segSel1_off;
	keypad[1] = (pinjCurrent & ~old2) & 0x08;
	keypad[2] = (pinjCurrent & ~old2) & 0x10;
	keypad[3] = (pinjCurrent & ~old2) & 0x20;
	old2 = pinjCurrent;
	
}
	