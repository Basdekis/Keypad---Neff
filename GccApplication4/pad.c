/*
 * pad.c
 *
 * Created: 18.01.2018 21:04:30
 *  Author: Julian
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "board.h"
#include "switch.h"
#include "pad.h"

	/*
				4	3	2	1
				
			8	1   2   3   A
			7	4	5	6	B
			6	7	8	9	C
			5	*	0	#	D
				
			1 - GPIO 3
			2 - GPIO 2
			3 - GPIO 1
			4 - GPIO 0
			
			5 - GPIO 7
			6 - GPIO 6
			7 - GPIO 5
			8 - GPIO 4
	
	*/

void initPad(){
	//lines
	PORTD.DIR = (PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm);
	//rows
	//PORTD.DIR |= (PIN3_bm | PIN2_bm | PIN1_bm | PIN0_bm);
	PORTD.PIN4CTRL = PORT_OPC_PULLDOWN_gc;
	PORTD.PIN5CTRL = PORT_OPC_PULLDOWN_gc;
	PORTR.PIN0CTRL = PORT_OPC_PULLDOWN_gc;
	PORTR.PIN1CTRL = PORT_OPC_PULLDOWN_gc;
}

uint16_t pad_scan(){
	PORTD.IN = 0;
	
	uint16_t buttonstates = 0x00;
	
	//PORTD.OUT = PIN4_bm;
	//buttonstates |= (PORTD.IN & 0x0f);
	//
	//PORTD.OUT = PIN5_bm;
	//buttonstates = (buttonstates << 4);
	//buttonstates |= (PORTD.IN & 0x0f);
	//
	//PORTR.OUT = PIN0_bm;
	//buttonstates = (buttonstates << 8);
	//buttonstates |= (PORTD.IN & 0x0f);
	//
	//PORTR.OUT = PIN1_bm;
	//buttonstates = (buttonstates << 12);
	//buttonstates |= (PORTD.IN & 0x0f);
	
	PORTD.OUT = 0x00;
	return buttonstates;
}