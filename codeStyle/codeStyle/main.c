/*
 * main.c
 *
 * Example program for correct code style
 *
 * Created: 02/09/2019 8:44:56 AM
 * Author : Mathis Kenneth
 * Version: 1.0.0
 * Last Edit: 02/09/2019 8:44:56 AM
 */ 

// ***PRE DEFINES***
#define F_CPU 8000000UL

// ***INCLUDES***
#include <avr/io.h>
#include <util/delay.h>

// ***DEFINES***
#define tstLeft_pos (pinjPos & (1<<1))
#define tstRight_pos (pinjPos & (1<<0))
#define higherPortA (PINA<<1)
#define lowerPortA (PINA>>1)

// ***FUNCTION DECLARATIONS***
void flanke();

// ***GLOBAL VARIABLES***
unsigned char pinjPos, pinjNeg;

// ***MAIN ROUTINE***
int main(void){
	
	// ***INIT***
	edge(); //In order for edges to be correct from the start
	
	// **Local Variables**
	
	// **Data Direction Registers**
	// 1 = Output
	DDRJ = 0x00;	//Button Register
	DDRA = 0xff;	//LED Register
	
	// ***SUPER LOOP***
	while (1){
		
		/**
			*Shift the led to the Left or Right
			*whenever a edge got detected on two different buttons.
		*/
		if(tstLeft_pos){
			if(PINA < 128) PORTA = higherPortA; //128 is the bit of LED7 (the last led)
		}
		
		if(tstRight_pos){
			if(PINA > 1) PORTA = lowerPortA; //1 is the bit of LED0 (the first led)
		}
		
		// **Detect new edges**
		edge();
		
		// **Idle for 10mS**
		_delay_ms(10);
	}
}

// ***EDGE DETECTION***
/**
	*Detects the positive and negative edge on a predefined register.
	*The edges get stored in the global vars for further use.
	*At the end the current state gets defined as the previous
	*state for the next edge to be detected.
*/
void edge(){
	static unsigned char pinjOld;
	unsigned char pinjCurrent = PINJ;
	
	pinjPos = pinjCurrent & ~pinjOld;
	pinjNeg = ~pinjCurrent & pinjOld;
	
	pinjOld = pinjCurrent;
}

