#include <stdio.h>
#include <stdlib.h>
#include "msp.h"
#include "uart.h"
#include "led.h"
#include "switches.h"
#include "Timer32.h"
#include "CortexM.h"
#include "Common.h"
#include "ADC14.h"
#include "ControlPins.h"
#include "SysTickTimer.h"
#include "camera.h"
#include "oled.h"

extern BOOLEAN g_sendData;
extern double leftZerosPercent;
extern double rightZerosPercent;

uint16_t binaryCameraData[128];
uint16_t finalCameraData[128];
uint16_t edgeCameraData[128];

//static char str[100];
uint16_t deltaR;
uint16_t deltaL;
uint16_t center;

char string[100];

void INIT_Camera(void) {
    g_sendData = FALSE;
    ControlPin_SI_Init();
    ControlPin_CLK_Init();
    ADC0_InitSWTriggerCh6();
}

uint16_t fivePointAverage(uint16_t a, uint16_t b, uint16_t c, uint16_t d, uint16_t e) {
    return (a + b + c + d + e)/5;
}

//void smoothCameraData(uint16_t line[]) {
//    int i;
//    for(i = 2; i < 126; i++) {
//        smoothData[i] = fivePointAverage(line[i-2], line[i-1], line[i], line[i+1], line[i+2]);
//    }
//}

void binarizeCameraData(uint16_t line[], uint16_t threshold) {
    int i;
    for(i = 0; i < 128; i++) {
        if(line[i] > threshold) {
            binaryCameraData[i] = 16383;
        } else {
            binaryCameraData[i] = 0;
        }
    }
}

void setEdgesHigh(int leftEdge[], int rightEdge[]) {
    int i;
    edgeCameraData[leftEdge[1]] = LOW;
    edgeCameraData[leftEdge[2]] = LOW;
    edgeCameraData[rightEdge[1]] = LOW;
    edgeCameraData[rightEdge[2]] = LOW;
    
    if (leftEdge[0] != -1) {
        edgeCameraData[leftEdge[0]] = HIGH;
    }
    if (rightEdge[0] != -1) {
        edgeCameraData[rightEdge[0]] = HIGH;
    }
    for (i = TOLERANCE; i > -1; i--) {
        edgeCameraData[i] = OUT_OF_RANGE;
    }
    for (i = 128-TOLERANCE; i < 128; i++) {
        edgeCameraData[i] = OUT_OF_RANGE;
    }
}

int getLeftEdge(uint16_t line[]) {
    int i;
    led2_on(BLUE);
    for (i = TOLERANCE; i < 128; i++) {
        if (line[i]-line[i-1] == LEFT_EDGE) {
            return i;
        }
    }
    return -1;
}

int getRightEdge(uint16_t line[]) {
    int i;
    led2_on(GREEN);
    for (i = 128-TOLERANCE; i > -1; i--) {
        if (line[i]-line[i-1] == RIGHT_EDGE) {
            return i;
        }
    }
    return -1;
}

int calculatePosition(int leftEdge, int rightEdge) {
    int position = -1;
    if (leftEdge != -1) {
        position = 64-leftEdge+TOLERANCE;
    } else if (rightEdge != -1) {
        led2_on(BLUE);
        position = 128-(rightEdge-64)-TOLERANCE;
    }
    return position;
}

BOOLEAN detect_carpet(uint16_t line[]) {
    int i;
    int countZeros = 0;
    for(i = 32; i < 97; i++) {
        if(line[i] == 0) {
            countZeros++;
        }
    }
    if (countZeros > 64) {
        return TRUE;
    } else {
        return FALSE;
    }
}
