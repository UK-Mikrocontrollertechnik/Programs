/**
 * SSD1306xLED - Library for the SSD1306 based OLED/PLED 128x64 displays
 *
 * @author Neven Boyanov
 *
 * This is part of the Tinusaur/SSD1306xLED project.
 *
 * Copyright (c) 2018 Neven Boyanov, The Tinusaur Team. All Rights Reserved.
 * Distributed as open source software under MIT License, see LICENSE.txt file.
 * Retain in your source code the link http://tinusaur.org to the Tinusaur project.
 *
 * Source code available at: https://bitbucket.org/tinusaur/ssd1306xled
 *
 */

//***INCLUDES***
#define F_CPU  16000000UL
#include <stdint.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "font6x8.h"
#include "font8x16.h"
#include "ssd1306xled.h"
#include "ssd1306xledtx.h"
#include "ssd1306xledfx.h"
#include "adc.h"
#include "edge.h"
#include "uart.h"
#include "i2c.h"
#include "rtc.h"
#include "lcd.h"

//***DEFINES***
#define TESTING_DELAY 500
#define DS1307_ADDR 0x68
#define tstStore_pos (btn.pinPos & (1<<0))
#define tstSleep_pos (btn.pinPos & (1<<1))

/**
* @brief The Main Routine, Bro!
* @param Void
*/
int main(void) {
	//**Init**
	DDRD |= 0x0f;
	DDRA = 0xff;
	_delay_ms(50);	// Small delay might be necessary if ssd1306_init is the first operation in the application.
	i2c_init();
	ssd1306_init();
	ssd1306tx_init(ssd1306xled_font6x8data, ' ');
	rtc_init();
	lcd_init();
	uart_init();
	
	rtc_t rtc;
	//Want to change the time? Y'all can do so here!
	/*rtc.hour = 0x10; //  10:47:00 am
	rtc.min =  0x47;
	rtc.sec =  0x00;

	rtc.date = 0x10; //10.10.19
	rtc.month = 0x10;
	rtc.year = 0x19;
	rtc.weekDay = 4;
	rtc_set(&rtc);*/
	lcd_setCursor(0,0);
	lcd_writeString("12:00:00");
	lcd_setCursor(0,1);
	lcd_writeString("m d m d f s s");
	lcd_setCursor(0,0);
	
	//EEPROM storage configuration
	//0=Week Config, At which days of the week a happens
	//1=Hour, 2=Minute 3=second
	//PORTA represents the stored week config
	PORTA = eeprom_read_byte((uint8_t*) 0);
	
	//**Variables**
	edge btn = {0,0, &PINJ};
	edge swt = {0,0, &PINC};
	uint8_t prevSec;
	const uint8_t SWITCHCHECKS[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02};
	const uint8_t WEEKDAYLIST[] = {'M', 'O', 'D', 'I', 'M', 'I', 'D', 'O', 'F', 'R', 'S', 'A', 'S', 'O',
									'm', 'd', 'm', 'd', 'f', 's', 's'};

	//***SUPER LOOP***
	while(1){
		//i2c_setBitrate(0x48); //used to run the RTC with a lower bitrate and the display with a higher one
		rtc_get(&rtc);
		//i2c_setBitrate(0x12);
		
		//**Output time and date to the OLED**
		if(prevSec != rtc.sec){
			ssd1306_clear();
			ssd1306_setpos(0,4);
			ssd1306tx_char(((rtc.hour>>4)&0x03)+48);
			ssd1306tx_char((rtc.hour&0x0f)+48);
			ssd1306tx_char(':');
			ssd1306tx_char((rtc.min>>4)+48);
			ssd1306tx_char((rtc.min&0x0f)+48);
			ssd1306tx_char(':');
			ssd1306tx_char((rtc.sec>>4)+48);
			ssd1306tx_char((rtc.sec&0x0f)+48);
			
			ssd1306_setpos(0,6);
			
			ssd1306tx_char(WEEKDAYLIST[rtc.weekDay-1]);
			ssd1306tx_char(WEEKDAYLIST[rtc.weekDay]);
					
			ssd1306tx_char(' ');
			ssd1306tx_char((rtc.date>>4)+48);
			ssd1306tx_char((rtc.date&0x0f)+48);
			ssd1306tx_char('.');
			ssd1306tx_char((rtc.month>>4)+48);
			ssd1306tx_char((rtc.month&0x0f)+48);
			ssd1306tx_char('.');
			ssd1306tx_char((rtc.year>>4)+48);
			ssd1306tx_char((rtc.year&0x0f)+48);
			prevSec = rtc.sec;
		}
		
		//**Store the new configuration in the EEPROM**
		edgeDetect(&btn);
		if(tstStore_pos){
			eeprom_write_byte((uint8_t*) 0, PINC);
			PORTA = PINC;
		}
		
		//**Switch Changes**
		//*Return to "0" if no switch is active. But only once.*
		edgeDetect(&swt);
		if(PINC == 0x00 && swt.pinNeg){
			lcd_setCursor(0,1);
			lcd_writeString("m d m d f s s");
			lcd_setCursor(0,0);
		}
		
		//*Update any changed switch on the display.*
		if(swt.pinPos || swt.pinNeg){
			for(int i=0; i<7; i++){
				lcd_setCursor(i*2,1);
				if(PINC & SWITCHCHECKS[i]){
					lcd_sendData(WEEKDAYLIST[i*2]);
				}
				else if(PINC!=0) lcd_sendData(WEEKDAYLIST[i+14]);
				lcd_setCursor(0,0);
			}
		}
		
		_delay_ms(10);
	}

	return 0;
}