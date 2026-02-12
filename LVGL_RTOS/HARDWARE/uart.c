#include "uart.h"
#include "stm32f10x_usart.h"
#include <string.h>
#include <stdio.h>
#define UART_GPIO_TX GPIOA
#define UART_GPIO_RX GPIOA

#define UART_PIN_TX GPIO_Pin_9
#define UART_PIN_RX GPIO_Pin_10

#define UART_GPIO_APB  RCC_APB2Periph_GPIOA
#define UART_APB  RCC_APB2Periph_USART1
#define UART_NUM  USART1

#define MAX_RECV 256
#define MAX_SEND 256

static uart_buf_t uart_recv_buf;
static uart_buf_t uart_send_buf;

//#define DEBUG_UART
#ifdef DEBUG_UART
#define UART_DEBUG(x) UART_printf x 
#else
#define UART_DEBUG(x)
#endif
void UART_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct ;
		USART_InitTypeDef USART_InitStruect;
	
		RCC_APB2PeriphClockCmd(UART_GPIO_APB, ENABLE);
		RCC_APB2PeriphClockCmd(UART_APB, ENABLE);
		
	
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Pin=UART_PIN_TX; 
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
		GPIO_Init(UART_GPIO_TX, &GPIO_InitStruct);
	
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_InitStruct.GPIO_Pin=UART_PIN_RX;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
		GPIO_Init(UART_GPIO_RX, &GPIO_InitStruct);
		
		USART_DeInit(UART_NUM); 
		USART_InitStruect.USART_BaudRate=115200;
		USART_InitStruect.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
		USART_InitStruect.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
		USART_InitStruect.USART_Parity=USART_Parity_No;
		USART_InitStruect.USART_StopBits=USART_StopBits_1;
		USART_InitStruect.USART_WordLength=USART_WordLength_8b;
		USART_Init(UART_NUM, &USART_InitStruect);
		
		USART_Cmd(UART_NUM, ENABLE);
}
void UART_Send(char *str, uint16_t size){
			if(size + uart_recv_buf.size > MAX_RECV){
				UART_DEBUG(("UART RECV FULL!!!\n"));
				return ;
			}
			memcpy(uart_recv_buf.buf + uart_recv_buf.size,str,size);
			uart_recv_buf.size += size;
			//
			uint16_t i;
			for(i = 0;i < uart_recv_buf.size; i++){
			USART_SendData(UART_NUM, uart_recv_buf.buf[i]);
			while(!USART_GetFlagStatus(UART_NUM, USART_FLAG_TXE));
			}
			uart_recv_buf.size = 0;
}
void UART_printf(const char* format, ...){
		va_list args;
		va_start(args,format);
		vsprintf(uart_send_buf.buf, format, args);
		uart_send_buf.size = strlen(uart_send_buf.buf);
		va_end(args);
		UART_Send(uart_send_buf.buf,uart_send_buf.size);
}
