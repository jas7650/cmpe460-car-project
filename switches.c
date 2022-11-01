#include "msp.h" 

#include "Common.h"

void switch1_init() {
	P1->SEL0 &= ~BIT1;
	P1->DIR &= ~BIT1;
	P1->REN |= BIT1;
	P1->OUT |= BIT1;
	P1->IES |= BIT1;
	P1->IE |= BIT1;
}

void switch2_init() {
	P1->SEL0 &= ~BIT4;
	P1->DIR &= ~BIT4;
	P1->REN |= BIT4;
	P1->OUT |= BIT4;
	P1->IES |= BIT4;
	P1->IE |= BIT4;
}

void Switches_Init(void)
{
    // configure PortPin for Switch 1 and Switch2 as port I/O 
    P1->SEL0 &= ~BIT1;
    P1->SEL0 &= ~BIT4;

    // configure as input
    P1->DIR &= ~BIT1;
    P1->DIR &= ~BIT4;
    
    // configure as pull up
    P1->REN |= BIT1;
    P1->REN |= BIT4;
    P1->OUT |= BIT1;
    P1->OUT |= BIT4;
    
    // configure as falling edge
    P1->IES |= BIT1;
    P1->IES |= BIT4;
    
    //configure as interrupt enabled
    P1->IE |= BIT1;
    P1->IE |= BIT4;
}
//------------Switch_Input------------
// Read and return the status of Switch1
// Input: none
// return: TRUE if pressed
// FALSE if not pressed
BOOLEAN Switch1_Pressed(void)
{
    BOOLEAN retVal = FALSE;
    // check if pressed
    if (P1->IN & BIT1)
        retVal = FALSE;
    else
        retVal = TRUE;

    return (retVal);// return TRUE(pressed) or FALSE(not pressed)
}
//------------Switch_Input------------
// Read and return the status of Switch2
// Input: none
// return: TRUE if pressed
// FALSE if not pressed
BOOLEAN Switch2_Pressed(void)
{
    BOOLEAN retVal = FALSE;
    // check if pressed
    if (P1->IN & BIT4)
        retVal = FALSE;
    else
        retVal = TRUE;

    return (retVal);// return TRUE(pressed) or FALSE(not pressed)
}