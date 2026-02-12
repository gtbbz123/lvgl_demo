#include "uart.h"
#include "stm32f4xx_usart.h"
#include <string.h>
#include <stdio.h>
#define UART_GPIO_TX GPIOA
#define UART_GPIO_RX GPIOA

#define UART_PIN_TX GPIO_Pin_9
#define UART_PIN_RX GPIO_Pin_10

#define UART_GPIO_APB  RCC_AHB1Periph_GPIOA
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
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_AHB1PeriphClockCmd(UART_GPIO_APB, ENABLE);
		RCC_APB2PeriphClockCmd(UART_APB, ENABLE);
		
		USART_StructInit(&USART_InitStructure);

		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
		GPIO_InitStruct.GPIO_Pin=UART_PIN_TX; 
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(UART_GPIO_TX, &GPIO_InitStruct);

		GPIO_PinAFConfig(UART_GPIO_TX, GPIO_PinSource9, GPIO_AF_USART1);

		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
		GPIO_InitStruct.GPIO_Pin=UART_PIN_RX;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(UART_GPIO_RX, &GPIO_InitStruct);

		GPIO_PinAFConfig(UART_GPIO_RX, GPIO_PinSource10, GPIO_AF_USART1);
		USART_DeInit(UART_NUM); 
		USART_InitStructure.USART_BaudRate=115200;
		USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
		USART_InitStructure.USART_Parity=USART_Parity_No;
		USART_InitStructure.USART_StopBits=USART_StopBits_1;
		USART_InitStructure.USART_WordLength=USART_WordLength_8b;
		USART_Init(UART_NUM, &USART_InitStructure);
		

		NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
		NVIC_Init(&NVIC_InitStructure);

		USART_ITConfig(UART_NUM, USART_IT_RXNE, ENABLE);

		USART_Cmd(UART_NUM, ENABLE);

}
void UART_Send(uint8_t *str, uint16_t size){
			uint16_t i;
			for(i = 0;i < size; i++){
			USART_SendData(UART_NUM, str[i]);
			while(!USART_GetFlagStatus(UART_NUM, USART_FLAG_TXE));
			}
}
void UART_printf(const char* format, ...){
		uint32_t size;
		va_list args;
		va_start(args,format);
		size = vsnprintf((char *)uart_send_buf.buf, MAX_SEND, format, args);
		va_end(args);
		if(size == MAX_SEND - 1){
			UART_DEBUG(("UART SEND FULL!!!\n"));
			return ;
		}
		uart_send_buf.size = size;
		UART_Send(uart_send_buf.buf,uart_send_buf.size);
}
void UART_GetRecv(uint8_t *buf){
	memcpy(buf, uart_recv_buf.buf, MAX_RECV);
	uart_recv_buf.size = 0;
}

void USART1_IRQHandler(void){
	if(USART_GetITStatus(UART_NUM, USART_IT_RXNE) == 1){
			if(uart_recv_buf.size == MAX_RECV - 1){
					UART_DEBUG(("UART RECV FULL!!!\n"));
					return ;
			}
			uart_recv_buf.buf[uart_recv_buf.size] = USART_ReceiveData(UART_NUM);
			uart_recv_buf.size++;
			uart_recv_buf.buf[uart_recv_buf.size] = '\0';
	}
}
