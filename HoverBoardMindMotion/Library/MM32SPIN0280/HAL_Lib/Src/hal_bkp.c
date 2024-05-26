////////////////////////////////////////////////////////////////////////////////
/// @file     hal_bkp.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE BKP FIRMWARE FUNCTIONS.
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
#define _HAL_BKP_C_

// Files includes
#include "types.h"
#include "hal_pwr.h"
#include "hal_rcc.h"
#include "hal_bkp.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup BKP_HAL
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup BKP_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  Writes user data to the specified data Backup Register.
/// @param  bkp_dr: specifies the data Backup Register.
///         This parameter can be BKP_DRx where x:[1, 10]
/// @param  data: data to write
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void BKP_WriteBackupRegister(BKPDR_Typedef bkp_dr, u16 data)
{
    *(vu16*)(BKP_BASE + bkp_dr) = data;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Reads data from the specified data Backup Register.
/// @param  bkp_dr: specifies the data Backup Register.
///         This parameter can be BKP_DRx where x:[1, 10]
/// @retval data: The content of the specified data Backup Register
////////////////////////////////////////////////////////////////////////////////
u16 BKP_ReadBackupRegister(BKPDR_Typedef bkp_dr)
{
    return (*(vu16*)(BKP_BASE + bkp_dr));
}
////////////////////////////////////////////////////////////////////////////////
//          Extended function interface
////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes the BKP peripheral, enable access to the backup
///         registers.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exBKP_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_PWR, ENABLE);
    //COMMON_EnableIpClock(emCLOCK_PWR);
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_BKP, ENABLE);

    PWR->CR |= PWR_CR_DBP;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Writes user data to the specified data Backup Register immediately.
/// @param  bkp_dr: specifies the data Backup Register.
///         This parameter can be BKP_DRx where x:[1, 10]
/// @param  data: data to write
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exBKP_ImmWrite(BKPDR_Typedef bkp_dr, u16 dat)
{
    PWR->CR |= PWR_CR_DBP;
    *(vu16*)(BKP_BASE + bkp_dr) = dat;
    PWR->CR &= ~PWR_CR_DBP;

}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Reads data from the specified data Backup Register immediately.
/// @param  bkp_dr: specifies the data Backup Register.
///         This parameter can be BKP_DRx where x:[1, 10]
/// @retval data: The content of the specified data Backup Register
////////////////////////////////////////////////////////////////////////////////
u16 exBKP_ImmRead(BKPDR_Typedef bkp_dr)
{
    u16 dat;
    PWR->CR |= PWR_CR_DBP;
    dat = (*(vu16*)(BKP_BASE + bkp_dr));
    PWR->CR &= ~PWR_CR_DBP;
    return dat;
}

/// @}

/// @}

/// @}
