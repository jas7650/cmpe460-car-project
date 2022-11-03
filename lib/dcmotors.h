#include "msp.h"
#include "uart.h"
#include "TimerA.h"

void initDCMotors();
void initServoMotor();
void driveForward(double dutyCycle);
void stopWheels();
void turnLeft();
void turnRight();
void centerWheels();
