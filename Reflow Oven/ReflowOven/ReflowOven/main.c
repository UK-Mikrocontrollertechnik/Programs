/**

* @file main.c
* @author Kenneth Mathis
* @version 1.0
* @brief Program for simulating a reflow oven's workflow
*
* ******************************
* Date      Vers.   Name            Comment/Change
* 17.09.19  1.0     Kenneth Mathis  Created
*/

//***INCLUDES***
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "matrix.h"
#include "sevenSegDisp.h"
#include "adc.h"
#include "convert.h"
#include "edge.h"
#include "RGB.h"

//***DEFINES***
//**Control Buttons**
#define tstStart_pos (ctrlButtons.pinPos & (1<<0))
#define tstStop_pos (ctrlButtons.pinPos & (1<<1))

//**Heatpad**
#define heatPad_on (PORTB |= (1<<4))
#define heatPad_off (PORTB &= ~(1<<4))

//***GLOBAL VARIABLES***
adc_t currentADC;
enum heatingStates {READY, DELAY, RAMPHEAT, HEAT, RAMPREFLOW, REFLOW, COOLDOWN};
enum heatingStates heatState_pv;
uint16_t delayCounter_pv;

//**Predefined Colours**
const color red = {1,0,0};
const color green = {0,1,0};
const color blue = {0,0,1};

//***PROTOTYPES***
void rampHeat(void);
void heatUp(void);
void rampReflow(void);
void reflow(void);
void coolDown(void);

/**
* @brief Main routine, this is where the magic happens.
* @param void
*/
int main(void){
	//**VARIABLES**
	edge ctrlButtons = {0,0,&PINJ}; //Struct for edge detection	
	heatState_pv = READY; //Variable to store the current process state
	
	//**Init**
	currentADC.usingADC = ADC2;
	adc_init(&currentADC);
	matrix_init();
	sei();
	colon_on;
	
	//**Data Direction Registers**
	DDRB = 0x10; //Set the 4th bit for the heatpad to output
	
    //***SUPER LOOP***
    while (1){
		//**Control button detection**
		edgeDetect(&ctrlButtons);
		if(tstStart_pos && heatState_pv == READY){
			heatState_pv = DELAY;
			delayCounter_pv = 10000; //Set a 10s Countdown
		}
		if(tstStop_pos){
			heatState_pv = COOLDOWN;
		}
		
		getValue(&currentADC);
		currentADC.adcReal = toTemeperature(currentADC.adcRaw);
		
		switch(heatState_pv){
			case READY:
				delayCounter_pv = 10000; //Use a 10s delay on startup if the heatpad has cooled
				colon_off;
				rgb(green);
				break;
			case DELAY: //Countdown from 10s
				colon_on;
				if(delayCounter_pv > 0){
					delayCounter_pv--;
					updateSegment((uint16_t)(delayCounter_pv/10), 4); //Update every 10mS with no Dot
				}
				else heatState_pv = RAMPHEAT;
				break;
			case RAMPHEAT:
				rampHeat();
				break;
			case HEAT:
				heatUp();
				break;
			case RAMPREFLOW:
				rampReflow();
				break;
			case REFLOW:
				reflow();
				break;
			case COOLDOWN:
				coolDown();
				break;
			default:
				break;
		}
		
		//***GLOBAL DELAY***
		_delay_ms(1);
    }
}

/**
* @brief Pre-Heat the reflow oven
* @param void
*/
void rampHeat(void){
	rgb(red);
	colon_off;
	heatPad_on;
	updateSegment(((uint16_t)(currentADC.adcReal*100)), 2); //Update every 10mS with 2 segment Dotted
	//Temperature over 35°C go to the the heating phase
	if(currentADC.adcReal >= 37.0){
		delayCounter_pv = 10000; //Use a 10s heating period
		heatState_pv = HEAT;
	}
}

/**
* @brief Heat the PCB
* @param void
*/
void heatUp(void){
	colon_on;
	if(delayCounter_pv > 0){
		delayCounter_pv--;
		updateSegment((uint16_t)(delayCounter_pv/10), 4); //Update every 10mS with no Dot
		//Temperature holding state
		if(currentADC.adcReal <= 37.0) heatPad_on;
		if(currentADC.adcReal > 40.0) heatPad_off;
	}
	else heatState_pv = RAMPREFLOW;
}

/**
* @brief Ramp up to reflow temperature
* @param void
*/
void rampReflow(void){
	colon_off;
	heatPad_on;
	updateSegment((uint16_t)(currentADC.adcReal*100), 2);
	if(currentADC.adcReal >= 45.0){
		delayCounter_pv = 10000; //Use a 10s reflow period
		heatState_pv = REFLOW;
	}
}

/**
* @brief Reflow dat board
* @param void
*/
void reflow(void){
	colon_on;
	if(delayCounter_pv > 0){
		delayCounter_pv--;
		updateSegment((uint16_t)(delayCounter_pv/10), 4); //Update every 10mS with no Dot
		//Temperature holding state
		if(currentADC.adcReal < 45.0) heatPad_on;
	}
	else heatState_pv = COOLDOWN;
}

/**
* @brief Cool down everything
* @param void
*/
void coolDown(void){
	rgb(blue);
	colon_off;
	heatPad_off;
	static uint16_t adcClearOffset; //ADC reads garbage after reflow part, this counteracts the problem
		
	updateSegment((uint16_t)(currentADC.adcReal*100), 2);
	if(currentADC.adcReal >= 30.0
		|| adcClearOffset <= 10000){ //Is true for 10s to counteract adc garbage.
		adcClearOffset++;
	}
	else{
		rgb(green);
		clearSeg;
		heatState_pv = READY;
		delayCounter_pv = 10000; //Use a 10s delay on startup if the heatpad has cooled
	}
}

//***INTERRUPTS***
/**
* @brief Interrupt for ADC-Conversion complete
* @param void
*/
ISR(ADC_vect){
	currentADC.adcRaw = ADC;
}