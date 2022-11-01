/*
 * Main module for testing the PWM Code for the K64F
 * 
 * Author:  
 * Created:  
 * Modified: Carson Clarke-Magrab <ctc7359@rit.edu> 
 * LJBeato
 * 2021
 */

#include "msp.h"
#include "./lib/uart.h"
#include "./lib/TimerA.h"
#include "./lib/oled.h"
#include "./lib/led.h"
#include <stdio.h>
#include <stdlib.h>
#include "./lib/switches.h"
#include "./lib/Timer32.h"
#include "./lib/CortexM.h"
#include "./lib/Common.h"
#include "./lib/ADC14.h"
#include "./lib/ControlPins.h"
#include "./lib/SysTickTimer.h"
#include "./lib/camera.h"
#include "./lib/dcmotors.h"

extern  unsigned char OLED_clr_data[1024];
extern unsigned char OLED_TEXT_ARR[1024];
extern unsigned char OLED_GRAPH_ARR[1024];

extern uint16_t line[128];

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
    //uart0_init();
    
    //initializations
    DisableInterrupts();
    //uart0_init();

    
    LED1_Init();
    LED2_Init();
    // remember that we double the desired frequency because we need to account

    INIT_Camera();
	
		initMotors();
    
    Switch2_Init();
    ControlPin_SI_Init();
    ControlPin_CLK_Init();
    EnableSysTickTimer();

    EnableInterrupts();
		
		while(line[64] > 16000) {
			driveForward(0.2);
		}
}

