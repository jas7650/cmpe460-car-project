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

extern uint16_t line[128];
extern BOOLEAN g_sendData;
extern double leftZerosPercent;
extern double rightZerosPercent;

uint16_t binaryCameraData[128];
uint16_t finalCameraData[128];

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

void smoothCameraData(void) {
    int i;
    for(i = 2; i < 126; i++) {
        line[i] = fivePointAverage(line[i-2], line[i-1], line[i], line[i+1], line[i+2]);
    }
}

void binarizeCameraData(uint16_t threshold) {
    int i;
    for(i = 0; i < 128; i++) {
        if(line[i] > threshold) {
            binaryCameraData[i] = 16383;
        } else {
            binaryCameraData[i] = 0;
        }
    }
}

void center_camera_data(int shiftVal) {
    int i;
    for(i = 0; i < 128; i++) {
        if(i < shiftVal) {
            finalCameraData[i] = 0;
        }else {
            finalCameraData[i] = binaryCameraData[i - shiftVal];
        }
    }
}

void calc_delta_right(uint16_t line[]) {
    int i;
    int countZeros = 0;
    for(i = 64; i < 128; i++) {
        if(line[i] == 0) {
            countZeros++;
        }
    }
    rightZerosPercent = countZeros/64.0;
}

void calc_delta_left(uint16_t line[]) {
    int i;
    int countZeros = 0;
    for(i = 0; i < 64; i++) {
        if(line[i] == 0) {
            countZeros++;
        }
    }
    leftZerosPercent = countZeros/64.0;
}

int calc_right_zeros(uint16_t line[]) {
    int i;
    int rightZeros = 0;
    for(i = 64; i < 128-TOLERANCE; i++) {
        if(line[i] == 0) {
            rightZeros++;
        }
    }
    return rightZeros;
}

int calc_left_zeros(uint16_t line[]) {
    int i;
    int leftZeros = 0;
    for(i = TOLERANCE; i < 64; i++) {
        if(line[i] == 0) {
            leftZeros++;
        }
    }
    return leftZeros;
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
