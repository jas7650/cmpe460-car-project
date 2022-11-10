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
#include <math.h>
#include "motors.h"

extern BOOLEAN g_sendData;
extern double leftZerosPercent;
extern double rightZerosPercent;

extern uint16_t line_data[128];
uint16_t binary_data[128];
uint16_t smooth_data[128];
uint16_t edge_data[128];
uint16_t center_data[128];

//static char str[100];
uint16_t deltaR;
uint16_t deltaL;

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

void smoothCameraData() {
    int i;
    for(i = 2; i < 126; i++) {
        smooth_data[i] = fivePointAverage(line_data[i-2], line_data[i-1], line_data[i], line_data[i+1], line_data[i+2]);
    }
}

void binarizeCameraData(uint16_t threshold) {
    int i;
    for(i = 0; i < 128; i++) {
        if(smooth_data[i] > threshold) {
            binary_data[i] = 16383;
        } else {
            binary_data[i] = 0;
        }
    }
}

double calcCenterMass(void) {
    int x = 0;
    int y = 0;
    int i;
    double d_center;
    for (i = TOLERANCE; i < 128-TOLERANCE; i++) {
        x += binary_data[i];
        y += (i+OFFSET)*binary_data[i];
    }
    d_center = ((double)y/(double)x);
    d_center = -1*(((d_center/(128-(2*TOLERANCE)))*120)-TOLERANCE-60);
    if (abs((int)(d_center+0.5)) < 4) {
        return 0;
    }
    return d_center;
}

void updateCenterData(double center_d, double prevCenter_d) {
    center_data[(int)floor(prevCenter_d)] = LOW;
    center_data[(int)floor(center_d)] = HIGH;
}

void setEdgesHigh(int leftEdge[], int rightEdge[]) {
    int i;
    edge_data[leftEdge[1]] = LOW;
    edge_data[leftEdge[2]] = LOW;
    edge_data[rightEdge[1]] = LOW;
    edge_data[rightEdge[2]] = LOW;
    
    if (leftEdge[0] != -1) {
        edge_data[leftEdge[0]] = HIGH;
    }
    if (rightEdge[0] != -1) {
        edge_data[rightEdge[0]] = HIGH;
    }
    for (i = TOLERANCE; i > -1; i--) {
        edge_data[i] = OUT_OF_RANGE;
    }
    for (i = 128-TOLERANCE; i < 128; i++) {
        edge_data[i] = OUT_OF_RANGE;
    }
}

int getLeftEdge(void) {
    int i;
    led2_on(BLUE);
    for (i = TOLERANCE; i < 128; i++) {
        if (binary_data[i]-binary_data[i-1] == LEFT_EDGE) {
            return i;
        }
    }
    return -1;
}

int getRightEdge(void) {
    int i;
    led2_on(GREEN);
    for (i = 128-TOLERANCE; i > -1; i--) {
        if (binary_data[i]-binary_data[i-1] == RIGHT_EDGE) {
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

BOOLEAN detect_carpet(void) {
    int i;
    int countZeros = 0;
    for(i = 32; i < 97; i++) {
        if(binary_data[i] == 0) {
            countZeros++;
        }
    }
    if (countZeros > 64) {
        return TRUE;
    } else {
        return FALSE;
    }
}
