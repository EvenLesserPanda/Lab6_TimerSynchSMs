/*	Author: gyama009
 *  Partner(s) Name: 
 *	Lab Section: 022
 *	Assignment: Lab #6 Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"

enum States{Start, Init, Increment, Decrement, Reset} state;

void Tick(){
	switch(state){
		case Start: // Initial transition
			PORTC = 0x07;
			state = Init;
			break;
		case Init:
			if((PINA & 0x03) == 0x03){
				state = Reset;
				PORTC = 0x00;
			}
			else if(((PINA & 0x02) == 0x02) && (PORTC > 0)){
				state = Decrement;
				PORTC -= 1;
			}
			else if(((PINA & 0x01) == 0x01) && (PORTC < 9)){
				state = Increment;
				PORTC += 1;
			}
			else{
				state = Init;
			}
			break;
		case Increment:
			if((PINA | 0x00) == 0x00){
				state = Init;
			}
			else if((PINA & 0x03) == 0x03){
				state = Reset;
				PORTC = 0x00;
			}
			else{
				state = Increment;
			}
			break;
		case Decrement:
			if((PINA | 0x00) == 0x00){
				state = Init;
			}
			else if((PINA & 0x03) == 0x03){
				state = Reset;
				PORTC = 0x00;
			}
			else{
				state = Decrement;
			}
			break;
		case Reset:
			if(((PINA & 0x03) == 0x03) || (PORTC == 0x09) || (PORTC == 0x00)){
				state = Reset;
				PORTC = 0x00;
			}
			else if(((PINA & 0x01) == 0x01) && (PORTC < 9)){
				state = Increment;
				PORTC += 1;
			}
			else if(((PINA & 0x02) == 0x02) && (PORTC > 0)){
				state = Decrement;
				PORTC -= 1;
			}
			else{
				state = Init;
			}
			break;
		default:
			state = Start;
			break;
	} // Transitions
	switch(state){ // State actions
		case Init:
			break;
		case Increment:
			break;
		case Decrement:
			break;
		case Reset:
			break;
		default:
			break;
	} // State actions
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs
	state = Start;
	TimerSet(100);
	TimerOn();
	while (1) {
		Tick();	
		while(!TimerFlag){}
		TimerFlag = 0;
	}
	return 0;
}
