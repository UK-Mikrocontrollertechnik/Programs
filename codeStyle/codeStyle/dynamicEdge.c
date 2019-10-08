/*
 * CFile1.c
 *
 * Created: 02/09/2019 12:43:02 PM
 *  Author: mathisk
 */ 

// *** STRUKTUREN ***
// * GPIO *
struct gpio{
	unsigned char pos;
	unsigned char neg;
};
/**
* Erfasst Flanken an PORTJ
* @return: Flankenauswertung
*/
struct gpio portj_flnk(uint8_t *port){
	static unsigned char gpio_old;
	struct gpio mygpio = 0;
	unsigned char gpio_val = PINJ;
	mygpio.pos = gpio_val & ~gpio_old;
	mygpio.neg = ~gpio_val & gpio_old;
	gpio_old = gpio_val;
	return mygpio;
}