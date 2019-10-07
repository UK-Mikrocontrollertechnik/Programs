/**
* Software for a stopwatch
*
* @Autor: Mathis Kenneth
* @Version: 1.1
* ******************************
* Datum 	Vers. 	Name 			Kommentar / Änderung
* 03.09.19	1.0		Mathis Kenneth 	Erstellt
* 16.09.19	1.1		Mathis Kenneth	General Revamp
*/

//***INCLUDES***
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

//***DEFINES***
//**Segment select defines**
#define segSel0_off (PORTG &= ~(1<<0))
#define segSel1_off (PORTG &= ~(1<<1))
#define segSel0_on (PORTG |= (1<<0))
#define segSel1_on (PORTG |= (1<<1))

//**Button press defines**
#define tstStartStop_pos (ctrlButtons.pinPos & (1<<0))
#define tstReset_pos (ctrlButtons.pinPos & (1<<1))

//**Set segment led's defines
#define setSeg(bit) (PORTH |= (bit))
#define delSeg(bit) (PORTH &= (bit))

//**Misc**
#define colonOn	(PORTG |= (1<<4))
#define segEnable (PORTG |= (1<<2))
#define segDisable (PORTG &= ~(1<<2))

//***STRUCT'S***
typedef struct{	//A struct to store the edge detection data
	uint8_t pinPos; //Positive edge
	uint8_t pinNeg; //Negative edge
	uint8_t *port;	//The port to do edge detection on
	uint8_t old;	//Previous value of the port
} edge;

//***FUNCTION PROTOTYPES***
void updateSegment(unsigned int segNumber);
uint8_t numberToBitmask(uint8_t num);
void edgeDetect(edge *port);

//***MAIN ROUTINE***
int main(void){
	//**Init**
	
	//**Variables**
	uint8_t isRunning;		//Is 1 when the stopwatch is counting
	uint8_t halfStepper;	//In order to run 5mS delay but increment delayCouner_pv only every 10mS
	unsigned int delayCounter_pv = 0; //Counts how many delays of 10mS have passed
	edge ctrlButtons = {0,0,&PINJ}; //Edge detect struct for control buttons
		
	//**Data Direction Registers**
	//*1=Output*
	DDRG = 0xff; //MUX
	DDRH = 0xff; //Segment LED's
	DDRJ = 0; //Ctrl Buttons 
	
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
		
		//**Do half steps and stop at a 99'990mS**
		if(delayCounter_pv < 9999 && isRunning){
			if(halfStepper){
				halfStepper = 0;
				delayCounter_pv++;
			}
			else halfStepper = 1;
		}
		
		//**Detect the edges**
		edgeDetect(&ctrlButtons);
		
		//**Global Delay**
		_delay_ms(5);
    }
}

/***UPDATE 7-SEGMENT***
 * Update the seven segment display with a number
 * Note: This function takes care of the incremeting
 * so no individual segment can be set.
 * @param segNumber: The Number to display
*/
void updateSegment(unsigned int segNumber){
	static uint8_t segPos_pv;
	
	segDisable; //Disable the segment in order to avoid ghost digits
	
	//**Select which segment is currently being displayed**
	switch(segPos_pv){
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
	if(segNumber == 0) bitmask = numberToBitmask(0); //If the given number is zero, display it as such
	else{
		uint8_t segDigit;
		segDigit = ((uint8_t)(segNumber/pow(10, segPos_pv)))%10;	//Get the digit at segPos_pv from segNumber
		bitmask = numberToBitmask(segDigit);
	}
	
	//**Update the segment**
	setSeg(bitmask);
	delSeg(bitmask);
	
	segEnable; //Make the segment visible again
	
	if(segPos_pv < 3) segPos_pv++; //increment the segment position till the last segment
	else segPos_pv = 0; //return to first segment after the last segment
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
*@return: Return via "reference"
*/
void edgeDetect(edge *port){
	uint8_t pinjCurrent = *(port->port);
	port->pinPos = pinjCurrent & ~port->old;
	port->pinNeg = ~pinjCurrent & port->old;
	port->old = pinjCurrent;
} // **EOF**
