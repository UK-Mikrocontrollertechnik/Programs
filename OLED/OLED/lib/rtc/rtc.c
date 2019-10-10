/**
* @file rtc.c
* @brief LIB to control a DS1307 RTC
* @author Kenneth Mathis
* @version 1.0
*
* *******************************
* Date      Vers.   Name            Comment/Change
* 10.10.19  1.0     Kenneth Mathis  Created
*/

#include "rtc.h"
#include "i2c.h"

void rtc_init(void){
    i2c_start(DS1307_WRITE_MODE); //Send the RTC address with write mode 
    i2c_write(DS1307_CONTROL_REG_ADDR); //Select the RTC ControlRegister
	i2c_write(0x00); //Disable the square wave output
	i2c_stop();
}

void rtc_set(rtc_t *rtc){
    i2c_start(DS1307_WRITE_MODE); //Send the RTC address with write mode
    i2c_write(DS1307_SECONDS_REG_ADDR); // Request sec RAM address at 00H
    i2c_write(rtc->sec);                    // Write sec to RAM address 00H
    i2c_write(rtc->min);                    // Write min to RAM address 01H
    i2c_write(rtc->hour);                    // Write hour to RAM address 02H
    i2c_write(rtc->weekDay);                // Write weekDay to RAM address 03H
    i2c_write(rtc->date);                    // Write date to RAM address 04H
    i2c_write(rtc->month);                    // Write month to RAM address 05H
    i2c_write(rtc->year);                    // Write year to RAM address 06h
    i2c_stop();                              // Stop the communication after Setting the Date
}

void rtc_setDate(rtc_t *rtc){
	i2c_start(DS1307_WRITE_MODE); //Send the RTC address with write mode
	i2c_write(DS1307_DATE_REG_ADDR); // Request sec RAM address at 00H
	i2c_write(rtc->weekDay);                // Write weekDay to RAM address 03H
	i2c_write(rtc->date);                    // Write date to RAM address 04H
	i2c_write(rtc->month);                    // Write month to RAM address 05H
	i2c_write(rtc->year);                    // Write year to RAM address 06h
	i2c_stop();                              // Stop the communication after Setting the Date
}

void rtc_get(rtc_t *rtc){
    i2c_start(DS1307_WRITE_MODE); // Start I2C communication
    i2c_write(DS1307_SECONDS_REG_ADDR); // Request Sec RAM address at 00H
    i2c_stop();                                // Stop I2C communication after selecting Sec Register

    i2c_start(DS1307_READ_MODE); // Start I2C communication
    rtc->sec = i2c_read(1);     // read second and return Positive ACK
    rtc->min = i2c_read(1);     // read minute and return Positive ACK
    rtc->hour= i2c_read(1);     // read hour and return Negative/No ACK
    rtc->weekDay = i2c_read(1); // read weekDay and return Positive ACK
    rtc->date= i2c_read(1);     // read Date and return Positive ACK
    rtc->month=i2c_read(1);     // read Month and return Positive ACK
    rtc->year =i2c_read(0);     // read Year and return Negative/No ACK
    i2c_stop();                 // Stop I2C communication after reading the Date
}
