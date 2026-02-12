#include "delay.h"
#include "stm32f4xx.h"
#include "uart.h"



#define DEBUG_DELAY
#ifdef DEBUG_DELAY
#define DELAY_DEBUG(x) UART_printf x;
#else
#define DELAY_DEBUG(x)
#endif
static volatile uint8_t flag = 0;
static void TIM3_Init(void);
void delay_init(void){
	TIM3_Init();
}
static void TIM3_Init(void){
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeDefStructure;
		NVIC_InitTypeDef NVIC_InitStrue;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		TIM_TimeBaseInitTypeDefStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitTypeDefStructure.TIM_CounterMode = TIM_CounterMode_Down;
		TIM_TimeBaseInitTypeDefStructure.TIM_Period = 0xFFFF;
		TIM_TimeBaseInitTypeDefStructure.TIM_Prescaler = 84 - 1; //1us
		
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitTypeDefStructure);
		
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
		
		NVIC_InitStrue.NVIC_IRQChannel=TIM3_IRQn;
		NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=0;
		NVIC_InitStrue.NVIC_IRQChannelSubPriority=0;
		NVIC_Init(&NVIC_InitStrue);
}

void TIM3_IRQHandler(void){
	if(TIM_GetITStatus(TIM3, TIM_IT_Update )!= RESET){
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		TIM_Cmd(TIM3, DISABLE);
		flag = 0;
	}
}
void delay_us( uint32_t n){
	if(n == 0)
		return;
	TIM_SetCounter(TIM3,n - 1);
	flag = 1;
	TIM_Cmd(TIM3, ENABLE);
	do{
		__NOP();
	}while(flag);
}
void delay_ms( uint32_t n){
	while(n--){
		delay_us(1000);
	}
}

