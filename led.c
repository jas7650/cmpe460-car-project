#include "msp.h" 
#include "Common.h"
#include "led.h"

void LED1_Init(void)
{
    // configure PortPin for LED1 as port I/O 
    P1->SEL0 &= ~BIT0;
    P1->SEL1 &= ~BIT0;

    // make built-in LED1 LED high drive strength
    P1->DS |= BIT0;

    // make built-in LED1 out     
    P1->DIR |= BIT0;

    // turn off LED
    P1->OUT &= ~BIT0;
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
    
    // make built-in LED2 LEDs high drive strength
    P2->DS |= BIT0;
    P2->DS |= BIT1;
    P2->DS |= BIT2;

    // make built-in LED2 out     
    P2->DIR |= BIT0;
    P2->DIR |= BIT1;
    P2->DIR |= BIT2;

    // turn off LED
    P2->OUT &= ~BIT0;
    P2->OUT &= ~BIT1;
    P2->OUT &= ~BIT2;
}

void led1_on(void) {
    P1->OUT |= BIT0;
}

void led1_off(void) {
    P1->OUT &= ~BIT0;
}

BOOLEAN led1_state(void) {
    if (P1->OUT & BIT0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void led2_on(int color) {
    switch(color) {
        case RED :
            P2->OUT |= BIT0;
            P2->OUT &= ~BIT1;
            P2->OUT &= ~BIT2;
            break;
        case GREEN :
            P2->OUT &= ~BIT0;
            P2->OUT |= BIT1;
            P2->OUT &= ~BIT2;
            break;
        case BLUE :
            P2->OUT &= ~BIT0;
            P2->OUT &= ~BIT1;
            P2->OUT |= BIT2;
            break;
        case CYAN:
            P2->OUT &= ~BIT0;
            P2->OUT |= BIT1;
            P2->OUT |= BIT2;
            break;
        case MAGENTA :
            P2->OUT |= BIT0;
            P2->OUT &= ~BIT1;
            P2->OUT |= BIT2;
            break;
        case YELLOW :
            P2->OUT |= BIT0;
            P2->OUT |= BIT1;
            P2->OUT &= ~BIT2;
            break;
        case WHITE :
            P2->OUT |= BIT0;
            P2->OUT |= BIT1; 
            P2->OUT |= BIT2;
            break;
    }
}

void led2_off(void) {
    P2->OUT &= BIT0;
    P2->OUT &= BIT1;
    P2->OUT &= BIT2;
}
