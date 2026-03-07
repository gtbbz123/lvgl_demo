#include "flash.h"
#include "stm32f4xx.h"

static FLASH_Status g_lastFlashStatus = FLASH_COMPLETE;
int Flash_init(void){
	FLASH_Unlock();

	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
                    FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
	FLASH_Lock();
	
	g_lastFlashStatus = FLASH_COMPLETE;

	return FLASH_OK;
}

uint32_t Flash_GetSectorFromAddress(uint32_t address) {
    /* 检查地址范围 */
    if (address < 0x08000000 || address >= 0x08200000) {
        return -1;
    }

    /* F429扇区划分 (2MB版本) */
    if (address < 0x08004000) return FLASH_Sector_0;      /* 16KB */
    else if (address < 0x08008000) return FLASH_Sector_1; /* 16KB */
    else if (address < 0x0800C000) return FLASH_Sector_2; /* 16KB */
    else if (address < 0x08010000) return FLASH_Sector_3; /* 16KB */
    else if (address < 0x08020000) return FLASH_Sector_4; /* 64KB */
    else if (address < 0x08040000) return FLASH_Sector_5; /* 128KB */
    else if (address < 0x08060000) return FLASH_Sector_6; /* 128KB */
    else if (address < 0x08080000) return FLASH_Sector_7; /* 128KB */
    else if (address < 0x080A0000) return FLASH_Sector_8; /* 128KB */
    else if (address < 0x080C0000) return FLASH_Sector_9; /* 128KB */
    else if (address < 0x080E0000) return FLASH_Sector_10; /* 128KB */
    else return FLASH_Sector_11;                           /* 128KB */
}
int Flash_EraseSector(uint32_t address) {
    uint32_t sector;
    
    /* 获取扇区编号 */
    sector = Flash_GetSectorFromAddress(address);
    /* 解锁Flash */
    FLASH_Unlock();
    
    /* 清空标志位 */
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
                    FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
    
    /* 执行扇区擦除 */
    /* 电压范围：FLASH_VOLTAGE_RANGE_3 = 2.7V - 3.6V (适用于3.3V系统) */
    g_lastFlashStatus = FLASH_EraseSector(sector, VoltageRange_3);
    
    /* 锁定Flash */
    FLASH_Lock();
    
    return (g_lastFlashStatus == FLASH_COMPLETE) ? FLASH_OK : FLASH_ERROR;
}
int Flash_EraseUserSector(void) {
    return Flash_EraseSector(FLASH_USER_START_ADDR);
}
int Flash_WriteHalfWord(uint32_t address, uint16_t data) {
    /* 检查地址是否半字对齐 */
    if (address & 0x01) {
        return FLASH_BAD_ADDR;
    }
    
    /* 解锁Flash */
    FLASH_Unlock();
    
    /* 清空标志位 */
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
                    FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
    
    /* 执行半字写入 */
    g_lastFlashStatus = FLASH_ProgramHalfWord(address, data);
    
    /* 锁定Flash */
    FLASH_Lock();
    
    return (g_lastFlashStatus == FLASH_COMPLETE) ? FLASH_OK : FLASH_ERROR;
}
int Flash_WriteByte(uint32_t address, uint8_t data) {
    uint32_t halfword_addr = address & ~0x01;  /* 对齐到半字地址 */
    uint16_t halfword_data;
    int ret;
    
    /* 读取当前的半字数据 */
    halfword_data = *(__IO uint16_t*)halfword_addr;
    
    /* 修改对应字节 */
    if (address & 0x01) {
        /* 写入高字节 */
        halfword_data = (halfword_data & 0x00FF) | (data << 8);
    } else {
        /* 写入低字节 */
        halfword_data = (halfword_data & 0xFF00) | data;
    }
    
    /* 写入半字 */
    ret = Flash_WriteHalfWord(halfword_addr, halfword_data);
    
    return ret;
}
uint8_t Flash_ReadByte(uint32_t address) {
    return *(__IO uint8_t*)address;
}
void Flash_ReadBuffer8(uint32_t address, uint8_t *pData, uint32_t len) {
    uint32_t i;
    for (i = 0; i < len; i++) {
        pData[i] = *(__IO uint8_t*)(address + i);
    }
}
int Flash_WriteBuffer8(uint32_t address, uint8_t *pData, uint32_t len) {
    uint32_t i;
    int ret;
    
    for (i = 0; i < len; i++) {
        ret = Flash_WriteByte(address + i, pData[i]);
        if (ret != FLASH_OK) {
            return ret;
        }
    }
    
    return FLASH_OK;
}