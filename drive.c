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

#define CENTER_SHIFT 20

extern  unsigned char OLED_clr_data[1024];
extern unsigned char OLED_TEXT_ARR[1024];
extern unsigned char OLED_GRAPH_ARR[1024];

extern uint16_t line[128];
extern BOOLEAN g_sendData;
uint16_t binaryCameraData[128];
uint16_t finalCameraData[128];
static uint16_t threshold = 12000;
static char str[100];

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
    
    Switch1_Init();
    Switch2_Init();
    EnableSysTickTimer();

    EnableInterrupts();
        
    while(1) {
        int i = 0;
        //smoothCameraData();
        //uart0_put("[");
        for(i = 0; i < 128; i++) {
            binaryCameraData[i] = binarizeCameraData(line[i], threshold);
            //sprintf(str, "%i", binaryCameraData[i]);
            //uart0_put(str);
        }
        for(i = 0; i < 128; i++) {
            if(i < CENTER_SHIFT) {
                finalCameraData[i] = 0;
            }else {
                finalCameraData[i] = binaryCameraData[i - CENTER_SHIFT];
            }
        }
        //uart0_put("]\r\n");
        if(g_sendData == TRUE) {
            OLED_DisplayCameraData(finalCameraData);
            g_sendData = FALSE;
        }
        
    }
}

