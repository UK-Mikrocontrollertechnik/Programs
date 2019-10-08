/*
 * RGB.c
 *
 * Created: 02/09/2019 12:50:23 PM
 * Author : mathisk
 */ 

//***PRE-DEFINES***
#define F_CPU 8000000UL

//***Includes***
#include <avr/io.h>
#include <util/delay.h>

//***DEFINES***
#define btnRed_pos edge_sp.pinPos & (1<<0)
#define btnGreen_pos edge_sp.pinPos & (1<<1)
#define btnBlue_pos edge_sp.pinPos & (1<<2)

//***STRUCT DEFINITIONS***
typedef struct{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} color;

typedef struct{
	uint8_t pinPos;
	uint8_t pinNeg;
	uint8_t *port;
	uint8_t old;
} edge;

//***FUNCTION DECLARATIONS***
void rgb(color);
void edgeDetect(edge *port);

//***MAIN ROUTINE***
int main(void)
{
	//**Data Direction Registers**
	//*1 = Output*
	DDRB = 0xff; //RGB Register
	DDRJ = 0x00; //Button Register
	
	//**Variable definitions**
	color theColor = {1,1,1};
	
	//**Init the RGB LED**
	rgb(theColor);
	
	edge edge_sp = {0,0,&PINJ};
	edgeDetect(&edge_sp);
	
	//***SUPER LOOP***
	while(1){
		
		/**Detect button presses based on positive edge
		*and invert the corresponding LED
		*/
		if(btnRed_pos){
			if(theColor.red) theColor.red = 0;
			else theColor.red = 1;
		}
		if(btnGreen_pos){
			if(theColor.green) theColor.green = 0;
			else theColor.green = 1;
		}
		if(btnBlue_pos){
			if(theColor.blue) theColor.blue = 0;
			else theColor.blue = 1;
		}
		
		rgb(theColor);
		
		edgeDetect(&edge_sp);
		_delay_ms(10);
	}
}

/**
*Set an RGB LED based on a color struct
*/
void rgb(color newColor){
	PORTB |= (newColor.red<<5)|(newColor.green<<6)|(newColor.blue<<7);
	
	//Cause a 0 turns anything off with an "and-set", its necessary to set every bit outside of
	//the RGB bits to 1. Thats why there is a |0x8f (|0b1000 1111) at the end.
	PORTB &= (newColor.red<<5)|(newColor.green<<6)|(newColor.blue<<7)|0x1f;
}


/**
*Edge detection on the rgb buttons
*/
void edgeDetect(edge *port){
	uint8_t pinjCurrent = *(port->port);
	port->pinPos = pinjCurrent & ~port->old;
	port->pinNeg = ~pinjCurrent & port->old;
	port->old = pinjCurrent;
}
