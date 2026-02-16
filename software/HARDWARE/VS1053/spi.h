#ifndef __SPI_H
#define __SPI_H

#include "sys.h"


#define SPI2_SCK_GPIO_PORT              GPIOB
#define SPI2_SCK_GPIO_PIN               GPIO_Pin_10
#define SPI2_SCK_GPIO_CLK_ENABLE()      do{ RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);}while(0)   /* PB口时钟使能 */
#define SPI2_SCK_GPIO_PIN_SOUTCE        GPIO_PinSource10


#define SPI2_MISO_GPIO_PORT             GPIOC
#define SPI2_MISO_GPIO_PIN              GPIO_Pin_2
#define SPI2_MISO_GPIO_CLK_ENABLE()     do{ RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);}while(0)   /* PB口时钟使能 */
#define SPI2_MISO_GPIO_PIN_SOUTCE       GPIO_PinSource2

#define SPI2_MOSI_GPIO_PORT             GPIOC
#define SPI2_MOSI_GPIO_PIN              GPIO_Pin_3
#define SPI2_MOSI_GPIO_CLK_ENABLE()     do{ RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); }while(0)   /* PB口时钟使能 */
#define SPI2_MOSI_GPIO_PIN_SOUTCE       GPIO_PinSource3

/* SPI2相关定义 */
#define SPI2_SPI                        SPI2
#define SPI2_SPI_CLK_ENABLE()           do{ RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE); }while(0)    /* SPI2时钟使能 */


/* SPI总线速度设置 */
#define SPI_SPEED_2         0
#define SPI_SPEED_4         1
#define SPI_SPEED_8         2
#define SPI_SPEED_16        3
#define SPI_SPEED_32        4
#define SPI_SPEED_64        5
#define SPI_SPEED_128       6
#define SPI_SPEED_256       7


void spi2_init(void);
void spi2_set_speed(uint8_t speed);
uint8_t spi2_read_write_byte(uint8_t txdata);

#endif

