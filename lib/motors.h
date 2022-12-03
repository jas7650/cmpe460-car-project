#include "msp.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>

#define SERVO_CENTER 7.5
#define SERVO_RIGHT 5.05
#define SERVO_LEFT 9.95

void initDCMotors(void);
void initServoMotor(void);
void driveForward(double dutyCycle);
double moveWheels(double center, double dutyCycle);
void turnWheels(double angle);
void updateSpeed(double error);
void differentialSpeed(double error);
