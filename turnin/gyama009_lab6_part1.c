/*	Author: Garrett Yamano
 *  Partner(s) Name: 
 *	Lab Section: 022
 *	Assignment: Lab #6 Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"

// Video Link: https://youtu.be/QIgLzzR-mI4

enum States {Start, Blink} state;

unsigned char cnt;

void Tick(){
	switch(state){ // Transitions
		case Start: // Initial transition
			cnt = 0x00;
			PORTB = 0x01;
			state = Blink;
			break;
		case Blink:
			if(cnt == 0x01){
				PORTB = 0x02;
			}
			else if(cnt == 0x02){
				PORTB = 0x04;
			}
			else{
				PORTB = 0x01;
				cnt = 0x00;
			}
			state = Blink;
			break;
		default:
			state = Start;
			break;
	} // Transitions
	switch(state){ // State actions
		case Blink:
			cnt++;
			break;
		default:
			break;
	} // State actions
}

int main(void) {
	DDRB = 0xFF; // Set port B to output
	PORTB = 0x00; // Init port B to 0s
	state = Start;
	TimerSet(1000);
	TimerOn();
	while (1) {
		Tick();
		while(!TimerFlag){}
		TimerFlag = 0;
	}
}
