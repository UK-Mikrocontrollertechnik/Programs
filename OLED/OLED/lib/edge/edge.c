/**
* @file edge.h
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
	uint8_t pinjCurrent = *(port->port);
	port->pinPos = pinjCurrent & ~port->old;
	port->pinNeg = ~pinjCurrent & port->old;
	port->old = pinjCurrent;
}