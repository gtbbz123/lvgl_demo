#include "led.h"
#include "stm32f10x.h"
void LED_Init(void){

		GPIO_InitTypeDef gpio_init_struct;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		gpio_init_struct.GPIO_Mode = GPIO_Mode_Out_PP;
		gpio_init_struct.GPIO_Pin = GPIO_Pin_1;
		gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &gpio_init_struct);     

		gpio_init_struct.GPIO_Pin = GPIO_Pin_2;
		GPIO_Init(GPIOA, &gpio_init_struct);  	
		
}

