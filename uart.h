#include "msp.h"
#include "Common.h"

void uart0_init();
BYTE uart0_getchar();
void uart0_putchar(char ch);
void uart0_put(char *ptr_str);
BOOLEAN uart0_dataAvailable();

void uart2_init();
BYTE uart2_getchar();
void uart2_putchar(char ch);
void uart2_put(char *ptr_str);
BOOLEAN uart2_dataAvailable();