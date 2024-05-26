////////////////////////////////////////////////////////////////////////////////
/// @file     reg_pwr.h
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

#ifndef __REG_PWR_H
#define __REG_PWR_H

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
/// @brief PWR Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_BASE                        (APB1PERIPH_BASE + 0x7000)              ///< Base Address: 0x40007000

////////////////////////////////////////////////////////////////////////////////
/// @brief PWR Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    union {
        __IO u32 CR;                                                            ///< Control register,                             offset: 0x00
        __IO u32 CR1;
    };
    union {
        __IO u32 CSR;                                                           ///< Control Status register                        offset: 0x04
        __IO u32 CSR1;
    };
    __IO u32 CR2;                                                               ///< Control register  2                            offset: 0x08
    __IO u32 CR3;                                                               ///< Control register  3                            offset: 0x0C
    __IO u32 CR4;                                                               ///< Control register  4                            offset: 0x10
    __IO u32 CR5;                                                               ///< Control register  5                            offset: 0x14
    __IO u32 RESERVED0x18;                                                      ///< Control reserved                               offset: 0x18
    __IO u32 SR;                                                                ///< Status  register                               offset: 0x1C
    __IO u32 SCR;                                                               ///< clear status register                          offset: 0x20
    __IO u32 CFGR;                                                              ///< Configuration register                         offset: 0x24
} PWR_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief PWR type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define PWR                             ((PWR_TypeDef*) PWR_BASE)

////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_CR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_CR_LDPS_Pos                 (0)
#define PWR_CR_LDPS                     (0x01U  << PWR_CR_LDPS_Pos)             ///< Domain Write Protction

#define PWR_CR_PDDS_Pos                 (1)
#define PWR_CR_PDDS                     (0x01U  << PWR_CR_PDDS_Pos)             ///< Power Down Deepsleep
#define PWR_CR_CSBF_Pos                 (3)
#define PWR_CR_CSBF                     (0x01U  << PWR_CR_CSBF_Pos)             ///< Clear Standby Flag

#define PWR_CR_PVDE_Pos                 (4)
#define PWR_CR_PVDE                     (0x01U  << PWR_CR_PVDE_Pos)             ///< Power Voltage Detector Enable

#define PWR_CR_DBP_Pos                  (8)
#define PWR_CR_DBP                      (0x01U  << PWR_CR_DBP_Pos)              ///< BackUp Domain Write Protect
#define PWR_CR_PLS_Pos                  (9)
#define PWR_CR_PLS                      (0x0FU  << PWR_CR_PLS_Pos)
#define PWR_CR_PLS_0                    (0x00U  << PWR_CR_PLS_Pos)             ///< PVD level selection 1.7 v
#define PWR_CR_PLS_1                    (0x01U  << PWR_CR_PLS_Pos)             ///< PVD level selection 2.0 v
#define PWR_CR_PLS_2                    (0x02U  << PWR_CR_PLS_Pos)             ///< PVD level selection 2.3 v
#define PWR_CR_PLS_3                    (0x03U  << PWR_CR_PLS_Pos)             ///< PVD level selection 2.6 v
#define PWR_CR_PLS_4                    (0x04U  << PWR_CR_PLS_Pos)             ///< PVD level selection 2.9 v
#define PWR_CR_PLS_5                    (0x05U  << PWR_CR_PLS_Pos)             ///< PVD level selection 3.2 v
#define PWR_CR_PLS_6                    (0x06U  << PWR_CR_PLS_Pos)             ///< PVD level selection 3.5 v
#define PWR_CR_PLS_7                    (0x07U  << PWR_CR_PLS_Pos)             ///< PVD level selection 3.8 v
#define PWR_CR_PLS_8                    (0x08U  << PWR_CR_PLS_Pos)             ///< PVD level selection 4.1 v
#define PWR_CR_PLS_9                    (0x09U  << PWR_CR_PLS_Pos)             ///< PVD level selection 4.4 v
#define PWR_CR_PLS_10                   (0x0AU  << PWR_CR_PLS_Pos)             ///< PVD level selection 4.7 v
#define PWR_CR_STDBYFSWK_Pos            (13)
#define PWR_CR_STDBYFSWK_2              (0x01U  << PWR_CR_STDBYFSWK_Pos)       ///< 2 LSI40K cycles to wake up the standby
#define PWR_CR_STDBYFSWK_3              (0x02U  << PWR_CR_STDBYFSWK_Pos)       ///< 3 LSI40K cycles to wake up the standby
#define PWR_CR_STDBYFSWK_4              (0x03U  << PWR_CR_STDBYFSWK_Pos)       ///< 4 LSI40K cycles to wake up the standby
#define PWR_CR_STDBYFSWK_5              (0x04U  << PWR_CR_STDBYFSWK_Pos)       ///< 5 LSI40K cycles to wake up the standby
#define PWR_CR_STDBYFSWK_6              (0x05U  << PWR_CR_STDBYFSWK_Pos)       ///< 6 LSI40K cycles to wake up the standby
#define PWR_CR_STDBYFSWK_7              (0x06U  << PWR_CR_STDBYFSWK_Pos)       ///< 7 LSI40K cycles to wake up the standby
#define PWR_CR_STDBYFSWK_8              (0x07U  << PWR_CR_STDBYFSWK_Pos)       ///< 8 LSI40K cycles to wake up the standby

////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_CSR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_CSR_WUF_Pos                 (0)
#define PWR_CSR_WUF                     (0x01U  << PWR_CSR_WUF_Pos)             ///< Wakeup Flag
#define PWR_CSR_SBF_Pos                 (1)
#define PWR_CSR_SBF                     (0x01U  << PWR_CSR_SBF_Pos)             ///< Standby Flag
#define PWR_CSR_PVDO_Pos                (2)
#define PWR_CSR_PVDO                    (0x01U  << PWR_CSR_PVDO_Pos)            ///< PVD Output
#define PWR_CSR_EWUP_Pos                (8)
#define PWR_CSR_EWUP                    (0x01U  << PWR_CSR_EWUP_Pos)             ///< Enable WKUP pin
#define PWR_CSR_EWUP1                   (0x01U  << PWR_CSR_EWUP_Pos)             ///< Enable WakeUp Pin 1
#define PWR_CSR_EWUP2                   (0x02U  << PWR_CSR_EWUP_Pos)             ///< Enable WakeUp Pin 2
#define PWR_CSR_EWUP3                   (0x04U  << PWR_CSR_EWUP_Pos)             ///< Enable WakeUp Pin 3
#define PWR_CSR_EWUP4                   (0x08U  << PWR_CSR_EWUP_Pos)             ///< Enable WakeUp Pin 4
#define PWR_CSR_EWUP5                   (0x10U  << PWR_CSR_EWUP_Pos)             ///< Enable WakeUp Pin 5
#define PWR_CSR_EWUP6                   (0x20U  << PWR_CSR_EWUP_Pos)             ///< Enable WakeUp Pin 6
#define PWR_CSR_VDTO_Pos                (14)
#define PWR_CSR_VDTO                    (0x01U  << PWR_CSR_VDTO_Pos)             ///< VDT Output

////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_CR2 register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_CR2_VDTE_Pos                 (6)
#define PWR_CR2_VDTE                     (0x01U << PWR_CR2_VDTE_Pos)           ///< Voltage detector enable
#define PWR_CR2_VLS_Pos                  (7)
#define PWR_CR2_VLS_0                    (0x00U << PWR_CR2_VLS_Pos)            ///< VDT level select 1.2V
#define PWR_CR2_VLS_1                    (0x01U << PWR_CR2_VLS_Pos)            ///< VDT level select 1.1V
#define PWR_CR2_VLS_2                    (0x02U << PWR_CR2_VLS_Pos)            ///< VDT level select 1.0V
#define PWR_CR2_VLS_3                    (0x03U << PWR_CR2_VLS_Pos)            ///< VDT level select 0.9V

////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_CR3 register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_CR3_WP1_Pos                (0)
#define PWR_CR3_WP1                    (0x01U << PWR_CR3_WP1_Pos)               ///< WKUP1 used for event polarity detection
#define PWR_CR3_WP2_Pos                (1)
#define PWR_CR3_WP2                    (0x01U << PWR_CR3_WP2_Pos)               ///< WKUP2 used for event polarity detection
#define PWR_CR3_WP3_Pos                (2)
#define PWR_CR3_WP3                    (0x01U << PWR_CR3_WP3_Pos)               ///< WKUP3 used for event polarity detection
#define PWR_CR3_WP4_Pos                (3)
#define PWR_CR3_WP4                    (0x01U << PWR_CR3_WP4_Pos)               ///< WKUP4 used for event polarity detection
#define PWR_CR3_WP5_Pos                (4)
#define PWR_CR3_WP5                    (0x01U << PWR_CR3_WP5_Pos)               ///< WKUP5 used for event polarity detection
#define PWR_CR3_WP6_Pos                (5)
#define PWR_CR3_WP6                    (0x01U << PWR_CR3_WP6_Pos)               ///< WKUP6 used for event polarity detection
////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_CR4 register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_CR4_FILTSEL0_Pos           (0)
#define PWR_CR4_FILTSEL0               (0x01U << PWR_CR4_FILTSEL0_Pos)          ///< selection wake-up source
#define PWR_CR4_FILTE0_Pos             (2)
#define PWR_CR4_FILTE0                 (0x01U << PWR_CR4_FILTE0_Pos)            ///< enable Filter 0
#define PWR_CR4_FILTF0_Pos             (4)
#define PWR_CR4_FILTF0                 (0x01U << PWR_CR4_FILTF0_Pos)            ///< Whether the wake source passes through filter 0
#define PWR_CR4_FILTCNT0_Pos           (8)
#define PWR_CR4_FILTCNT0               (0xFFU << PWR_CR4_FILTCNT0_Pos)          ///< Filter 0 counter
////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_CR5 register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_CR5_FILTSEL1_Pos           (0)
#define PWR_CR5_FILTSEL1               (0x01U << PWR_CR5_FILTSEL1_Pos)          ///< selection wake-up source
#define PWR_CR5_FILTE1_Pos             (2)
#define PWR_CR5_FILTE1                 (0x01U << PWR_CR5_FILTE1_Pos)            ///< enable Filter 1
#define PWR_CR5_FILTF1_Pos             (4)
#define PWR_CR5_FILTF1                 (0x01U << PWR_CR5_FILTF1_Pos)            ///< Whether the wake source passes through filter 1
#define PWR_CR5_FILTCNT1_Pos           (8)
#define PWR_CR5_FILTCNT1               (0xFFU << PWR_CR5_FILTCNT1_Pos)          ///< Filter 1 counter

////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_SR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_SR_WUF2_Pos                (1)
#define PWR_SR_WUF2                    (0x01U << PWR_SR_WUF2_Pos)               ///< wake-up flag 2
#define PWR_SR_WUF3_Pos                (2)
#define PWR_SR_WUF3                    (0x01U << PWR_SR_WUF3_Pos)               ///< wake-up flag 3
#define PWR_SR_WUF4_Pos                (3)
#define PWR_SR_WUF4                    (0x01U << PWR_SR_WUF4_Pos)               ///< wake-up flag 4
#define PWR_SR_WUF5_Pos                (4)
#define PWR_SR_WUF5                    (0x01U << PWR_SR_WUF5_Pos)               ///< wake-up flag 5
#define PWR_SR_WUF6_Pos                (5)
#define PWR_SR_WUF6                    (0x01U << PWR_SR_WUF6_Pos)               ///< wake-up flag 6
////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_SCR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_SCR_CWUF1_Pos              (0)
#define PWR_SCR_CWUF1                  (0x01U << PWR_SCR_CWUF1_Pos)             ///< clear wake-up flag 1
#define PWR_SCR_CWUF2_Pos              (1)
#define PWR_SCR_CWUF2                  (0x01U << PWR_SCR_CWUF2_Pos)             ///< clear wake-up flag 2
#define PWR_SCR_CWUF3_Pos              (2)
#define PWR_SCR_CWUF3                  (0x01U << PWR_SCR_CWUF3_Pos)             ///< clear wake-up flag 3
#define PWR_SCR_CWUF4_Pos              (3)
#define PWR_SCR_CWUF4                  (0x01U << PWR_SCR_CWUF4_Pos)             ///< clear wake-up flag 4
#define PWR_SCR_CWUF5_Pos              (4)
#define PWR_SCR_CWUF5                  (0x01U << PWR_SCR_CWUF5_Pos)             ///< clear wake-up flag 5
#define PWR_SCR_CWUF6_Pos              (5)
#define PWR_SCR_CWUF6                  (0x01U << PWR_SCR_CWUF6_Pos)             ///< clear wake-up flag 6
////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_CFGR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_CFGR_LSICALSEL_Pos         (0)
#define PWR_CFGR_LSICALSEL             (0x1FU << PWR_CFGR_LSICALSEL_Pos)        ///< Enable internal clock calibration
#define PWR_CFGR_LSICAL_Pos            (5)
#define PWR_CFGR_LSICAL                (0x1FU << PWR_CFGR_LSICAL_Pos)           ///< Internal high-speed clock calibration

/// @}

/// @}

/// @}

#ifdef __cplusplus
}
#endif

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
