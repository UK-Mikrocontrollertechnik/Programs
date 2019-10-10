/**
* @file rtc.h
* @brief LIB to control a DS1307 RTC
* @author Kenneth Mathis
* @version 1.0
*
* *******************************
* Date      Vers.   Name            Comment/Change
* 10.10.19  1.0     Kenneth Mathis  Created
*/

#ifndef _RTC_H_
#define _RTC_H_

#include <avr/io.h>

typedef struct{
  uint8_t sec;
  uint8_t min;
  uint8_t hour;
  uint8_t weekDay;
  uint8_t date;
  uint8_t month;
  uint8_t year;  
}rtc_t;

#define DS1307_READ_MODE  0xD1u  // DS1307 ID Read
#define DS1307_WRITE_MODE  0xD0u  // DS1307 ID Write

#define DS1307_SECONDS_REG_ADDR 0x00u   // Address to access Ds1307 SEC register
#define DS1307_DATE_REG_ADDR     0x03u   // Address to access Ds1307 DATE register
#define DS1307_CONTROL_REG_ADDR  0x07u   // Address to access Ds1307 CONTROL register

/**
* @brief Initialize the RTC communication over i2c
* @param void
*/
void rtc_init(void);

/**
* @brief Set the time and date on the RTC
* @param rtc A rtc_t pointer pointing to a complete new time and date struct
*/
void rtc_set(rtc_t *rtc);

/**
* @brief Set the date on the RTC
* @param rtc A rtc_t pointer pointing to a complete new time and date struct
*/
void rtc_setDate(rtc_t *rtc);

/**
* @brief Get the time and date of the RTC
* @param rtc Sets the time and date to a rtc_t var via reference.
* @return Void
*/
void rtc_get(rtc_t *rtc);

#endif
