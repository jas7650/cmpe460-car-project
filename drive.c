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

int leftEdge[3], rightEdge[3];
double percentDutyCycle = SERVO_CENTER;
int differenceChange;

extern uint16_t line_1[128];
extern uint16_t line_2[128];
extern uint16_t line_3[128];
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
        //smoothCameraData();
        //binarizeCameraData(THRESHOLD);
        leftEdge[2] = leftEdge[1];
        leftEdge[1] = leftEdge[0];
        leftEdge[0] = calc_left_edge(line_1);
        
        rightEdge[2] = rightEdge[1];
        rightEdge[1] = rightEdge[0];
        rightEdge[0] = calc_right_edge(line_1);
        
        setEdgesHigh(leftEdge, rightEdge, line_1);
        
        if(g_sendData == TRUE) {
            OLED_DisplayCameraData(edgeCameraData);
            g_sendData = FALSE;
        }
        
//        if (!detect_carpet(line_1)) {
//            driveForward(0.275);
//        } else {
//            driveForward(0);
//        }
        percentDutyCycle = moveWheels(leftEdge, rightEdge, percentDutyCycle);
    }
}

