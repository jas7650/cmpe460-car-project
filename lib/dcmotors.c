#include "msp.h"
#include "uart.h"
#include "TimerA.h"

void initMotors() {
	TIMER_A0_PWM_Init(SystemCoreClock/20000, 0.0, 1); //Motor 1
  TIMER_A0_PWM_Init(SystemCoreClock/20000, 0.0, 2); //Motor 1
	
	TIMER_A0_PWM_Init(SystemCoreClock/20000, 0.0, 3); //Motor 2
  TIMER_A0_PWM_Init(SystemCoreClock/20000, 0.0, 4); //Motor 2
}

void driveForward(double dutyCycle) {
	TIMER_A0_PWM_DutyCycle(dutyCycle, 1);
	TIMER_A0_PWM_DutyCycle(0, 2);
	
	TIMER_A0_PWM_DutyCycle(dutyCycle, 3);
	TIMER_A0_PWM_DutyCycle(0, 4);
}