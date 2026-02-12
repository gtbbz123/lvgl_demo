#include "timer.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "lvgl.h"
#include "led.h"
#include "uart.h"
#define LED0(x)   do{ x ? \
                      GPIO_SetBits(GPIOA, GPIO_Pin_1) : \
                      GPIO_ResetBits(GPIOA, GPIO_Pin_1); \
                  }while(0)      /* LED0·­×ª */
#define LED1(x)   do{ x ? \
                      GPIO_SetBits(GPIOA, GPIO_Pin_2) : \
                      GPIO_ResetBits(GPIOA, GPIO_Pin_2); \
                  }while(0)      /* LED0·­×ª */

									
								


void TIM2_Init(uint16_t arr, uint16_t psc){
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitTypeDefStructure;
		NVIC_InitTypeDef NVIC_InitStrue;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		TIM_TimeBaseInitTypeDefStructure.TIM_ClockDivision = TIM_CounterMode_Up;
		TIM_TimeBaseInitTypeDefStructure.TIM_CounterMode = TIM_CKD_DIV1;
		TIM_TimeBaseInitTypeDefStructure.TIM_Period = arr;
		TIM_TimeBaseInitTypeDefStructure.TIM_Prescaler = psc;
		
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitTypeDefStructure);
		
		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
		
		NVIC_InitStrue.NVIC_IRQChannel=TIM2_IRQn;
		NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=0;
		NVIC_InitStrue.NVIC_IRQChannelSubPriority=0;
		NVIC_Init(&NVIC_InitStrue);

		TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(){
	if(TIM_GetITStatus(TIM2, TIM_IT_Update )!= RESET){
#if 1
		static int i = 0;
		//lv_tick_inc(1);
		i++;
		#if 0
		if(i >=1000){
			i = 0;
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)){
				LED0(0);
		}
		else{
			LED0(1);
		}
		}
#endif
		#else
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)){
				LED0(0);
		}
		else{
			LED0(1);
		}
		#endif
				TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

