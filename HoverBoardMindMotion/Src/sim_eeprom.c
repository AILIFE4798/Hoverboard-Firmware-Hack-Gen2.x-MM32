////////////////////////////////////////////////////////////////////////////////
/// @file    sim_eeprom.c
/// @author  AE TEAM
/// @brief   THIS FILE PROVIDES SIM-EEPROM FUNCTIONS.
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#define _SIM_EEPROM_C_

// Files includes
#include "hal_conf.h"
#include "../Inc/sim_eeprom.h"
#include "../Inc/pinout.h" 

#define M8(adr)  (*((vu8  *) (adr)))
#define M16(adr) (*((vu16 *) (adr)))


#define BASED_FLASH_SECTOR_ADDRESS   0x08007800
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Example_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup SIM_EEPROM
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup SIM_EEPROM_Exported_Constants
/// @{
extern uint16_t pinstorage[64];


////////////////////////////////////////////////////////////////////////////////
/// @brief  Erases a specified FLASH page.
/// @note   This function can be used for all MM32 devices.
/// @param  Page_Address: The page address to be erased.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
static void FLASH_SIM_EraseEE(u32 pageAddress)
{
    FLASH_Unlock();
    FLASH_ErasePage(pageAddress);
    FLASH_Lock();
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Programs a buffer at a specified address.
/// @note   This function can be used for all MM32 devices.
/// @param *buf: the pointer of the buffer to be programmed.
/// @param  addr: specifies the address to be programmed.
/// @param  len: the number of bytes in the buffer.
///         This parameter can only be even.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
static void FLASH_SIM_ProgramEE(u16* buf, u32 addr, u16 len)
{
    u16 i;
    FLASH_Unlock();
    for ( i = 0; i < len / 2; i++) {
        FLASH_ProgramHalfWord(addr, *buf);
        addr += 2;
        buf++;
    }
    FLASH_Lock();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Determine if the data that at the ptr address with the length is len
///         is empty.
/// @note   This function can be used for all MM32 devices.
/// @param *ptr: the pointer of the starting address.
/// @param  len: the number of bytes.
///         This parameter can only be even.
/// @retval True presents the data is empty,
///         false presents the data has been written.
////////////////////////////////////////////////////////////////////////////////
static u8 FLASH_SIM_FindEmpty(u32 ptr, u16 len)
{
    u16 i, readdata;
    u8  ret = 1;
    for (i = 0; i < (len / 2); i++) {
        readdata = M16(ptr + i * 2);
        if ( readdata != 0xffff) {
            ret = 0;
            break;
        }
    }
    return ret;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Locate the writable area on the specified address.
/// @note   This function can be used for all MM32 devices.
/// @param  pageAddress: specifies the beginning of the EEprom.
///         The EEprom can be some continuously pages in the flash.
/// @param  len: the number of bytes to be written.
///         This parameter can only be even.
/// @retval the pointer of the starting address.
////////////////////////////////////////////////////////////////////////////////
u32 FLASH_SIM_WriteLocate(u32 pageAddress, u16 len)
{
    u16 i;
    u32 ptr = pageAddress;
    if( (pageAddress % 2 ) != 0) {
        while(1);
    }
    if((0x800 % len) != 0)
        while(1);

    for (i = 0; i < (0x0800 / len); i++) {
        ptr = (pageAddress + i * len);
        if (FLASH_SIM_FindEmpty(ptr, len) == 1) {
            break;
        }
    }
    if(i == (0x0800 / len))
        ptr = 0;
    return ptr;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Programs a buffer at a specified address.
/// @note   This function can be used for all MM32 devices.
/// @param *buf: the pointer of the buffer to be programmed.
/// @param  pageAddress: specifies the beginning of the EEprom.
///         The EEprom can be some continuously pages in the flash.
/// @param  len: the number of bytes in the buffer.
///         This parameter can only be even.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
static void FLASH_SIM_WriteEE(u16* buf, u32 pageAddress, u16 len)
{
    u32 ptr = FLASH_SIM_WriteLocate(pageAddress, len);
    if (ptr == 0) {
        FLASH_SIM_EraseEE(pageAddress + 0x000);
        FLASH_SIM_EraseEE(pageAddress + 0x400);
        FLASH_SIM_ProgramEE(buf, pageAddress, len);
    }
    else {
        if (ptr == (pageAddress + 0x0400 - len)) {
            FLASH_SIM_EraseEE(pageAddress + 0x400);
            FLASH_SIM_ProgramEE(buf, (u32)ptr, len);
        }
        else if (ptr == (pageAddress + 0x0800 - len)) {
            FLASH_SIM_EraseEE(pageAddress + 0x000);
            FLASH_SIM_ProgramEE(buf, (u32)ptr, len);
        }
        else {
            FLASH_SIM_ProgramEE(buf, (u32)ptr, len);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Initialize eeprom.
/// @note   This function can be used for all MM32 devices.
/// @note   Erases the pages for EEPROM or continue to operate EEPROM.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void FLASH_SIM_EEPROM_Init(void)
{
    FLASH_SIM_EraseEE((u32)(BASED_FLASH_SECTOR_ADDRESS) + 0x0000);
    FLASH_SIM_EraseEE((u32)(BASED_FLASH_SECTOR_ADDRESS) + 0x0400);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  read the last set of data that was written in the specified EEPROM.
/// @note   This function can be used for all MM32 devices.
/// @param  ptr: the buffer to store the last set of data in EEPROM
/// @param  len: the length of data that the user wants to get
/// @note   The actual length is the minimum of len and the EEPROM blockSize
/// @retval s32: -1: the EEPROM is empty
///         0: the instance does not exist
///         1: Read data operation succeeded
////////////////////////////////////////////////////////////////////////////////
s32 EEPROM_Read(u8* ptr, u16 len)
{
    u32 pAddr;
    pAddr = FLASH_SIM_WriteLocate((u32)BASED_FLASH_SECTOR_ADDRESS, len);
    //u16* pAddr   = FLASH_SIM_Locate((u32)(BASED_FLASH_SECTOR_ADDRESS), len);

    if (pAddr == 0) {
        return  -1;
    }
    else if (pAddr == BASED_FLASH_SECTOR_ADDRESS) {
        pAddr = (BASED_FLASH_SECTOR_ADDRESS + 0x0800 - len);
    }
    else {
        pAddr -= len;
    }
    memcpy(ptr, (s8*)pAddr, len);

    return len;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  write the set of data in the specified EEPROM.
/// @note   This function can be used for all MM32 devices.
/// @param  ptr: the buffer that store the data to be written in EEPROM
/// @note   the data cannot be all 0xFF
/// @param  len: the length of ptr
/// @note   The actual length is the minimum of len and the EEPROM blockSize
/// @retval s32: false: the EEPROM_Instance does not exist
///         true: Write data operation succeeded
////////////////////////////////////////////////////////////////////////////////
s32 EEPROM_Write(u8* ptr, u16 len)
{
    FLASH_SIM_WriteEE((u16*)ptr, (u32)(BASED_FLASH_SECTOR_ADDRESS), len);
    return len;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  run the test that use FLASH simulate EEPROM
/// @note   it need to be careful to the write data can not be all 0xFFFF ;
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
s32 FLASH_SIM_EEPROM_Test(void)
{
    u16 testwrdata[16];
    u16 testrddata[16];
    u16 len = 16;
    u16 i, j;
    for(j = 0; j < 128; j++) {
        for(i = 0; i < len; i++) {
            if(i == 0)
                testwrdata[i] = j;
            else
                testwrdata[i] = 0xfffe - j - i;
        }
        EEPROM_Write((u8*)testwrdata, 2 * len);
        EEPROM_Read((u8*)testrddata, 2 * len);
        __NOP();
    }
    return 0;
}

uint8_t restorecfg(){
	uint16_t tmp[64];
	EEPROM_Read((u8*)tmp, 2 * 64);
	if(tmp[MAGICNUM_POS]==MAGIC_NUMBER){    //verify config is valid
		for(uint8_t i=0;i<64;i++){
			pinstorage[i]=tmp[i];
		}
		if(HALLAPIN<PINCOUNT&&HALLBPIN<PINCOUNT&&HALLCPIN<PINCOUNT&&TXPIN<PINCOUNT&&RXPIN<PINCOUNT){
			return 1;
		}else{
			return 0;
		}
	}else{
		return 0;
	}
}
