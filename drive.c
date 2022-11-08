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

extern  unsigned char OLED_clr_data[1024];
extern unsigned char OLED_TEXT_ARR[1024];
extern unsigned char OLED_GRAPH_ARR[1024];

int leftEdge, rightEdge;
int position = 64;
double percentDutyCycle = SERVO_CENTER;
int differenceChange;

extern uint16_t line_1[128];
extern uint16_t edge_data[128];
uint16_t position_data[128];

extern BOOLEAN g_sendData;
extern uint16_t binaryCameraData[128];
extern uint16_t finalCameraData[128];
extern uint16_t edgeCameraData[128];
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
        int i = 0;
        leftEdge = getLeftEdge(line_1);
        rightEdge = getRightEdge(line_1);
        position_data[position] = LOW;
        position = calculatePosition(leftEdge, rightEdge);
        if (position != -1) {
            position_data[position] = HIGH/2;
        }
        position_data[FAR_LEFT] = HIGH;
        position_data[FAR_RIGHT] = HIGH;
        
//        if(g_sendData == TRUE) {
//            OLED_DisplayCameraData(position_data);
//            g_sendData = FALSE;
//        }
        
//        if (leftEdge != -1 && rightEdge != -1) {
//            driveForward(0.275);
//            led2_off();
//        } else {
//            driveForward(0);
//            led2_on(RED);
//        }
        percentDutyCycle = moveWheels(position, percentDutyCycle);
    }
}

