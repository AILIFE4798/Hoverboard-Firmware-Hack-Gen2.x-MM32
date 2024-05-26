////////////////////////////////////////////////////////////////////////////////
/// @file     hal_opamp.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE OPAMP
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
#ifndef __HAL_OPAMP_H
#define __HAL_OPAMP_H

#ifdef __cplusplus
extern "C" {
#endif

// Files includes
#include "types.h"
#include "reg_opamp.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup OPAMP_HAL
/// @brief OPAMP HAL modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup OPAMP_Exported_Types
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief OPAMP_OutputLevel
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    OPAMP1 = OPAMP_CSR_OP1, //  OPAMP1_EN,
    OPAMP2 = OPAMP_CSR_OP2,
    OPAMP3 = OPAMP_CSR_OP3,
    OPAMP4 = OPAMP_CSR_OP4
} emOPAMP_OutEn;
/// @}

#define OPAMP_Selection_OPAMP1          OPAMP_CSR_OP1
#define OPAMP_Selection_OPAMP2          OPAMP_CSR_OP2
#define OPAMP_Selection_OPAMP3          OPAMP_CSR_OP3
#define OPAMP_Selection_OPAMP4          OPAMP_CSR_OP4

////////////////////////////////////////////////////////////////////////////////
///@defgroup OPAMP_Exported_Variables
/// @{
#ifdef _HAL_OPAMP_C_

#define GLOBAL
#else
#define GLOBAL extern
#endif

#undef GLOBAL
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup OPAMP_Exported_Functions
/// @{

void OPAMP_Configure(emOPAMP_OutEn opamp, FunctionalState state);
void OPAMP_Cmd(u32 opampbit, FunctionalState state);
/// @}

/// @}

/// @}

#ifdef __cplusplus
}
#endif

////////////////////////////////////////////////////////////////////////////////
#endif// __HAL_OPAMP_H
////////////////////////////////////////////////////////////////////////////////
