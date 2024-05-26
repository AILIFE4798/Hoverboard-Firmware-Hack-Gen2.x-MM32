////////////////////////////////////////////////////////////////////////////////
/// @file     reg_crc.h
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

#ifndef __REG_CRC_H
#define __REG_CRC_H

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
/// @brief CRC Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define CRC_BASE                        (AHBPERIPH_BASE + 0x3000)               ///< Base Address: 0x40023000

////////////////////////////////////////////////////////////////////////////////
/// @brief CRC Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32   DR;                                                              ///< CRC data register,                             offset: 0x00
    __IO u32   IDR;                                                             ///< CRC independent data register,                 offset: 0x04
    __IO u32   CR;                                                              ///< CRC control register,                          offset: 0x08
    __IO u32   MIR;                                                             ///< Middle data register,                          offset: 0x0C
} CRC_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief CRC type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define CRC                             ((CRC_TypeDef*) CRC_BASE)

////////////////////////////////////////////////////////////////////////////////
/// @brief CRC_DR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CRC_DR_DATA_Pos                 (0)
#define CRC_DR_DATA                     (0xFFFFFFFFU << CRC_DR_DATA_Pos)        ///< Data register bits
////////////////////////////////////////////////////////////////////////////////
/// @brief CRC_IDR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CRC_IDR_DATA_Pos                (0)
#define CRC_IDR_DATA                    (0xFFU << CRC_IDR_DATA_Pos)             ///< General-purpose 8-bit data register bits

////////////////////////////////////////////////////////////////////////////////
/// @brief CRC_CR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CRC_CR_RST_Pos                  (0)
#define CRC_CR_RST                      (0x01U << CRC_CR_RST_Pos)               ///< RESET bit
#define CRC_CR_AS_Pos                   (1)                                     ///< Algorithm selection
#define CRC_CR_AS                       (0x01U << CRC_CR_AS_Pos)
#define CRC_CR_ISIZE_Pos                (2)
#define CRC_CR_ISIZE_MODE_0             (0x00U << CRC_CR_ISIZE_Pos)             ///< Input bit width selection 32 bit
#define CRC_CR_ISIZE_MODE_1             (0x01U << CRC_CR_ISIZE_Pos)             ///< Input bit width selection 16 bit
#define CRC_CR_ISIZE_MODE_2             (0x02U << CRC_CR_ISIZE_Pos)             ///< Input bit width selection  8 bit
#define CRC_CR_IES_Pos                  (4)
#define CRC_CR_IES                      (0x01U << CRC_CR_IES_Pos)               ///< big endian input
#define CRC_CR_IES_LITTLE_ENDIAN        (0x00U << CRC_CR_IES_Pos)               ///< little endian input
#define CRC_CR_IES_BIG_ENDIAN           (0x01U << CRC_CR_IES_Pos)               ///< big endian input
#define CRC_CR_OES_Pos                  (5)
#define CRC_CR_OES                      (0x01U << CRC_CR_OES_Pos)               ///< big endian output
#define CRC_CR_OES_LITTLE_ENDIAN        (0x00U << CRC_CR_OES_Pos)               ///< little endian output
#define CRC_CR_OES_BIG_ENDIAN           (0x01U << CRC_CR_OES_Pos)               ///< big endian output

#define CRC_CR_RESET_Pos                CRC_CR_RST_Pos
#define CRC_CR_RESET                    CRC_CR_RST                              ///< RESET bit
#define CRC_CR_MGN_Pos                  CRC_CR_AS_Pos                           ///< Algorithm selection
#define CRC_CR_MGN                      CRC_CR_AS
#define CRC_CR_BITSEL_Pos               CRC_CR_ISIZE_Pos
#define CRC_CR_BITSEL_0                 CRC_CR_ISIZE_MODE_0                     ///< Input bit width selection 32 bit
#define CRC_CR_BITSEL_1                 CRC_CR_ISIZE_MODE_1                     ///< Input bit width selection 16 bit
#define CRC_CR_BITSEL_2                 CRC_CR_ISIZE_MODE_2                     ///< Input bit width selection  8 bit
#define CRC_CR_BIG_EI_Pos               CRC_CR_IES_Pos
#define CRC_CR_BIG_EI                   CRC_CR_IES                              ///< big endian input
#define CRC_CR_BIG_EO_Pos               CRC_CR_OES_Pos
#define CRC_CR_BIG_EO                   CRC_CR_OES                              ///< big endian output

////////////////////////////////////////////////////////////////////////////////
/// @brief CRC_MIR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CRC_MIR_Pos                     (0)
#define CRC_MIR                         (0xFFFFFFFFU << CRC_MIR_Pos)            ///< Middle data register

/// @}

/// @}

/// @}

#ifdef __cplusplus
}
#endif

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
