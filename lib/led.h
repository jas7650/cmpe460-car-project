#include "msp.h" 
#include "Common.h"

#define RED 0
#define GREEN 1
#define BLUE 2
#define CYAN 3
#define MAGENTA 4
#define YELLOW 5
#define WHITE 6

void LED1_Init(void);
void LED2_Init(void);
void led1_on(void);
void led1_off(void);
BOOLEAN led1_state(void);
void led2_on(int color);
void led2_off(void);
