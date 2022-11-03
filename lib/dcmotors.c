#include "msp.h"
#include "uart.h"
#include "TimerA.h"
 
void initDCMotors() {
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

void initServoMotor() {
    TIMER_A2_PWM_Init(((SystemCoreClock/8)/50)/2, SERVO_CENTER, 1);
}

void driveForward(double dutyCycle) {
	TIMER_A0_PWM_DutyCycle(dutyCycle, 1);
	TIMER_A0_PWM_DutyCycle(0, 2);
	
	TIMER_A0_PWM_DutyCycle(dutyCycle, 3);
	TIMER_A0_PWM_DutyCycle(0, 4);
}

void stopWheels() {
    TIMER_A0_PWM_DutyCycle(0.0, 1);
	TIMER_A0_PWM_DutyCycle(0.0, 2);
	
	TIMER_A0_PWM_DutyCycle(0.0, 3);
	TIMER_A0_PWM_DutyCycle(0.0, 4);
}

void turnLeft() {
    TIMER_A2_PWM_DutyCycle(SERVO_CLOCKWISE, 1);
}

void turnRight() {
    TIMER_A2_PWM_DutyCycle(SERVO_COUNTER_CLOCKWISE, 1);
}

void centerWheels() {
    TIMER_A2_PWM_DutyCycle(SERVO_CENTER, 1);
}