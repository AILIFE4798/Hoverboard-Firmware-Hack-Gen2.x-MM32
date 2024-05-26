////////////////////////////////////////////////////////////////////////////////
/// @file     mm32_reg.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE SERIES OF
///           MM32 FIRMWARE LIBRARY.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
////////////////////////////////////////////////////////////////////////////////
#ifndef __MM32_REG_H
#define __MM32_REG_H

#include <stdint.h>
#include <stdbool.h>
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__CC_ARM)
#pragma anon_unions
#elif defined(__ICCARM__)
#pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic ignored "-Wc11-extensions"
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined(__GNUC__)
// anonymous unions are enabled by default
#else
#warning Not supported compiler type
#endif

#include "reg_common.h"
#include "reg_adc.h"
#include "reg_bkp.h"
#include "reg_comp.h"
#include "reg_crc.h"
#include "reg_dac.h"
#include "reg_dbg.h"
#include "reg_div.h"
#include "reg_dma.h"
#include "reg_exti.h"
#include "reg_flash.h"
#include "reg_gpio.h"
#include "reg_i2c.h"
#include "reg_iwdg.h"
#include "reg_opamp.h"
#include "reg_pwm.h"
#include "reg_pwr.h"
#include "reg_rcc.h"
#include "reg_sqrt.h"
#include "reg_spi.h"
#include "reg_syscfg.h"
#include "reg_tim.h"
#include "reg_uart.h"
#include "reg_wwdg.h"

////////////////////////////////////////////////////////////////////////////////
#include "mm32_reg_redefine_v1.h"
////////////////////////////////////////////////////////////////////////////////

/// @}

/// @}

/// @}

#ifdef __cplusplus
}
#endif

////////////////////////////////////////////////////////////////////////////////
#endif//__MM32_REG_H
////////////////////////////////////////////////////////////////////////////////
