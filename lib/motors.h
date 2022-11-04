#include "msp.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>

#define SERVO_CENTER 7.5/100
#define SERVO_LEFT 5/100.0
#define SERVO_RIGHT 10/100.0

void init_dc_motors(void);
void init_servo_motor(void);
void drive_forward(double dutyCycle);
void stop_wheels(void);
void turn_left(void);
void turn_right(void);
void center_wheels(void);
