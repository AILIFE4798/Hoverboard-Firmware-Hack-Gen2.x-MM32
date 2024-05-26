////////////////////////////////////////////////////////////////////////////////
/// @file     reg_pwm.h
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

#ifndef __REG_PWM_H
#define __REG_PWM_H

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
/// @brief PWM Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define PWM_BASE                        (APB2PERIPH_BASE + 0x6400)              ///< Base Address: 0x40016400

////////////////////////////////////////////////////////////////////////////////
/// @brief PWM Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 CSR;                                                                 ///< Control PWM output status register,            offset: 0x00
    __IO u32 APMSKR;                                                              ///< Auto phase mask register,                      offset: 0x04
    __IO u32 APMDLR;                                                              ///< Auto phase mask dalay register,                offset: 0x08
} PWM_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief PWM type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define PWM                             ((PWM_TypeDef*) PWM_BASE)

////////////////////////////////////////////////////////////////////////////////
/// @brief PWM_CSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define PWM_CSR_CCE_Pos                 (0)
#define PWM_CSR_CCE                     (0x01U << PWM_CSR_CCE_Pos)              ///< Current Compensation Enable
#define PWM_CSR_CPE_Pos                 (1)
#define PWM_CSR_CPE                     (0x01U << PWM_CSR_CPE_Pos)              ///< Current Protection Enable
#define PWM_CSR_APMTIE_Pos              (2)
#define PWM_CSR_APMTIE                  (0x01U << PWM_CSR_APMTIE_Pos)           ///< Auto Phase Mask Trigger Interrupt Enable
#define PWM_CSR_TERRIE_Pos              (3)
#define PWM_CSR_TERRIE                  (0x01U << PWM_CSR_TERRIE_Pos)           ///< Trigger Error Interrupt Enable
#define PWM_CSR_CC_TRGSEL_Pos           (4)
#define PWM_CSR_CC_TRGSEL               (0x03U << PWM_CSR_CC_TRGSEL_Pos)        ///< Current Compensation Trigger Selection
#define PWM_CSR_CC_STRG_Pos             (6)
#define PWM_CSR_CC_STRG                 (0x01U << PWM_CSR_CC_STRG_Pos)          ///< Current Compensation Software Trigger
#define PWM_CSR_CP_TRGSEL_Pos           (7)
#define PWM_CSR_CP_TRGSEL_1             (0x00U << PWM_CSR_CP_TRGSEL_Pos)        ///< Current Protection Trigger Selection COMP 1
#define PWM_CSR_CP_TRGSEL_2             (0x01U << PWM_CSR_CP_TRGSEL_Pos)        ///< Current Protection Trigger Selection COMP 2
#define PWM_CSR_CP_TRGSEL_3             (0x02U << PWM_CSR_CP_TRGSEL_Pos)        ///< Current Protection Trigger Selection COMP 3
#define PWM_CSR_CP_TRGSEL_4             (0x03U << PWM_CSR_CP_TRGSEL_Pos)        ///< Current Protection Trigger Selection COMP 4
#define PWM_CSR_CP_TRGSEL_5             (0x04U << PWM_CSR_CP_TRGSEL_Pos)        ///< Current Protection Trigger Selection COMP 5
#define PWM_CSR_CP_TRGSEL_4_5           (0x05U << PWM_CSR_CP_TRGSEL_Pos)        ///< Current Protection Trigger Selection COMP 4 and COMP5
#define PWM_CSR_CP_MDSEL_Pos            (10)
#define PWM_CSR_CP_MDSEL                (0x01U << PWM_CSR_CP_MDSEL_Pos)         ///< Current Protection Mode Selection
#define PWM_CSR_APMTIF_Pos              (11)
#define PWM_CSR_APMTIF                  (0x01U << PWM_CSR_APMTIF_Pos)           ///< Auto Phase Mask Trigger Flag
#define PWM_CSR_TERRIF_Pos              (12)
#define PWM_CSR_TERRIF                  (0x01U << PWM_CSR_TERRIF_Pos)           ///< Trigger Error Flag
#define PWM_CSR_IOFLT_Pos               (13)
#define PWM_CSR_IOFLT                   (0x07U << PWM_CSR_IOFLT_Pos)            ///< GPIO Input Filter
#define PWM_CSR_HALL_TRGSEL_Pos         (16)
#define PWM_CSR_HALL_TRGSEL             (0x01U << PWM_CSR_HALL_TRGSEL_Pos)      ///< Hall Sensor Trigger 3-channel select
#define PWM_CSR_CUREN_Pos               (18)
#define PWM_CSR_CUREN                   (0x01U << PWM_CSR_CUREN_Pos)            ///< Enable Current Input Status Value
#define PWM_CSR_MSKDAT_Pos              (19)
#define PWM_CSR_MSKDAT                  (0x3FU << PWM_CSR_MSKDAT_Pos)           ///< Immediate Output of The Port when PWM is Masked
#define PWM_CSR_MSKEN_Pos               (25)
#define PWM_CSR_MSKEN                   (0x3FU << PWM_CSR_MSKEN_Pos)            ///< PWM Output Mask Immediately Enable

////////////////////////////////////////////////////////////////////////////////
/// @brief PWM_APMSKR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define PWM_APMSKR_MSKDAT_Pos           (0)
#define PWM_APMSKR_MSKDAT               (0x3FU << PWM_APMSKR_MSKDAT_Pos)         ///< PWM Mask Data
#define PWM_APMSKR_MSKEN_Pos            (8)
#define PWM_APMSKR_MSKEN                (0x3FU << PWM_APMSKR_MSKEN_Pos)         ///< PWM Mask Function Enable
#define PWM_APMSKR_APM_TRIGSEL_Pos      (16)
#define PWM_APMSKR_APM_TRIGSEL          (0x03U << PWM_APMSKR_APM_TRIGSEL_Pos)   ///< COMP 1/2/3 trigger automatic commutation shielding function
#define PWM_APMSKR_APM_TRIGSEL_DISABLE  (0x00U << PWM_APMSKR_APM_TRIGSEL_Pos)   ///< Disable Auto Phase Mask Tigger
#define PWM_APMSKR_APM_TRIGSEL_SOFT     (0x01U << PWM_APMSKR_APM_TRIGSEL_Pos)   ///< Software trigger automatic commutation shielding function
#define PWM_APMSKR_APM_TRIGSEL_GPIO     (0x02U << PWM_APMSKR_APM_TRIGSEL_Pos)   ///< GPIO trigger automatic commutation shielding function

#define PWM_APMSKR_APM_STRG_Pos         (18)
#define PWM_APMSKR_APM_STRG             (0x01U << PWM_APMSKR_APM_STRG_Pos)      ///< Auto Phase Mask Software Trigger
#define PWM_APMSKR_ENTRGI_Pos           (20)
#define PWM_APMSKR_ENTRGI               (0x07U << PWM_APMSKR_ENTRGI_Pos)        ///< Expect Next Trigger Input
#define PWM_APMSKR_CTRGI_Pos            (23)
#define PWM_APMSKR_CTRGI                (0x07U << PWM_APMSKR_CTRGI_Pos)         ///< Current Trigger Input

////////////////////////////////////////////////////////////////////////////////
/// @brief PWM_CSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define PWM_APMDLR_Pos                  (0)
#define PWM_APMDLR                      (0x3FFFFFFU << PWM_APMDLR_Pos)          ///< Auto Phase Mask delay load register

/// @}

/// @}

/// @}

#ifdef __cplusplus
}
#endif

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
