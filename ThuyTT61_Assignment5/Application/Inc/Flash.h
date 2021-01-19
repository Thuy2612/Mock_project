#if !defined (__FLASH_H__)
#define __FLASH_H__


 
#include <stdint.h>

 
#define CMD_PROGRAM_LONGWORD     (0x06)
#define CMD_ERASE_FLASH_SECTOR   (0x09)
 
uint32_t Read_FlashAddress(uint32_t Addr);

 
uint8_t Program_LongWord_8B(uint32_t Addr,uint8_t *Data);

 
uint8_t Program_LongWord(uint32_t Addr,uint32_t Data);

 
uint8_t Erase_Sector(uint32_t Addr);
 
uint8_t Erase_Multi_Sector(uint32_t Addr,uint8_t Size);

#endif