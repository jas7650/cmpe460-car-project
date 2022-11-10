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

extern  unsigned char OLED_clr_data[1024];
extern unsigned char OLED_TEXT_ARR[1024];
extern unsigned char OLED_GRAPH_ARR[1024];

int leftEdge, rightEdge;
int position = 64;
double percentDutyCycle = SERVO_CENTER;
int differenceChange;
double center, prevCenter = 0;
double angle = 0;
double error, oldError = 0;

double kp = 1/10.0;

extern uint16_t line_data[128];
extern uint16_t smooth_data[128];
extern uint16_t binary_data[128];
extern uint16_t edge_data[128];
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
            smoothCameraData();
            binarizeCameraData(THRESHOLD);
            error = calcCenterMass();                  //Returns a value -60 through 60
            //center = error+60;
            //updateCenterData(center, prevCenter);
            angle = error*2.25;
            turnWheels(angle);
            if (detect_carpet()) {
                driveForward(0);
            } else {
                driveForward(.35);
            }
            //OLED_DisplayCameraData(center_data);
            //prevCenter = error;
            g_sendData = FALSE;
        }
    }
}

