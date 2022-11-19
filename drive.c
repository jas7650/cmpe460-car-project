/*
 * Main module for testing the PWM Code for the K64F
 * 
 * Author:  
 * Created:  
 * Modified: Carson Clarke-Magrab <ctc7359@rit.edu> 
 * LJBeato
 * 2021
 */
#include <stdio.h>
#include <stdlib.h>
#include "msp.h"
#include "./lib/uart.h"
#include "./lib/oled.h"
#include "./lib/led.h"
#include "./lib/switches.h"
#include "./lib/Timer32.h"
#include "./lib/CortexM.h"
#include "./lib/Common.h"
#include "./lib/ADC14.h"
#include "./lib/ControlPins.h"
#include "./lib/SysTickTimer.h"
#include "./lib/camera.h"
#include "./lib/motors.h"
#include "./lib/camera.h"
#include <math.h>

extern unsigned char OLED_clr_data[1024];
extern unsigned char OLED_TEXT_ARR[1024];
extern unsigned char OLED_GRAPH_ARR[1024];

double percentDutyCycle = SERVO_CENTER;
int differenceChange;
double center, prevCenter = 0;
double angle, oldAngle = 0;
double errorArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
double error, currentError, oldError1, oldError2 = 0;

double kp = .57;
double kd = 0.3;
double ki = 0;

extern uint16_t line_data[128];
extern uint16_t smooth_data[128];
extern uint16_t binary_data[128];
extern uint16_t center_data[128];

uint16_t position_data[128];

extern BOOLEAN g_sendData;
static char str[1024];

void main_delay(int del){
    volatile int i;
    for (i=0; i<del*50000; i++){
        ;// Do nothing
    }
}

double get_integral(void) {
    double sum;
    int i;
    for (i = 1; i < 10; i++) {
        sum += (errorArray[i]+errorArray[i-1])/2.0;
    }
    return sum;
}

double sum_error(int index) {
    double sum;
    int i;
    for (i = index; i < index+7; i++) {
        sum += errorArray[i];
    }
    return sum;
}

int main(void) {
    //initialize OLED
    OLED_Init();
    OLED_display_on();
    OLED_display_clear();
    OLED_display_on();
    
    //initialize uart
    uart0_init();
    
    //initializations
    DisableInterrupts();
   
    LED1_Init();
    LED2_Init();

    INIT_Camera();
    
    initDCMotors();
    initServoMotor();
    
    Switch1_Init();
    Switch2_Init();
    EnableSysTickTimer();

    EnableInterrupts();  
    while(1) {
        
        if(g_sendData == TRUE) {
            int i;
            smoothCameraData();
            binarizeCameraData(THRESHOLD);
            error = calcCenterMass();                  //Returns a value -60 through 60
            for (i = 1; i < 10; i++) {
                errorArray[i] = errorArray[i-1];
            }
            errorArray[0] = error;
            currentError = sum_error(0);
            //center = error+60;
            //updateCenterData(center, prevCenter);
            angle = oldAngle + kp*(currentError-oldError1) + ki*((currentError+oldError1)/2) + kd*(currentError-2*oldError1+oldError2);
            //angle = error*2.25;
            turnWheels(angle);
            if (detect_carpet()) {
                driveForward(0);
            } else {
                driveForward(.35);
            }
            //OLED_DisplayCameraData(center_data);
            //prevCenter = error;
            oldAngle = angle;
            oldError2 = oldError1;
            oldError1 = currentError;
            g_sendData = FALSE;
        }
    }
}
