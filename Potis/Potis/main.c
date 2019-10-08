/**
* @file adc.h
* @brief Poti's Binary value on LED's
* @author Kenneth Mathis
* @version 1.0
*
* *******************************
* Date      Vers.   Name            Comment/Change
* 17.09.19  1.0     Kenneth Mathis  Created
*
*/


//***INCLUDES***
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"

//***GLOBAL VARIABLES***
uint8_t isConverting;

//***MAIN ROUTINE***
int main(void){
	
	//**Variables**
	adc_t currentADC; //An ADC stuct to store all the relevant data
	currentADC.usingADC = ADC3;
	currentADC.is8BitMode = 1;
	
	//**Init**
	adc_init(&currentADC);
	sei();
	
    //***SUPER LOOP***
    while (1){
		if(!isConverting) startConversion();
    }
}

//***INTERRUPTS***
//**Adc Conversion Complete Interrupt**
ISR(ADC_vect){
	PORTA = ADCH;
	isConverting = 0;
}