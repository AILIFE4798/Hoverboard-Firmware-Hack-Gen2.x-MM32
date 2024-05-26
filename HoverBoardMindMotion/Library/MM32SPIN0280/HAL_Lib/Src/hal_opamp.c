////////////////////////////////////////////////////////////////////////////////
/// @file     hal_opamp.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE OPAMP FIRMWARE FUNCTIONS.
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
#define _HAL_OPAMP_C

// Files includes
#include "types.h"
#include "hal_opamp.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup OPAMP_HAL
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup OPAMP_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified OPAMP peripheral.
/// @param  opamp: the selected OPAMP.
///         This parameter can be OPx where x can be 1 to 4
/// @param  state: new state of the OPAMP peripheral.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void OPAMP_Configure(emOPAMP_OutEn opamp, FunctionalState state)
{
    (state != DISABLE) ? (OPAMP->CSR |= opamp) : (OPAMP->CSR &= ~opamp);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified OPAMP peripheral.
/// @param  opampbit: the selected OPAMP.
///         This parameter can be OPx where x can be 1 to 4
///             OPAMP_Selection_OPAMP1
///             OPAMP_Selection_OPAMP2
///             OPAMP_Selection_OPAMP3
///             OPAMP_Selection_OPAMP4
/// @param  state: new state of the OPAMP peripheral.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void OPAMP_Cmd(u32 opampbit, FunctionalState state)
{
    (state != DISABLE) ? (OPAMP->CSR |= opampbit) : (OPAMP->CSR &= ~opampbit);
}

/// @}

/// @}

/// @}
