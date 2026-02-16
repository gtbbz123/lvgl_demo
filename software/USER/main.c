#include "led.h"
#include "delay.h"
#include "uart.h"
#include "lcd.h"
#include "sdio_sdcard.h"
#include "ff.h"
#include "FREERTOS.H"
#include "task.h"
#include "vs1053.h"
#include "spi.h"
//跑马灯实验 -库函数版本
//STM32F4工程-库函数版本
//https://shop58085959.taobao.com		
RCC_ClocksTypeDef rcc_clocks;



static void task1(void * args){
	while(1){
	GPIO_ResetBits(GPIOF,GPIO_Pin_9);  //LED0对应引脚GPIOF.9拉低，亮  等同D1=0;
	GPIO_SetBits(GPIOF,GPIO_Pin_10);   //LED1对应引脚GPIOF.10拉高，灭 等同D2=1;
	vTaskDelay(500);  		   //延时300ms
	GPIO_SetBits(GPIOF,GPIO_Pin_9);	   //LED0对应引脚GPIOF.0拉高，灭  等同D1=1;
	GPIO_ResetBits(GPIOF,GPIO_Pin_10); //LED1对应引脚GPIOF.10拉低，亮 等同D2=0;
	vTaskDelay(500); 
	}
}
TaskHandle_t task2Handler;

static void task2(void * args){
		vs10xx_reset();
		vs10xx_soft_reset();
		while(1){
		audio_play_song("0:llh.mp3");
		//spi2_read_write_byte(0x35);

//			UART_printf("DQ = %d\n",PCin(5));
//		vTaskDelay(1000);
//		VS10XX_RST(1);
//		VS10XX_XCS(1);
//		VS10XX_XDCS(1);
//		vTaskDelay(1000);
//		VS10XX_RST(0);
//		VS10XX_XCS(0);
//		VS10XX_XDCS(0);
	}
}
TaskHandle_t task1Handler;
void test(void);
int main(void)
{ 
	
	delay_init();		  //初始化延时函数
	LED_Init();		        //初始化LED端口
	UART_Init();
	vs10xx_init();
	test();
	xTaskCreate(task1,"task1",128,NULL,1,&task1Handler);
	xTaskCreate(task2,"task2",128,NULL,1,&task2Handler);
	vTaskStartScheduler();

}
u8 buf[512];
u8 rec[512];

FATFS FILE;
char path[64] = "0:abc.txt";
u8 work[4096];
void test(void){
//	SD_Error state;
//	state = SD_Init();
//	buf[0] = 123;
//	buf[1] = 234;
//	SD_WriteDisk(buf, 0, 1);
//	SD_ReadDisk(rec, 0, 1);
//	UART_printf("state = %d\n", state);
//	UART_printf("rec0 = %d\n", rec[0]);
//	UART_printf("rec1 = %d\n", rec[1]);
	FRESULT res;
	res = f_mount(&FILE, "0:", 1);
	UART_printf("f_mount res = %d\n", res);
	if(res != 0)
	f_mkfs("0:", NULL, work, FF_MAX_SS);
}


