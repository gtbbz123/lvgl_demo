#include "led.h"
#include "delay.h"
#include "uart.h"
//跑马灯实验 -库函数版本
//STM32F4工程-库函数版本
//https://shop58085959.taobao.com		
RCC_ClocksTypeDef rcc_clocks;

void test(void);
int main(void)
{ 
	
	delay_init();		  //初始化延时函数
	LED_Init();		        //初始化LED端口
	UART_Init();
//	RCC_GetClocksFreq(&rcc_clocks);

//	UART_printf("SYSCLKL:%ld\n", rcc_clocks.SYSCLK_Frequency);
//	UART_printf("PCLK1_Frequency:%ld\n", rcc_clocks.PCLK1_Frequency);
//	UART_printf("PCLK2_Frequency:%ld\n", rcc_clocks.PCLK2_Frequency);
//	UART_printf("HCLK_Frequency:%ld\n", rcc_clocks.HCLK_Frequency);
	while(1)
	{
	test();
	GPIO_ResetBits(GPIOF,GPIO_Pin_9);  //LED0对应引脚GPIOF.9拉低，亮  等同D1=0;
	GPIO_SetBits(GPIOF,GPIO_Pin_10);   //LED1对应引脚GPIOF.10拉高，灭 等同D2=1;
	delay_ms(500);  		   //延时300ms
	GPIO_SetBits(GPIOF,GPIO_Pin_9);	   //LED0对应引脚GPIOF.0拉高，灭  等同D1=1;
	GPIO_ResetBits(GPIOF,GPIO_Pin_10); //LED1对应引脚GPIOF.10拉低，亮 等同D2=0;
	delay_ms(500);                     //延时300ms
	}
}

void test(void){
		uint8_t buf[256];
		UART_GetRecv(buf); 
		UART_printf((char *)buf);
		UART_printf("\n");
}


