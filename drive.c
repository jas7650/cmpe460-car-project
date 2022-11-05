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

#define CENTER_SHIFT 0
#define THRESHOLD 8000

extern  unsigned char OLED_clr_data[1024];
extern unsigned char OLED_TEXT_ARR[1024];
extern unsigned char OLED_GRAPH_ARR[1024];

double leftZerosPercent;
double rightZerosPercent;
int leftZeros, rightZeros;

extern uint16_t line[128];
extern BOOLEAN g_sendData;
extern uint16_t binaryCameraData[128];
extern uint16_t finalCameraData[128];
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
        smoothCameraData();
        binarizeCameraData(THRESHOLD);
        if(g_sendData == TRUE) {
            OLED_DisplayCameraData(binaryCameraData);
            g_sendData = FALSE;
        }
        leftZeros = calc_left_zeros(binaryCameraData);
        rightZeros = calc_right_zeros(binaryCameraData);
        if (!detect_carpet(binaryCameraData)) {
            driveForward(0.275);
        } else {
            driveForward(0);
        }
        moveWheels(leftZeros, rightZeros);
    }
}

