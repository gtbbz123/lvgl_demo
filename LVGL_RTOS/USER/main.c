#include"stm32f10x.h"
#include "led.h"
#include "lcd.h"
#include "touch.h"
#include "timer.h"
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "FreeRTOSConfig.h"
#include <stdint.h>
#include "delay.h"
#include "uart.h"
#include "task.h"
#include "my_gui.h"

TaskHandle_t task1Handler;
TaskHandle_t task2Handler;

static void task1(void *arg)
{
	while(1)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		vTaskDelay(500);
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		vTaskDelay(500);
	}
}

static void task2(void *arg)
{
	while(1)
	{
		lv_task_handler();
		vTaskDelay(5);
	}
}

int main(void){
		LED_Init();
		UART_Init();
		delay_init();
		//TIM2_Init(1000 - 1, 72 - 1);// 0.1ms * 10=1ms´¥·¢
	  delay_ms(2000);
	  UART_printf("START!!\n");
		lv_init();
		lv_port_disp_init();
		lv_port_indev_init();
		my_gui();
//		lv_obj_t * switch_obj = lv_switch_create(lv_scr_act());
//		lv_obj_set_size(switch_obj,40,20);
//		lv_obj_align(switch_obj, LV_ALIGN_CENTER,0,0);
		xTaskCreate(task1,"task1",512,NULL,2,&task1Handler);
		xTaskCreate(task2,"task2",512,NULL,2,&task2Handler);
		vTaskStartScheduler();
	
	//tp_init();
	//lcd_init();
		while(1){
			//lv_task_handler();
			
			
			
			//tp_dev.scan(0);	    
			//lcd_show_num(100, 100, tp_dev.x[0], 4, 12, BLACK);
			//lcd_show_num(100, 120, tp_dev.y[0], 4, 12, BLACK); 
			//lcd_show_num(120, 120, 114514, 6, 12, BLACK); 
//			UART_printf("CC\n");
//			LED0(0);
//			LED1(1);
//			delay_ms(1000);
//			LED0(1);
//			LED1(0);
//			delay_ms(1000);
		}
}

