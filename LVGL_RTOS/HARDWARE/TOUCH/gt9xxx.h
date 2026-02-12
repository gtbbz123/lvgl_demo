/**
 ****************************************************************************************************
 * @file        gt9xxx.h
 * @version     V1.0
 * @brief       电容触摸屏-GT9xxx 驱动代码
 * @note        GT系列电容触摸屏IC通用驱动,本代码支持: GT9147/GT917S/GT968/GT1151/GT9271 等多种
 *              驱动IC
 *
 ****************************************************************************************************
 * @attention   Waiken-Smart 慧勤智远
 *
 * 实验平台:    STM32F103ZET6小系统板
 *
 ****************************************************************************************************
 */	

#ifndef __GT9XXX_H
#define __GT9XXX_H

#include <stdint.h>


/******************************************************************************************/
/* GT9XXX INT 和 RST 引脚 定义 */

#define GT9XXX_RST_GPIO_PORT            GPIOG
#define GT9XXX_RST_GPIO_PIN             GPIO_Pin_3
#define GT9XXX_RST_GPIO_CLK_ENABLE()    do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE); }while(0)   /* PG口时钟使能 */

#define GT9XXX_INT_GPIO_PORT            GPIOG
#define GT9XXX_INT_GPIO_PIN             GPIO_Pin_4
#define GT9XXX_INT_GPIO_CLK_ENABLE()    do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE); }while(0)   /* PG口时钟使能 */

/******************************************************************************************/

/* 与电容触摸屏连接的芯片引脚(未包含IIC引脚) 
 * IO操作函数 
 */
#define GT9XXX_RST(x)     do{ x ? \
															GPIO_SetBits(GT9XXX_RST_GPIO_PORT,GT9XXX_RST_GPIO_PIN):\
                              GPIO_ResetBits(GT9XXX_RST_GPIO_PORT,GT9XXX_RST_GPIO_PIN);\
                          }while(0)       /* 复位引脚 */


#define GT9XXX_INT        GPIO_ReadOutputDataBit(GT9XXX_INT_GPIO_PORT, GT9XXX_INT_GPIO_PIN)    /* 读取做的引脚 */

/* IIC读写命令 */
#define GT9XXX_CMD_WR       0X28        /* 写命令 */
#define GT9XXX_CMD_RD       0X29        /* 读命令 */

/* GT9XXX 部分寄存器定义  */
#define GT9XXX_CTRL_REG     0X8040      /* GT9XXX控制寄存器 */
#define GT9XXX_CFGS_REG     0X8047      /* GT9XXX配置起始地址寄存器 */
#define GT9XXX_CHECK_REG    0X80FF      /* GT9XXX校验和寄存器 */
#define GT9XXX_PID_REG      0X8140      /* GT9XXX产品ID寄存器 */

#define GT9XXX_GSTID_REG    0X814E      /* GT9XXX当前检测到的触摸情况 */
#define GT9XXX_TP1_REG      0X8150      /* 第一个触摸点数据地址 */
#define GT9XXX_TP2_REG      0X8158      /* 第二个触摸点数据地址 */
#define GT9XXX_TP3_REG      0X8160      /* 第三个触摸点数据地址 */
#define GT9XXX_TP4_REG      0X8168      /* 第四个触摸点数据地址 */
#define GT9XXX_TP5_REG      0X8170      /* 第五个触摸点数据地址 */
#define GT9XXX_TP6_REG      0X8178      /* 第六个触摸点数据地址 */
#define GT9XXX_TP7_REG      0X8180      /* 第七个触摸点数据地址 */
#define GT9XXX_TP8_REG      0X8188      /* 第八个触摸点数据地址 */
#define GT9XXX_TP9_REG      0X8190      /* 第九个触摸点数据地址 */
#define GT9XXX_TP10_REG     0X8198      /* 第十个触摸点数据地址 */
 

/******************************************************************************************/
/* 函数声明 */

uint8_t gt9xxx_wr_reg(uint16_t reg,uint8_t *buf,uint8_t len);   /* 向gt9xx写入数据 */
void gt9xxx_rd_reg(uint16_t reg,uint8_t *buf,uint8_t len);      /* 从gt9xx读取数据 */
uint8_t gt9xxx_init(void);                                      /* 初始化gt9xxx触摸屏 */
uint8_t gt9xxx_scan(uint8_t mode);                              /* 扫描触摸屏 */

#endif













