/**
* @file convert.c
* @brief LIB to covert raw ADC values to more useful stuff
* @author Kenneth Mathis
* @version 1.0
*
* *******************************
* Date      Vers.   Name            Comment/Change
* 17.09.19  1.0     Kenneth Mathis  Created
*
*/


//***INCLUDES***
#include "convert.h"

//***FUNCTIONS***
float toTemeperature(uint16_t adcValue){
	//Linear Temperature conversion
	//float temp;
	//temp = (26.32*toVoltage(adcValue))-40.8;
	
	//Conversion via Simplified Steinhart-Hart B-Parameter Equation
	//See: https://learn.adafruit.com/thermistor/using-a-thermistor
	float steinhart;
	steinhart = (toResistance(adcValue))/10000.0; // (R/Ro)
	steinhart = log(steinhart);					// ln(R/Ro)
	steinhart /= 3510;							// 1/B * ln(R/Ro)
	steinhart += 1.0 / (25.0 + 273.15);			// + (1/To)
	steinhart = 1.0 / steinhart;				// Invert
	steinhart -= 273.15;						// convert to C
	
  return steinhart;
}

float toVoltage(uint16_t adcValue){
	float volt;
	volt = adcValue*0.0048875; //voltage = adcVal*(5V/1023)
  return volt;
}

float toResistance(uint16_t adcValue){
	float resistance;
	resistance = (50000.0/toVoltage(adcValue))-10000; //resistance = (Vcc*R2/Vadc)-R2
  return resistance;
}