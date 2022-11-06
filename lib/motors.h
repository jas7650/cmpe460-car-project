#include "msp.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>

#define SERVO_CENTER 7.5/100
#define SERVO_RIGHT 5/100.0
#define SERVO_1_2_RIGHT 6.25/100.0
#define SERVO_1_4_RIGHT 6.875/100.0
#define SERVO_3_4_RIGHT 5.625/100.0
#define SERVO_LEFT 10/100.0
#define SERVO_1_2_LEFT 8.75/100.0
#define SERVO_1_4_LEFT 8.125/100.0
#define SERVO_3_4_LEFT 9.375/100.0

#define SERVO_1_LEFT -0.25
#define SERVO_2_LEFT -0.75
#define SERVO_3_LEFT -1.5
#define SERVO_4_LEFT -2.5

#define SERVO_1_RIGHT 0.25
#define SERVO_2_RIGHT 0.75
#define SERVO_3_RIGHT 1.5
#define SERVO_4_RIGHT 2.5

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
double moveWheels(int left[], int right[], double dutyCycle);
