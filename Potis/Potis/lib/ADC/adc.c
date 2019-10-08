/**
* @file adc.c
* @brief LIB to control the ADC on the ZLV-Mint Board
* @author Kenneth Mathis
* @version 1.0
*
* *******************************
* Date      Vers.   Name            Comment/Change
* 09.09.19  1.0     Kenneth Mathis  Created
* 17.09.19  1.1     Kenneth Mathis  Added interrupts
*
*/

//***INCLUDES***
#include <avr/io.h>
#include "adc.h"

void adc_init(adc_t *theADC){
	ADCSRA |= (1<<7); //Enable ADC
	ADCSRA |= (1<<3); //Enable ADC conversion complete interrupts
	if(theADC->isLeftAdjusted || theADC->is8BitMode) ADMUX |= (1<<5); //Produce left adjusted result (8-Bit Mode)
	ADMUX |= (theADC->usingADC & 0x1f); //Set the mux to the right DAC, Note: The mux Bits are in two Registers!
	ADCSRB |= ((theADC->usingADC>>1) & 0x08);
}

void startConversion(void){
	ADCSRA |= (1<<6); //Start the adc conversion
}

void getValue(adc_t *theADC){
	ADCSRA |= (1<<6); //Start the adc conversion
	while(!(ADCSRA & 0x10)); //Wait till the conversion has ended
	if(theADC->is8BitMode) theADC->adcRaw = ADCH; //Return an 8-Bit value if wanted
	else theADC->adcRaw = ADC;
}