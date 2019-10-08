/**
* @file convert.h
* @brief LIB to covert raw ADC values to more useful stuff
* @author Kenneth Mathis
* @version 1.0
*
* *******************************
* Date      Vers.   Name            Comment/Change
* 17.09.19  1.0     Kenneth Mathis  Created
*
*/


#ifndef CONVERT_H
#define COVNERT_H

#include <avr/io.h>
#include "adc.h"

//***PROTOTYPES***
/**
 * @brief Turns a ADC value into its temperature equivalent.
 * @param adcValue An adc value
 * @return temperature in celsius
*/
float toTemeperature(uint16_t adcValue);

/**
 * @brief Turns a ADC value into its Voltage equivalent.
 * @param adcValue An adc value.
 * @return Voltage at ADC.
*/
float toVoltage(uint16_t adcValue);

/**
 * @brief Determines R1 in a 10k/10k voltage divider.
 * @param adcValue An adc value.
 * @return R1 at ADC.
*/
float toResistance(uint16_t adcValue);

#endif