#include "msp.h"
#include "uart.h"
#include "motors.h"

// Make these arrays 5 deep, since we are using indexes 1-4 for the pins
static uint32_t DEFAULT_PERIOD_A0[5] = {0,0,0,0,0};
static uint32_t DEFAULT_PERIOD_A2[5] = {0,0,0,0,0};

//***************************PWM_Init*******************************
// PWM output on P2.4, P2.5, P2.6, P2.7
// Inputs:  period of P2.4...P2.7 is number of counts before output changes state
//          percentDutyCycle (0 -> 1.0)
//          pin number (1,2,3,4)
// Outputs: none

int TIMER_A0_PWM_Init(uint16_t period, double percentDutyCycle, uint16_t pin)
{
    uint16_t dutyCycle;
    // Timer A0.1
    if (pin == 1){
        P2->SEL0 |= BIT(4);
        P2->SEL1 &= ~BIT(4);
        P2->DIR |= BIT(4);
    }
    // Timer A0.2
    else if (pin == 2){
        P2->SEL0 |= BIT(5);
        P2->SEL1 &= ~BIT(5);
        P2->DIR |= BIT(5);
    }    
    // Timer A0.3
    else if (pin == 3){
    P2->SEL0 |= BIT(6);
        P2->SEL1 &= ~BIT(6);
        P2->DIR |= BIT(6);
    }    
    // Timer A0.4
    else if (pin == 4){
    P2->SEL0 |= BIT(7);
        P2->SEL1 &= ~BIT(7);
        P2->DIR |= BIT(7);
    }
    else {
        return -2;
    }
    // save the period for this timer instance
    // DEFAULT_PERIOD_A0[pin] where pin is the pin number
    DEFAULT_PERIOD_A0[pin] = period;
    // TIMER_A0->CCR[0]
    TIMER_A0->CCR[0] = period;
    // TIMER_A0->CCTL[pin]
    TIMER_A0->CCTL[0] |= BIT(7);
    TIMER_A0->CCTL[pin] |= BIT(6);
    // set the duty cycle
    dutyCycle = (uint16_t) (percentDutyCycle * (double)DEFAULT_PERIOD_A0[pin]);

    // CCR[n] contains the dutyCycle just calculated, where n is the pin number
    //TIMER_A0->CCR[pin]
    TIMER_A0->CCR[pin] = dutyCycle;
    
    // Timer CONTROL register
    // TIMER_A0->CTL
    TIMER_A0->CTL = 0x0230;
    return 0;
}
//***************************PWM_Duty1*******************************
// change duty cycle of PWM output on pin
// Inputs:  dutycycle, pin
// Outputs: none
// percentDutyCycle is a number between 0 and 1  (ie. 0.5 = 50%)
void TIMER_A0_PWM_DutyCycle(double percentDutyCycle, uint16_t pin){
    TIMER_A0->CCR[pin] = (uint16_t) (percentDutyCycle * (double)DEFAULT_PERIOD_A0[pin]);
}
 
void init_dc_motors() {
    P3->SEL0 &= ~BIT(6);
    P3->SEL1 &= ~BIT(6);
    P3->DIR |= BIT(6);
    P3->OUT |= BIT(6);
    P3->SEL0 &= ~BIT(7);
    P3->SEL1 &= ~BIT(7);
    P3->DIR |= BIT(7);
    P3->OUT |= BIT(7);
    TIMER_A0_PWM_Init(SystemCoreClock/20000, 0.0, 1); //Motor 1
    TIMER_A0_PWM_Init(SystemCoreClock/20000, 0.0, 2); //Motor 1
    
    TIMER_A0_PWM_Init(SystemCoreClock/20000, 0.0, 3); //Motor 2
    TIMER_A0_PWM_Init(SystemCoreClock/20000, 0.0, 4); //Motor 2
}

//initializes servo motor with a frequency and position
void init_servo_motor(void) {
    uint16_t dutyCycle;
    // NOTE: Timer A2 only exposes 1 PWM pin
    // TimerA2.1
    P5->SEL0 |= BIT(6);
    P5->SEL1 &= ~BIT(6);
    P5->DIR |= BIT(6);
    
   // NOTE: Setup similar to TimerA0
    // save the period for this timer instance
    // DEFAULT_PERIOD_A0[pin] where pin is the pin number
    DEFAULT_PERIOD_A2[1] = ((SystemCoreClock/8)/50)/2;
    // TIMER_A0->CCR[0]
    TIMER_A2->CCR[0] = ((SystemCoreClock/8)/50)/2;
    // TIMER_A0->CCTL[pin]
    TIMER_A2->CCTL[0] |= BIT(7);
    TIMER_A2->CCTL[1] |= BIT(6);
    // set the duty cycle
    dutyCycle = (uint16_t) (SERVO_CENTER * (double)DEFAULT_PERIOD_A2[1]);

    // CCR[n] contains the dutyCycle just calculated, where n is the pin number
    //TIMER_A0->CCR[pin]
    TIMER_A2->CCR[1] = dutyCycle;
    
    // Timer CONTROL register
    // TIMER_A0->CTL
    TIMER_A2->CTL = 0x0230;
      // You will have to use the prescaler (clock divider) to get down to 20ms
    TIMER_A2->CTL |= BIT(7);
    TIMER_A2->CTL |= BIT(6);
    
    //TIMER_A2->EX0 |= BIT(2);
    //TIMER_A2->EX0 |= BIT(1);
    //TIMER_A2->EX0 |= BIT(0);
}

//drives forward with varying speed
void drive_forward(double dutyCycle) {
    TIMER_A0_PWM_DutyCycle(dutyCycle, 1);
    TIMER_A0_PWM_DutyCycle(0, 2);
    
    TIMER_A0_PWM_DutyCycle(dutyCycle, 3);
    TIMER_A0_PWM_DutyCycle(0, 4);
}

//stops the car
void stop_wheels() {
    TIMER_A0_PWM_DutyCycle(0.0, 1);
    TIMER_A0_PWM_DutyCycle(0.0, 2);
    
    TIMER_A0_PWM_DutyCycle(0.0, 3);
    TIMER_A0_PWM_DutyCycle(0.0, 4);
}

//turns left by a degree given by an argument
void turn_left() {
    TIMER_A2->CCR[1] = (uint16_t) (SERVO_LEFT * (double)DEFAULT_PERIOD_A2[1]);
}

//turns right by a degree given by an argument
void turn_right() {
    TIMER_A2->CCR[1] = (uint16_t) (SERVO_RIGHT * (double)DEFAULT_PERIOD_A2[1]);
}

//turns the wheels back to center
void center_wheels() {
    TIMER_A2->CCR[1] = (uint16_t) (SERVO_CENTER * (double)DEFAULT_PERIOD_A2[1]);
}
