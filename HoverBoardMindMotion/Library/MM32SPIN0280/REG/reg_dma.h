////////////////////////////////////////////////////////////////////////////////
/// @file     reg_dma.h
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

#ifndef __REG_DMA_H
#define __REG_DMA_H

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
/// @brief DMA Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define DMA1_BASE                       (AHBPERIPH_BASE + 0x0000)               ///< Base Address: 0x40020000
#define DMA1_Channel1_BASE              (AHBPERIPH_BASE + 0x0008)               ///< Base Address: 0x40020008
#define DMA1_Channel2_BASE              (AHBPERIPH_BASE + 0x001C)               ///< Base Address: 0x4002001C
#define DMA1_Channel3_BASE              (AHBPERIPH_BASE + 0x0030)               ///< Base Address: 0x40020030
#define DMA1_Channel4_BASE              (AHBPERIPH_BASE + 0x0044)               ///< Base Address: 0x40020044
#define DMA1_Channel5_BASE              (AHBPERIPH_BASE + 0x0058)               ///< Base Address: 0x40020058

////////////////////////////////////////////////////////////////////////////////
/// @brief DMA Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 CCR;                                                               ///< DMA channel x configuration register           offset: 0x00
    __IO u32 CNDTR;                                                             ///< DMA channel x number of data register          offset: 0x04
    __IO u32 CPAR;                                                              ///< DMA channel x peripheral address register      offset: 0x08
    __IO u32 CMAR;                                                              ///< DMA channel x memory address register          offset: 0x0C
} DMA_Channel_TypeDef;

typedef struct {
    __IO u32 ISR;                                                               ///< Interrupt Status Register                      offset: 0x00
    __IO u32 IFCR;                                                              ///< Interrupt Flag Clear Register                  offset: 0x04
} DMA_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief DMA type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define DMA1                            ((DMA_TypeDef*) DMA1_BASE)
#define DMA1_ch1                        ((DMA_Channel_TypeDef*) DMA1_Channel1_BASE)
#define DMA1_ch2                        ((DMA_Channel_TypeDef*) DMA1_Channel2_BASE)
#define DMA1_ch3                        ((DMA_Channel_TypeDef*) DMA1_Channel3_BASE)
#define DMA1_ch4                        ((DMA_Channel_TypeDef*) DMA1_Channel4_BASE)
#define DMA1_ch5                        ((DMA_Channel_TypeDef*) DMA1_Channel5_BASE)

#define DMA1_Channel1                   ((DMA_Channel_TypeDef*) DMA1_Channel1_BASE)
#define DMA1_Channel2                   ((DMA_Channel_TypeDef*) DMA1_Channel2_BASE)
#define DMA1_Channel3                   ((DMA_Channel_TypeDef*) DMA1_Channel3_BASE)
#define DMA1_Channel4                   ((DMA_Channel_TypeDef*) DMA1_Channel4_BASE)
#define DMA1_Channel5                   ((DMA_Channel_TypeDef*) DMA1_Channel5_BASE)

////////////////////////////////////////////////////////////////////////////////
/// @brief DMA_ISR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DMA_ISR_GIF1_Pos                (0)
#define DMA_ISR_GIF1                    (0x01U << DMA_ISR_GIF1_Pos)             ///< Channel 1 Global interrupt flag
#define DMA_ISR_TCIF1_Pos               (1)
#define DMA_ISR_TCIF1                   (0x01U << DMA_ISR_TCIF1_Pos)            ///< Channel 1 Transfer Complete flag
#define DMA_ISR_HTIF1_Pos               (2)
#define DMA_ISR_HTIF1                   (0x01U << DMA_ISR_HTIF1_Pos)            ///< Channel 1 Half Transfer flag
#define DMA_ISR_TEIF1_Pos               (3)
#define DMA_ISR_TEIF1                   (0x01U << DMA_ISR_TEIF1_Pos)            ///< Channel 1 Transfer Error flag
#define DMA_ISR_GIF2_Pos                (4)
#define DMA_ISR_GIF2                    (0x01U << DMA_ISR_GIF2_Pos)             ///< Channel 2 Global interrupt flag
#define DMA_ISR_TCIF2_Pos               (5)
#define DMA_ISR_TCIF2                   (0x01U << DMA_ISR_TCIF2_Pos)            ///< Channel 2 Transfer Complete flag
#define DMA_ISR_HTIF2_Pos               (6)
#define DMA_ISR_HTIF2                   (0x01U << DMA_ISR_HTIF2_Pos)            ///< Channel 2 Half Transfer flag
#define DMA_ISR_TEIF2_Pos               (7)
#define DMA_ISR_TEIF2                   (0x01U << DMA_ISR_TEIF2_Pos)            ///< Channel 2 Transfer Error flag
#define DMA_ISR_GIF3_Pos                (8)
#define DMA_ISR_GIF3                    (0x01U << DMA_ISR_GIF3_Pos)             ///< Channel 3 Global interrupt flag
#define DMA_ISR_TCIF3_Pos               (9)
#define DMA_ISR_TCIF3                   (0x01U << DMA_ISR_TCIF3_Pos)            ///< Channel 3 Transfer Complete flag
#define DMA_ISR_HTIF3_Pos               (10)
#define DMA_ISR_HTIF3                   (0x01U << DMA_ISR_HTIF3_Pos)            ///< Channel 3 Half Transfer flag
#define DMA_ISR_TEIF3_Pos               (11)
#define DMA_ISR_TEIF3                   (0x01U << DMA_ISR_TEIF3_Pos)            ///< Channel 3 Transfer Error flag
#define DMA_ISR_GIF4_Pos                (12)
#define DMA_ISR_GIF4                    (0x01U << DMA_ISR_GIF4_Pos)             ///< Channel 4 Global interrupt flag
#define DMA_ISR_TCIF4_Pos               (13)
#define DMA_ISR_TCIF4                   (0x01U << DMA_ISR_TCIF4_Pos)            ///< Channel 4 Transfer Complete flag
#define DMA_ISR_HTIF4_Pos               (14)
#define DMA_ISR_HTIF4                   (0x01U << DMA_ISR_HTIF4_Pos)            ///< Channel 4 Half Transfer flag
#define DMA_ISR_TEIF4_Pos               (15)
#define DMA_ISR_TEIF4                   (0x01U << DMA_ISR_TEIF4_Pos)            ///< Channel 4 Transfer Error flag
#define DMA_ISR_GIF5_Pos                (16)
#define DMA_ISR_GIF5                    (0x01U << DMA_ISR_GIF5_Pos)             ///< Channel 5 Global interrupt flag
#define DMA_ISR_TCIF5_Pos               (17)
#define DMA_ISR_TCIF5                   (0x01U << DMA_ISR_TCIF5_Pos)            ///< Channel 5 Transfer Complete flag
#define DMA_ISR_HTIF5_Pos               (18)
#define DMA_ISR_HTIF5                   (0x01U << DMA_ISR_HTIF5_Pos)            ///< Channel 5 Half Transfer flag
#define DMA_ISR_TEIF5_Pos               (19)
#define DMA_ISR_TEIF5                   (0x01U << DMA_ISR_TEIF5_Pos)            ///< Channel 5 Transfer Error flag

////////////////////////////////////////////////////////////////////////////////
/// @brief DMA_IFCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DMA_IFCR_CGIF1_Pos              (0)
#define DMA_IFCR_CGIF1                  (0x01U << DMA_IFCR_CGIF1_Pos)           ///< Channel 1 Global interrupt clearr
#define DMA_IFCR_CTCIF1_Pos             (1)
#define DMA_IFCR_CTCIF1                 (0x01U << DMA_IFCR_CTCIF1_Pos)          ///< Channel 1 Transfer Complete clear
#define DMA_IFCR_CHTIF1_Pos             (2)
#define DMA_IFCR_CHTIF1                 (0x01U << DMA_IFCR_CHTIF1_Pos)          ///< Channel 1 Half Transfer clear
#define DMA_IFCR_CTEIF1_Pos             (3)
#define DMA_IFCR_CTEIF1                 (0x01U << DMA_IFCR_CTEIF1_Pos)          ///< Channel 1 Transfer Error clear
#define DMA_IFCR_CGIF2_Pos              (4)
#define DMA_IFCR_CGIF2                  (0x01U << DMA_IFCR_CGIF2_Pos)           ///< Channel 2 Global interrupt clear
#define DMA_IFCR_CTCIF2_Pos             (5)
#define DMA_IFCR_CTCIF2                 (0x01U << DMA_IFCR_CTCIF2_Pos)          ///< Channel 2 Transfer Complete clear
#define DMA_IFCR_CHTIF2_Pos             (6)
#define DMA_IFCR_CHTIF2                 (0x01U << DMA_IFCR_CHTIF2_Pos)          ///< Channel 2 Half Transfer clear
#define DMA_IFCR_CTEIF2_Pos             (7)
#define DMA_IFCR_CTEIF2                 (0x01U << DMA_IFCR_CTEIF2_Pos)          ///< Channel 2 Transfer Error clear
#define DMA_IFCR_CGIF3_Pos              (8)
#define DMA_IFCR_CGIF3                  (0x01U << DMA_IFCR_CGIF3_Pos)           ///< Channel 3 Global interrupt clear
#define DMA_IFCR_CTCIF3_Pos             (9)
#define DMA_IFCR_CTCIF3                 (0x01U << DMA_IFCR_CTCIF3_Pos)          ///< Channel 3 Transfer Complete clear
#define DMA_IFCR_CHTIF3_Pos             (10)
#define DMA_IFCR_CHTIF3                 (0x01U << DMA_IFCR_CHTIF3_Pos)          ///< Channel 3 Half Transfer clear
#define DMA_IFCR_CTEIF3_Pos             (11)
#define DMA_IFCR_CTEIF3                 (0x01U << DMA_IFCR_CTEIF3_Pos)          ///< Channel 3 Transfer Error clear
#define DMA_IFCR_CGIF4_Pos              (12)
#define DMA_IFCR_CGIF4                  (0x01U << DMA_IFCR_CGIF4_Pos)           ///< Channel 4 Global interrupt clear
#define DMA_IFCR_CTCIF4_Pos             (13)
#define DMA_IFCR_CTCIF4                 (0x01U << DMA_IFCR_CTCIF4_Pos)          ///< Channel 4 Transfer Complete clear
#define DMA_IFCR_CHTIF4_Pos             (14)
#define DMA_IFCR_CHTIF4                 (0x01U << DMA_IFCR_CHTIF4_Pos)          ///< Channel 4 Half Transfer clear
#define DMA_IFCR_CTEIF4_Pos             (15)
#define DMA_IFCR_CTEIF4                 (0x01U << DMA_IFCR_CTEIF4_Pos)          ///< Channel 4 Transfer Error clear
#define DMA_IFCR_CGIF5_Pos              (16)
#define DMA_IFCR_CGIF5                  (0x01U << DMA_IFCR_CGIF5_Pos)           ///< Channel 5 Global interrupt clear
#define DMA_IFCR_CTCIF5_Pos             (17)
#define DMA_IFCR_CTCIF5                 (0x01U << DMA_IFCR_CTCIF5_Pos)          ///< Channel 5 Transfer Complete clear
#define DMA_IFCR_CHTIF5_Pos             (18)
#define DMA_IFCR_CHTIF5                 (0x01U << DMA_IFCR_CHTIF5_Pos)          ///< Channel 5 Half Transfer clear
#define DMA_IFCR_CTEIF5_Pos             (19)
#define DMA_IFCR_CTEIF5                 (0x01U << DMA_IFCR_CTEIF5_Pos)          ///< Channel 5 Transfer Error clear

////////////////////////////////////////////////////////////////////////////////
/// @brief DMA_CCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DMA_CCR_EN_Pos                  (0)
#define DMA_CCR_EN                      (0x01U << DMA_CCR_EN_Pos)               ///< Channel enabl
#define DMA_CCR_TCIE_Pos                (1)
#define DMA_CCR_TCIE                    (0x01U << DMA_CCR_TCIE_Pos)             ///< Transfer complete interrupt enable
#define DMA_CCR_HTIE_Pos                (2)
#define DMA_CCR_HTIE                    (0x01U << DMA_CCR_HTIE_Pos)             ///< Half Transfer interrupt enable
#define DMA_CCR_TEIE_Pos                (3)
#define DMA_CCR_TEIE                    (0x01U << DMA_CCR_TEIE_Pos)             ///< Transfer error interrupt enable
#define DMA_CCR_DIR_Pos                 (4)
#define DMA_CCR_DIR                     (0x01U << DMA_CCR_DIR_Pos)              ///< Data transfer direction
#define DMA_CCR_CIRC_Pos                (5)
#define DMA_CCR_CIRC                    (0x01U << DMA_CCR_CIRC_Pos)             ///< Circular mode
#define DMA_CCR_PINC_Pos                (6)
#define DMA_CCR_PINC                    (0x01U << DMA_CCR_PINC_Pos)             ///< Peripheral increment mode
#define DMA_CCR_MINC_Pos                (7)
#define DMA_CCR_MINC                    (0x01U << DMA_CCR_MINC_Pos)             ///< Memory increment mode

#define DMA_CCR_PSIZE_Pos               (8)
#define DMA_CCR_PSIZE                   (0x03U << DMA_CCR_PSIZE_Pos)            ///< PSIZE[1:0] bits (Peripheral size)
#define DMA_CCR_PSIZE_0                 (0x01U << DMA_CCR_PSIZE_Pos)            ///< Bit0
#define DMA_CCR_PSIZE_1                 (0x02U << DMA_CCR_PSIZE_Pos)            ///< Bit1

#define DMA_CCR_PSIZE_BYTE              (0x00U << DMA_CCR_PSIZE_Pos)            ///< DMA Peripheral Data Size Byte
#define DMA_CCR_PSIZE_HALFWORD          (0x01U << DMA_CCR_PSIZE_Pos)            ///< DMA Peripheral Data Size HalfWord
#define DMA_CCR_PSIZE_WORD              (0x02U << DMA_CCR_PSIZE_Pos)            ///< DMA Peripheral Data Size Word

#define DMA_CCR_MSIZE_Pos               (10)
#define DMA_CCR_MSIZE                   (0x03U << DMA_CCR_MSIZE_Pos)            ///< MSIZE[1:0] bits (Memory size)
#define DMA_CCR_MSIZE_0                 (0x01U << DMA_CCR_MSIZE_Pos)            ///< Bit0
#define DMA_CCR_MSIZE_1                 (0x02U << DMA_CCR_MSIZE_Pos)            ///< Bit1

#define DMA_CCR_MSIZE_BYTE              (0x00U << DMA_CCR_MSIZE_Pos)            ///< DMA Memory Data Size Byte
#define DMA_CCR_MSIZE_HALFWORD          (0x01U << DMA_CCR_MSIZE_Pos)            ///< DMA Memory Data Size HalfWord
#define DMA_CCR_MSIZE_WORD              (0x02U << DMA_CCR_MSIZE_Pos)            ///< DMA Memory Data Size Word

#define DMA_CCR_PL_Pos                  (12)
#define DMA_CCR_PL                      (0x03U << DMA_CCR_PL_Pos)               ///< PL[1:0] bits(Channel Priority level)
#define DMA_CCR_PL_0                    (0x01U << DMA_CCR_PL_Pos)               ///< Bit0
#define DMA_CCR_PL_1                    (0x02U << DMA_CCR_PL_Pos)               ///< Bit1

#define DMA_CCR_PL_Low                  (0x00U << DMA_CCR_PL_Pos)               ///< DMA Priority Low
#define DMA_CCR_PL_Medium               (0x01U << DMA_CCR_PL_Pos)               ///< DMA Priority Medium
#define DMA_CCR_PL_High                 (0x02U << DMA_CCR_PL_Pos)               ///< DMA Priority High
#define DMA_CCR_PL_VeryHigh             (0x03U << DMA_CCR_PL_Pos)               ///< DMA Priority VeryHigh
#define DMA_CCR_M2M_Pos                 (14)
#define DMA_CCR_M2M                     (0x01U << DMA_CCR_M2M_Pos)              ///< Memory to memory mode

#define DMA_CCR_ARE_Pos                 (15)
#define DMA_CCR_ARE                     (0x01U << DMA_CCR_ARE_Pos)              ///< Auto-Reload Enable bit

////////////////////////////////////////////////////////////////////////////////
/// @brief DMA_CNDTR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DMA_CNDTR_NDT_Pos               (0)
#define DMA_CNDTR_NDT                   (0xFFFFU << DMA_CNDTR_NDT_Pos)          ///< Number of data to Transfer

////////////////////////////////////////////////////////////////////////////////
/// @brief DMA_CPAR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DMA_CPAR_PA_Pos                 (0)
#define DMA_CPAR_PA                     (0xFFFFFFFFU << DMA_CPAR_PA_Pos)        ///< Peripheral Address

////////////////////////////////////////////////////////////////////////////////
/// @brief DMA_CMAR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define DMA_CMAR_MA_Pos                 (0)
#define DMA_CMAR_MA                     (0xFFFFFFFFU << DMA_CMAR_MA_Pos)        ///< Peripheral Address

/// @}

/// @}

/// @}

#ifdef __cplusplus
}
#endif

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
