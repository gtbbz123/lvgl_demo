#ifndef __FLASH_H
#define __FLASH_H
#include <stdint.h>
#define FLASH_USER_START_ADDR   0x080E0000  /* 选择Sector 10作为存储区 (128KB) */
#define FLASH_USER_END_ADDR     0x080FFFFF  /* Sector 10的结束地址 */
#define FLASH_USER_SECTOR       FLASH_Sector_10

/* 错误码定义 */
#define FLASH_OK         0
#define FLASH_ERROR      -1
#define FLASH_TIMEOUT    -2
#define FLASH_BAD_ADDR   -3




uint32_t Flash_GetSectorFromAddress(uint32_t address);
int Flash_init(void);
int Flash_EraseSector(uint32_t address);
int Flash_EraseUserSector(void);
int Flash_WriteHalfWord(uint32_t address, uint16_t data);
int Flash_WriteByte(uint32_t address, uint8_t data);
uint8_t Flash_ReadByte(uint32_t address);
void Flash_ReadBuffer8(uint32_t address, uint8_t *pData, uint32_t len);
int Flash_WriteBuffer8(uint32_t address, uint8_t *pData, uint32_t len);
#endif

