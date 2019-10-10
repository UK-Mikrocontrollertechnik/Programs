/**
* @file i2c.h
* @brief LIB to control a i2c/twi bus.
* @author Kenneth Mathis
* @version 1.0
*
* ******************************
* Date      Vers.   Name            Comment/Change
* 09.10.19  1.0     Kenneth Mathis  Created
*/



#ifndef I2C_H
#define I2C_H

#include <avr/io.h>
#include <math.h>								
#define SCL_CLK 100000L //TWI clk frequency

#define I2C_EN TWCR |= (1<<TWEN);
#define I2C_DN TWCR &= ~(1<<TWEN);

/**
* @brief Initializes the I2C bus.
* @param Void
*/
void i2c_init(void);

/**
* @brief Sends an I2C start condition.
* @param Void
*/
uint8_t i2c_start(uint8_t addr);

/**
* @brief Sends an I2C stop condition.
* @param Void
*/
void i2c_stop(void);

/**
* @brief Sends on the I2C bus.
* @param data Data to be sent over the I2C bus.
*/
uint8_t i2c_write(uint8_t data);

/**
* @brief Reads data from the I2C bus.
* @param ack Whether the read should be acknowledged
*/
uint8_t i2c_read(uint8_t ack);

/**
* @brief Set a new Bitrate for the I2C bus
* @param bitr The new Bitrate
*/
void i2c_setBitrate(uint8_t bitr);

#endif