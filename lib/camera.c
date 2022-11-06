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

void smoothCameraData(uint16_t line[]) {
    int i;
    for(i = 2; i < 126; i++) {
        line[i] = fivePointAverage(line[i-2], line[i-1], line[i], line[i+1], line[i+2]);
    }
}

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

void setEdgesHigh(int leftEdge[], int rightEdge[], uint16_t line[]) {
    edgeCameraData[leftEdge[1]] = 0;
    edgeCameraData[leftEdge[2]] = 0;
    edgeCameraData[rightEdge[1]] = 0;
    edgeCameraData[rightEdge[2]] = 0;
    
    if (leftEdge[0] != -1) {
        edgeCameraData[leftEdge[0]] = 16383;
    }
    if (rightEdge[0] != -1) {
        edgeCameraData[rightEdge[0]] = 16383;
    }
}

int calc_right_edge(uint16_t line[]) {
    int i;
    for(i = 128-TOLERANCE; i > 0; i--) {
        if(line[i+1] == LOW && line[i] == HIGH && line[i-1] == HIGH) {
            return i;
        }
    }
    return -1;
}

int calc_left_edge(uint16_t line[]) {
    int i;
    for(i = TOLERANCE; i < 128; i++) {
        if(line[i-1] == LOW && line[i] == HIGH && line[i+1] == HIGH) {
            return i;
        }
    }
    return -1;
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
