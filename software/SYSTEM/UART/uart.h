#ifndef __UART_H__
#define __UART_H__
#include <stdint.h>
#include <stdarg.h>

#define MAX_RECV 256
typedef struct{
	uint16_t size;
	uint8_t buf[MAX_RECV];
}uart_buf_t;

void UART_Init(void);
void UART_Send(uint8_t *str, uint16_t size);
void UART_GetRecv(uint8_t *buf);
void UART_printf(const char* format, ...);
#endif

