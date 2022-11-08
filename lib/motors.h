#include "msp.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>

#define SERVO_CENTER 7.5
#define SERVO_RIGHT 5
#define SERVO_1_2_RIGHT 6.25
#define SERVO_1_4_RIGHT 6.875
#define SERVO_3_4_RIGHT 5.625
#define SERVO_LEFT 10
#define SERVO_1_2_LEFT 8.75
#define SERVO_1_4_LEFT 8.125
#define SERVO_3_4_LEFT 9.375

#define LEFT 1
#define RIGHT -1

#define SERVO_1 2.5
#define SERVO_2 SERVO_1/2
#define SERVO_3 SERVO_2/2
#define SERVO_4 SERVO_3/2
#define SERVO_5 SERVO_4/2
#define SERVO_6 SERVO_5/2
#define SERVO_7 SERVO_6/2



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
double moveWheels(int position, double dutyCycle);
