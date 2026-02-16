#include "spi.h"
#include "uart.h"

//#define DEBUG_SPI
#ifdef DEBUG_SPI
#define  SPI_DEBUG(x) UART_printf x
#else  
#define SPI_DEBUG(x)
#endif
void spi2_init(void){
	SPI_InitTypeDef SPI_InitStructure;
	SPI_StructInit(&SPI_InitStructure);
	
	SPI2_SPI_CLK_ENABLE();

	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;

	GPIO_InitTypeDef GPIO_InitStructure;

	SPI2_SCK_GPIO_CLK_ENABLE();
	SPI2_MISO_GPIO_CLK_ENABLE();
	SPI2_MOSI_GPIO_CLK_ENABLE();

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = SPI2_SCK_GPIO_PIN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI2_SCK_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SPI2_MOSI_GPIO_PIN;
	GPIO_Init(SPI2_MOSI_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SPI2_MISO_GPIO_PIN;
	GPIO_Init(SPI2_MISO_GPIO_PORT, &GPIO_InitStructure);

	GPIO_PinAFConfig(SPI2_SCK_GPIO_PORT, SPI2_SCK_GPIO_PIN_SOUTCE, GPIO_AF_SPI2);
	GPIO_PinAFConfig(SPI2_MOSI_GPIO_PORT, SPI2_MOSI_GPIO_PIN_SOUTCE, GPIO_AF_SPI2);
	GPIO_PinAFConfig(SPI2_MISO_GPIO_PORT, SPI2_MISO_GPIO_PIN_SOUTCE, GPIO_AF_SPI2);

	SPI_Init(SPI2, &SPI_InitStructure);
	
	SPI_Cmd(SPI2, ENABLE);

	spi2_read_write_byte(0Xff);
}
void spi2_set_speed(uint8_t speed){
	SPI_Cmd(SPI2, DISABLE);
	SPI2->CR1 &= 0XFFC7;
	SPI2->CR1 |= speed << 3;
	SPI_Cmd(SPI2, ENABLE);
}
uint8_t spi2_read_write_byte(uint8_t txdata){
	uint8_t ans;
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI2, txdata);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	ans = SPI_I2S_ReceiveData(SPI2);
	SPI_DEBUG(("spi2_read_write_byte = 0x%x\n", ans));
	return ans;
}



