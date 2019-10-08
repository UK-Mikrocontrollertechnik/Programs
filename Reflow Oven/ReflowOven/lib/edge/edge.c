/**
* @file edge.c
* @brief LIB to detect positive and negative edges
* @author Kenneth Mathis
* @version 1.0
*
* *******************************
* Date      Vers.   Name            Comment/Change
* 17.09.19  1.0     Kenneth Mathis  Created
*
*/

//***INCLUDES***
#include "edge.h"

void edgeDetect(edge *port){
	uint8_t pinCurrent = *(port->port);
	port->pinPos = pinCurrent & ~port->old;
	port->pinNeg = ~pinCurrent & port->old;
	port->old = pinCurrent;
}