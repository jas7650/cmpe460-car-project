#include "msp.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>

#define SERVO_CENTER 7.5/100
#define SERVO_RIGHT 5/100.0
#define SERVO_HALF_RIGHT 6.25/100.0
#define SERVO_LEFT 10/100.0
#define SERVO_HALF_LEFT 8.75/100.0

void initDCMotors(void);
void initServoMotor(void);
void driveForward(double dutyCycle);
void stopWheels(void);
void turnLeft(void);
void turnHalfLeft(void);
void turnRight(void);
void turnHalfRight(void);
void centerWheels(void);
int TIMER_A0_PWM_Init(uint16_t period, double percentDutyCycle, uint16_t pin);
void TIMER_A2_PWM_DutyCycle(double percentDutyCycle, uint16_t pin);
int TIMER_A2_PWM_Init(uint16_t period, double percentDutyCycle, uint16_t pin);
void TIMER_A2_PWM_DutyCycle(double percentDutyCycle, uint16_t pin);
