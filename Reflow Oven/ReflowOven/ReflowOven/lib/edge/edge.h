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

#ifndef EDGE_H
#define EDGE_H
	//***INCLUDES***
	#include <avr/io.h>
	
	//***STRUCT DEFINITIONS***
	typedef struct{	//A struct to store the edge detection data
		uint8_t pinPos; //Positive edge
		uint8_t pinNeg; //Negative edge
		uint8_t *port;	//The port to do edge detection on
		uint8_t old;	//Previous value of the port
	} edge;

	//***PROTOTYPES***
	/**
	* @brief: A function used to detect edges on a port
	* @param: An edge struct to stores all the necessary stuff from the edge detection
 	* @return: Return via "reference"
	*/
	void edgeDetect(edge *port);

#endif