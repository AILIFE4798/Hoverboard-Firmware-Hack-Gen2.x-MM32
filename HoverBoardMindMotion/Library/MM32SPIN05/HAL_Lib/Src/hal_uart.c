////////////////////////////////////////////////////////////////////////////////
/// @file     hal_uart.c
/// @file     hal_uart.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE UART FIRMWARE FUNCTIONS.
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
#define _HAL_UART_C_

// Files includes
#include "hal_rcc.h"
#include "hal_uart.h"
#include "hal_gpio.h"
#include "hal_dma.h"
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
///@addtogroup UART_HAL
///@{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup UART_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  Deinitializes the uart peripheral registers to their
///         default reset values.
/// @param  uart: Select the UART or the UART peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_DeInit(UART_TypeDef* uart)
{


    if(UART2 == uart) {
        exRCC_APB1PeriphReset(RCC_APB1ENR_UART2);
    }
    if(UART1 == uart) {
        exRCC_APB2PeriphReset(RCC_APB2ENR_UART1);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes the uart peripheral according to the specified
///         parameters in the UART_InitStruct .
/// @param  uart: Select the UART or the UART peripheral.
/// @param  init_struct: pointer to a UART_InitTypeDef structure
///         that contains the configuration information for the
///         specified UART peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_Init(UART_TypeDef* uart, UART_InitTypeDef* init_struct)
{
    u32 apbclock = 0x00;
    // UART CCR Configuration
    MODIFY_REG(uart->CCR, UART_CCR_CHAR, init_struct->WordLength);


    MODIFY_REG(uart->CCR, (UART_CCR_SPB0 | UART_CCR_SPB1), init_struct->StopBits);

    MODIFY_REG(uart->CCR, (UART_CCR_PEN | UART_CCR_PSEL), init_struct->Parity);

    // UART GCR Configuration
    MODIFY_REG(uart->GCR, (UART_GCR_TX | UART_GCR_RX), init_struct->Mode);
    MODIFY_REG(uart->GCR, UART_GCR_AUTOFLOW, init_struct->HWFlowControl);

    //UART BRR Configuration
    //Configure the UART Baud Rate
    if (uart == UART1) {
        apbclock = RCC_GetPCLK2Freq();
    }
    else {
        apbclock = RCC_GetPCLK1Freq();
    }				
		apbclock =72000000;//temp fix by AILIFE because RCC_GetPCLK1Freq() always report 8M
    // Determine the UART_baud
    uart->BRR = (apbclock / init_struct->BaudRate) / 16;
    uart->FRA = (apbclock / init_struct->BaudRate) % 16;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Fills each UART_InitStruct member with its default value.
/// @param  init_struct: pointer to a UART_InitTypeDef structure
///         which will be initialized.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_StructInit(UART_InitTypeDef* init_struct)
{
    // UART_InitStruct members default value
    init_struct->BaudRate       = 9600;
    init_struct->WordLength     = UART_WordLength_8b;
    init_struct->StopBits       = UART_StopBits_1;
    init_struct->Parity         = UART_Parity_No;
    init_struct->Mode           = UART_GCR_RX | UART_GCR_TX;
    init_struct->HWFlowControl  = UART_HWFlowControl_None;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified UART peripheral.
/// @param  uart: Select the UART or the UART peripheral.
/// @param  state: new state of the uart peripheral.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_Cmd(UART_TypeDef* uart, FunctionalState state)
{
    MODIFY_REG(uart->GCR, UART_GCR_UART, state << UART_GCR_UART_Pos);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified UART interrupts.
/// @param  uart: Select the UART or the UART peripheral.
/// @param  it: specifies the UART interrupt sources to be
///         enabled or disabled.
///         This parameter can be one of the following values:
/// @arg    UART_IT_ERR:  Error interrupt(Frame error,)
/// @arg    UART_IT_PE:   Parity Error interrupt
/// @arg    UART_OVER_ERR:  overrun Error interrupt
/// @arg    UART_IT_RXIEN: Receive Data register interrupt
/// @arg    UART_IT_TXIEN:  Tansmit Data Register empty interrupt
///
/// @param  state: new state of the specified uart interrupts.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_ITConfig(UART_TypeDef* uart, u16 it, FunctionalState state)
{
    (state) ? (uart->IER |= it) : (uart->IER &= ~it);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the UART DMA interface.
/// @param  uart: Select the UART or the UART peripheral.
/// @param  dma_request: specifies the DMA request.
///         This parameter can be any combination of the following values:
/// @arg    UART_DMAReq_EN: UART DMA transmit request
///
/// @param  state: new state of the DMA Request sources.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_DMACmd(UART_TypeDef* uart, u16 dma_request, FunctionalState state)
{
    MODIFY_REG(uart->GCR, UART_GCR_DMA, state << UART_GCR_DMA_Pos);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Transmits single data through the uart peripheral.
/// @param  uart: Select the UART or the UART peripheral.
/// @param  Data: the data to transmit.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_SendData(UART_TypeDef* uart, u16 value)
{
    // Transmit Data
    WRITE_REG(uart->TDR, (value & 0xFFU));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the most recent received data by the uart peripheral.
/// @param  uart: Select the UART or the UART peripheral.
/// @retval  The received data.
////////////////////////////////////////////////////////////////////////////////
u16 UART_ReceiveData(UART_TypeDef* uart)
{
    // Receive Data
    return (u16)(uart->RDR & 0xFFU);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the specified UART flag is set or not.
/// @param  uart: Select the UART or the UART peripheral.
/// @param  flag: specifies the flag to check.
///         This parameter can be one of the following values:
/// @arg    UART_FLAG_TXEMPTY: Transmit data register empty flag
/// @arg    UART_FLAG_TXFULL: Transmit data buffer full
/// @arg    UART_FLAG_RXAVL: RX Buffer has a byte flag
/// @arg    UART_FLAG_OVER: OverRun Error flag
/// @arg    UART_FLAG_TXEPT: tx and shifter are emptys flag
/// @retval  The new state of UART_FLAG (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
FlagStatus UART_GetFlagStatus(UART_TypeDef* uart, u16 flag)
{
    return (uart->CSR & flag) ? SET : RESET;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the specified UART interrupt has occurred or not.
/// @param  uart: Select the UART or the UART peripheral.
/// @param  it: specifies the UART interrupt source to check.
///         This parameter can be one of the following values:
/// @arg    UART_IT_ERR:  Error interrupt(Frame error,)
/// @arg    UART_IT_PE:   Parity Error interrupt
/// @arg    UART_OVER_ERR:  overrun Error interrupt
/// @arg    UART_IT_RXIEN: Receive Data register interrupt
/// @arg    UART_IT_TXIEN:  Tansmit Data Register empty interrupt
/// @retval  The new state of UART_IT (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
ITStatus UART_GetITStatus(UART_TypeDef* uart, u16 it)
{
    return (uart->ISR & it) ? SET : RESET;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears the uart interrupt pending bits.
/// @param  uart: Select the UART or the UART peripheral.
/// @param  it: specifies the interrupt pending bit to clear.
///         This parameter can be one of the following values:
/// @arg    UART_IT_ERR:  Error interrupt(Frame error,)
/// @arg    UART_IT_PE:   Parity Error interrupt
/// @arg    UART_OVER_ERR:  overrun Error interrupt
/// @arg    UART_IT_RXIEN: Receive Data register interrupt
/// @arg    UART_IT_TXIEN:  Tansmit Data Register empty interrupt
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_ClearITPendingBit(UART_TypeDef* uart, u16 it)
{
    //clear UART_IT pendings bit
    uart->ICR = it;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Selects the UART WakeUp method.
/// @param  uart: Select the UART or the UART peripheral.
/// @param  mode: specifies the UART wakeup method.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_WakeUpConfig(UART_TypeDef* uart, UART_WakeUp_TypeDef mode)
{
    MODIFY_REG(uart->CCR, UART_CCR_WAKE, mode);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Determines if the UART is in mute mode or not.
/// @param  uart: Select the UART or the UART peripheral.
/// @param  state: new state of the UART mute mode.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_ReceiverWakeUpCmd(UART_TypeDef* uart, FunctionalState state)
{
    MODIFY_REG(uart->CCR, UART_CCR_RWU, state << UART_CCR_RWU_Pos);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the address of the UART Rx Address.
/// @param  uart: Select the UART or the UART peripheral.
/// @param  address: Indicates the address of the UART Rx Address.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_SetRXAddress(UART_TypeDef* uart, u8 address)
{
    MODIFY_REG(uart->RXAR, UART_RXAR_ADDR, address);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the address of the UART Rx MASK.
/// @param  uart: Select the UART or the UART peripheral.
/// @param  address: Indicates the address of the UART Rx MASK.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_SetRXMASK(UART_TypeDef* uart, u8 address)
{
    MODIFY_REG(uart->RXMR, UART_RXMR_MASK, address);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  ENBALE or DISABLE the UART's 9bit.
/// @param  uart: Select the UART or the UART peripheral.
/// @param  state: new state of the UART 9 bit.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_Enable9bit(UART_TypeDef* uart, FunctionalState state)
{
    MODIFY_REG(uart->CCR, UART_CCR_B8EN, state << UART_CCR_B8EN_Pos);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Set the UART's 9bit Level.
/// @param  uart: Select the UART or the UART peripheral.
/// @param  state: new state of the UART 9 bit.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_Set9bitLevel(UART_TypeDef* uart, FunctionalState state)
{
    MODIFY_REG(uart->CCR, UART_CCR_B8TXD, state << UART_CCR_B8TXD_Pos);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Set the UART's 9bit Polarity.
/// @param  uart: Select the UART or the UART peripheral.
/// @param  polarity: new state of the UART 9 bit Polarity.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_Set9bitPolarity(UART_TypeDef* uart, UART_9bit_Polarity_TypeDef polarity)
{
    MODIFY_REG(uart->CCR, UART_CCR_B8POL, polarity);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Set the UART's 9bit Automatic Toggle.
/// @param  uart: Select the UART or the UART peripheral.
/// @param  state: new state of the UART 9 bit Automatic Toggle.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_Set9bitAutomaticToggle(UART_TypeDef* uart, FunctionalState state)
{
    MODIFY_REG(uart->CCR, UART_CCR_B8TOG, state << UART_CCR_B8TOG_Pos);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the UART Half Duplex communication.
/// @param  uart: Select the UART or the UART peripheral.
/// @param  state: new state of the UART Communication.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_HalfDuplexCmd(UART_TypeDef* uart, FunctionalState state)
{
    MODIFY_REG(uart->SCR, UART_SCR_HDSEL, state << UART_SCR_HDSEL_Pos);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets the specified UART guard time.
/// @param  uart: Select the UART or the UART peripheral.
/// @param  guard_time: specifies the guard time.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_SetGuardTime(UART_TypeDef* uart, u8 guard_time)
{
    MODIFY_REG(uart->SCR, UART_SCR_SCFCNT, guard_time << UART_SCR_SCFCNT_Pos);
    // Clear the UART Guard time
    // uart->SCR &= SCR_SCFCNT_Mask;
    // Set the UART guard time
    // uart->SCR |= (u16)((u16)guard_time << 0x04);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the UART's Smart Card mode.
/// @param  uart: Select the UART or the UART peripheral.
/// @param  state: new state of the Smart Card mode.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_SmartCardCmd(UART_TypeDef* uart, FunctionalState state)
{
    MODIFY_REG(uart->SCR, UART_SCR_SCEN, state << UART_SCR_SCEN_Pos);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables NACK transmission.
/// @param  uart: Select the UART or the UART peripheral.
/// @param  state: new state of the NACK transmission.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_SmartCardNACKCmd(UART_TypeDef* uart, FunctionalState state)
{
    MODIFY_REG(uart->SCR, UART_SCR_SCARB, state << UART_SCR_SCARB_Pos);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Transmits break characters.
/// @param  uart: Select the UART or the UART peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART_SendBreak(UART_TypeDef* uart)
{
    SET_BIT(uart->CCR, UART_CCR_BRK);
}

/// @}

/// @}

/// @}
