#include "msp.h"
#include "uart.h"         
#include "led.h"          
#include <stdio.h>        
#include <string.h>
#include "bluetooth.h"

int phoneCharCount = 0;
char phoneBuffer[100];

char* receiveDataFromPhone() {
    int i;
    if(uart2_dataAvailable()) {
        char ch = uart2_getchar();
        if(ch == 'p' || ch == 'i' || ch == 'd') {
            uart0_put("PhoneBuffer: ");
            uart0_put(phoneBuffer);
            uart0_put("\r\n");
            phoneCharCount = 0;
            return phoneBuffer;
            //for(i = 0; i < phoneCharCount; i++) {
                //phoneBuffer[i] = 0;
            //}
            //phoneCharCount = 0;
        } else {
            if(phoneCharCount < 100) {
                phoneBuffer[phoneCharCount] = ch;
                phoneCharCount++;
            }
        }
    }
}

char getCharFromPhone() {
    char ch = uart2_getchar();
    return ch;
}
