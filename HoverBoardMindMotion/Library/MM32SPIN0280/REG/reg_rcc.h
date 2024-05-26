////////////////////////////////////////////////////////////////////////////////
/// @file     reg_rcc.h
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

#ifndef __REG_RCC_H
#define __REG_RCC_H

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
/// @brief RCC Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_BASE                        (AHBPERIPH_BASE + 0x1000)               ///< Base Address: 0x40021000

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 CR;                                                                ///< Control Register                               offset: 0x00
    __IO u32 CFGR;                                                              ///< Configuration Register                         offset: 0x04
    __IO u32 CIR;                                                               ///< Clock Interrupt Register                       offset: 0x08
    __IO u32 APB2RSTR;                                                          ///< Advanced Peripheral Bus 2 Reset Register       offset: 0x0C
    __IO u32 APB1RSTR;                                                          ///< Advanced Peripheral Bus 1 Reset Register       offset: 0x10
    __IO u32 AHBENR;                                                            ///< Advanced High Performance Bus Enable Register  offset: 0x14
    __IO u32 APB2ENR;                                                           ///< Advanced Peripheral Bus 2 Enable Register      offset: 0x18
    __IO u32 APB1ENR;                                                           ///< Advanced Peripheral Bus 1 Enable Register      offset: 0x1C
    __IO u32 BDCR;                                                              ///< Backup Domain Control Register                 offset: 0x20
    __IO u32 CSR;                                                               ///< Control Status Register                        offset: 0x24
    __IO u32 AHBRSTR;                                                           ///< Advanced High Performance Bus Reset Register   offset: 0x28
    __IO u32 CFGR2;                                                             ///< Advanced High Performance Bus Reset Register   offset: 0x2C
    __IO u32 RESERVEDOFFSET0X30[4];                                             ///< Reserved                                       offset: 0x30 34 38 3C
    __IO u32 SYSCFGR;                                                           ///< System Configuration Register                  offset: 0x40
    __IO u32 HSIDLY;                                                            ///< HSI delay Register                             offset: 0x44
    __IO u32 HSEDLY;                                                            ///< HSE delay Register                             offset: 0x48
    __IO u32 ICSCR;                                                             ///< Internal clock source calibration register     offset: 0x4C
    __IO u32 PLLCFGR;                                                           ///< PLL Configuration Register                     offset: 0x50
} RCC_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC                             ((RCC_TypeDef*) RCC_BASE)

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_CR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_CR_HSION_Pos                (0)
#define RCC_CR_HSION                    (0x01U << RCC_CR_HSION_Pos)             ///< Internal High Speed clock enable

#define RCC_CR_HSIRDY_Pos               (1)
#define RCC_CR_HSIRDY                   (0x01U << RCC_CR_HSIRDY_Pos)            ///< Internal High Speed clock ready flag

#define RCC_CR_LPF_BYP_Pos              (4)
#define RCC_CR_LPF_BYP                  (0x01U << RCC_CR_LPF_BYP_Pos)           ///< LPF_IN direct output
#define RCC_CR_LPF_SEL_Pos              (5)
#define RCC_CR_LPF_SEL                  (0x01U << RCC_CR_LPF_SEL_Pos)           ///< Output after LPF filtering
#define RCC_CR_DEGLITCH_BYP_Pos         (6)
#define RCC_CR_DEGLITCH_BYP             (0x01U << RCC_CR_DEGLITCH_BYP_Pos)      ///< Bypass deburring function
#define RCC_CR_DEGLITCH_SEL_Pos         (7)
#define RCC_CR_DEGLITCH_SEL             (0x01U << RCC_CR_DEGLITCH_SEL_Pos)      ///< Deburring width 5nS
#define RCC_CR_HSE_OUTPUTSEL_Pos        (8)
#define RCC_CR_HSE_OUTPUTSEL            (0x01U << RCC_CR_HSE_OUTPUTSEL_Pos)     ///< Filtered output

#define RCC_CR_HSEON_Pos                (16)
#define RCC_CR_HSEON                    (0x01U << RCC_CR_HSEON_Pos)             ///< External High Speed clock enable
#define RCC_CR_HSERDY_Pos               (17)
#define RCC_CR_HSERDY                   (0x01U << RCC_CR_HSERDY_Pos)            ///< External High Speed clock ready flag
#define RCC_CR_HSEBYP_Pos               (18)
#define RCC_CR_HSEBYP                   (0x01U << RCC_CR_HSEBYP_Pos)            ///< External High Speed clock Bypass
#define RCC_CR_CSSON_Pos                (19)
#define RCC_CR_CSSON                    (0x01U << RCC_CR_CSSON_Pos)             ///< Clock Security System enable

#define RCC_CR_PLLON_Pos                (24)
#define RCC_CR_PLLON                    (0x01U << RCC_CR_PLLON_Pos)             ///< PLL enable
#define RCC_CR_PLLRDY_Pos               (25)
#define RCC_CR_PLLRDY                   (0x01U << RCC_CR_PLLRDY_Pos)            ///< PLL clock ready flag
////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_CFGR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_CFGR_SW_Pos                 (0)
#define RCC_CFGR_SW                     (0x03U << RCC_CFGR_SW_Pos)              ///< SW[1:0] bits (System clock Switch)
#define RCC_CFGR_SW_HSI                 (0x00U << RCC_CFGR_SW_Pos)              ///< HSI selected as system clock
#define RCC_CFGR_SW_HSE                 (0x01U << RCC_CFGR_SW_Pos)              ///< HSE selected as system clock
#define RCC_CFGR_SW_PLL                 (0x02U << RCC_CFGR_SW_Pos)              ///< PLL selected as system clock
#define RCC_CFGR_SW_LSI                 (0x03U << RCC_CFGR_SW_Pos)              ///< LSI selected as system clock

#define RCC_CFGR_SWS_Pos                (2)
#define RCC_CFGR_SWS                    (0x03U << RCC_CFGR_SWS_Pos)             ///< SWS[1:0] bits (System Clock Switch Status)
#define RCC_CFGR_SWS_HSI                (0x00U << RCC_CFGR_SWS_Pos)             ///< HSI/6 oscillator used as system clock
#define RCC_CFGR_SWS_HSE                (0x01U << RCC_CFGR_SWS_Pos)             ///< HSE oscillator used as system clock
#define RCC_CFGR_SWS_PLL                (0x02U << RCC_CFGR_SWS_Pos)             ///< PLL used as system clock
#define RCC_CFGR_SWS_LSI                (0x03U << RCC_CFGR_SWS_Pos)             ///< LSI used as system clock

#define RCC_CFGR_HPRE_Pos               (4)
#define RCC_CFGR_HPRE                   (0x0FU << RCC_CFGR_HPRE_Pos)            ///< HPRE[3:0] bits (AHB prescaler)
#define RCC_CFGR_PPRE_0                 (0x01U << RCC_CFGR_HPRE_Pos)            ///< Bit 0
#define RCC_CFGR_PPRE_1                 (0x02U << RCC_CFGR_HPRE_Pos)            ///< Bit 1
#define RCC_CFGR_PPRE_2                 (0x04U << RCC_CFGR_HPRE_Pos)            ///< Bit 2
#define RCC_CFGR_PPRE_3                 (0x08U << RCC_CFGR_HPRE_Pos)            ///< Bit 3

#define RCC_CFGR_HPRE_DIV1              (0x00U << RCC_CFGR_HPRE_Pos)            ///< AHB = FCLK = SYSCLK not divided
#define RCC_CFGR_HPRE_DIV2              (0x08U << RCC_CFGR_HPRE_Pos)            ///< AHB = FCLK = SYSCLK divided by 2
#define RCC_CFGR_HPRE_DIV4              (0x09U << RCC_CFGR_HPRE_Pos)            ///< AHB = FCLK = SYSCLK divided by 4
#define RCC_CFGR_HPRE_DIV8              (0x0AU << RCC_CFGR_HPRE_Pos)            ///< AHB = FCLK = SYSCLK divided by 8
#define RCC_CFGR_HPRE_DIV16             (0x0BU << RCC_CFGR_HPRE_Pos)            ///< AHB = FCLK = SYSCLK divided by 16
#define RCC_CFGR_HPRE_DIV64             (0x0CU << RCC_CFGR_HPRE_Pos)            ///< AHB = FCLK = SYSCLK divided by 64
#define RCC_CFGR_HPRE_DIV128            (0x0DU << RCC_CFGR_HPRE_Pos)            ///< AHB = FCLK = SYSCLK divided by 128
#define RCC_CFGR_HPRE_DIV256            (0x0EU << RCC_CFGR_HPRE_Pos)            ///< AHB = FCLK = SYSCLK divided by 256
#define RCC_CFGR_HPRE_DIV512            (0x0FU << RCC_CFGR_HPRE_Pos)            ///< AHB = FCLK = SYSCLK divided by 512

#define RCC_CFGR_PPRE1_Pos              (8)
#define RCC_CFGR_PPRE1                  (0x07U << RCC_CFGR_PPRE1_Pos)           ///< PRE1[2:0] bits (APB1 prescaler)
#define RCC_CFGR_PPRE1_0                (0x01U << RCC_CFGR_PPRE1_Pos)           ///< Bit 0
#define RCC_CFGR_PPRE1_1                (0x02U << RCC_CFGR_PPRE1_Pos)           ///< Bit 1
#define RCC_CFGR_PPRE1_2                (0x04U << RCC_CFGR_PPRE1_Pos)           ///< Bit 2

#define RCC_CFGR_PPRE1_DIV1             (0x00U << RCC_CFGR_PPRE1_Pos)           ///< APB1 = HCLK not divided
#define RCC_CFGR_PPRE1_DIV2             (0x04U << RCC_CFGR_PPRE1_Pos)           ///< APB1 = HCLK divided by 2
#define RCC_CFGR_PPRE1_DIV4             (0x05U << RCC_CFGR_PPRE1_Pos)           ///< APB1 = HCLK divided by 4
#define RCC_CFGR_PPRE1_DIV8             (0x06U << RCC_CFGR_PPRE1_Pos)           ///< APB1 = HCLK divided by 8
#define RCC_CFGR_PPRE1_DIV16            (0x07U << RCC_CFGR_PPRE1_Pos)           ///< APB1 = HCLK divided by 16

#define RCC_CFGR_PPRE2_Pos              (11)
#define RCC_CFGR_PPRE2                  (0x07U << RCC_CFGR_PPRE2_Pos)           ///< PRE2[2:0] bits (APB2 prescaler)
#define RCC_CFGR_PPRE2_0                (0x01U << RCC_CFGR_PPRE2_Pos)           ///< Bit 0
#define RCC_CFGR_PPRE2_1                (0x02U << RCC_CFGR_PPRE2_Pos)           ///< Bit 1
#define RCC_CFGR_PPRE2_2                (0x04U << RCC_CFGR_PPRE2_Pos)           ///< Bit 2

#define RCC_CFGR_PPRE2_DIV1             (0x00U << RCC_CFGR_PPRE2_Pos)           ///< APB2 = HCLK not divided
#define RCC_CFGR_PPRE2_DIV2             (0x04U << RCC_CFGR_PPRE2_Pos)           ///< APB2 = HCLK divided by 2
#define RCC_CFGR_PPRE2_DIV4             (0x05U << RCC_CFGR_PPRE2_Pos)           ///< APB2 = HCLK divided by 4
#define RCC_CFGR_PPRE2_DIV8             (0x06U << RCC_CFGR_PPRE2_Pos)           ///< APB2 = HCLK divided by 8
#define RCC_CFGR_PPRE2_DIV16            (0x07U << RCC_CFGR_PPRE2_Pos)           ///< APB2 = HCLK divided by 16

#define RCC_CFGR_CKOFF_Pos              (14)
#define RCC_CFGR_CKOFF                  (0x01U << RCC_CFGR_CKOFF_Pos)           ///< Disable hardware to turn off the clock automatically

#define RCC_CFGR_MCO_Pos                (24)
#define RCC_CFGR_MCO                    (0x07U << RCC_CFGR_MCO_Pos)             ///< MCO[2:0] bits (Microcontroller Clock Output)
#define RCC_CFGR_MCO_NOCLOCK            (0x00U << RCC_CFGR_MCO_Pos)             ///< No clock
#define RCC_CFGR_MCO_LSI                (0x02U << RCC_CFGR_MCO_Pos)             ///< LSI clock
#define RCC_CFGR_MCO_LSE                (0x03U << RCC_CFGR_MCO_Pos)             ///< LSE clock
#define RCC_CFGR_MCO_SYSCLK             (0x04U << RCC_CFGR_MCO_Pos)             ///< System clock selected
#define RCC_CFGR_MCO_HSI                (0x05U << RCC_CFGR_MCO_Pos)             ///< Internal 48 MHz RC oscillator clock selected
#define RCC_CFGR_MCO_HSE                (0x06U << RCC_CFGR_MCO_Pos)             ///< External 1-25 MHz oscillator clock selected
#define RCC_CFGR_MCO_PLL                (0x07U << RCC_CFGR_MCO_Pos)             ///< PLL clock divided by 2 selected
#define RCC_CFGR_MCO_PLLDIV2            (0x07U << RCC_CFGR_MCO_Pos)             ///< PLL clock divided by 2 selected
////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_CIR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_CIR_LSIRDYF_Pos             (0)
#define RCC_CIR_LSIRDYF                 (0x01U << RCC_CIR_LSIRDYF_Pos)          ///< LSI Ready Interrupt flag

#define RCC_CIR_HSIRDYF_Pos             (2)
#define RCC_CIR_HSIRDYF                 (0x01U << RCC_CIR_HSIRDYF_Pos)          ///< HSI Ready Interrupt flag
#define RCC_CIR_HSERDYF_Pos             (3)
#define RCC_CIR_HSERDYF                 (0x01U << RCC_CIR_HSERDYF_Pos)          ///< HSE Ready Interrupt flag

#define RCC_CIR_PLLRDYF_Pos             (4)
#define RCC_CIR_PLLRDYF                 (0x01U << RCC_CIR_PLLRDYF_Pos)          ///< PLL Ready Interrupt flag

#define RCC_CIR_CSSF_Pos                (7)
#define RCC_CIR_CSSF                    (0x01U << RCC_CIR_CSSF_Pos)             ///< Clock Security System Interrupt flag
#define RCC_CIR_LSIRDYIE_Pos            (8)
#define RCC_CIR_LSIRDYIE                (0x01U << RCC_CIR_LSIRDYIE_Pos)         ///< LSI Ready Interrupt Enable

#define RCC_CIR_HSIRDYIE_Pos            (10)
#define RCC_CIR_HSIRDYIE                (0x01U << RCC_CIR_HSIRDYIE_Pos)         ///< HSI Ready Interrupt Enable
#define RCC_CIR_HSERDYIE_Pos            (11)
#define RCC_CIR_HSERDYIE                (0x01U << RCC_CIR_HSIRDYIE_Pos)         ///< HSE Ready Interrupt Enable

#define RCC_CIR_PLLRDYIE_Pos            (12)
#define RCC_CIR_PLLRDYIE                (0x01U << RCC_CIR_PLLRDYIE_Pos)         ///< PLL Ready Interrupt Enable

#define RCC_CIR_LSIRDYC_Pos             (16)
#define RCC_CIR_LSIRDYC                 (0x01U << RCC_CIR_LSIRDYC_Pos)          ///< LSI Ready Interrupt Clear

#define RCC_CIR_HSIRDYC_Pos             (18)
#define RCC_CIR_HSIRDYC                 (0x01U << RCC_CIR_HSIRDYC_Pos)          ///< HSI Ready Interrupt Clear
#define RCC_CIR_HSERDYC_Pos             (19)
#define RCC_CIR_HSERDYC                 (0x01U << RCC_CIR_HSERDYC_Pos)          ///< HSE Ready Interrupt Clear

#define RCC_CIR_PLLRDYC_Pos             (20)
#define RCC_CIR_PLLRDYC                 (0x01U << RCC_CIR_PLLRDYC_Pos)          ///< PLL Ready Interrupt Clear

#define RCC_CIR_CSSC_Pos                (23)
#define RCC_CIR_CSSC                    (0x01U << RCC_CIR_CSSC_Pos)             ///< Clock Security System Interrupt Clear

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_APB2RSTR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_APB2RSTR_EXTI_Pos           (0)
#define RCC_APB2RSTR_EXTI               (0x01U << RCC_APB2RSTR_EXTI_Pos)        ///< System Configuration register reset
#define RCC_APB2RSTR_SYSCFG_Pos         (0)
#define RCC_APB2RSTR_SYSCFG             (0x01U << RCC_APB2RSTR_SYSCFG_Pos)      ///< System Configuration register reset

#define RCC_APB2RSTR_ADC1_Pos           (9)
#define RCC_APB2RSTR_ADC1               (0x01U << RCC_APB2RSTR_ADC1_Pos)        ///< ADC interface reset
#define RCC_APB2RSTR_ADC2_Pos           (10)
#define RCC_APB2RSTR_ADC2               (0x01U << RCC_APB2RSTR_ADC2_Pos)        ///< ADC interface reset

#define RCC_APB2RSTR_TIM1_Pos           (11)
#define RCC_APB2RSTR_TIM1               (0x01U << RCC_APB2RSTR_TIM1_Pos)        ///< TIM1 Timer reset
#define RCC_APB2RSTR_SPI1_Pos           (12)
#define RCC_APB2RSTR_SPI1               (0x01U << RCC_APB2RSTR_SPI1_Pos)        ///< SPI 1 reset
#define RCC_APB2RSTR_TIM8_Pos           (13)
#define RCC_APB2RSTR_TIM8               (0x01U << RCC_APB2RSTR_TIM8_Pos)        ///< TIM8 Timer reset

#define RCC_APB2RSTR_UART1_Pos          (14)
#define RCC_APB2RSTR_UART1              (0x01U << RCC_APB2RSTR_UART1_Pos)       ///< UART1 reset

#define RCC_APB2RSTR_COMP_Pos           (15)
#define RCC_APB2RSTR_COMP               (0x01U << RCC_APB2RSTR_COMP_Pos)        ///< COMP interface reset
#define RCC_APB2RSTR_OPAMP_Pos          (15)
#define RCC_APB2RSTR_OPAMP              (0x01U << RCC_APB2RSTR_OPAMP_Pos)       ///< OPAMP interface reset
#define RCC_APB2RSTR_TIM14_Pos          (16)
#define RCC_APB2RSTR_TIM14              (0x01U << RCC_APB2RSTR_TIM14_Pos)       ///< TIM14 Timer reset
#define RCC_APB2RSTR_TIM16_Pos          (17)
#define RCC_APB2RSTR_TIM16              (0x01U << RCC_APB2RSTR_TIM16_Pos)       ///< TIM16 Timer reset
#define RCC_APB2RSTR_TIM17_Pos          (18)
#define RCC_APB2RSTR_TIM17              (0x01U << RCC_APB2RSTR_TIM17_Pos)       ///< TIM17 Timer reset
#define RCC_APB2RSTR_DBGMCU_Pos         (22)
#define RCC_APB2RSTR_DBGMCU             (0x01U << RCC_APB2RSTR_DBGMCU_Pos)      ///< DBGMCU reset
#define RCC_APB2RSTR_PWM_Pos            (23)
#define RCC_APB2RSTR_PWM                (0x01U << RCC_APB2RSTR_PWM_Pos)         ///< PWM reset

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_APB1RSTR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_APB1RSTR_TIM2_Pos           (0)
#define RCC_APB1RSTR_TIM2               (0x01U << RCC_APB1RSTR_TIM2_Pos)        ///< Timer 2 reset
#define RCC_APB1RSTR_TIM3_Pos           (1)
#define RCC_APB1RSTR_TIM3               (0x01U << RCC_APB1RSTR_TIM3_Pos)        ///< Timer 3 reset
#define RCC_APB1RSTR_WWDG_Pos           (11)
#define RCC_APB1RSTR_WWDG               (0x01U << RCC_APB1RSTR_WWDG_Pos)        ///< Window Watchdog reset
#define RCC_APB1RSTR_SPI2_Pos           (14)
#define RCC_APB1RSTR_SPI2               (0x01U << RCC_APB1RSTR_SPI2_Pos)        ///< SPI 2 reset
#define RCC_APB1RSTR_UART2_Pos          (17)
#define RCC_APB1RSTR_UART2              (0x01U << RCC_APB1RSTR_UART2_Pos)       ///< UART 2 reset
#define RCC_APB1RSTR_UART3_Pos          (18)
#define RCC_APB1RSTR_UART3              (0x01U << RCC_APB1RSTR_UART3_Pos)       ///< UART 3 reset
#define RCC_APB1RSTR_I2C1_Pos           (21)
#define RCC_APB1RSTR_I2C1               (0x01U << RCC_APB1RSTR_I2C1_Pos)        ///< I2C 1 reset
#define RCC_APB1RSTR_BKP_Pos            (24)
#define RCC_APB1RSTR_BKP                (0x01U << RCC_APB1RSTR_BKP_Pos)         ///< BKP reset
#define RCC_APB1RSTR_CSM_Pos            (26)
#define RCC_APB1RSTR_CSM                (0x01U << RCC_APB1RSTR_CSM_Pos)         ///< CSM reset
#define RCC_APB1RSTR_PWR_Pos            (28)
#define RCC_APB1RSTR_PWR                (0x01U << RCC_APB1RSTR_PWR_Pos)         ///< Power interface reset
#define RCC_APB1RSTR_DAC_Pos            (29)
#define RCC_APB1RSTR_DAC                (0x01U << RCC_APB1RSTR_DAC_Pos)         ///< DAC reset

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_AHBENR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_AHBENR_DMA1_Pos             (0)
#define RCC_AHBENR_DMA1                 (0x01U << RCC_AHBENR_DMA1_Pos)          ///< DMA clock enable
#define RCC_AHBENR_SRAM_Pos             (2)
#define RCC_AHBENR_SRAM                 (0x01U << RCC_AHBENR_SRAM_Pos)          ///< SRAM interface clock enable
#define RCC_AHBENR_FLITF_Pos            (4)
#define RCC_AHBENR_FLITF                (0x01U << RCC_AHBENR_FLITF_Pos)         ///< FLITF clock enable
#define RCC_AHBENR_CRC_Pos              (6)
#define RCC_AHBENR_CRC                  (0x01U << RCC_AHBENR_CRC_Pos)           ///< Internal High Speed clock Calibration
#define RCC_AHBENR_GPIOA_Pos            (17)
#define RCC_AHBENR_GPIOA                (0x01U << RCC_AHBENR_GPIOA_Pos)         ///< GPIOA clock enable
#define RCC_AHBENR_GPIOB_Pos            (18)
#define RCC_AHBENR_GPIOB                (0x01U << RCC_AHBENR_GPIOB_Pos)         ///< GPIOB clock enable
#define RCC_AHBENR_GPIOC_Pos            (19)
#define RCC_AHBENR_GPIOC                (0x01U << RCC_AHBENR_GPIOC_Pos)         ///< GPIOC clock enable
#define RCC_AHBENR_GPIOD_Pos            (20)
#define RCC_AHBENR_GPIOD                (0x01U << RCC_AHBENR_GPIOD_Pos)         ///< GPIOD clock enable
#define RCC_AHBENR_HWSQRT_Pos           (25)
#define RCC_AHBENR_HWSQRT               (0x01U << RCC_AHBENR_HWSQRT_Pos)        ///< HWSQRT clock enable
#define RCC_AHBENR_HWDIV_Pos            (26)
#define RCC_AHBENR_HWDIV                (0x01U << RCC_AHBENR_HWDIV_Pos)         ///< HWDIV clock enable
////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_APB2ENR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_APB2ENR_SYSCFG_Pos          (0)
#define RCC_APB2ENR_SYSCFG              (0x01U << RCC_APB2ENR_SYSCFG_Pos)       ///< SYSCFG Block enable
#define RCC_APB2ENR_ADC1_Pos            (9)
#define RCC_APB2ENR_ADC1                (0x01U << RCC_APB2ENR_ADC1_Pos)         ///< ADC 1 interface clock enable
#define RCC_APB2ENR_ADC2_Pos            (10)
#define RCC_APB2ENR_ADC2                (0x01U << RCC_APB2ENR_ADC2_Pos)         ///< ADC 2 interface clock enable

#define RCC_APB2ENR_TIM1_Pos            (11)
#define RCC_APB2ENR_TIM1                (0x01U << RCC_APB2ENR_TIM1_Pos)         ///< TIM1 Timer clock enable
#define RCC_APB2ENR_SPI1_Pos            (12)
#define RCC_APB2ENR_SPI1                (0x01U << RCC_APB2ENR_SPI1_Pos)         ///< SPI 1 clock enable
#define RCC_APB2ENR_TIM8_Pos            (13)
#define RCC_APB2ENR_TIM8                (0x01U << RCC_APB2ENR_TIM8_Pos)         ///< TIM8 Timer clock enable
#define RCC_APB2ENR_UART1_Pos           (14)
#define RCC_APB2ENR_UART1               (0x01U << RCC_APB2ENR_UART1_Pos)        ///< UART1 clock ena
#define RCC_APB2ENR_COMP_Pos            (15)
#define RCC_APB2ENR_COMP                (0x01U << RCC_APB2ENR_COMP_Pos)         ///< Comparator interface clock enable

#define RCC_APB2ENR_OPAMP_Pos           (15)
#define RCC_APB2ENR_OPAMP               (0x01U << RCC_APB2ENR_OPAMP_Pos)        ///< OPAMP interface clock enable

#define RCC_APB2ENR_TIM14_Pos           (16)
#define RCC_APB2ENR_TIM14               (0x01U << RCC_APB2ENR_TIM14_Pos)        ///< TIM14 Timer clock enable

#define RCC_APB2ENR_TIM16_Pos           (17)
#define RCC_APB2ENR_TIM16               (0x01U << RCC_APB2ENR_TIM16_Pos)        ///< TIM16 Timer clock enable
#define RCC_APB2ENR_TIM17_Pos           (18)
#define RCC_APB2ENR_TIM17               (0x01U << RCC_APB2ENR_TIM17_Pos)        ///< TIM17 Timer clock enable
#define RCC_APB2ENR_DBGMCU_Pos          (22)
#define RCC_APB2ENR_DBGMCU              (0x01U << RCC_APB2ENR_DBGMCU_Pos)       ///< DBGMCU clock enable
#define RCC_APB2ENR_PWM_Pos             (23)
#define RCC_APB2ENR_PWM                 (0x01U << RCC_APB2ENR_PWM_Pos)       ///< PWM clock enable

#define RCC_APB2ENR_EXTI_Pos            (29)
#define RCC_APB2ENR_EXTI                (0x01U << RCC_APB2ENR_EXTI_Pos)         ///< EXTI Block enable

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_APB1ENR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_APB1ENR_TIM2_Pos            (0)
#define RCC_APB1ENR_TIM2                (0x01U << RCC_APB1ENR_TIM2_Pos)         ///< Timer 2 clock enable
#define RCC_APB1ENR_TIM3_Pos            (1)
#define RCC_APB1ENR_TIM3                (0x01U << RCC_APB1ENR_TIM3_Pos)         ///< Timer 3 clock enabled
#define RCC_APB1ENR_WWDG_Pos            (11)
#define RCC_APB1ENR_WWDG                (0x01U << RCC_APB1ENR_WWDG_Pos)         ///< Window Watchdog clock enable
#define RCC_APB1ENR_SPI2_Pos            (14)
#define RCC_APB1ENR_SPI2                (0x01U << RCC_APB1ENR_SPI2_Pos)         ///< SPI 2 clock enable
#define RCC_APB1ENR_UART2_Pos           (17)
#define RCC_APB1ENR_UART2               (0x01U << RCC_APB1ENR_UART2_Pos)        ///< UART 2 clock enable
#define RCC_APB1ENR_UART3_Pos           (18)
#define RCC_APB1ENR_UART3               (0x01U << RCC_APB1ENR_UART3_Pos)        ///< UART 3 clock enable
#define RCC_APB1ENR_I2C1_Pos            (21)
#define RCC_APB1ENR_I2C1                (0x01U << RCC_APB1ENR_I2C1_Pos)         ///< I2C 1 clock enable
#define RCC_APB1ENR_BKP_Pos             (24)
#define RCC_APB1ENR_BKP                 (0x01U << RCC_APB1ENR_BKP_Pos)          ///< BKP clock enable
#define RCC_APB1ENR_CSM_Pos             (26)
#define RCC_APB1ENR_CSM                 (0x01U << RCC_APB1ENR_CSM_Pos)          ///< CSM clock enable
#define RCC_APB1ENR_PWR_Pos             (28)
#define RCC_APB1ENR_PWR                 (0x01U << RCC_APB1ENR_PWR_Pos)          ///< Power interface clock enable
#define RCC_APB1ENR_DAC_Pos             (29)
#define RCC_APB1ENR_DAC                 (0x01U << RCC_APB1ENR_DAC_Pos)          ///< DAC interface clock enable
#define RCC_APB1ENR_IWDG_Pos            (30)
#define RCC_APB1ENR_IWDG                (0x01U << RCC_APB1ENR_IWDG_Pos)          ///< IWDG interface clock enable

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_BDCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_BDCR_BDRST_Pos              (16)
#define RCC_BDCR_BDRST                  (0x01U << RCC_BDCR_BDRST_Pos)           ///< Backup domain software reset

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_CSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_CSR_LSION_Pos               (0)
#define RCC_CSR_LSION                   (0x01U << RCC_CSR_LSION_Pos)            ///< Internal Low Speed oscillator enable
#define RCC_CSR_LSIRDY_Pos              (1)
#define RCC_CSR_LSIRDY                  (0x01U << RCC_CSR_LSIRDY_Pos)           ///< Internal Low Speed oscillator Ready
#define RCC_CSR_PVD_Pos                 (6)
#define RCC_CSR_PVD                     (0x01U << RCC_CSR_PVD_Pos)              ///< PVD reset enable
#define RCC_CSR_LOCK_Pos                (7)
#define RCC_CSR_LOCK                    (0x01U << RCC_CSR_LOCK_Pos)             ///< CPU LOCK reset enable
#define RCC_CSR_VDT_RSTN_Pos            (8)
#define RCC_CSR_VDT_RSTN                (0x01U << RCC_CSR_VDT_RSTN_Pos)         ///< VDT reset enable
#define RCC_CSR_VDTRSTF_Pos             (21)
#define RCC_CSR_VDTRSTF                 (0x01U << RCC_CSR_VDTRSTF_Pos)          ///< VDT reset flag
#define RCC_CSR_PVDRSTF_Pos             (22)
#define RCC_CSR_PVDRSTF                 (0x01U << RCC_CSR_PVDRSTF_Pos)          ///< PVD reset flag
#define RCC_CSR_LOCKUPF_Pos             (23)
#define RCC_CSR_LOCKUPF                 (0x01U << RCC_CSR_LOCKUPF_Pos)          ///< CPU lockup reset flag

#define RCC_CSR_RMVF_Pos                (24)
#define RCC_CSR_RMVF                    (0x01U << RCC_CSR_RMVF_Pos)             ///< Remove reset flag
#define RCC_CSR_PINRSTF_Pos             (26)
#define RCC_CSR_PINRSTF                 (0x01U << RCC_CSR_PINRSTF_Pos)          ///< PIN reset flag

#define RCC_CSR_PORRSTF_Pos             (27)
#define RCC_CSR_PORRSTF                 (0x01U << RCC_CSR_PORRSTF_Pos)          ///< POR/PDR reset flag

#define RCC_CSR_SFTRSTF_Pos             (28)
#define RCC_CSR_SFTRSTF                 (0x01U << RCC_CSR_SFTRSTF_Pos)          ///< Software Reset flag

#define RCC_CSR_IWDGRSTF_Pos            (29)
#define RCC_CSR_IWDGRSTF                (0x01U << RCC_CSR_IWDGRSTF_Pos)         ///< Independent Watchdog reset flag

#define RCC_CSR_WWDGRSTF_Pos            (30)
#define RCC_CSR_WWDGRSTF                (0x01U << RCC_CSR_WWDGRSTF_Pos)         ///< Window watchdog reset flag
#define RCC_CSR_LPWRRSTF_Pos            (31)
#define RCC_CSR_LPWRRSTF                (0x01U << RCC_CSR_LPWRRSTF_Pos)         ///< Low power reset flag

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_AHBRSTR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_AHBRSTR_DMA1_Pos            (0)
#define RCC_AHBRSTR_DMA1                (0x01U << RCC_AHBRSTR_DMA1_Pos)         ///< DMA clock reset
#define RCC_AHBRSTR_CRC_Pos             (6)
#define RCC_AHBRSTR_CRC                 (0x01U << RCC_AHBRSTR_CRC_Pos)          ///< Internal High Speed clock Calibration
#define RCC_AHBRSTR_GPIOA_Pos           (17)
#define RCC_AHBRSTR_GPIOA               (0x01U << RCC_AHBRSTR_GPIOA_Pos)        ///< GPIOA clock reset
#define RCC_AHBRSTR_GPIOB_Pos           (18)
#define RCC_AHBRSTR_GPIOB               (0x01U << RCC_AHBRSTR_GPIOB_Pos)        ///< GPIOB clock reset
#define RCC_AHBRSTR_GPIOC_Pos           (19)
#define RCC_AHBRSTR_GPIOC               (0x01U << RCC_AHBRSTR_GPIOC_Pos)        ///< GPIOC clock reset
#define RCC_AHBRSTR_GPIOD_Pos           (20)
#define RCC_AHBRSTR_GPIOD               (0x01U << RCC_AHBRSTR_GPIOD_Pos)        ///< GPIOD clock reset
#define RCC_AHBRSTR_HWSQRT_Pos           (25)
#define RCC_AHBRSTR_HWSQRT               (0x01U << RCC_AHBRSTR_HWSQRT_Pos)      ///< HWSQRT clock reset
#define RCC_AHBRSTR_HWDIV_Pos           (26)
#define RCC_AHBRSTR_HWDIV               (0x01U << RCC_AHBRSTR_HWDIV_Pos)        ///< HWDIV clock reset

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_CFGR2 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////

#define RCC_CFGR2_MCO_PRE_Pos           (20)
#define RCC_CFGR2_MCO_PRE_1             (0x00U << RCC_CFGR2_MCO_PRE_Pos)        ///< MCO 1 frequency division
#define RCC_CFGR2_MCO_PRE_2             (0x08U << RCC_CFGR2_MCO_PRE_Pos)        ///< MCO 2 frequency division
#define RCC_CFGR2_MCO_PRE_4             (0x09U << RCC_CFGR2_MCO_PRE_Pos)        ///< MCO 4   frequency division
#define RCC_CFGR2_MCO_PRE_8             (0x0AU << RCC_CFGR2_MCO_PRE_Pos)        ///< MCO 8   frequency division
#define RCC_CFGR2_MCO_PRE_16            (0x0BU << RCC_CFGR2_MCO_PRE_Pos)        ///< MCO 16  frequency division
#define RCC_CFGR2_MCO_PRE_64            (0x0CU << RCC_CFGR2_MCO_PRE_Pos)        ///< MCO 64  frequency division
#define RCC_CFGR2_MCO_PRE_128           (0x0DU << RCC_CFGR2_MCO_PRE_Pos)        ///< MCO 128 frequency division
#define RCC_CFGR2_MCO_PRE_256           (0x0EU << RCC_CFGR2_MCO_PRE_Pos)        ///< MCO 256 frequency division

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_SYSCFG Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_SYSCFG_PROGCHECKEN_Pos      (0)
#define RCC_SYSCFG_PROGCHECKEN          (0x01U << RCC_SYSCFG_PROGCHECKEN_Pos)   ///< Whether to check the number in Flash when writing to Flash
#define RCC_SYSCFG_PAGESIZE_Pos         (1)
#define RCC_SYSCFG_PAGESIZE             (0x01U << RCC_SYSCFG_PAGESIZE_Pos)      ///< Flash Page size
#define RCC_SYSCFG_OSC_RTRIM_Pos        (8)
#define RCC_SYSCFG_OSC_RTRIM            (0x03U << RCC_SYSCFG_OSC_RTRIM_Pos)     ///< Oscillator feedback resistance trimming
#define RCC_SYSCFG_RFB_SEL_Pos          (8)
#define RCC_SYSCFG_RFB_SEL_0            (0x00U << RCC_SYSCFG_RFB_SEL_Pos)     ///< Feedback resistance select 2M
#define RCC_SYSCFG_RFB_SEL_1            (0x01U << RCC_SYSCFG_RFB_SEL_Pos)     ///< Feedback resistance select 1M
#define RCC_SYSCFG_RFB_SEL_2            (0x02U << RCC_SYSCFG_RFB_SEL_Pos)     ///< Feedback resistance select 500K
#define RCC_SYSCFG_RFB_SEL_3            (0x03U << RCC_SYSCFG_RFB_SEL_Pos)     ///< Feedback resistance select 200K
#define RCC_SYSCFG_OSC_LPFEN_Pos        (14)
#define RCC_SYSCFG_OSC_LPFEN            (0x01U << RCC_SYSCFG_OSC_LPFEN_Pos)     ///< Oscillator low pass filtering enable
#define RCC_CONFIG_PAGESIZE_Pos         RCC_SYSCFG_PAGESIZE_Pos
#define RCC_CONFIG_PAGESIZE             RCC_SYSCFG_PAGESIZE
#define RCC_CONFIG_OSC_RTRIM_Pos        RCC_SYSCFG_OSC_RTRIM_Pos
#define RCC_CONFIG_OSC_RTRIM            RCC_SYSCFG_OSC_RTRIM
#define RCC_CONFIG_OSC_LPFEN_Pos        RCC_SYSCFG_OSC_LPFEN_Pos
#define RCC_CONFIG_OSC_LPFEN            RCC_SYSCFG_OSC_LPFEN
////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_HSIDLY Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_HSIDLY_Pos                  (0)
#define RCC_HSIDLY                      (0xFFU << RCC_HSIDLY_Pos)               ///< HSI delay count value
////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_HSEDLY Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_HSEDLY_Pos                  (0)
#define RCC_HSEDLY                      (0xFFFFU << RCC_HSEDLY_Pos)             ///< HSE delay count value
////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_ICSCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_ICSCR_HSICALSEL_Pos         (11)
#define RCC_ICSCR_HSICALSEL             (0x1FU << RCC_ICSCR_HSICALSEL_Pos)      ///< Select the value of register HSICAL
#define RCC_ICSCR_HSICALSFT_Pos         (16)
#define RCC_ICSCR_HSICALSFT             (0x1FU << RCC_ICSCR_HSICALSFT_Pos)      ///< Select the value of register HSICAL

////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_PLLCFGR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_PLLCFGR_PLLSRC_Pos          (0)
#define RCC_PLLCFGR_PLLSRC              (0x01U << RCC_PLLCFGR_PLLSRC_Pos)       ///< HSE as PLL entry clock
#define RCC_PLLCFGR_PLLXTPRE_Pos        (1)
#define RCC_PLLCFGR_PLLXTPRE            (0x01U << RCC_PLLCFGR_PLLXTPRE_Pos)     ///< HSE frequency division for PLL entry
#define RCC_PLLCFGR_PLL_ICTRL_Pos       (2)
#define RCC_PLLCFGR_PLL_ICTRL           (0x03U << RCC_PLLCFGR_PLL_ICTRL_Pos)    ///< PLL CP current control signals mask
#define RCC_PLLCFGR_PLL_ICTRL_0         (0x00U << RCC_PLLCFGR_PLL_ICTRL_Pos)    ///< PLL CP current control signals 2.5u
#define RCC_PLLCFGR_PLL_ICTRL_1         (0x01U << RCC_PLLCFGR_PLL_ICTRL_Pos)    ///< PLL CP current control signals 5u
#define RCC_PLLCFGR_PLL_ICTRL_2         (0x02U << RCC_PLLCFGR_PLL_ICTRL_Pos)    ///< PLL CP current control signals 7.5u
#define RCC_PLLCFGR_PLL_ICTRL_3         (0x03U << RCC_PLLCFGR_PLL_ICTRL_Pos)    ///< PLL CP current control signals 10u
#define RCC_PLLCFGR_PLL_ICTRL_2_5       (0x00U << RCC_PLLCFGR_PLL_ICTRL_Pos)    ///< PLL CP current control signals 2.5u
#define RCC_PLLCFGR_PLL_ICTRL_5         (0x01U << RCC_PLLCFGR_PLL_ICTRL_Pos)    ///< PLL CP current control signals 5u
#define RCC_PLLCFGR_PLL_ICTRL_7_5       (0x02U << RCC_PLLCFGR_PLL_ICTRL_Pos)    ///< PLL CP current control signals 7.5u
#define RCC_PLLCFGR_PLL_ICTRL_10        (0x03U << RCC_PLLCFGR_PLL_ICTRL_Pos)    ///< PLL CP current control signals 10u
#define RCC_PLLCFGR_PLL_LDS_Pos         (4)
#define RCC_PLLCFGR_PLL_LDS             (0x03U << RCC_PLLCFGR_PLL_LDS_Pos)      ///< PLL LOCK DETECTOR ACCURACY SELECT
#define RCC_PLLCFGR_PLL_LDS_0           (0x00U << RCC_PLLCFGR_PLL_LDS_Pos)      ///< PLL LOCK DETECTOR ACCURACY value = 0
#define RCC_PLLCFGR_PLL_LDS_1           (0x01U << RCC_PLLCFGR_PLL_LDS_Pos)      ///< PLL LOCK DETECTOR ACCURACY value = 1
#define RCC_PLLCFGR_PLL_LDS_2           (0x02U << RCC_PLLCFGR_PLL_LDS_Pos)      ///< PLL LOCK DETECTOR ACCURACY value = 2
#define RCC_PLLCFGR_PLL_LDS_3           (0x03U << RCC_PLLCFGR_PLL_LDS_Pos)      ///< PLL LOCK DETECTOR ACCURACY value = 3
#define RCC_PLLCFGR_PLL_DP_Pos          (8)
#define RCC_PLLCFGR_PLL_DP              (0x07U << RCC_PLLCFGR_PLL_DP_Pos)       ///< PLL DP
#define RCC_PLLCFGR_PLL_DN_Pos          (16)
#define RCC_PLLCFGR_PLL_DN              (0xFFU << RCC_PLLCFGR_PLL_DN_Pos)       ///< PLL DN
#define RCC_PLLCFGR_PLL_DM_Pos          (29)
#define RCC_PLLCFGR_PLL_DM              (0x07U << RCC_PLLCFGR_PLL_DM_Pos)       ///< PLL DM
////////////////////////////////////////////////////////////////////////////////
/// @brief RCC_PLLDLY Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define RCC_PLLDLY_EQU_CNT_Pos          (0)
#define RCC_PLLDLY_EQU_CNT              (0x03FFU << RCC_PLLDLY_EQU_CNT_Pos)       ///< PLL delay time

/// @}

/// @}

/// @}

#ifdef __cplusplus
}
#endif

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
