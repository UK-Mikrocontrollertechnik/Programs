/**
* @file adc.h
* @brief LIB to control the ADC on the ZLV-Mint Board
* @author Kenneth Mathis
* @version 1.1
*
* *******************************
* Date      Vers.   Name            Comment/Change
* 09.09.19  1.0     Kenneth Mathis  Created
* 17.09.19  1.1     Kenneth Mathis  Added interrupts
*
*/

//***FILE GUARD***
#ifndef ADC_H
#define ADC_H

	//A list of all the single ended input ADC's and their mux "id"
	enum tblADC {ADC0=0,ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7,ADC8=32,ADC9,ADC10,ADC11,ADC12,ADC13,ADC14,ADC15};
	
	//A struct for storing all the adc revlevant data
	typedef struct{
		 enum tblADC usingADC;
		 uint16_t adcRaw;
         float adcReal;
		 uint8_t isLeftAdjusted;
		 uint8_t is8BitMode;
	} adc_t;
	
	//***PROTOTYPES***
	/**
	* @brief Initializes the ADC for use and defines the wanted MUX config.
	* @param theADC An adc_t stcut is used to determine all the init values.
	*/
	void adc_init(adc_t *theADC);
	
	/**
	* @brief Start the conversion when an interrupt is used 
	* @param Void
	*/
	void startConversion(void);
	
	/**
	* @brief Reads the current value on the ADC value and stores its via "reference".
	* @param theADC adc_t struct for storing the adcRaw into.
	*/
	void getValue(adc_t *theADC);

#endif
