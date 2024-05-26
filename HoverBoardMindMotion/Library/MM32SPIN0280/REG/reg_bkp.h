////////////////////////////////////////////////////////////////////////////////
/// @file     reg_bkp.h
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

#ifndef __REG_BKP_H
#define __REG_BKP_H

// Files includes

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

////////////////////////////////////////////////////////////////////////////////
/// @brief BKP Base Address Definition
////////////////////////////////////////////////////////////////////////////////

#define BKP_BASE                        (APB1PERIPH_BASE + 0x280C)              ///< Base Address: 0x4000280C

////////////////////////////////////////////////////////////////////////////////
/// @brief BKP Register Structure Definition
////////////////////////////////////////////////////////////////////////////////

#define BKP_NUMBER  20

typedef struct {
    __IO u32 RESERVED0;                                                         ///< Reserved,                              offset: 0x00
    __IO u32 DR1;                                                               ///< BKP data register 1,                   offset: 0x04    BKP_DR1
    __IO u32 DR2;                                                               ///< BKP data register 2,                   offset: 0x08    BKP_DR2
    __IO u32 DR3;                                                               ///< BKP data register 3,                   offset: 0x0C    BKP_DR3
    __IO u32 DR4;                                                               ///< BKP data register 4,                   offset: 0x10    BKP_DR4
    __IO u32 DR5;                                                               ///< BKP data register 5,                   offset: 0x14    BKP_DR5
    __IO u32 DR6;                                                               ///< BKP data register 6,                   offset: 0x18    BKP_DR6
    __IO u32 DR7;                                                               ///< BKP data register 7,                   offset: 0x1C    BKP_DR7
    __IO u32 DR8;                                                               ///< BKP data register 8,                   offset: 0x20    BKP_DR8
    __IO u32 DR9;                                                               ///< BKP data register 9,                   offset: 0x24    BKP_DR9
    __IO u32 DR10;                                                              ///< BKP data register 10                   offset: 0x28    BKP_DR10
    __IO u32 DR11;                                                              ///< BKP data register 11,                  offset: 0x2C    BKP_DR11
    __IO u32 DR12;                                                              ///< BKP data register 12,                  offset: 0x30    BKP_DR12
    __IO u32 DR13;                                                              ///< BKP data register 13,                  offset: 0x34    BKP_DR13
    __IO u32 DR14;                                                              ///< BKP data register 14,                  offset: 0x38    BKP_DR14
    __IO u32 DR15;                                                              ///< BKP data register 15,                  offset: 0x3C    BKP_DR15
    __IO u32 DR16;                                                              ///< BKP data register 16,                  offset: 0x40    BKP_DR16
    __IO u32 DR17;                                                              ///< BKP data register 17,                  offset: 0x44    BKP_DR17
    __IO u32 DR18;                                                              ///< BKP data register 18,                  offset: 0x48    BKP_DR18
    __IO u32 DR19;                                                              ///< BKP data register 19,                  offset: 0x4C    BKP_DR19
    __IO u32 DR20;                                                              ///< BKP data register 20,                  offset: 0x50    BKP_DR20
} BKP_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief BKP type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define BKP                             ((BKP_TypeDef*) BKP_BASE)

////////////////////////////////////////////////////////////////////////////////
/// @brief BKP_DRn Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define BKP_DR_DATA_Pos                 (0)
#define BKP_DR_DATA                     (0xFFFFU << BKP_DR_DATA)                ///< Backup data

/// @}

/// @}

/// @}

#ifdef __cplusplus
}
#endif

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
