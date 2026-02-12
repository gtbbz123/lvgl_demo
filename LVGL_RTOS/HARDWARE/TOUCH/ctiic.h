/**
 ****************************************************************************************************
 * @file        ctiic.h
 * @version     V1.0
 * @brief       电容触摸屏驱动-IIC通信部分 驱动代码
 ****************************************************************************************************
 * @attention   Waiken-Smart 慧勤智远
 *
 * 实验平台:    STM32F103ZET6小系统板
 *
 ****************************************************************************************************
 */

#ifndef __CT_IIC_H
#define __CT_IIC_H

#include <stdint.h>


/******************************************************************************************/
/* CT_IIC 引脚 定义 */

#define CT_IIC_SCL_GPIO_PORT            GPIOG
#define CT_IIC_SCL_GPIO_PIN             GPIO_Pin_2
#define CT_IIC_SCL_GPIO_CLK_ENABLE()    do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE); }while(0)   /* PG口时钟使能 */

#define CT_IIC_SDA_GPIO_PORT            GPIOG
#define CT_IIC_SDA_GPIO_PIN             GPIO_Pin_5
#define CT_IIC_SDA_GPIO_CLK_ENABLE()    do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE); }while(0)   /* PG口时钟使能 */

/******************************************************************************************/

/* IO操作 */
#define CT_IIC_SCL(x)     do{ x ? \
															GPIO_SetBits(CT_IIC_SCL_GPIO_PORT, CT_IIC_SCL_GPIO_PIN):\
                              GPIO_ResetBits(CT_IIC_SCL_GPIO_PORT, CT_IIC_SCL_GPIO_PIN); \
                          }while(0)       /* SCL */

#define CT_IIC_SDA(x)     do{ x ? \
																GPIO_SetBits(CT_IIC_SDA_GPIO_PORT, CT_IIC_SDA_GPIO_PIN):	\
                              GPIO_ResetBits(CT_IIC_SDA_GPIO_PORT, CT_IIC_SDA_GPIO_PIN); \
                          }while(0)       /* SDA */

#define CT_READ_SDA       GPIO_ReadInputDataBit(CT_IIC_SDA_GPIO_PORT, CT_IIC_SDA_GPIO_PIN) /* 读取SDA */


/* IIC所有操作函数 */
void ct_iic_init(void);             /* 初始化IIC的IO口 */
void ct_iic_stop(void);             /* 发送IIC停止信号 */
void ct_iic_start(void);            /* 发送IIC开始信号 */

void ct_iic_ack(void);              /* IIC发送ACK信号 */
void ct_iic_nack(void);             /* IIC不发送ACK信号 */
uint8_t ct_iic_wait_ack(void);      /* IIC等待ACK信号 */

void ct_iic_send_byte(uint8_t txd);         /* IIC发送一个字节 */
uint8_t ct_iic_read_byte(unsigned char ack);/* IIC读取一个字节 */

#endif







