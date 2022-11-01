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
void LED1_On(void);
void LED1_Off(void);
void LED2_Off(void);
void LED2_Red(void);
void LED2_Green(void);
void LED2_Blue(void);
BOOLEAN LED1_State(void);
void LED2_On(int color);