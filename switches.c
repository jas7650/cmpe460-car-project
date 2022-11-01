#include "msp.h" 
#include "Common.h"
#include "CortexM.h"



void Switch1_Init(void)
{
    // configure PortPin for Switch 1 and Switch2 as port I/O 
    P1->SEL0 &= ~BIT1;
    P1->SEL1 &= ~BIT1;

    // configure as input
    P1->DIR &= ~BIT1;
    
    // configure as pull up
    P1->REN |= BIT1;
    P1->OUT |= BIT1;
}

void Switch2_Init(void)
{
    // configure PortPin for Switch 2 as port I/O 
    P1->SEL0 &= ~BIT4;
    P1->SEL1 &= ~BIT4;

    // configure as input
    P1->DIR &= ~BIT4;
    
    // configure as pull up
    P1->REN |= BIT4;
    P1->OUT |= BIT4;
}

//  I/O interrupt pin setup
//
// DIR     SEL0/SEL1    IE    IES     Port Mode
//  0          00        0     0       Input, rising edge trigger
//  0          00        0     1       Input, falling edge trigger, interrupt
//  0          00        1     0       Input, rising edge trigger, interrupt
//  0          00        1     1       Input, falling edge trigger, interrupt
//

void Switch1_Interrupt_Init(void)
{
    // disable interrupts
    DisableInterrupts();
    // initialize the Switch as per previous lab
    Switch1_Init();
    
    //7-0 PxIFG RW 0h Port X interrupt flag
    //0b = No interrupt is pending.
    //1b = Interrupt is pending.
    // clear flag1 (reduce possibility of extra interrupt)    
    P1->IFG &= ~BIT1; 

    //7-0 PxIE RW 0h Port X interrupt enable
    //0b = Corresponding port interrupt disabled
    //1b = Corresponding port interrupt enabled    
    // arm interrupt on  P1.1    
    P1->IE |= BIT1;

    //7-0 PxIES RW Undefined Port X interrupt edge select
    //0b = PxIFG flag is set with a low-to-high transition.
    //1b = PxIFG flag is set with a high-to-low transition
    // now set the pin to cause falling edge interrupt event
    // P1.1 is falling edge event
    P1->IES |= BIT1;
    
    // now set the pin to cause falling edge interrupt event
    NVIC_IPR8 = (NVIC_IPR8 & 0x00FFFFFF)|0x40000000; // priority 2
    
    // enable Port 1 - interrupt 35 in NVIC    
    NVIC_ISER1 = 0x00000008;  
    
    // enable interrupts  (// clear the I bit    )
    EnableInterrupts();
    
}
void Switch2_Interrupt_Init(void)
{
    // disable interrupts
    DisableInterrupts();
    
    // initialize the Switch as per previous lab
    Switch2_Init();
    
    // now set the pin to cause falling edge interrupt event
    // P1.4 is falling edge event
    P1->IES |= BIT4;
  
    // clear flag4 (reduce possibility of extra interrupt)
    P1->IFG &= ~BIT4; 
  
    // arm interrupt on P1.4 
    P1->IE |= BIT4;
    
    // now set the pin to cause falling edge interrupt event
    NVIC_IPR8 = (NVIC_IPR8&0x00FFFFFF)|0x40000000; // priority 2
    
    // enable Port 1 - interrupt 35 in NVIC
    NVIC_ISER1 = 0x00000008;         
    
    // enable interrupts  (// clear the I bit    )
    EnableInterrupts();              
}
