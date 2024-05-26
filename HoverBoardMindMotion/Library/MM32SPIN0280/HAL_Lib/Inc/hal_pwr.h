////////////////////////////////////////////////////////////////////////////////
/// @file     hal_pwr.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE PWR
///           FIRMWARE LIBRARY.
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
#ifndef __HAL_PWR_H
#define __HAL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

// Files includes
#include "types.h"
#include "reg_pwr.h"
#include "reg_syscfg.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup PWR_HAL
/// @brief PWR HAL modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup PWR_Exported_Types
/// @{

typedef enum {
    emWUP_Pin1 = 0,
    emWUP_Pin2 = 1,
    emWUP_Pin3,
    emWUP_Pin4,
    emWUP_Pin5,
    emWUP_Pin6,
} emWUP_Pin_Typedef;
////////////////////////////////////////////////////////////////////////////////
/// @brief PVD_detection_level

typedef enum {
    emPVD_LEVEL0  = PWR_CR_PLS_0,
    emPVD_LEVEL1  = PWR_CR_PLS_1,
    emPVD_LEVEL2  = PWR_CR_PLS_2,
    emPVD_LEVEL3  = PWR_CR_PLS_3,
    emPVD_LEVEL4  = PWR_CR_PLS_4,
    emPVD_LEVEL5  = PWR_CR_PLS_5,
    emPVD_LEVEL6  = PWR_CR_PLS_6,
    emPVD_LEVEL7  = PWR_CR_PLS_7,
    emPVD_LEVEL8  = PWR_CR_PLS_8,
    emPVD_LEVEL9  = PWR_CR_PLS_9,
    emPVD_LEVEL10 = PWR_CR_PLS_10
} emPVD_Level_Typedef;
#define PWR_PVDLevel_1V7          PWR_CR_PLS_0
#define PWR_PVDLevel_2V0          PWR_CR_PLS_1
#define PWR_PVDLevel_2V3          PWR_CR_PLS_2
#define PWR_PVDLevel_2V6          PWR_CR_PLS_3
#define PWR_PVDLevel_2V9          PWR_CR_PLS_4
#define PWR_PVDLevel_3V2          PWR_CR_PLS_5
#define PWR_PVDLevel_3V5          PWR_CR_PLS_6
#define PWR_PVDLevel_3V8          PWR_CR_PLS_7
#define PWR_PVDLevel_4V1          PWR_CR_PLS_8
#define PWR_PVDLevel_4V4          PWR_CR_PLS_9
#define PWR_PVDLevel_4V7          PWR_CR_PLS_10

/// @brief Regulator_state_is_STOP_mode
typedef enum {
    PWR_Regulator_ON       = 0x00000000,
    PWR_Regulator_LowPower = 0x00000001

} emPWR_Reg_Stop_mode_Typedef;

/// @brief STOP_mode_entry
typedef enum {
    PWR_STOPEntry_WFI = 0x00000001,
    PWR_STOPEntry_WFE = 0x00000002

} emPWR_STOP_ModeEn_Typedef;

/// @brief Low Power Mode
typedef enum {
    LP_STOP_MODE    = 0,
    LP_SLEEP_MODE   = 1,
    LP_STANDBY_MODE = 2
} emPWR_LP_Mode_Typedef;

/// @brief Wait_for_mode
typedef enum {
    LP_WFI,
    LP_WFE
} emPWR_Wait_Mode_Typedef;
/// @brief PWR_Flag
typedef enum {
    PWR_FLAG_WU   = PWR_CSR_WUF,
    PWR_FLAG_SB   = PWR_CSR_SBF,

    PWR_FLAG_PVDO = PWR_CSR_PVDO

} emPWR_PWR_Flag_Typedef;

/// @}

///////////////////////////////////////////////////////////////////////////////
/// @defgroup PWR_Exported_Variables
/// @{

#ifdef _HAL_PWR_C_

#define GLOBAL
#else
#define GLOBAL extern
#endif

#undef GLOBAL

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup PWR_Exported_Functions
/// @{

void PWR_DeInit(void);

void PWR_BackupAccessCmd(FunctionalState state);

void PWR_PVDCmd(FunctionalState state);
void PWR_PVDLevelConfig(emPVD_Level_Typedef pvd_level);
void PWR_WakeUpPinCmd(FunctionalState state);
void PWR_EnterSTOPMode(emPWR_Reg_Stop_mode_Typedef regulator, emPWR_STOP_ModeEn_Typedef stop_entry);
void PWR_EnterSTANDBYMode(void);

void PWR_ClearFlag(u32 flag);
FlagStatus PWR_GetFlagStatus(u32 flag);
void exPWR_EnterLowPowerMode(emPWR_LP_Mode_Typedef lp_mode, emPWR_Wait_Mode_Typedef wait_mode);

/// @}

/// @}

/// @}

#ifdef __cplusplus
}
#endif

////////////////////////////////////////////////////////////////////////////////
#endif// __HAL_PWR_H
////////////////////////////////////////////////////////////////////////////////
