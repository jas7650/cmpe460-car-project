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
#include <stdint.h>
#include <stdio.h>

#define TOLERANCE 20
#define THRESHOLD 8000
#define HIGH 16383
#define LOW 0
#define OUT_OF_RANGE 16383/2

void INIT_Camera(void);
uint16_t fivePointAverage(uint16_t a, uint16_t b, uint16_t c, uint16_t d, uint16_t e);
void smoothCameraData(uint16_t line[]);
void binarizeCameraData(uint16_t line[], uint16_t threshold);
int calc_right_edge(uint16_t line[]);
int calc_left_edge(uint16_t line[]);
BOOLEAN detect_carpet(uint16_t line[]);
void setEdgesHigh(int leftEdge[], int rightEdge[], uint16_t line[]);
