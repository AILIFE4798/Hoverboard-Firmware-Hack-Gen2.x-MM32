////////////////////////////////////////////////////////////////////////////////
/// @file     reg_sqrt.h
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

#ifndef __REG_SQRT_H
#define __REG_SQRT_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"
#include "reg_common.h"

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
/// @brief SQRT Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define SQRT_BASE                   (PERIPH_BASE + 0x00030000 + 0x0400)              ///< Base Address: 0x40030400

////////////////////////////////////////////////////////////////////////////////
/// @brief SQRT Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 SQR;                                                               ///< Square data register,                          offset: 0x00
    union {
        __IO u32 RESULT;                                                        ///< Result data register,                          offset: 0x04
        __IO u32 ROOT;
    };
} SQRT_TypeDef, ROOT_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief SQRT type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define SQRT                        ((SQRT_TypeDef*) SQRT_BASE)
#define HWROOT                      ((ROOT_TypeDef*) SQRT_BASE)

////////////////////////////////////////////////////////////////////////////////
/// @brief HWSQRT Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SQRT_SQR_SQUARE_Pos         (0)
#define SQRT_SQR_SQUARE             (0xFFFFFFFFU << SQRT_SQR_SQUARE_Pos)        ///< Square data register

////////////////////////////////////////////////////////////////////////////////
/// @brief HWSQRT_SQR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SQRT_RESULT_RESULT_Pos      (0)
#define SQRT_RESULT_RESULT          (0xFFFFU << SQRT_RESULT_RESULT_Pos)     ///< Square result register

/// @}

/// @}

/// @}

#ifdef __cplusplus
}
#endif

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
