#ifndef __UART_H__
#define __UART_H__
#include <stdint.h>
#include <stdarg.h>

#define MAX_RECV 256
typedef struct{
	uint16_t size;
	char buf[MAX_RECV];
}uart_buf_t;

void UART_Init(void);
void UART_Send(char *str, uint16_t size);
void UART_printf(const char* format, ...);
#endif

