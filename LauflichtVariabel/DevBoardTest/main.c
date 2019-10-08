/*


 * DevBoardTest.c
 *
 * Created: 27/08/2019 9:03:05 AM
 * Author : mathisk
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define setLed(bit) (PORTA |= (1<<bit))
#define clearLed(bit) (PORTA &= ~(1<<bit))
#define tstStartStop_pos (pinjPos & (1<<7))
#define tstDirection_pos (pinjPos & (1<<6))
#define tstFaster_pos (pinjPos & (1<<4))
#define tstSlower_pos (pinjPos & (1<<5))

void flanke();

unsigned char pinjPos, pinjNeg;

int main(void){
	//Data Direction registers 1 == Output!
	DDRA = 0xFF; //LED Port
	DDRJ = 0; //Button Port
	
	uint8_t delayCounter_pv; //Counts how many delays have passed
	uint8_t isRunning;
	uint8_t isReverse;
	uint8_t currentLED_sp = 7; //Starting LED is LED7
	unsigned int ledOnTime_sp = 100; //led stays on for 1s (100*10mS) on startup
	
	setLed(currentLED_sp);
	
    /* Replace with your application code */
    while (1){
		flanke();
		
		
		if(tstStartStop_pos){
			if(isRunning) isRunning = 0;
			else isRunning = 1;
		}
		
		if(tstDirection_pos){
			if(isReverse) isReverse = 0;
			else isReverse = 1;
		}
		
		if(tstFaster_pos){
			if(ledOnTime_sp > 20) ledOnTime_sp -= 20; //Decrement ledOnTime by 200mS, don't get below 200mS
		}
		
		if(tstSlower_pos){
			if(ledOnTime_sp <= 200) ledOnTime_sp += 20; //Increment ledOnTime by 200mS, don't get above 2S
		}
		
		if(isRunning){
			if(delayCounter_pv < ledOnTime_sp){
				setLed(currentLED_sp); //If the ledOnTime hasn't passed the current led is on
				delayCounter_pv++;
			}
			//Increment/decrement the led position and reset if its the last one
			else{
				delayCounter_pv = 0;
				clearLed(currentLED_sp);
				
				if(isReverse){
					if(currentLED_sp < 7) currentLED_sp++;
					else currentLED_sp = 0;
				}
				else{
					if(currentLED_sp > 0) currentLED_sp--;
					else currentLED_sp = 7;
				}
			}
		}
		
		_delay_ms(10);
    }
}

void flanke(){
	static unsigned char pinjOld;
	unsigned char pinjCurrent = PINJ;
	pinjPos = pinjCurrent & ~pinjOld;
	pinjNeg = ~pinjCurrent & pinjOld;
	pinjOld = pinjCurrent;
}