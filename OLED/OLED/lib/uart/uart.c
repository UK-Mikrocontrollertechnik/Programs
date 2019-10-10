/**
* @file uart.c
* @brief LIB to control the uart protocol.
* @author Kenneth Mathis
* @version 1.0
*
* *******************************
* Date      Vers.   Name            Comment/Change
* 01.10.19  1.0     Kenneth Mathis  Created
*/

#include "uart.h"

void uart_init(void){
	UCSR1B |= (1<<RXEN1)|(1<<TXEN1); //Enable Rx and Tx
	UCSR1C |= (1<<UCSZ11)|(1<<UCSZ10);
	UBRR1L = BAUD_PRESCALE;
	UBRR1H = (BAUD_PRESCALE>>8);
}

void uart_tx(uint8_t txData){
	while (!(UCSR1A & (1<<UDRE1)));  // Wait for empty transmit buffer, 1=Empty
	UDR1 = txData;
}

void uart_tx_str(uint8_t *str){
	uint8_t j=0;
	while (str[j]!=0){
		uart_tx(str[j]);
		j++;
	}
}

void uart_tx_crlf(void){
	uart_tx(13);
	uart_tx(10);
}

uint8_t uart_rx(void){
	while ((UCSR1A & (1 << RXC1)) == 0); // Wait for empty transmit buffer, 1=Empty
	return(UDR1);
}
