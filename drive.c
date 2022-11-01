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
    // Initialize UART and PWM
    uart0_init();
    TIMER_A2_PWM_Init(((SystemCoreClock/8)/50)/2, SERVO_CENTER, 1);
    main_delay(10);
    TIMER_A2_PWM_DutyCycle(SERVO_CLOCKWISE, 1);
    main_delay(10);
    TIMER_A2_PWM_DutyCycle(SERVO_COUNTER_COUNTER, 1);
    main_delay(10);
    TIMER_A2_PWM_DutyCycle(SERVO_CENTER, 1);
}

