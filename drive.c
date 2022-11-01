/*
 * Main module for testing the PWM Code for the K64F
 * 
 * Author:  
 * Created:  
 * Modified: Carson Clarke-Magrab <ctc7359@rit.edu> 
 * LJBeato
 * 2021
 */
 
 //THIS COMMENT SHOULD ONLY BE IN daniel_dev BRANCH

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

extern  unsigned char OLED_clr_data[1024];
extern unsigned char OLED_TEXT_ARR[1024];
extern unsigned char OLED_GRAPH_ARR[1024];

uint16_t lineData[128];
extern uint16_t line[128];
extern BOOLEAN g_sendData;
static char str[100];
void msdelay(int delay)
{
    int i,j;
    for(i=0;i<delay;i++)
        for(j=0;j<16000;j++);
}

/**
 * Waits for a delay (in milliseconds)
 * 
 * del - The delay in milliseconds
 */
void main_delay(int del){
    volatile int i;
    for (i=0; i<del*50000; i++){
        ;// Do nothing
    }
}

void INIT_Camera(void)
{
    g_sendData = FALSE;
    ControlPin_SI_Init();
    ControlPin_CLK_Init();
    ADC0_InitSWTriggerCh6();
}

void myDelay(void)
{
    volatile int j = 0;
    for (j = 0; j < 800000; j++)
    {
        ;
    }
}

/*
//DC MAIN
int main(void) {
    // Initialize UART and PWM
    uart0_init();
    TIMER_A0_PWM_Init(SystemCoreClock/20000, 0.2, 1);
    TIMER_A0_PWM_Init(SystemCoreClock/20000, 0.2, 2);
    
    // Print welcome over serial
    uart0_put("Running... \n\r");
    
    while(1)  //loop forever
    {
        uint16_t dc = 0;
        uint16_t freq = 50; // Frequency = 50 Hz 
        uint16_t dir = 0;
        double dutyCycle = 0;
        char c = 48;
        char buffer[20];
        int i=0;
        
        
        uart0_put("loop 1\r\n");
        // 0 to 100% duty cycle in forward direction
        for (i=0; i<100; i++) {
            sprintf(buffer, "i: %d\r\n", i);
            uart0_put(buffer);
            dutyCycle = i/100.0;
            sprintf(buffer, "dc: %f\r\n", dutyCycle);
            uart0_put(buffer);
            TIMER_A0_PWM_DutyCycle(dutyCycle, 1);
            TIMER_A0_PWM_DutyCycle(0, 2);
            main_delay(1);
        }
        
        uart0_put("loop 2\r\n");
        // 100% down to 0% duty cycle in the forward direction
        for (i=100; i>=0; i--) {
            sprintf(buffer, "i: %d\r\n", i);
            uart0_put(buffer);
            dutyCycle = i/100.0;
            sprintf(buffer, "dc: %f\r\n", dutyCycle);
            uart0_put(buffer);
            TIMER_A0_PWM_DutyCycle(dutyCycle, 1);
            TIMER_A0_PWM_DutyCycle(0, 2);
            main_delay(1);
        }
        
        uart0_put("loop 3\r\n");
        // 0 to 100% duty cycle in reverse direction
        for (i=0; i<100; i++) {
            sprintf(buffer, "i: %d\r\n", i);
            uart0_put(buffer);
            dutyCycle = i/100.0;
            sprintf(buffer, "dc: %f\r\n", dutyCycle);
            uart0_put(buffer);
            TIMER_A0_PWM_DutyCycle(0, 1);
            TIMER_A0_PWM_DutyCycle(dutyCycle, 2);
            main_delay(1);
        }
        
        uart0_put("loop 4\r\n");
        // 100% down to 0% duty cycle in the reverse direction
        for (i=100; i>=0; i--) {
            sprintf(buffer, "i: %d\r\n", i);
            uart0_put(buffer);
            dutyCycle = i/100.0;
            sprintf(buffer, "dc: %f\r\n", dutyCycle);
            TIMER_A0_PWM_DutyCycle(0, 1);
            TIMER_A0_PWM_DutyCycle(dutyCycle, 2);
            main_delay(1);
        }

    }
    return 0;
}
*/

/*
//STEPPER MAIN
int main(void) {
    
    int forward = 0;
    int phase = 0;
    
    uart0_init();
    
    uart0_put("Setting P4.1-P4.4 SEL0 and SEL1 to 0\r\n");
    P4->SEL0 &= ~BIT(1);
    P4->SEL1 &= ~BIT(1);
    P4->DIR |= BIT(1);
    P4->DS |= BIT(1);
    
    P4->SEL0 &= ~BIT(2);
    P4->SEL1 &= ~BIT(2);
    P4->DIR |= BIT(2);
    P4->DS |= BIT(2);
    
    P4->SEL0 &= ~BIT(3);
    P4->SEL1 &= ~BIT(3);
    P4->DIR |= BIT(3);
    P4->DS |= BIT(3);
    
    P4->SEL0 &= ~BIT(4);
    P4->SEL1 &= ~BIT(4);
    P4->DIR |= BIT(4);
    P4->DS |= BIT(4);
    while(1) {
        //Turn off all coils, set GPIO pins to 0
        uart0_put("Turning off all coils\r\n");
        P4->OUT = 0;
        //Set one pin high at a time
        if(forward) {
            if(phase == 0) {
                //Turn on coil A
                uart0_put("Turn on coil A\r\n");
                P4->OUT = BIT(1);
                //main_delay(10);
                phase++;
            }
            else if(phase == 1) {
                //Turn on coil B
                uart0_put("Turn on coil B\r\n");
                P4->OUT = BIT(2);
            //    main_delay(10);
                phase++;
            }
            else if(phase == 2) {
                //Turn on coil C
                uart0_put("Turn on coil C\r\n");
                P4->OUT = BIT(3);
                //main_delay(10);
                phase++;
            }
            else {
                //Turn on coil D
                uart0_put("Turn on coil D\r\n");
                P4->OUT = BIT(4);
                //main_delay(10);
                phase=0;
            }
        } else {
            //Reverse
            if(phase == 0) {
                //Turn on coil D
                P4->OUT = BIT(4);
                phase++;
            }
            else if(phase == 1) {
                //Turn on coil C
                P4->OUT = BIT(3);
                phase++;
            }
            else if(phase == 2) {
                //Turn on coil B
                P4->OUT = BIT(2);
                phase++;
            }
            else {
                //Turn on coil A
                P4->OUT = BIT(1);
                phase=0;
            }
        }
        main_delay(10);
    }
    return 0;
}
*/

/*
//PWM MAIN DC
int main(void) {
    // Initialize UART and PWM
    uart0_init();
    TIMER_A0_PWM_Init((SystemCoreClock/10000)/2, 0.2, 1);
    // Part 1 - UNCOMMENT THIS
    // Generate 20% duty cycle at 10kHz
    // INSERT CODE HERE
    
    for(;;) ;  //then loop forever
}
*/


//PWM MAIN SERVO
int main(void) {
    
    int i;
    int delta;
    
    //initialize OLED
    OLED_Init();
    OLED_display_on();
    OLED_display_clear();
    OLED_display_on();
    
    //initialize uart
    uart0_init();
    
    //initializations
    DisableInterrupts();
    uart0_init();
    uart0_put("\r\nLab5 CAMERA demo\r\n");

    
    uart0_put("\r\nINIT LEDs\r\n");
    LED1_Init();
    LED2_Init();
    // remember that we double the desired frequency because we need to account

    uart0_put("\r\nINIT Camera CLK and SI\r\n");
    uart0_put("\r\nINIT ADC\r\n");
    INIT_Camera();
    
    uart0_put("\r\nINIT Switch 2\r\n");
    Switch2_Init();
    ControlPin_SI_Init();
    ControlPin_CLK_Init();
    EnableSysTickTimer();


    uart0_put("\r\nEnable Interrupts\r\n");
    EnableInterrupts();
    uart0_put("\r\nInterrupts successfully enabled\r\n");

    while(1)
    {

        if (g_sendData == TRUE) 
        {
            led1_on();
            // send the array over uart
            sprintf(str,"%i\n\r",-1); // start value
            uart0_put(str);
            for (i = 0; i < 128; i++) 
            {
                sprintf(str,"%i\n\r", line[i]);
                uart0_put(str);
            }
            sprintf(str,"%i\n\r",-2); // end value
            uart0_put(str);
            led1_off();
            g_sendData = FALSE;
        }
        // do a small delay
        myDelay();
    }
		
    // create some fake 14-bit camera line data 0 - >2^14 in a 128 short array that utilizes all 14 bits
    for (i = 0; i < 128; i++)
        lineData[i] = 4;
    while(1)
    {
            OLED_write_display(OLED_TEXT_ARR);
            msdelay(500);
            OLED_DisplayCameraData(lineData);
            msdelay(500);
    }
    
    // Initialize UART and PWM
//    TIMER_A2_PWM_Init(((SystemCoreClock/8)/50)/2, SERVO_CENTER, 1);
//    main_delay(10);
//    TIMER_A2_PWM_DutyCycle(SERVO_CLOCKWISE, 1);
//    main_delay(10);
//    TIMER_A2_PWM_DutyCycle(SERVO_COUNTER_COUNTER, 1);
//    main_delay(10);
//    TIMER_A2_PWM_DutyCycle(SERVO_CENTER, 1);
}

