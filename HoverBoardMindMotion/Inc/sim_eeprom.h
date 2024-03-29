////////////////////////////////////////////////////////////////////////////////
/// @file    sim_eeprom.h
/// @author  AE TEAM
/// @brief   THIS FILE PROVIDES ALL THE SYSTEM FIRMWARE FUNCTIONS.
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#ifndef __SIM_EEPROM_H
#define __SIM_EEPROM_H

// Files includes
#include <string.h>

#ifdef TARGET_MM32SPIN25
#include "HAL_device.h"                 // Device header
#else
#include "mm32_device.h"                // Device header
#endif
#include "hal_conf.h"





////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Variables
/// @{
#ifdef _SIM_EEPROM_C_
#define GLOBAL
#else
#define GLOBAL extern
#endif
#undef GLOBAL

/// @}


////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Functions
/// @{
void FLASH_SIM_EEPROM_Init(void);
s32 EEPROM_Write(u8* ptr, u16 len);
s32 EEPROM_Read(u8* ptr, u16 len);
s32 FLASH_SIM_EEPROM_Test(void);
uint8_t restorecfg();
/// @}


/// @}

/// @}


////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
