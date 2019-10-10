/**
* @file uart.h
* @brief LIB to control the uart protocol.
* @author Kenneth Mathis
* @version 1.0
*
* *******************************
* Date      Vers.   Name            Comment/Change
* 01.10.19  1.0     Kenneth Mathis  Created
*/


#ifndef UART_H
#define UART_H

#include <avr/io.h>

#define BAUDRATE 9600
#define BAUD_PRESCALE ((16000000 / (BAUDRATE * 16UL)) - 1) //((F_CPU/(baud*16))-1)

/**
* @brief Initialize the UART communication over USB
* @param void
*/
void uart_init(void);

/**
* @brief Send a byte over UART
* @param void
*/
void uart_tx(uint8_t txData);

/**
* @brief Receive a byte over UART
* @param void
*/
uint8_t uart_rx(void);

/**
* @brief Send a string over UART
* @param str Pointer to the string which needs to be printed.
*/
void uart_tx_str(uint8_t *str);

/**
* @brief Send a CR/LF over UART
* @param void
*/
void uart_tx_crlf(void);

#endif