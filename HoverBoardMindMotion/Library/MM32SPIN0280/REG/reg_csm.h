////////////////////////////////////////////////////////////////////////////////
/// @file     reg_csm.h
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

#ifndef __REG_CSM_H
#define __REG_CSM_H

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
/// @brief WWDG Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define CSM_BASE                       (APB1PERIPH_BASE + 0x6800)              ///< Base Address: 0x40006800

////////////////////////////////////////////////////////////////////////////////
/// @brief WWDG Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 TXREG1;                                                           ///< CSM send data register 1                       offset: 0x00
    __IO u32 TXREG2;                                                           ///< CSM send data register 2                       offset: 0x04
    __IO u32 RXREG1;                                                           ///< CSM receive data register 1                    offset: 0x08
    __IO u32 RXREG2;                                                           ///< CSM receive data register 2                    offset: 0x0C
    __IO u32 ISR ;                                                             ///< CSM interrupt status register                  offset: 0x10
    __IO u32 IER ;                                                             ///< CSM interrupt enable register                  offset: 0x14
    __IO u32 CR1 ;                                                             ///< CSM control register 1                         offset: 0x18
    __IO u32 CR2 ;                                                             ///< CSM control register 2                         offset: 0x1C
    __IO u32 CFG ;                                                             ///< CSM configuration register                     offset: 0x20
    __IO u32 SPG ;                                                             ///< CSM baud rate register                         offset: 0x24
    __IO u32 BCNT;                                                             ///< CSM data bit length register                   offset: 0x28                                                               ///< Status register                                offset: 0x08
} CSM_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief WWDG type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define CSM                            ((WWDG_TypeDef*) CSM_BASE)

////////////////////////////////////////////////////////////////////////////////
/// @brief CSM_TXREG1 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CSM_TXREG1_Pos                 (0)
#define CSM_TXREG1                     (0xFFFFFFFFU << CSM_TXREG1_Pos)              ///< Transmit data register
////////////////////////////////////////////////////////////////////////////////
/// @brief CSM_TXREG2 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CSM_TXREG2_Pos                 (0)
#define CSM_TXREG2                     (0xFFFFFFFFU << CSM_TXREG2_Pos)              ///< Transmit data register
////////////////////////////////////////////////////////////////////////////////
/// @brief CSM_RXREG1 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CSM_RXREG1_Pos                 (0)
#define CSM_RXREG1                     (0xFFFFFFFFU << CSM_RXREG1_Pos)              ///< Transmit data register
////////////////////////////////////////////////////////////////////////////////
/// @brief CSM_RXREG2 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CSM_RXREG2_Pos                 (0)
#define CSM_RXREG2                     (0xFFFFFFFFU << CSM_RXREG2_Pos)              ///< Transmit data register
////////////////////////////////////////////////////////////////////////////////
/// @brief CSM_ISR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CSM_ISR_TX_Pos                 (0)
#define CSM_ISR_TX                     (0x01U << CSM_ISR_TX_Pos)               ///< Transmit FIFO available interrupt flag
#define CSM_ISR_RX_Pos                 (1)
#define CSM_ISR_RX                     (0x01U << CSM_ISR_RX_Pos)               ///< Receive data available interrupt flag
#define CSM_ISR_TXC_Pos                (2)
#define CSM_ISR_TXC                    (0x01U << CSM_ISR_TXC_Pos)              ///< Transmit complete interrupt flag
#define CSM_ISR_START_Pos              (3)
#define CSM_ISR_START                  (0x01U << CSM_ISR_START_Pos)            ///< Start receiving data interrupt flag
#define CSM_ISR_STOP_Pos               (4)
#define CSM_ISR_STOP                   (0x01U << CSM_ISR_STOP_Pos)             ///< Stop receiving data interrupt flag
////////////////////////////////////////////////////////////////////////////////
/// @brief CSM_IER Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CSM_IER_TX_Pos                 (0)
#define CSM_IER_TX                     (0x01U << CSM_IER_TX_Pos)               ///< Transmit FIFO available interrupt enable
#define CSM_IER_RX_Pos                 (1)
#define CSM_IER_RX                     (0x01U << CSM_IER_RX_Pos)               ///< Receive data available interrupt enable
#define CSM_IER_TXC_Pos                (2)
#define CSM_IER_TXC                    (0x01U << CSM_IER_TXC_Pos)              ///< Transmit complete interrupt enable
#define CSM_IER_START_Pos              (3)
#define CSM_IER_START                  (0x01U << CSM_IER_START_Pos)            ///< Start receiving data interrupt enable
#define CSM_IER_STOP_Pos               (4)
#define CSM_IER_STOP                   (0x01U << CSM_IER_STOP_Pos)             ///< Stop receiving data interrupt enable
////////////////////////////////////////////////////////////////////////////////
/// @brief CSM_CR1 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CSM_CR1_EN1_Pos                 (0)
#define CSM_CR1_EN1                     (0x01U << CSM_CR1_EN1_Pos)               ///< Module enable control
#define CSM_CR1_IDLP1_Pos               (1)
#define CSM_CR1_IDLP1                   (0x01U << CSM_CR1_IDLP1_Pos)             ///< High level in idle state
#define CSM_CR1_INSEL1_Pos              (2)
#define CSM_CR1_INSEL1                  (0x01U << CSM_CR1_INSEL1_Pos)            ///< Input signal source select COMP
#define CSM_CR1_DMAEN1_Pos              (3)
#define CSM_CR1_DMAEN1                  (0x01U << CSM_CR1_DMAEN1_Pos)            ///< DMA enable control
#define CSM_CR1_TXSEL1_Pos              (4)
#define CSM_CR1_TXSEL1                  (0x01U << CSM_CR1_TXSEL1_Pos)             ///< Send and receive data selection control
////////////////////////////////////////////////////////////////////////////////
/// @brief CSM_CR2 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CSM_CR1_EN2_Pos                 (0)
#define CSM_CR1_EN2                     (0x01U << CSM_CR1_EN2_Pos)               ///< Module enable control
#define CSM_CR1_IDLP2_Pos               (1)
#define CSM_CR1_IDLP2                   (0x01U << CSM_CR1_IDLP2_Pos)             ///< High level in idle state
#define CSM_CR1_INSEL2_Pos              (2)
#define CSM_CR1_INSEL2                  (0x01U << CSM_CR1_INSEL2_Pos)            ///< Input signal source select COMP
#define CSM_CR1_DMAEN2_Pos              (3)
#define CSM_CR1_DMAEN2                  (0x01U << CSM_CR1_DMAEN2_Pos)            ///< DMA enable control
#define CSM_CR1_TXSEL2_Pos              (4)
#define CSM_CR1_TXSEL2                  (0x01U << CSM_CR1_TXSEL2_Pos)             ///< Send and receive data selection control
////////////////////////////////////////////////////////////////////////////////
/// @brief CSM_CFG Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CSM_CFG_STARTSEL_Pos             (0)
#define CSM_CFG_STARTSEL                 (0x01U << CSM_CFG_STARTSEL_Pos)            ///< Start condition detection
#define CSM_CFG_STOPSEL_Pos              (1)
#define CSM_CFG_STOPSEL                  (0x01U << CSM_CFG_STOPSEL_Pos)             ///< Sampling end condition
#define CSM_CFG_MSEL_Pos                 (2)
#define CSM_CFG_MSEL                     (0x01U << CSM_CFG_MSEL_Pos)                ///< Channel master-slave selection
#define CSM_CFG_MAXBIT_Pos               (16)
#define CSM_CFG_MAXBIT                   (0xFFFFU << CSM_CFG_MAXBIT_Pos)            ///<The length of the data sent and received
////////////////////////////////////////////////////////////////////////////////
/// @brief CSM_SPG Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CSM_SPG_SPBRG_Pos                (0)
#define CSM_SPG_SPBRG                    (0xFFFFU << CSM_SPG_SPBRG_Pos)            ///< baud rate control register for simple data
////////////////////////////////////////////////////////////////////////////////
/// @brief CSM_BCNT Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define CSM_BCNT_Pos                     (0)
#define CSM_BCNT                         (0xFFFFU << CSM_BCNT_Pos)                ///< Current received or sent data bit length

/// @}

/// @}

/// @}

#ifdef __cplusplus
}
#endif

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
