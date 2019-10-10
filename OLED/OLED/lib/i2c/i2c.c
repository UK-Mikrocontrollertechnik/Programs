/**
* @file i2c.c
* @brief LIB to control a i2c/twi bus.
* @author Kenneth Mathis
* @version 1.0
*
* ******************************
* Date      Vers.   Name            Comment/Change
* 09.10.19  1.0     Kenneth Mathis  Created
*/

#include "i2c.h"

void i2c_init(void){
	uint8_t bitrate;
	bitrate = 0x12; //((16000000/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))));
	TWBR = bitrate; //Set the I2C bitrate (formula form Datasheet)
	TWAMR = (0xff<<1); //Disable the masking register
}


uint8_t i2c_start(uint8_t addr){
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT); //Create Start Condition & Clear interrupt flag
	while (!(TWCR & (1<<TWINT))); //Wait for current job to finish
	if((TWSR & 0xF8)!=0x08) return 1; //Return 1 if start condition failed
	TWDR = addr; //Set slave address to send
	TWCR = (1<<TWINT)|(1<<TWEN); //Send address
	while (!(TWCR & (1<<TWINT)));//Wait address transmission to finish
	if ((TWSR & 0xF8) == 0x18)return 0; //return 0 for sucessful address transmit
	if ((TWSR & 0xF8) == 0x20)return 2; //return 2 for nack received
	else return 3; //return 3 to indicate SLA+W failed
}

void i2c_stop(void){
	TWCR |= (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); //Send stop condition
	while(TWCR & (1<<TWSTO)); //Wait for successful transmit of stop condition.
}

uint8_t i2c_write(uint8_t data){
	TWDR = data; //Transmit given data
	TWCR = (1<<TWINT)|(1<<TWEN); //Clear interrupt flag
	while (!(TWCR & (1<<TWINT))); //Wait for transmission complete
	if ((TWSR & 0xF8) == 0x28)return 0; //return 0 if ack received
	if ((TWSR & 0xF8) == 0x30)return 1; //return 1 if nack received
	else return 2; //Else return 2 to indicate a failed transmission
}

uint8_t i2c_read(uint8_t ack){
	TWCR = (1<<TWEN)|(1<<TWINT)|((ack&0x01)<<TWEA); //Create Start Condition, Clear interrupt flag & enable ack if needed
	while (!(TWCR & (1<<TWINT))); //Wait for transmission complete
	return TWDR;
}

void i2c_setBitrate(uint8_t bitr){
	TWBR = bitr;
}