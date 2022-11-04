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

void INIT_Camera(void);
uint16_t fivePointAverage(uint16_t a, uint16_t b, uint16_t c, uint16_t d, uint16_t e);
void smoothCameraData(void);
void binarizeCameraData(uint16_t threshold);
void center_camera_data(int shiftVal);
int calc_delta_right(uint16_t line[]);
int calc_delta_left(uint16_t line[]);