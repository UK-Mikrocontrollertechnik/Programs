/*
 * Stoppuhr.c
 *
 * Created: 03/09/2019 9:43:59 AM
 * Author : mathisk
 */ 

//***INCLUDES***
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

//***DEFINES***
#define colonOn	(PORTG |= (1<<4))
#define segEnable (PORTG |= (1<<2))
#define segDisable (PORTG &= ~(1<<2))


#define segSel0_off (PORTG &= ~(1<<0))
#define segSel1_off (PORTG &= ~(1<<1))
#define segSel0_on (PORTG |= (1<<0))
#define segSel1_on (PORTG |= (1<<1))

#define tstStartStop_pos (ctrlButtons.pinPos & (1<<0))
#define tstReset_pos (ctrlButtons.pinPos & (1<<1))

#define setSeg(bit) (PORTH |= (bit))
#define delSeg(bit) (PORTH &= (bit))

//***STRUCT'S***
typedef struct{
	uint8_t pinPos;
	uint8_t pinNeg;
	uint8_t *port;
	uint8_t old;
} edge;

//***FUNCTION PROTOTYPES***
void updateSegment(unsigned int segNumber);	//Sets the 7-segment based on a number, the position shifts with every update
uint8_t numberToBitmask(uint8_t num);	//Turns any number into a 7-segment bitmask
void edgeDetect(edge *port);	//Function used for edge detection

//***MAIN ROUTINE***
int main(void){
	//**Init**
	
	//**Variables**
	uint8_t isRunning;
	uint8_t halfStepper; //In order to run 5mS delay but increment delayCouner_pv only every 10mS
	unsigned int delayCounter_pv = 0;
	edge ctrlButtons = {0,0,&PINJ};
		
	//**Data Direction Registers**
	//*1=Output*
	DDRG = 0xff;
	DDRH = 0xff;
	DDRJ = 0;
	
	//**Turn on the colon led and enable the segment**
	colonOn;
	segEnable;
	//***SUPER LOOP***
    while (1){
		
		//**Detect positive Edges on StartStop and Reset**
		if(tstStartStop_pos) isRunning = !isRunning;
		if(tstReset_pos){
			delayCounter_pv = 0;
			isRunning = 0;
		}
		
		//**Update the segment**
		if(delayCounter_pv == 0)updateSegment(0);
		else updateSegment(delayCounter_pv);
		
		//**Do half steps and stop at a minute (59'990mS)**
		if(delayCounter_pv < 9999 && isRunning){
			if(halfStepper){
				halfStepper = 0;
				delayCounter_pv++;
			}
			else halfStepper = 1;
		}
		
		//**Detect the edges**
		edgeDetect(&ctrlButtons);
		_delay_ms(5);
    }
}

/***UPDATE 7-SEGMENT***
 * Update the seven segment display with a number
 * Note: This function takes care of the incremeting
 * so no individual segment can be set.
 * @param segNumber: The Number to display
 * @return: VOID
*/
void updateSegment(unsigned int segNumber){
	static uint8_t segPos;
	
	//**Select which segment is currently being displayed**
	switch(segPos){
		case 0:
			segSel0_off;
			segSel1_off;
			break;
		case 1:
			segSel0_on;
			segSel1_off;
			break;
		case 2:
			segSel0_off;
			segSel1_on;
			break;
		case 3:
			segSel0_on;
			segSel1_on;
			break;
		default:
			segSel0_off;
			segSel1_off;
			break;
	}
	
	//**Create the bitmask for the given number and set PORTH to it**
	uint8_t bitmask;
	if(segNumber == 0){
		bitmask = numberToBitmask(0); //If the given number is zero, display it as such
	}
	else{
		uint8_t segDigit;
		segDigit = ((uint8_t)(segNumber/pow(10, segPos)))%10;	//Get the digit at segPos from segNumber
		bitmask = numberToBitmask(segDigit);
	}
	segDisable;
	setSeg(bitmask);
	delSeg(bitmask);
	segEnable;
	
	if(segPos < 3) segPos++; //increment the segment position till the last segment
	else segPos = 0; //set the segment position to zero if its past the last one
}

/***NUMBER TO BITMASK***
 * Turns a number into a seven segment bitmask
 * @param: num = the number to turn into a 7-segment bitmask
 * @return: the bitmask of the given number
*/
uint8_t numberToBitmask(uint8_t num){
	switch(num){
		case 0:
			return 0b00111111;
		case 1:
			return 0b00000110;
		case 2:
			return 0b01011011;
		case 3:
			return 0b01001111;
		case 4:
			return 0b01100110;
		case 5:
			return 0b01101101;
		case 6:
			return 0b01111101;
		case 7:
			return 0b00000111;
		case 8:
			return 0b01111111;
		case 9:
			return 0b01101111;
		default:
			return 0b01000000;
	}
}

// ***EDGE DETECTION***
/**
*@param: An edge struct is needed which defines stores all the necessary stuff for the edge detection
*@return: VOID
*/
void edgeDetect(edge *port){
	uint8_t pinjCurrent = *(port->port);
	port->pinPos = pinjCurrent & ~port->old;
	port->pinNeg = ~pinjCurrent & port->old;
	port->old = pinjCurrent;
} // **EOF**
