#include "msp.h" 
#include "Common.h"
#include "led.h"

void LED1_Init(void) {
	// configure PortPin for LED1 as port I/O 
	P1->SEL0 &= ~BIT0;
	P1->SEL1 &= ~BIT0;
	P1->DIR |= BIT0;

	// make built-in LED1 LED high drive strength
	P1->DS |= BIT0;

	// make built-in LED1 out	 
	P1->OUT |= BIT0;

	// turn off LED
	P1->OUT &= ~BIT0;
}

void LED1_On(void) {
	P1->OUT |= BIT0;
}

void LED1_Off(void) {
	P1->OUT &= ~BIT0;
}

BOOLEAN LED1_State(void) {
	if(P1->OUT & BIT0) {
		return TRUE;
	} else {
		return FALSE;
	}
}

void LED2_Init(void)
{
	// configure PortPin for LED2 as port I/O 
	P2->SEL0 &= ~BIT0;
	P2->SEL1 &= ~BIT0;
	P2->SEL0 &= ~BIT1;
	P2->SEL1 &= ~BIT1;
	P2->SEL0 &= ~BIT2;
	P2->SEL1 &= ~BIT2;
	P2->DIR |= BIT0;
	P2->DIR |= BIT1;
	P2->DIR |= BIT2;

	// make built-in LED2 LEDs high drive strength
	P2->DS |= BIT0;
	P2->DS |= BIT1;
	P2->DS |= BIT2;

	// make built-in LED2 out	 
	P2->OUT |= BIT0;
	P2->OUT |= BIT1;
	P2->OUT |= BIT2;

	// turn off LED
	P2->OUT &= ~BIT0;
	P2->OUT &= ~BIT1;
	P2->OUT &= ~BIT2;
}

void LED2_Off(void) {
	P2->OUT &= ~BIT0;
	P2->OUT &= ~BIT1;
	P2->OUT &= ~BIT2;
}

void LED2_On(int color) {
	switch (color) {
		case RED:
			P2->OUT |= BIT0;
			P2->OUT &= ~BIT1;
		  	P2->OUT &= ~BIT2;
			break;
		case GREEN:
			P2->OUT &= ~BIT0;
			P2->OUT |= BIT1;
		  	P2->OUT &= ~BIT2;
			break;
		case BLUE:
			P2->OUT &= ~BIT0;
			P2->OUT &= ~BIT1;
		  	P2->OUT |= BIT2;
			break;
		case CYAN:
			P2->OUT &= ~BIT0;
			P2->OUT |= BIT1;
		  	P2->OUT |= BIT2;
			break;
		case MAGENTA:
			P2->OUT |= BIT0;
			P2->OUT &= ~BIT1;
		  	P2->OUT |= BIT2;
			break;
		case YELLOW:
			P2->OUT |= BIT0;
			P2->OUT |= BIT1;
		  	P2->OUT &= ~BIT2;
			break;
		case WHITE:
			P2->OUT |= BIT0;
			P2->OUT |= BIT1;
		  	P2->OUT |= BIT2;
			break;
	}
}

void LED2_Red(void) {
	P2->OUT |= BIT0;
}

void LED2_Green(void) {
	P2->OUT |= BIT1;
}

void LED2_Blue(void) {
	P2->OUT |= BIT2;
}