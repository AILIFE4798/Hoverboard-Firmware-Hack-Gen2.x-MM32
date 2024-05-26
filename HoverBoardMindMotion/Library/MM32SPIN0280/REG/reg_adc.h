////////////////////////////////////////////////////////////////////////////////
/// @file     reg_adc.h
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

#ifndef __REG_ADC_H
#define __REG_ADC_H

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
/// @brief ADC Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC1_BASE                       (APB2PERIPH_BASE + 0x2400)              ///< Base Address: 0x40012400
#define ADC2_BASE                       (APB2PERIPH_BASE + 0x2800)              ///< Base Address: 0x40012800

#define ADC_VOLTAGE_REF_BASE            (0x1FFFF7E0U)                           ///< Voltage Reference base address(Half Word)
#define ADC_TEMPERATURE_BASE            (0x1FFFF7F6U)                           ///< Temperature base address(Half Word)
#define ADC_AVG_SLOPE_VALUE             (4.955)                                 ///< Temperature Avg_Slope value
// T(C) = (Vsense - V25) / Avg_Slope + 25
// V25: Vsense value for 25C
// T(C) = (Value * Vdda - offset * 3300) / (4096 * Avg_slope) + 25
// offset = (M16(ADC_TEMPERATURE_BASE)
// Vsense: current output voltage of the temperature sensor
// Vsense = Value * Vdda /4096 (Value is the converted result data of ADC)
// Avg_Slope: Average Slope for curve between Temperature vs. Vsense (given in mV/C or uV/C)
// Refer to the Temperature Sensor section for the actual values of V25 and Avg_Slope.
// Vref Fomula  (VREFoffset/4096) * 3.3V = (Value/4096)* VDDA
// VDDA = (VREFoffset/Value) * 3.3

////////////////////////////////////////////////////////////////////////////////
/// @brief Analog-to-Digital Converter register
////////////////////////////////////////////////////////////////////////////////

typedef struct {
    union {
        __IO u32 DR;                                                            ///< ADC data register,                             offset: 0x00
        __IO u32 ADDATA;
    };
    union {
        __IO u32 CFGR;                                                          ///< ADC configuration register,                    offset: 0x04
        __IO u32 ADCFG;
    };
    union {
        __IO u32 CR;                                                            ///< ADC control register,                          offset: 0x08
        __IO u32 ADCR;
    };
    union {
        __IO u32 CHSR;                                                          ///< ADC channel selection register,                offset: 0x0C
        __IO u32 ADCHS;
    };
    union {
        __IO u32 CMPR;                                                          ///< ADC window compare register,                   offset: 0x10
        __IO u32 ADCMPR;
    };
    union {
        __IO u32 SR;                                                            ///< ADC status register,                           offset: 0x14
        __IO u32 ADSTA;
    };
    union {
        __IO u32 CH0DR;                                                         ///< ADC channel0 data register,                    offset: 0x18
        __IO u32 ADDR0;
    };
    union {
        __IO u32 CH1DR;                                                         ///< ADC channel1 data register,                    offset: 0x1C
        __IO u32 ADDR1;
    };
    union {
        __IO u32 CH2DR;                                                         ///< ADC channel2 data register,                    offset: 0x20
        __IO u32 ADDR2;
    };
    union {
        __IO u32 CH3DR;                                                         ///< ADC channel3 data register,                    offset: 0x24
        __IO u32 ADDR3;
    };
    union {
        __IO u32 CH4DR;                                                         ///< ADC channel4 data register,                    offset: 0x28
        __IO u32 ADDR4;
    };
    union {
        __IO u32 CH5DR;                                                         ///< ADC channel5 data register,                    offset: 0x2C
        __IO u32 ADDR5;
    };
    union {
        __IO u32 CH6DR;                                                         ///< ADC channel6 data register,                    offset: 0x30
        __IO u32 ADDR6;
    };
    union {
        __IO u32 CH7DR;                                                         ///< ADC channel7 data register,                    offset: 0x34
        __IO u32 ADDR7;
    };
    union {
        __IO u32 CH8DR;                                                         ///< ADC channel8 data register,                    offset: 0x38
        __IO u32 ADDR8;
    };
    union {
        __IO u32 CH9DR;                                                         ///< ADC channel9 data register,                    offset: 0x3C
        __IO u32 ADDR9;
    };
    union {
        __IO u32 CH10DR;                                                        ///< ADC channel10 data register,                   offset: 0x40
        __IO u32 ADDR10;
    };
    union {
        __IO u32 CH11DR;                                                        ///< ADC channel11 data register,                   offset: 0x44
        __IO u32 ADDR11;
    };
    union {
        __IO u32 CH12DR;                                                        ///< ADC channel12 data register,                   offset: 0x48
        __IO u32 ADDR12;
    };
    union {
        __IO u32 CH13DR;                                                        ///< ADC channel13 data register,                   offset: 0x4C
        __IO u32 ADDR13;
    };
    union {
        __IO u32 CH14DR;                                                        ///< ADC channel14 data register,                   offset: 0x50
        __IO u32 ADDR14;
    };
    union {
        __IO u32 CH15DR;                                                        ///< ADC channel15 data register,                   offset: 0x54
        __IO u32 ADDR15;
    };
    __IO u32 SREXT;                                                             ///< ADC Extended Status Register,                  offset: 0x58
    __IO u32 CHANY0;                                                            ///< ADC any Chan Select Register 0,                offset: 0x5C
    __IO u32 CHANY1;                                                            ///< ADC any Chan Select Register 1,                offset: 0x60
    __IO u32 ANYCFG;                                                            ///< ADC any Chan config Register,                  offset: 0x64
    __IO u32 ANYCR;                                                             ///< ADC any Chan control Register,                 offset: 0x68
    __IO u32 ADCFG2;                                                            ///< ADC configuration register                     offset: 0x6C
    __IO u32 SMPR1;                                                             ///< Sampling configuration register 1              offset: 0x70
    __IO u32 SMPR2;                                                             ///< Sampling configuration register 2              offset: 0x74
    __IO u32 RESERVED0x78;                                                      ///< Reserved                                       offset: 0x78
    __IO u32 JOFR0;                                                             ///< Injection channel data compensation register 0 offset: 0x7C
    __IO u32 JOFR1;                                                             ///< Injection channel data compensation register 1 offset: 0x80
    __IO u32 JOFR2;                                                             ///< Injection channel data compensation register 2 offset: 0x84
    __IO u32 JOFR3;                                                             ///< Injection channel data compensation register 3 offset: 0x88
    __IO u32 JSQR;                                                              ///< Injection sequence register                    offset: 0x8C
    __IO u32 JDATA;                                                             ///< Inject data register                           offset: 0x90
    __IO u32 CORRS;                                                             ///< ADC single-ended correction parameter register offset: 0x94
    __IO u32 CORRD;                                                             ///< ADC differential correction register           offset: 0x98
    __IO u32 CORRP;                                                             ///< ADC pseudo-differential parameter register     offset: 0x9C
    __IO u32 RESERVED0xA0;                                                      ///< Reserved                                       offset: 0xA0
    __IO u32 RESERVED0xA4;                                                      ///< Reserved                                       offset: 0xA4
    __IO u32 RESERVED0xA8;                                                      ///< Reserved                                       offset: 0xA8
    __IO u32 RESERVED0xAC;                                                      ///< Reserved                                       offset: 0xAC
    __IO u32 JDR0;                                                              ///< Injection channel data register 0              offset: 0xB0
    __IO u32 JDR1;                                                              ///< Injection channel data register 1              offset: 0xB4
    __IO u32 JDR2;                                                              ///< Injection channel data register 2              offset: 0xB8
    __IO u32 JDR3;                                                              ///< Injection channel data register 3              offset: 0xBC
} ADC_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC1                            ((ADC_TypeDef*) ADC1_BASE)
#define ADC2                            ((ADC_TypeDef*) ADC2_BASE)

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_DR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_DR_DATA_Pos                 (0)
#define ADC_DR_DATA                     (0xFFFFU << ADC_DR_DATA_Pos)            ///< ADC 12bit convert data

#define ADC_DR_CH_Pos                   (16)
#define ADC_DR_CH                       (0x0FU << ADC_DR_CH_Pos)                ///< CHANNELSEL[19:16] (ADC current channel convert data)
#define ADC_DR_CH0                      (0x00U << ADC_DR_CH_Pos)                ///< ADC Channel select  0
#define ADC_DR_CH1                      (0x01U << ADC_DR_CH_Pos)                ///< ADC Channel select  1
#define ADC_DR_CH2                      (0x02U << ADC_DR_CH_Pos)                ///< ADC Channel select  2
#define ADC_DR_CH3                      (0x03U << ADC_DR_CH_Pos)                ///< ADC Channel select  3
#define ADC_DR_CH4                      (0x04U << ADC_DR_CH_Pos)                ///< ADC Channel select  4
#define ADC_DR_CH5                      (0x05U << ADC_DR_CH_Pos)                ///< ADC Channel select  5
#define ADC_DR_CH6                      (0x06U << ADC_DR_CH_Pos)                ///< ADC Channel select  6
#define ADC_DR_CH7                      (0x07U << ADC_DR_CH_Pos)                ///< ADC Channel select  7
#define ADC_DR_CH8                      (0x08U << ADC_DR_CH_Pos)                ///< ADC Channel select  8
#define ADC_DR_CH9                      (0x09U << ADC_DR_CH_Pos)                ///< ADC Channel select  9
#define ADC_DR_CH10                     (0x0AU << ADC_DR_CH_Pos)                ///< ADC Channel select  10
#define ADC_DR_CH11                     (0x0BU << ADC_DR_CH_Pos)                ///< ADC Channel select  11
#define ADC_DR_CH12                     (0x0CU << ADC_DR_CH_Pos)                ///< ADC Channel select  12
#define ADC_DR_CH13                     (0x0DU << ADC_DR_CH_Pos)                ///< ADC Channel select  13
#define ADC_DR_CH14                     (0x0EU << ADC_DR_CH_Pos)                ///< ADC Channel select  14
#define ADC_DR_CH15                     (0x0FU << ADC_DR_CH_Pos)                ///< ADC Channel select  15
#define ADC_DR_TempSensor               ADC_DR_CH15                             ///< ADC Channel select  15
#define ADC_DR_VoltRef                  ADC_DR_CH14                             ///< ADC Channel select  14
//  only for SPIN0280's TempSensor Chan= 15, VoltRef Chan= 14, it is different with SPIN2x and other series

#define ADC_DR_OVERRUN_Pos              (20)
#define ADC_DR_OVERRUN                  (0x01U << ADC_DR_OVERRUN_Pos)           ///< ADC data will be cover
#define ADC_DR_VALID_Pos                (21)
#define ADC_DR_VALID                    (0x01U << ADC_DR_VALID_Pos)             ///< ADC data[11:0] is valid

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CFGR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_CFGR_ADEN_Pos               (0)
#define ADC_CFGR_ADEN                   (0x01U << ADC_CFGR_ADEN_Pos)            ///< Enable ADC convert
#define ADC_CFGR_ADWEN_Pos              (1)
#define ADC_CFGR_ADWEN                  (0x01U << ADC_CFGR_ADWEN_Pos)           ///< Enable ADC window compare

#define ADC_CFGR_TSEN_Pos               (2)
#define ADC_CFGR_TSEN                   (0x01U << ADC_CFGR_TSEN_Pos)             ///< Enable ADC temperature sensor
//legacy define
#define ADC_CFGR_TEN_Pos                ADC_CFGR_TSEN_Pos
#define ADC_CFGR_TEN                    ADC_CFGR_TSEN

#define ADC_CFGR_VSEN_Pos               (3)
#define ADC_CFGR_VSEN                   (0x01U << ADC_CFGR_VSEN_Pos)            ///< Enable ADC voltage reference
//legacy define
#define ADC_CFGR_VEN_Pos                ADC_CFGR_VSEN_Pos
#define ADC_CFGR_VEN                    ADC_CFGR_VSEN

#define ADC_CFGR_PRE_Pos                (4)
#define ADC_CFGR_PREL_Pos               (14)
#define ADC_CFGR_PRE                    ((0x07U << ADC_CFGR_PRE_Pos) + (0x01U << ADC_CFGR_PREL_Pos))
#define ADC_CFGR_PRE_2                  (0x00U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 2
#define ADC_CFGR_PRE_4                  (0x01U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 4
#define ADC_CFGR_PRE_6                  (0x02U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 6
#define ADC_CFGR_PRE_8                  (0x03U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 8
#define ADC_CFGR_PRE_10                 (0x04U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 10
#define ADC_CFGR_PRE_12                 (0x05U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 12
#define ADC_CFGR_PRE_14                 (0x06U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 14
#define ADC_CFGR_PRE_16                 (0x07U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 16
#define ADC_CFGR_PRE_3                  ((0x01U << ADC_CFGR_PREL_Pos) + (0x00U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 3
#define ADC_CFGR_PRE_5                  ((0x01U << ADC_CFGR_PREL_Pos) + (0x01U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 5
#define ADC_CFGR_PRE_7                  ((0x01U << ADC_CFGR_PREL_Pos) + (0x02U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 7
#define ADC_CFGR_PRE_9                  ((0x01U << ADC_CFGR_PREL_Pos) + (0x03U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 9
#define ADC_CFGR_PRE_11                 ((0x01U << ADC_CFGR_PREL_Pos) + (0x04U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 11
#define ADC_CFGR_PRE_13                 ((0x01U << ADC_CFGR_PREL_Pos) + (0x05U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 13
#define ADC_CFGR_PRE_15                 ((0x01U << ADC_CFGR_PREL_Pos) + (0x06U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 15
#define ADC_CFGR_PRE_17                 ((0x01U << ADC_CFGR_PREL_Pos) + (0x07U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 17
#define ADC_CFGR_RSLTCTL_Pos            (7)
#define ADC_CFGR_RSLTCTL                (0x07U << ADC_CFGR_RSLTCTL_Pos)         ///< ADC resolution select
#define ADC_CFGR_RSLTCTL_12             (0x00U << ADC_CFGR_RSLTCTL_Pos)         ///< ADC resolution select 12bit or Pseudo-differential conversion data resolution select 13 bit
#define ADC_CFGR_RSLTCTL_11             (0x01U << ADC_CFGR_RSLTCTL_Pos)         ///< ADC resolution select 11bit or Pseudo-differential conversion data resolution select 12 bit
#define ADC_CFGR_RSLTCTL_10             (0x02U << ADC_CFGR_RSLTCTL_Pos)         ///< ADC resolution select 10bit or Pseudo-differential conversion data resolution select 11 bit
#define ADC_CFGR_RSLTCTL_9              (0x03U << ADC_CFGR_RSLTCTL_Pos)         ///< ADC resolution select 9bit  or Pseudo-differential conversion data resolution select 10 bit
#define ADC_CFGR_RSLTCTL_8              (0x04U << ADC_CFGR_RSLTCTL_Pos)         ///< ADC resolution select 8bit  or Pseudo-differential conversion data resolution select 9 bit

#define ADC_CFGR_RSLTCTL_PD_13          (0x00U << ADC_CFGR_RSLTCTL_Pos)         ///< Pseudo-differential conversion data resolution select 13 bit
#define ADC_CFGR_RSLTCTL_PD_12          (0x01U << ADC_CFGR_RSLTCTL_Pos)         ///< Pseudo-differential conversion data resolution select 12 bit
#define ADC_CFGR_RSLTCTL_PD_11          (0x02U << ADC_CFGR_RSLTCTL_Pos)         ///< Pseudo-differential conversion data resolution select 11 bit
#define ADC_CFGR_RSLTCTL_PD_10          (0x03U << ADC_CFGR_RSLTCTL_Pos)         ///< Pseudo-differential conversion data resolution select 10 bit
#define ADC_CFGR_RSLTCTL_PD_9           (0x04U << ADC_CFGR_RSLTCTL_Pos)         ///< Pseudo-differential conversion data resolution select 9 bit
#define ADC_CFGR_JAWDEN_Pos             (16)
#define ADC_CFGR_JAWDEN                 (0x01U << ADC_CFGR_JAWDEN_Pos)          ///< Inject ADC conversion window comparison enable
//legacy define
#define ADC_CFGR_JADWEN_Pos             ADC_CFGR_JAWDEN_Pos
#define ADC_CFGR_JADWEN                 ADC_CFGR_JAWDEN

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_CR_EOSIE_Pos                (0)
#define ADC_CR_EOSIE                    (0x01U << ADC_CR_EOSIE_Pos)             ///< ADC interrupt enable
//legacy define
#define ADC_CR_ADIE_Pos                 ADC_CR_EOSIE_Pos
#define ADC_CR_ADIE                     ADC_CR_EOSIE

#define ADC_CR_AWDIE_Pos                (1)
#define ADC_CR_AWDIE                    (0x01U << ADC_CR_AWDIE_Pos)             ///< Interrupt Enable of Analog Watchdog
//legacy define
#define ADC_CR_ADWIE_Pos                ADC_CR_AWDIE_Pos
#define ADC_CR_ADWIE                    ADC_CR_AWDIE

#define ADC_CR_TRGEN_Pos                (2)
#define ADC_CR_TRGEN                    (0x01U << ADC_CR_TRGEN_Pos)             ///< extranal trigger single start AD convert
#define ADC_CR_DMAEN_Pos                (3)
#define ADC_CR_DMAEN                    (0x01U << ADC_CR_DMAEN_Pos)             ///< ADC DMA enable

#define ADC_CR_ADST_Pos                 (8)
#define ADC_CR_ADST                     (0x01U << ADC_CR_ADST_Pos)              ///< ADC start convert data
#define ADC_CR_MD_Pos                   (9)
#define ADC_CR_MD                       (0x03U << ADC_CR_MD_Pos)                ///< ADC convert mode
//legacy define
#define ADC_CR_MODE_Pos                 ADC_CR_MD_Pos
#define ADC_CR_MODE                     ADC_CR_MD
#define ADC_CR_IMM                      (0x00U << ADC_CR_MODE_Pos)              ///< ADC imm convert mode
#define ADC_CR_SCAN                     (0x01U << ADC_CR_MODE_Pos)              ///< ADC scan convert mode
#define ADC_CR_CONTINUE                 (0x02U << ADC_CR_MODE_Pos)              ///< ADC continue scan convert mode
#define ADC_CR_ALIGN_Pos                (11)
#define ADC_CR_ALIGN                    (0x01U << ADC_CR_ALIGN_Pos)             ///< ADC data align
#define ADC_CR_LEFT                     (0x01U << ADC_CR_ALIGN_Pos)             ///< ADC data left align
#define ADC_CR_RIGHT                    (0x00U << ADC_CR_ALIGN_Pos)             ///< ADC data right align
#define ADC_CR_CMPCH_Pos                (12)
#define ADC_CR_CMPCH                    (0x0FU << ADC_CR_CMPCH_Pos)             ///< CMPCH[15:12] ADC window compare channel0 convert data
#define ADC_CR_CMPCH_0                  (0x00U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 0 Conversion Results
#define ADC_CR_CMPCH_1                  (0x01U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 1 Conversion Results
#define ADC_CR_CMPCH_2                  (0x02U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 2 Conversion Results
#define ADC_CR_CMPCH_3                  (0x03U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 3 Conversion Results
#define ADC_CR_CMPCH_4                  (0x04U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 4 Conversion Results
#define ADC_CR_CMPCH_5                  (0x05U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 5 Conversion Results
#define ADC_CR_CMPCH_6                  (0x06U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 6 Conversion Results
#define ADC_CR_CMPCH_7                  (0x07U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 7 Conversion Results
#define ADC_CR_CMPCH_8                  (0x08U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 8 Conversion Results
#define ADC_CR_CMPCH_9                  (0x09U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 9 Conversion Results
#define ADC_CR_CMPCH_10                 (0x0AU << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 10 Conversion Results
#define ADC_CR_CMPCH_11                 (0x0BU << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 11 Conversion Results
#define ADC_CR_CMPCH_12                 (0x0CU << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 12 Conversion Results
#define ADC_CR_CMPCH_13                 (0x0DU << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 13 Conversion Results
#define ADC_CR_CMPCH_14                 (0x0FU << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 14 Conversion Results
#define ADC_CR_CMPCH_ALL                (0x0EU << ADC_CR_CMPCH_Pos)             ///< Select Compare ALL Channel Conversion Results
//  only for SPIN0280's TempSensor Chan= 15, VoltRef Chan= 14, it is different with SPIN2x and other series

#define ADC_CR_SCANDIR_Pos              (16)
#define ADC_CR_SCANDIR                  (0x01U << ADC_CR_SCANDIR_Pos)           ///< ADC scan direction
#define ADC_CR_TRGSEL_H_Pos             (17)
#define ADC_CR_TRGSEL_L_Pos             (4)
#define ADC_CR_TRGSEL                   ((0x03U << ADC_CR_TRGSEL_H_Pos) + (0x07U << ADC_CR_TRGSEL_L_Pos))   ///< TRGSEL[6:4][18:17] ADC external trigger source select
#define ADC_CR_T1_CC1                   (0x00U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is T1_CC1
#define ADC_CR_T1_CC2                   (0x01U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is T1_CC2
#define ADC_CR_T1_CC3                   (0x02U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is T1_CC3
#define ADC_CR_T2_CC2                   (0x03U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is T2_CC2
#define ADC_CR_T3_TRIG                  (0x04U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is T3_TRIG
#define ADC_CR_T1_CC4_CC5               (0x05U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is TIM1_CC4 or TIM1_CC5
#define ADC_CR_T3_CC1                   (0x06U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is T3_CC1
#define ADC_CR_EXTI_11                  (0x07U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is EXTI_11
#define ADC_CR_T1_TRIG                  ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x00U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is T1_TRIG
#define ADC_CR_T8_CC4                   ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x01U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is T8_CC4
#define ADC_CR_T8_CC4_CC5               ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x02U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is T8_CC4_CC5
#define ADC_CR_T2_CC1                   ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x03U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is T2_CC1
#define ADC_CR_T3_CC4                   ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x04U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is T3_CC4
#define ADC_CR_T2_TRIG                  ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x05U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is T2_TRIG
#define ADC_CR_T8_CC5                   ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x06U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is T8_CC5
#define ADC_CR_EXTI_15                  ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x07U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is EXTI_15
#define ADC_CR_T1_CC4                   ((0x02U << ADC_CR_TRGSEL_H_Pos) + (0x00U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is T1_CC4
#define ADC_CR_T1_CC5                   ((0x02U << ADC_CR_TRGSEL_H_Pos) + (0x01U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is T1_CC5

#define ADC_CR_TRGSHIFT_Pos             (19)
#define ADC_CR_TRGSHIFT                 (0x07U << ADC_CR_TRGSHIFT_Pos)          ///< External trigger shift sample
#define ADC_CR_TRGSHIFT_0               (0x00U << ADC_CR_TRGSHIFT_Pos)          ///< No shift
#define ADC_CR_TRGSHIFT_4               (0x01U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 4 period
#define ADC_CR_TRGSHIFT_16              (0x02U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 16 period
#define ADC_CR_TRGSHIFT_32              (0x03U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 32 period
#define ADC_CR_TRGSHIFT_64              (0x04U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 64 period
#define ADC_CR_TRGSHIFT_128             (0x05U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 128 period
#define ADC_CR_TRGSHIFT_256             (0x06U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 256 period
#define ADC_CR_TRGSHIFT_512             (0x07U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 512 period
#define ADC_CR_CALIBEN_Pos              (22)
#define ADC_CR_CALIBEN                  (0x01U << ADC_CR_CALIBEN_Pos)           ///< Self-calibration enable
#define ADC_CR_CALIBSEL_Pos             (23)
#define ADC_CR_CALIBSEL                 (0x01U << ADC_CR_CALIBSEL_Pos)          ///< Self-calibration voltage selection
#define ADC_CR_TRG_EDGE_Pos             (24)
#define ADC_CR_TRG_EDGE                 (0x03U << ADC_CR_TRG_EDGE_Pos)          ///< ADC trig edge config
#define ADC_CR_TRG_EDGE_DUAL            (0x00U << ADC_CR_TRG_EDGE_Pos)          ///< ADC dual edge trig mode
#define ADC_CR_TRG_EDGE_DOWN            (0x01U << ADC_CR_TRG_EDGE_Pos)          ///< ADC down edge trig mode
#define ADC_CR_TRG_EDGE_UP              (0x02U << ADC_CR_TRG_EDGE_Pos)          ///< ADC up   edge trig mode
#define ADC_CR_TRG_EDGE_MASK            (0x03U << ADC_CR_TRG_EDGE_Pos)          ///< ADC mask edge trig mode

#define ADC_CR_EOSMPIE_Pos              (26)
#define ADC_CR_EOSMPIE                  (0X01U << ADC_CR_EOSMPIE_Pos)           ///< ADC end sampling flag interrupt enable
#define ADC_CR_EOCIE_Pos                (27)
#define ADC_CR_EOCIE                    (0X01U << ADC_CR_EOCIE_Pos)             ///< ADC end of conversion interrupt enable

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CHSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_CHSR_CH0_Pos                (0)
#define ADC_CHSR_CH0                    (0x01U << ADC_CHSR_CH0_Pos)             ///< Enable ADC channel 0
#define ADC_CHSR_CH1_Pos                (1)
#define ADC_CHSR_CH1                    (0x01U << ADC_CHSR_CH1_Pos)             ///< Enable ADC channel 1
#define ADC_CHSR_CH2_Pos                (2)
#define ADC_CHSR_CH2                    (0x01U << ADC_CHSR_CH2_Pos)             ///< Enable ADC channel 2
#define ADC_CHSR_CH3_Pos                (3)
#define ADC_CHSR_CH3                    (0x01U << ADC_CHSR_CH3_Pos)             ///< Enable ADC channel 3
#define ADC_CHSR_CH4_Pos                (4)
#define ADC_CHSR_CH4                    (0x01U << ADC_CHSR_CH4_Pos)             ///< Enable ADC channel 4
#define ADC_CHSR_CH5_Pos                (5)
#define ADC_CHSR_CH5                    (0x01U << ADC_CHSR_CH5_Pos)             ///< Enable ADC channel 5
#define ADC_CHSR_CH6_Pos                (6)
#define ADC_CHSR_CH6                    (0x01U << ADC_CHSR_CH6_Pos)             ///< Enable ADC channel 6
#define ADC_CHSR_CH7_Pos                (7)
#define ADC_CHSR_CH7                    (0x01U << ADC_CHSR_CH7_Pos)             ///< Enable ADC channel 7
#define ADC_CHSR_CH8_Pos                (8)
#define ADC_CHSR_CH8                    (0x01U << ADC_CHSR_CH8_Pos)             ///< Enable ADC channel 8
#define ADC_CHSR_CH9_Pos                (9)
#define ADC_CHSR_CH9                    (0x01U << ADC_CHSR_CH9_Pos)             ///< Enable ADC channel 9
#define ADC_CHSR_CH10_Pos               (10)
#define ADC_CHSR_CH10                   (0x01U << ADC_CHSR_CH10_Pos)            ///< Enable ADC channel 10
#define ADC_CHSR_CH11_Pos               (11)
#define ADC_CHSR_CH11                   (0x01U << ADC_CHSR_CH11_Pos)            ///< Enable ADC channel 11
#define ADC_CHSR_CH12_Pos               (12)
#define ADC_CHSR_CH12                   (0x01U << ADC_CHSR_CH12_Pos)            ///< Enable ADC channel 12
#define ADC_CHSR_CH13_Pos               (13)
#define ADC_CHSR_CH13                   (0x01U << ADC_CHSR_CH13_Pos)            ///< Enable ADC channel 13
#define ADC_CHSR_CH14_Pos               (14)
#define ADC_CHSR_CH14                   (0x01U << ADC_CHSR_CH14_Pos)            ///< Enable ADC channel 14
#define ADC_CHSR_CH15_Pos               (15)
#define ADC_CHSR_CH15                   (0x01U << ADC_CHSR_CH15_Pos)            ///< Enable ADC channel 15
#define ADC_CHSR_CHT_Pos                ADC_CHSR_CH15_Pos
#define ADC_CHSR_CHT                    ADC_CHSR_CH15                           ///< Enable Temperature Sensor
#define ADC_CHSR_CHV_Pos                ADC_CHSR_CH14_Pos
#define ADC_CHSR_CHV                    ADC_CHSR_CH14                           ///< Enable Voltage Sensor
//  only for SPIN0280's TempSensor Chan= 15, VoltRef Chan= 14, it is different with SPIN2x and other series
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CMPR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_CMPR_CMPLDATA_Pos           (0)
#define ADC_CMPR_CMPLDATA               (0x0FFFU << ADC_CMPR_CMPLDATA_Pos)      ///< ADC 12bit window compare DOWN LEVEL DATA
#define ADC_CMPR_CMPHDATA_Pos           (16)
#define ADC_CMPR_CMPHDATA               (0x0FFFU << ADC_CMPR_CMPHDATA_Pos)      ///< ADC 12bit window compare UP LEVEL DATA

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_SR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_SR_EOSIF_Pos                (0)
#define ADC_SR_EOSIF                    (0x01U << ADC_SR_EOSIF_Pos)             ///< ADC convert complete flag
//legacy define
#define ADC_SR_ADIF_Pos                 ADC_SR_EOSIF_Pos
#define ADC_SR_ADIF                     ADC_SR_EOSIF

#define ADC_SR_AWDIF_Pos                (1)
#define ADC_SR_AWDIF                    (0x01U << ADC_SR_AWDIF_Pos)             ///< ADC compare flag
//legacy define
#define ADC_SR_ADWIF_Pos                ADC_SR_AWDIF_Pos
#define ADC_SR_ADWIF                    ADC_SR_AWDIF

#define ADC_SR_BUSY_Pos                 (2)
#define ADC_SR_BUSY                     (0x01U << ADC_SR_BUSY_Pos)              ///< ADC busy flag
#define ADC_SR_CH_Pos                   (4)
#define ADC_SR_CH                       (0x0FU << ADC_SR_CH_Pos)                ///< CHANNEL[7:4] ADC current channel
#define ADC_SR_CH0                      (0x00U << ADC_SR_CH_Pos)                ///< Channel 0 is the current conversion channel
#define ADC_SR_CH1                      (0x01U << ADC_SR_CH_Pos)                ///< Channel 1 is the current conversion channel
#define ADC_SR_CH2                      (0x02U << ADC_SR_CH_Pos)                ///< Channel 2 is the current conversion channel
#define ADC_SR_CH3                      (0x03U << ADC_SR_CH_Pos)                ///< Channel 3 is the current conversion channel
#define ADC_SR_CH4                      (0x04U << ADC_SR_CH_Pos)                ///< Channel 4 is the current conversion channel
#define ADC_SR_CH5                      (0x05U << ADC_SR_CH_Pos)                ///< Channel 5 is the current conversion channel
#define ADC_SR_CH6                      (0x06U << ADC_SR_CH_Pos)                ///< Channel 6 is the current conversion channel
#define ADC_SR_CH7                      (0x07U << ADC_SR_CH_Pos)                ///< Channel 7 is the current conversion channel
#define ADC_SR_CH8                      (0x08U << ADC_SR_CH_Pos)                ///< Channel 8 is the current conversion channel
#define ADC_SR_CH9                      (0x09U << ADC_SR_CH_Pos)                ///< Channel 9 is the current conversion channel
#define ADC_SR_CH10                     (0x0AU << ADC_SR_CH_Pos)                ///< Channel 10 is the current conversion channel
#define ADC_SR_CH11                     (0x0BU << ADC_SR_CH_Pos)                ///< Channel 11 is the current conversion channel
#define ADC_SR_CH12                     (0x0CU << ADC_SR_CH_Pos)                ///< Channel 12 is the current conversion channel
#define ADC_SR_CH13                     (0x0DU << ADC_SR_CH_Pos)                ///< Channel 13 is the current conversion channel
#define ADC_SR_CH14                     (0x0EU << ADC_SR_CH_Pos)                ///< Channel 14 is the current conversion channel
#define ADC_SR_CH15                     (0x0FU << ADC_SR_CH_Pos)                ///< Channel 15 is the current conversion channel
#define ADC_SR_CHT                      ADC_SR_CH15                             ///< Channel 15 is the current conversion channel
#define ADC_SR_CHV                      ADC_SR_CH14                             ///< Channel 14 is the current conversion channel
//  only for SPIN0280's TempSensor Chan= 15, VoltRef Chan= 14, it is different with SPIN2x and other series
#define ADC_SR_VALID_Pos                (8)
#define ADC_SR_VALID                    (0x0FFFU << ADC_SR_VALID_Pos)           ///< VALID[19:8] ADC channel 0..11 valid flag
#define ADC_SR_OVERRUN_Pos              (20)
#define ADC_SR_OVERRUN                  (0x0FFFU << ADC_SR_OVERRUN_Pos)         ///< OVERRUN[31:20] ADC channel 0..11 data covered flag

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CHnDR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_CHDR_DATA_Pos               (0)
#define ADC_CHDR_DATA                   (0xFFFFU << ADC_CHDR_DATA_Pos)          ///< ADC channel convert data
#define ADC_CHDR_OVERRUN_Pos            (20)
#define ADC_CHDR_OVERRUN                (0x01U << ADC_CHDR_OVERRUN_Pos)         ///< ADC data covered flag
#define ADC_CHDR_VALID_Pos              (21)
#define ADC_CHDR_VALID                  (0x01U << ADC_CHDR_VALID_Pos)           ///< ADC data valid flag

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_SREXT Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_SREXT_VALID_Pos             (0)
#define ADC_SREXT_VALID                 (0x0FU << ADC_SREXT_VALID_Pos)          ///< VALID[3:0] ADC channel 12,14..15 valid flag
#define ADC_SREXT_VALID_CH12            (0x01U << ADC_SREXT_VALID_Pos)          ///< channel 12
#define ADC_SREXT_VALID_CH13            (0x02U << ADC_SREXT_VALID_Pos)          ///< channel 13
#define ADC_SREXT_VALID_CH14            (0x04U << ADC_SREXT_VALID_Pos)          ///< channel 14  V_SENSOR
#define ADC_SREXT_VALID_CH15            (0x08U << ADC_SREXT_VALID_Pos)          ///< channel 15  T_SENSOR
//  only for SPIN0280's TempSensor Chan= 15, VoltRef Chan= 14, it is different with SPIN2x and other series
#define ADC_SREXT_OVERRUN_Pos           (4)
#define ADC_SREXT_OVERRUN               (0x0FU << ADC_SREXT_OVERRUN_Pos)        ///< OVERRUN[7:4] ADC channel 12,14..15 data covered flag
#define ADC_SREXT_OVERRUN_CH12          (0x01U << ADC_SREXT_OVERRUN_Pos)        ///< channel 12
#define ADC_SREXT_OVERRUN_CH13          (0x02U << ADC_SREXT_OVERRUN_Pos)        ///< channel 13
#define ADC_SREXT_OVERRUN_CH14          (0x04U << ADC_SREXT_OVERRUN_Pos)        ///< channel 14  V_SENSOR
#define ADC_SREXT_OVERRUN_CH15          (0x08U << ADC_SREXT_OVERRUN_Pos)        ///< channel 15  T_SENSOR
//  only for SPIN0280's TempSensor Chan= 15, VoltRef Chan= 14, it is different with SPIN2x and other series
#define ADC_SREXT_EOSMPIF_Pos           (16)
#define ADC_SREXT_EOSMPIF               (0x01U << ADC_SREXT_EOSMPIF_Pos)        ///< End of sampling interrupt flag
#define ADC_SREXT_EOCIF_Pos             (17)
#define ADC_SREXT_EOCIF                 (0x01U << ADC_SREXT_EOCIF_Pos)          ///< End of conversion interrupt flag
#define ADC_SREXT_JEOSMPIF_Pos          (18)
#define ADC_SREXT_JEOSMPIF              (0x01U << ADC_SREXT_JEOSMPIF_Pos)       ///< Injected channel end of sampling interrupt flag
#define ADC_SREXT_JEOCIF_Pos            (19)
#define ADC_SREXT_JEOCIF                (0x03U << ADC_SREXT_JEOCIF_Pos)         ///< Injected channel end of conversion interrupt flag
#define ADC_SREXT_JEOSIF_Pos            (20)
#define ADC_SREXT_JEOSIF                (0x03U << ADC_SREXT_JEOSIF_Pos)         ///< Injected channel end of sequential conversion interrupt flag
#define ADC_SREXT_JBUSY_Pos             (21)
#define ADC_SREXT_JBUSY                 (0x01U << ADC_SREXT_JBUSY_Pos)          ///< Injection mode busy/idle
#define ADC_SREXT_EOCALIF_Pos           (24)
#define ADC_SREXT_EOCALIF               (0x01U << ADC_SREXT_EOCALIF_Pos)        ///< End of calibration interrupt flag
#define ADC_SREXT_CALBUSY_Pos           (25)
#define ADC_SREXT_CALBUSY               (0x01U << ADC_SREXT_CALBUSY_Pos)        ///< calibration Busy
#define ADC_SREXT_FREOCIF_Pos           (26)
#define ADC_SREXT_FREOCIF               (0x01U << ADC_SREXT_FREOCIF_Pos)        ///< The calibration factor is read to the end of the data register

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CHANY0 select Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_CHANY0_SEL0_Pos             (0)                                     ///< CHANY_SEL0 (Bit 0)
#define ADC_CHANY0_SEL0                 (0x0FU << ADC_CHANY0_SEL0_Pos)          ///< CHANY_SEL0 (Bitfield-Mask: 0x0f)
#define ADC_CHANY0_SEL1_Pos             (4)                                     ///< CHANY_SEL1 (Bit 4)
#define ADC_CHANY0_SEL1                 (0x0FU << ADC_CHANY0_SEL1_Pos)          ///< CHANY_SEL1 (Bitfield-Mask: 0x0f)
#define ADC_CHANY0_SEL2_Pos             (8)                                     ///< CHANY_SEL2 (Bit 8)
#define ADC_CHANY0_SEL2                 (0x0FU << ADC_CHANY0_SEL2_Pos)          ///< CHANY_SEL2 (Bitfield-Mask: 0x0f)
#define ADC_CHANY0_SEL3_Pos             (12)                                    ///< CHANY_SEL3 (Bit 12)
#define ADC_CHANY0_SEL3                 (0x0FU << ADC_CHANY0_SEL3_Pos)          ///< CHANY_SEL3 (Bitfield-Mask: 0x0f)
#define ADC_CHANY0_SEL4_Pos             (16)                                    ///< CHANY_SEL4 (Bit 16)
#define ADC_CHANY0_SEL4                 (0x0FU << ADC_CHANY0_SEL4_Pos)          ///< CHANY_SEL4 (Bitfield-Mask: 0x0f)
#define ADC_CHANY0_SEL5_Pos             (20)                                    ///< CHANY_SEL5 (Bit 20)
#define ADC_CHANY0_SEL5                 (0x0FU << ADC_CHANY0_SEL5_Pos)          ///< CHANY_SEL5 (Bitfield-Mask: 0x0f)
#define ADC_CHANY0_SEL6_Pos             (24)                                    ///< CHANY_SEL6 (Bit 24)
#define ADC_CHANY0_SEL6                 (0x0FU << ADC_CHANY0_SEL6_Pos)          ///< CHANY_SEL6 (Bitfield-Mask: 0x0f)
#define ADC_CHANY0_SEL7_Pos             (28)                                    ///< CHANY_SEL7 (Bit 28)
#define ADC_CHANY0_SEL7                 (0x0FU << ADC_CHANY0_SEL7_Pos)          ///< CHANY_SEL7 (Bitfield-Mask: 0x0f)

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CHANY1 select Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_CHANY1_SEL8_Pos             (0)                                     ///< CHANY_SEL8 (Bit 0)
#define ADC_CHANY1_SEL8                 (0x0FU << ADC_CHANY1_SEL8_Pos)          ///< CHANY_SEL8 (Bitfield-Mask: 0x0f)
#define ADC_CHANY1_SEL9_Pos             (4)                                     ///< CHANY_SEL9 (Bit 4)
#define ADC_CHANY1_SEL9                 (0x0FU << ADC_CHANY1_SEL9_Pos)          ///< CHANY_SEL9 (Bitfield-Mask: 0x0f)
#define ADC_CHANY1_SEL10_Pos            (8)                                     ///< CHANY_SEL10 (Bit 8)
#define ADC_CHANY1_SEL10                (0x0FU << ADC_CHANY1_SEL10_Pos)         ///< CHANY_SEL10 (Bitfield-Mask: 0x0f)
#define ADC_CHANY1_SEL11_Pos            (12)                                    ///< CHANY_SEL11 (Bit 12)
#define ADC_CHANY1_SEL11                (0x0FU << ADC_CHANY1_SEL11_Pos)         ///< CHANY_SEL11 (Bitfield-Mask: 0x0f)
#define ADC_CHANY1_SEL12_Pos            (16)                                    ///< CHANY_SEL12 (Bit 16)
#define ADC_CHANY1_SEL12                (0x0FU << ADC_CHANY1_SEL12_Pos)         ///< CHANY_SEL12 (Bitfield-Mask: 0x0f)
#define ADC_CHANY1_SEL13_Pos            (20)                                    ///< CHANY_SEL13 (Bit 20)
#define ADC_CHANY1_SEL13                (0x0FU << ADC_CHANY1_SEL13_Pos)         ///< CHANY_SEL13 (Bitfield-Mask: 0x0f)
#define ADC_CHANY1_SEL14_Pos            (24)                                    ///< CHANY_SEL14 (Bit 24)
#define ADC_CHANY1_SEL14                (0x0FU << ADC_CHANY1_SEL14_Pos)         ///< CHANY_SEL14 (Bitfield-Mask: 0x0f)
#define ADC_CHANY1_SEL15_Pos            (28)                                    ///< CHANY_SEL15 (Bit 28)
#define ADC_CHANY1_SEL15                (0x0FU << ADC_CHANY1_SEL15_Pos)         ///< CHANY_SEL15 (Bitfield-Mask: 0x0f)

#define ADC1_CHANY0_SEL0_Pos            ADC_CHANY0_SEL0_Pos                     ///< CHANY_SEL0 (Bit 0)
#define ADC1_CHANY0_SEL0                ADC_CHANY0_SEL0                         ///< CHANY_SEL0 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY0_SEL1_Pos            ADC_CHANY0_SEL1_Pos                     ///< CHANY_SEL1 (Bit 4)
#define ADC1_CHANY0_SEL1                ADC_CHANY0_SEL1                         ///< CHANY_SEL1 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY0_SEL2_Pos            ADC_CHANY0_SEL2_Pos                     ///< CHANY_SEL2 (Bit 8)
#define ADC1_CHANY0_SEL2                ADC_CHANY0_SEL2                         ///< CHANY_SEL2 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY0_SEL3_Pos            ADC_CHANY0_SEL3_Pos                     ///< CHANY_SEL3 (Bit 12)
#define ADC1_CHANY0_SEL3                ADC_CHANY0_SEL3                         ///< CHANY_SEL3 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY0_SEL4_Pos            ADC_CHANY0_SEL4_Pos                     ///< CHANY_SEL4 (Bit 16)
#define ADC1_CHANY0_SEL4                ADC_CHANY0_SEL4                         ///< CHANY_SEL4 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY0_SEL5_Pos            ADC_CHANY0_SEL5_Pos                     ///< CHANY_SEL5 (Bit 20)
#define ADC1_CHANY0_SEL5                ADC_CHANY0_SEL5                         ///< CHANY_SEL5 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY0_SEL6_Pos            ADC_CHANY0_SEL6_Pos                     ///< CHANY_SEL6 (Bit 24)
#define ADC1_CHANY0_SEL6                ADC_CHANY0_SEL6                         ///< CHANY_SEL6 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY0_SEL7_Pos            ADC_CHANY0_SEL7_Pos                     ///< CHANY_SEL7 (Bit 28)
#define ADC1_CHANY0_SEL7                ADC_CHANY0_SEL7                         ///< CHANY_SEL7 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY1_SEL8_Pos            ADC_CHANY1_SEL8_Pos                     ///< CHANY_SEL8 (Bit 0)
#define ADC1_CHANY1_SEL8                ADC_CHANY1_SEL8                         ///< CHANY_SEL8 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY1_SEL9_Pos            ADC_CHANY1_SEL9_Pos                     ///< CHANY_SEL9 (Bit 4)
#define ADC1_CHANY1_SEL9                ADC_CHANY1_SEL9                         ///< CHANY_SEL9 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY1_SEL10_Pos           ADC_CHANY1_SEL10_Pos                    ///< CHANY_SEL10 (Bit 8)
#define ADC1_CHANY1_SEL10               ADC_CHANY1_SEL10                        ///< CHANY_SEL10 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY1_SEL11_Pos           ADC_CHANY1_SEL11_Pos                    ///< CHANY_SEL11 (Bit 12)
#define ADC1_CHANY1_SEL11               ADC_CHANY1_SEL11                        ///< CHANY_SEL11 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY1_SEL12_Pos           ADC_CHANY1_SEL12_Pos                    ///< CHANY_SEL12 (Bit 16)
#define ADC1_CHANY1_SEL12               ADC_CHANY1_SEL12                        ///< CHANY_SEL12 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY1_SEL13_Pos           ADC_CHANY1_SEL13_Pos                    ///< CHANY_SEL13 (Bit 20)
#define ADC1_CHANY1_SEL13               ADC_CHANY1_SEL13                        ///< CHANY_SEL13 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY1_SEL14_Pos           ADC_CHANY1_SEL14_Pos                    ///< CHANY_SEL14 (Bit 24)
#define ADC1_CHANY1_SEL14               ADC_CHANY1_SEL14                        ///< CHANY_SEL14 (Bitfield-Mask: 0x0f)
#define ADC1_CHANY1_SEL15_Pos           ADC_CHANY1_SEL15_Pos                    ///< CHANY_SEL15 (Bit 28)
#define ADC1_CHANY1_SEL15               ADC_CHANY1_SEL15                        ///< CHANY_SEL15 (Bitfield-Mask: 0x0f)

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CHANY config number Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_CHANY_CFG_NUM_Max           (16)                                    ///< CHANY_CFG_NUM Max Value is 16
#define ADC1_CHANY_CFG_NUM_Max          ADC_CHANY_CFG_NUM_Max
#define ADC_CHANY_CFG_NUM_Pos           (0)                                     ///< CHANY_CFG_NUM Pos
#define ADC_CHANY_CFG_NUM               (0x0FU << ADC_CHANY_CFG_NUM_Pos)        ///< CHANY_CFG_NUM (Bitfield-Mask: 0x0f)

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CHANY mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_ANY_CR_CHANY_MDEN_Pos       (0)                                     ///< CHANY_MDEN (Bit 0)
#define ADC_ANY_CR_CHANY_MDEN           (0x01U << ADC_ANY_CR_CHANY_MDEN_Pos)    ///< CHANY_MDEN (Bitfield-Mask: 0x01)
#define ADC1_CHANY_CR_MDEN_Pos          ADC_ANY_CR_CHANY_MDEN_Pos
#define ADC1_CHANY_CR_MDEN              ADC_ANY_CR_CHANY_MDEN

#define ADC_ANY_CR_JCEN_Pos             (1)
#define ADC_ANY_CR_JCEN                 (0x01U << ADC_ANY_CR_JCEN_Pos)          ///< Injected channel enable
#define ADC_ANY_CR_JEOSMPIE_Pos         (2)
#define ADC_ANY_CR_JEOSMPIE             (0x01U << ADC_ANY_CR_JEOSMPIE_Pos)      ///< Interrupt enable the end of sequence conversion for injected channel
#define ADC_ANY_CR_JEOCIE_Pos           (3)
#define ADC_ANY_CR_JEOCIE               (0x01U << ADC_ANY_CR_JEOCIE_Pos)        ///< Interrupt enable the end of conversion for injected channel
#define ADC_ANY_CR_JEOSIE_Pos           (4)
#define ADC_ANY_CR_JEOSIE               (0x01U << ADC_ANY_CR_JEOSIE_Pos)        ///< Interrupt enable the end of sequence conversion for injected channel
#define ADC_ANY_CR_JAUTO_Pos            (5)
#define ADC_ANY_CR_JAUTO                (0x01U << ADC_ANY_CR_JAUTO_Pos)         ///<Automatic Injected group conversion
#define ADC_ANY_CR_JADST_Pos            (6)
#define ADC_ANY_CR_JADST                (0x01U << ADC_ANY_CR_JADST_Pos)         ///< Start conversion of injected channels
#define ADC_ANY_CR_JTRGEN_Pos           (7)
#define ADC_ANY_CR_JTRGEN               (0x01U << ADC_ANY_CR_JTRGEN_Pos)        ///< External trigger conversion mode for injected channels
#define ADC_ANY_CR_JTRGSEL_Pos          (8)                                     ///< External event select for injected group
#define ADC_ANY_CR_JTRGSEL              (0x1FU << ADC_ANY_CR_JTRGSEL_Pos)
#define ADC_ANY_CR_JTRGSEL_TIM1_CC1     (0x00U << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM1  CC1
#define ADC_ANY_CR_JTRGSEL_TIM1_CC2     (0x01U << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM1  CC2
#define ADC_ANY_CR_JTRGSEL_TIM1_CC3     (0x02U << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM1  CC3
#define ADC_ANY_CR_JTRGSEL_TIM2_CC2     (0x03U << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM2  CC2
#define ADC_ANY_CR_JTRGSEL_TIM3_TRGO    (0x04U << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM3  TRGO
#define ADC_ANY_CR_JTRGSEL_TIM1_CC4_CC5 (0x05U << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM1  CC4 or CC5
#define ADC_ANY_CR_JTRGSEL_TIM3_CC1     (0x06U << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM3  CC1
#define ADC_ANY_CR_JTRGSEL_EXTI11       (0x07U << ADC_ANY_CR_JTRGSEL_Pos)       ///< EXTI11
#define ADC_ANY_CR_JTRGSEL_TIM1_TRGO    (0x08U << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM1  TRGO
#define ADC_ANY_CR_JTRGSEL_TIM8_CC4     (0x09U << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM8  CC4
#define ADC_ANY_CR_JTRGSEL_TIM8_CC4_CC5 (0x0AU << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM8 CC4 or CC5
#define ADC_ANY_CR_JTRGSEL_TIM2_CC1     (0x0BU << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM2   CC1
#define ADC_ANY_CR_JTRGSEL_TIM3_CC4     (0x0CU << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM3   CC4
#define ADC_ANY_CR_JTRGSEL_TIM2_TRGO    (0x0DU << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM2 TRGO
#define ADC_ANY_CR_JTRGSEL_TIM8_CC5     (0x0EU << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM8 CC5
#define ADC_ANY_CR_JTRGSEL_EXTI15       (0x0FU << ADC_ANY_CR_JTRGSEL_Pos)       ///< EXTI 15
#define ADC_ANY_CR_JTRGSEL_TIM1_CC4     (0x10U << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM1 CC4
#define ADC_ANY_CR_JTRGSEL_TIM1_CC5     (0x11U << ADC_ANY_CR_JTRGSEL_Pos)       ///< TIM1 CC5
#define ADC_ANY_CR_JTRGSEL_EXTI_15      ADC_ANY_CR_JTRGSEL_EXTI15
#define ADC_ANY_CR_JTRGSHIFT_Pos        (13)                                    ///< select the sample time of corresponding channel
#define ADC_ANY_CR_JTRGSHIFT_0          (0x00U << ADC_ANY_CR_JTRGSHIFT_Pos)     ///< 0   cycle
#define ADC_ANY_CR_JTRGSHIFT_4          (0x01U << ADC_ANY_CR_JTRGSHIFT_Pos)     ///< 4   cycle
#define ADC_ANY_CR_JTRGSHIFT_16         (0x02U << ADC_ANY_CR_JTRGSHIFT_Pos)     ///< 16  cycle
#define ADC_ANY_CR_JTRGSHIFT_32         (0x03U << ADC_ANY_CR_JTRGSHIFT_Pos)     ///< 32  cycle
#define ADC_ANY_CR_JTRGSHIFT_64         (0x04U << ADC_ANY_CR_JTRGSHIFT_Pos)     ///< 64  cycle
#define ADC_ANY_CR_JTRGSHIFT_128        (0x05U << ADC_ANY_CR_JTRGSHIFT_Pos)     ///< 128 cycle
#define ADC_ANY_CR_JTRGSHIFT_256        (0x06U << ADC_ANY_CR_JTRGSHIFT_Pos)     ///< 256 cycle
#define ADC_ANY_CR_JTRGSHIFT_512        (0x07U << ADC_ANY_CR_JTRGSHIFT_Pos)     ///< 512 cycle
#define ADC_ANY_CR_JTRGEDGE_Pos         (16)                                    ///< Injection mode triggers edge selection
#define ADC_ANY_CR_JTRGEDGE_R_F         (0x00U << ADC_ANY_CR_JTRGEDGE_Pos)      ///< Triggered along both rising and falling edges
#define ADC_ANY_CR_JTRGEDGE_F           (0x01U << ADC_ANY_CR_JTRGEDGE_Pos)      ///< Drop edge trigger
#define ADC_ANY_CR_JTRGEDGE_R           (0x02U << ADC_ANY_CR_JTRGEDGE_Pos)      ///< Rising edge trigger
#define ADC_ANY_CR_JTRGEDGE_S           (0x03U << ADC_ANY_CR_JTRGEDGE_Pos)      ///< Shield trigger

#define ADC_ANY_CR_ADCAL_Pos            (20)
#define ADC_ANY_CR_ADCAL                (0x01U << ADC_ANY_CR_ADCAL_Pos)         ///< Calibration finish
#define ADC_ANY_CR_EOCALIE_Pos          (21)
#define ADC_ANY_CR_EOCALIE              (0x01U << ADC_ANY_CR_EOCALIE_Pos)       ///< End of calibration interrupt enable

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_ADCFG2 config  Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_ADCFG2_CORREN_Pos           (0)
#define ADC_ADCFG2_CORREN               (0x01U << ADC_ADCFG2_CORREN_Pos)        ///< Conversion correction enable
#define ADC_ADCFG2_ADCCR_Pos            (1)
#define ADC_ADCFG2_ADCCR                (0x01U << ADC_ADCFG2_ADCCR_Pos)         ///< Reference voltage selection
#define ADC_ADCFG2_ADCSREF_Pos          (2)
#define ADC_ADCFG2_ADCSREF              (0x01U << ADC_ADCFG2_ADCSREF_Pos)       ///< Reference voltage selection
#define ADC_ADCFG2_CORRVSEL_Pos         (3)
#define ADC_ADCFG2_CORRVSEL             (0x01U << ADC_ADCFG2_CORRVSEL_Pos)      ///< correct vref select 15/16 Vref
#define ADC_ADCFG2_DC_Pos               (4)
#define ADC_ADCFG2_DC_0_1               (0x01U << ADC_ADCFG2_DC_Pos)            ///< Differential channel select 0_1
#define ADC_ADCFG2_DC_2_3               (0x02U << ADC_ADCFG2_DC_Pos)            ///< Differential channel select 2_3
#define ADC_ADCFG2_DC_4_5               (0x04U << ADC_ADCFG2_DC_Pos)            ///< Differential channel select 4_5
#define ADC_ADCFG2_DC_6_7               (0x08U << ADC_ADCFG2_DC_Pos)            ///< Differential channel select 6_7
#define ADC_ADCFG2_DC_12_13             (0x10U << ADC_ADCFG2_DC_Pos)            ///< Differential channel select 12_13
#define ADC_ADCFG2_PSDC_Pos             (10)
#define ADC_ADCFG2_PSDC_0_1             (0x01U << ADC_ADCFG2_PSDC_Pos)          ///< Pseudo differential channel select 0_1
#define ADC_ADCFG2_PSDC_2_3             (0x02U << ADC_ADCFG2_PSDC_Pos)          ///< Pseudo differential channel select 2_3
#define ADC_ADCFG2_PSDC_4_5             (0x04U << ADC_ADCFG2_PSDC_Pos)          ///< Pseudo differential channel select 4_5
#define ADC_ADCFG2_PSDC_6_7             (0x08U << ADC_ADCFG2_PSDC_Pos)          ///< Pseudo differential channel select 6_7
#define ADC_ADCFG2_PSDC_12_13           (0x10U << ADC_ADCFG2_PSDC_Pos)          ///< Pseudo differential channel select 12_13
#define ADC_ADCFG2_ADCALPRE_Pos         (15)
#define ADC_ADCFG2_ADCALPRE             (0x01U << ADC_ADCFG2_ADCALPRE_Pos)      ///< calibration clk frequency division

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_SMPR1 mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_SMPR_SAMCTL_Pos             (0)                                     ///< select the sample time of corresponding channel off_set Position
#define ADC_SMPR_SAMCTL_Msk             (0x0FU << ADC_SMPR_SAMCTL_Pos)          ///< select the sample time of corresponding channel mask for Value
#define ADC_SMPR_SAMCTL_SEL_0           (0x00U << ADC_SMPR_SAMCTL_Pos)          ///< 3_5     cycle
#define ADC_SMPR_SAMCTL_SEL_1           (0x01U << ADC_SMPR_SAMCTL_Pos)          ///< 4_5     cycle
#define ADC_SMPR_SAMCTL_SEL_2           (0x02U << ADC_SMPR_SAMCTL_Pos)          ///< 5_5     cycle
#define ADC_SMPR_SAMCTL_SEL_3           (0x03U << ADC_SMPR_SAMCTL_Pos)          ///< 6_5     cycle
#define ADC_SMPR_SAMCTL_SEL_4           (0x04U << ADC_SMPR_SAMCTL_Pos)          ///< 7_5     cycle
#define ADC_SMPR_SAMCTL_SEL_5           (0x05U << ADC_SMPR_SAMCTL_Pos)          ///< 11_5    cycle
#define ADC_SMPR_SAMCTL_SEL_6           (0x06U << ADC_SMPR_SAMCTL_Pos)          ///< 13_5    cycle
#define ADC_SMPR_SAMCTL_SEL_7           (0x07U << ADC_SMPR_SAMCTL_Pos)          ///< 15_5    cycle
#define ADC_SMPR_SAMCTL_SEL_8           (0x08U << ADC_SMPR_SAMCTL_Pos)          ///< 19_5    cycle
#define ADC_SMPR_SAMCTL_SEL_9           (0x09U << ADC_SMPR_SAMCTL_Pos)          ///< 29_5    cycle
#define ADC_SMPR_SAMCTL_SEL_10          (0x0AU << ADC_SMPR_SAMCTL_Pos)          ///< 39_5    cycle
#define ADC_SMPR_SAMCTL_SEL_11          (0x0BU << ADC_SMPR_SAMCTL_Pos)          ///< 59_5    cycle
#define ADC_SMPR_SAMCTL_SEL_12          (0x0CU << ADC_SMPR_SAMCTL_Pos)          ///< 79_5    cycle
#define ADC_SMPR_SAMCTL_SEL_13          (0x0DU << ADC_SMPR_SAMCTL_Pos)          ///< 119_5   cycle
#define ADC_SMPR_SAMCTL_SEL_14          (0x0EU << ADC_SMPR_SAMCTL_Pos)          ///< 159_5   cycle
#define ADC_SMPR_SAMCTL_SEL_15          (0x0FU << ADC_SMPR_SAMCTL_Pos)          ///< 240_5   cycle

#define ADC_SMPR_SAMCTL_3_5             (0x00U << ADC_SMPR_SAMCTL_Pos)          ///< 3_5     cycle
#define ADC_SMPR_SAMCTL_4_5             (0x01U << ADC_SMPR_SAMCTL_Pos)          ///< 4_5     cycle
#define ADC_SMPR_SAMCTL_5_5             (0x02U << ADC_SMPR_SAMCTL_Pos)          ///< 5_5     cycle
#define ADC_SMPR_SAMCTL_6_5             (0x03U << ADC_SMPR_SAMCTL_Pos)          ///< 6_5     cycle
#define ADC_SMPR_SAMCTL_7_5             (0x04U << ADC_SMPR_SAMCTL_Pos)          ///< 7_5     cycle
#define ADC_SMPR_SAMCTL_11_5            (0x05U << ADC_SMPR_SAMCTL_Pos)          ///< 11_5    cycle
#define ADC_SMPR_SAMCTL_13_5            (0x06U << ADC_SMPR_SAMCTL_Pos)          ///< 13_5    cycle
#define ADC_SMPR_SAMCTL_15_5            (0x07U << ADC_SMPR_SAMCTL_Pos)          ///< 15_5    cycle
#define ADC_SMPR_SAMCTL_19_5            (0x08U << ADC_SMPR_SAMCTL_Pos)          ///< 19_5    cycle
#define ADC_SMPR_SAMCTL_29_5            (0x09U << ADC_SMPR_SAMCTL_Pos)          ///< 29_5    cycle
#define ADC_SMPR_SAMCTL_39_5            (0x0AU << ADC_SMPR_SAMCTL_Pos)          ///< 39_5    cycle
#define ADC_SMPR_SAMCTL_59_5            (0x0BU << ADC_SMPR_SAMCTL_Pos)          ///< 59_5    cycle
#define ADC_SMPR_SAMCTL_79_5            (0x0CU << ADC_SMPR_SAMCTL_Pos)          ///< 79_5    cycle
#define ADC_SMPR_SAMCTL_119_5           (0x0DU << ADC_SMPR_SAMCTL_Pos)          ///< 119_5   cycle
#define ADC_SMPR_SAMCTL_159_5           (0x0EU << ADC_SMPR_SAMCTL_Pos)          ///< 159_5   cycle
#define ADC_SMPR_SAMCTL_240_5           (0x0FU << ADC_SMPR_SAMCTL_Pos)          ///< 240_5   cycle

#define ADC_SMPR_SAMCTL_Pos_ShiftStep   (4)

#define ADC_SMPR1_SAMCTL0_Pos           (0)                                     ///< select the sample time of corresponding channel off_set Position
#define ADC_SMPR1_SAMCTL0_Msk           (0x0FU << ADC_SMPR1_SAMCTL0_Pos)        ///< select the sample time of corresponding channel mask for Value
#define ADC_SMPR1_SAMCTL0_3_5           (0x00U << ADC_SMPR1_SAMCTL0_Pos)        ///< 3_5     cycle
#define ADC_SMPR1_SAMCTL0_4_5           (0x01U << ADC_SMPR1_SAMCTL0_Pos)        ///< 4_5     cycle
#define ADC_SMPR1_SAMCTL0_5_5           (0x02U << ADC_SMPR1_SAMCTL0_Pos)        ///< 5_5     cycle
#define ADC_SMPR1_SAMCTL0_6_5           (0x03U << ADC_SMPR1_SAMCTL0_Pos)        ///< 6_5     cycle
#define ADC_SMPR1_SAMCTL0_7_5           (0x04U << ADC_SMPR1_SAMCTL0_Pos)        ///< 7_5     cycle
#define ADC_SMPR1_SAMCTL0_11_5          (0x05U << ADC_SMPR1_SAMCTL0_Pos)        ///< 11_5    cycle
#define ADC_SMPR1_SAMCTL0_13_5          (0x06U << ADC_SMPR1_SAMCTL0_Pos)        ///< 13_5    cycle
#define ADC_SMPR1_SAMCTL0_15_5          (0x07U << ADC_SMPR1_SAMCTL0_Pos)        ///< 15_5    cycle
#define ADC_SMPR1_SAMCTL0_19_5          (0x08U << ADC_SMPR1_SAMCTL0_Pos)        ///< 19_5    cycle
#define ADC_SMPR1_SAMCTL0_29_5          (0x09U << ADC_SMPR1_SAMCTL0_Pos)        ///< 29_5    cycle
#define ADC_SMPR1_SAMCTL0_39_5          (0x0AU << ADC_SMPR1_SAMCTL0_Pos)        ///< 39_5    cycle
#define ADC_SMPR1_SAMCTL0_59_5          (0x0BU << ADC_SMPR1_SAMCTL0_Pos)        ///< 59_5    cycle
#define ADC_SMPR1_SAMCTL0_79_5          (0x0CU << ADC_SMPR1_SAMCTL0_Pos)        ///< 79_5    cycle
#define ADC_SMPR1_SAMCTL0_119_5         (0x0DU << ADC_SMPR1_SAMCTL0_Pos)        ///< 119_5   cycle
#define ADC_SMPR1_SAMCTL0_159_5         (0x0EU << ADC_SMPR1_SAMCTL0_Pos)        ///< 159_5   cycle
#define ADC_SMPR1_SAMCTL0_240_5         (0x0FU << ADC_SMPR1_SAMCTL0_Pos)        ///< 240_5   cycle
#define ADC_SMPR1_SAMCTL1_Pos           (4)                                     ///< select the sample time of corresponding channel off_set Position
#define ADC_SMPR1_SAMCTL1_Msk           (0x0FU << ADC_SMPR1_SAMCTL1_Pos)        ///< select the sample time of corresponding channel mask for Value
#define ADC_SMPR1_SAMCTL1_3_5           (0x00U << ADC_SMPR1_SAMCTL1_Pos)        ///< 3_5     cycle
#define ADC_SMPR1_SAMCTL1_4_5           (0x01U << ADC_SMPR1_SAMCTL1_Pos)        ///< 4_5     cycle
#define ADC_SMPR1_SAMCTL1_5_5           (0x02U << ADC_SMPR1_SAMCTL1_Pos)        ///< 5_5     cycle
#define ADC_SMPR1_SAMCTL1_6_5           (0x03U << ADC_SMPR1_SAMCTL1_Pos)        ///< 6_5     cycle
#define ADC_SMPR1_SAMCTL1_7_5           (0x04U << ADC_SMPR1_SAMCTL1_Pos)        ///< 7_5     cycle
#define ADC_SMPR1_SAMCTL1_11_5          (0x05U << ADC_SMPR1_SAMCTL1_Pos)        ///< 11_5    cycle
#define ADC_SMPR1_SAMCTL1_13_5          (0x06U << ADC_SMPR1_SAMCTL1_Pos)        ///< 13_5    cycle
#define ADC_SMPR1_SAMCTL1_15_5          (0x07U << ADC_SMPR1_SAMCTL1_Pos)        ///< 15_5    cycle
#define ADC_SMPR1_SAMCTL1_19_5          (0x08U << ADC_SMPR1_SAMCTL1_Pos)        ///< 19_5    cycle
#define ADC_SMPR1_SAMCTL1_29_5          (0x09U << ADC_SMPR1_SAMCTL1_Pos)        ///< 29_5    cycle
#define ADC_SMPR1_SAMCTL1_39_5          (0x0AU << ADC_SMPR1_SAMCTL1_Pos)        ///< 39_5    cycle
#define ADC_SMPR1_SAMCTL1_59_5          (0x0BU << ADC_SMPR1_SAMCTL1_Pos)        ///< 59_5    cycle
#define ADC_SMPR1_SAMCTL1_79_5          (0x0CU << ADC_SMPR1_SAMCTL1_Pos)        ///< 79_5    cycle
#define ADC_SMPR1_SAMCTL1_119_5         (0x0DU << ADC_SMPR1_SAMCTL1_Pos)        ///< 119_5   cycle
#define ADC_SMPR1_SAMCTL1_159_5         (0x0EU << ADC_SMPR1_SAMCTL1_Pos)        ///< 159_5   cycle
#define ADC_SMPR1_SAMCTL1_240_5         (0x0FU << ADC_SMPR1_SAMCTL1_Pos)        ///< 240_5   cycle
#define ADC_SMPR1_SAMCTL2_Pos           (8)                                     ///< select the sample time of corresponding channel off_set Position
#define ADC_SMPR1_SAMCTL2_Msk           (0x0FU << ADC_SMPR1_SAMCTL2_Pos)        ///< select the sample time of corresponding channel mask for Value
#define ADC_SMPR1_SAMCTL2_3_5           (0x00U << ADC_SMPR1_SAMCTL2_Pos)        ///< 3_5     cycle
#define ADC_SMPR1_SAMCTL2_4_5           (0x01U << ADC_SMPR1_SAMCTL2_Pos)        ///< 4_5     cycle
#define ADC_SMPR1_SAMCTL2_5_5           (0x02U << ADC_SMPR1_SAMCTL2_Pos)        ///< 5_5     cycle
#define ADC_SMPR1_SAMCTL2_6_5           (0x03U << ADC_SMPR1_SAMCTL2_Pos)        ///< 6_5     cycle
#define ADC_SMPR1_SAMCTL2_7_5           (0x04U << ADC_SMPR1_SAMCTL2_Pos)        ///< 7_5     cycle
#define ADC_SMPR1_SAMCTL2_11_5          (0x05U << ADC_SMPR1_SAMCTL2_Pos)        ///< 11_5    cycle
#define ADC_SMPR1_SAMCTL2_13_5          (0x06U << ADC_SMPR1_SAMCTL2_Pos)        ///< 13_5    cycle
#define ADC_SMPR1_SAMCTL2_15_5          (0x07U << ADC_SMPR1_SAMCTL2_Pos)        ///< 15_5    cycle
#define ADC_SMPR1_SAMCTL2_19_5          (0x08U << ADC_SMPR1_SAMCTL2_Pos)        ///< 19_5    cycle
#define ADC_SMPR1_SAMCTL2_29_5          (0x09U << ADC_SMPR1_SAMCTL2_Pos)        ///< 29_5    cycle
#define ADC_SMPR1_SAMCTL2_39_5          (0x0AU << ADC_SMPR1_SAMCTL2_Pos)        ///< 39_5    cycle
#define ADC_SMPR1_SAMCTL2_59_5          (0x0BU << ADC_SMPR1_SAMCTL2_Pos)        ///< 59_5    cycle
#define ADC_SMPR1_SAMCTL2_79_5          (0x0CU << ADC_SMPR1_SAMCTL2_Pos)        ///< 79_5    cycle
#define ADC_SMPR1_SAMCTL2_119_5         (0x0DU << ADC_SMPR1_SAMCTL2_Pos)        ///< 119_5   cycle
#define ADC_SMPR1_SAMCTL2_159_5         (0x0EU << ADC_SMPR1_SAMCTL2_Pos)        ///< 159_5   cycle
#define ADC_SMPR1_SAMCTL2_240_5         (0x0FU << ADC_SMPR1_SAMCTL2_Pos)        ///< 240_5   cycle
#define ADC_SMPR1_SAMCTL3_Pos           (12)                                    ///< select the sample time of corresponding channel off_set Position
#define ADC_SMPR1_SAMCTL3_Msk           (0x0FU << ADC_SMPR1_SAMCTL3_Pos)        ///< select the sample time of corresponding channel mask for Value
#define ADC_SMPR1_SAMCTL3_3_5           (0x00U << ADC_SMPR1_SAMCTL3_Pos)        ///< 3_5     cycle
#define ADC_SMPR1_SAMCTL3_4_5           (0x01U << ADC_SMPR1_SAMCTL3_Pos)        ///< 4_5     cycle
#define ADC_SMPR1_SAMCTL3_5_5           (0x02U << ADC_SMPR1_SAMCTL3_Pos)        ///< 5_5     cycle
#define ADC_SMPR1_SAMCTL3_6_5           (0x03U << ADC_SMPR1_SAMCTL3_Pos)        ///< 6_5     cycle
#define ADC_SMPR1_SAMCTL3_7_5           (0x04U << ADC_SMPR1_SAMCTL3_Pos)        ///< 7_5     cycle
#define ADC_SMPR1_SAMCTL3_11_5          (0x05U << ADC_SMPR1_SAMCTL3_Pos)        ///< 11_5    cycle
#define ADC_SMPR1_SAMCTL3_13_5          (0x06U << ADC_SMPR1_SAMCTL3_Pos)        ///< 13_5    cycle
#define ADC_SMPR1_SAMCTL3_15_5          (0x07U << ADC_SMPR1_SAMCTL3_Pos)        ///< 15_5    cycle
#define ADC_SMPR1_SAMCTL3_19_5          (0x08U << ADC_SMPR1_SAMCTL3_Pos)        ///< 19_5    cycle
#define ADC_SMPR1_SAMCTL3_29_5          (0x09U << ADC_SMPR1_SAMCTL3_Pos)        ///< 29_5    cycle
#define ADC_SMPR1_SAMCTL3_39_5          (0x0AU << ADC_SMPR1_SAMCTL3_Pos)        ///< 39_5    cycle
#define ADC_SMPR1_SAMCTL3_59_5          (0x0BU << ADC_SMPR1_SAMCTL3_Pos)        ///< 59_5    cycle
#define ADC_SMPR1_SAMCTL3_79_5          (0x0CU << ADC_SMPR1_SAMCTL3_Pos)        ///< 79_5    cycle
#define ADC_SMPR1_SAMCTL3_119_5         (0x0DU << ADC_SMPR1_SAMCTL3_Pos)        ///< 119_5   cycle
#define ADC_SMPR1_SAMCTL3_159_5         (0x0EU << ADC_SMPR1_SAMCTL3_Pos)        ///< 159_5   cycle
#define ADC_SMPR1_SAMCTL3_240_5         (0x0FU << ADC_SMPR1_SAMCTL3_Pos)        ///< 240_5   cycle
#define ADC_SMPR1_SAMCTL4_Pos           (16)                                    ///< select the sample time of corresponding channel off_set Position
#define ADC_SMPR1_SAMCTL4_Msk           (0x0FU << ADC_SMPR1_SAMCTL4_Pos)        ///< select the sample time of corresponding channel mask for Value
#define ADC_SMPR1_SAMCTL4_3_5           (0x00U << ADC_SMPR1_SAMCTL4_Pos)        ///< 3_5     cycle
#define ADC_SMPR1_SAMCTL4_4_5           (0x01U << ADC_SMPR1_SAMCTL4_Pos)        ///< 4_5     cycle
#define ADC_SMPR1_SAMCTL4_5_5           (0x02U << ADC_SMPR1_SAMCTL4_Pos)        ///< 5_5     cycle
#define ADC_SMPR1_SAMCTL4_6_5           (0x03U << ADC_SMPR1_SAMCTL4_Pos)        ///< 6_5     cycle
#define ADC_SMPR1_SAMCTL4_7_5           (0x04U << ADC_SMPR1_SAMCTL4_Pos)        ///< 7_5     cycle
#define ADC_SMPR1_SAMCTL4_11_5          (0x05U << ADC_SMPR1_SAMCTL4_Pos)        ///< 11_5    cycle
#define ADC_SMPR1_SAMCTL4_13_5          (0x06U << ADC_SMPR1_SAMCTL4_Pos)        ///< 13_5    cycle
#define ADC_SMPR1_SAMCTL4_15_5          (0x07U << ADC_SMPR1_SAMCTL4_Pos)        ///< 15_5    cycle
#define ADC_SMPR1_SAMCTL4_19_5          (0x08U << ADC_SMPR1_SAMCTL4_Pos)        ///< 19_5    cycle
#define ADC_SMPR1_SAMCTL4_29_5          (0x09U << ADC_SMPR1_SAMCTL4_Pos)        ///< 29_5    cycle
#define ADC_SMPR1_SAMCTL4_39_5          (0x0AU << ADC_SMPR1_SAMCTL4_Pos)        ///< 39_5    cycle
#define ADC_SMPR1_SAMCTL4_59_5          (0x0BU << ADC_SMPR1_SAMCTL4_Pos)        ///< 59_5    cycle
#define ADC_SMPR1_SAMCTL4_79_5          (0x0CU << ADC_SMPR1_SAMCTL4_Pos)        ///< 79_5    cycle
#define ADC_SMPR1_SAMCTL4_119_5         (0x0DU << ADC_SMPR1_SAMCTL4_Pos)        ///< 119_5   cycle
#define ADC_SMPR1_SAMCTL4_159_5         (0x0EU << ADC_SMPR1_SAMCTL4_Pos)        ///< 159_5   cycle
#define ADC_SMPR1_SAMCTL4_240_5         (0x0FU << ADC_SMPR1_SAMCTL4_Pos)        ///< 240_5   cycle
#define ADC_SMPR1_SAMCTL5_Pos           (20)                                    ///< select the sample time of corresponding channel off_set Position
#define ADC_SMPR1_SAMCTL5_Msk           (0x0FU << ADC_SMPR1_SAMCTL5_Pos)        ///< select the sample time of corresponding channel mask for Value
#define ADC_SMPR1_SAMCTL5_3_5           (0x00U << ADC_SMPR1_SAMCTL5_Pos)        ///< 3_5     cycle
#define ADC_SMPR1_SAMCTL5_4_5           (0x01U << ADC_SMPR1_SAMCTL5_Pos)        ///< 4_5     cycle
#define ADC_SMPR1_SAMCTL5_5_5           (0x02U << ADC_SMPR1_SAMCTL5_Pos)        ///< 5_5     cycle
#define ADC_SMPR1_SAMCTL5_6_5           (0x03U << ADC_SMPR1_SAMCTL5_Pos)        ///< 6_5     cycle
#define ADC_SMPR1_SAMCTL5_7_5           (0x04U << ADC_SMPR1_SAMCTL5_Pos)        ///< 7_5     cycle
#define ADC_SMPR1_SAMCTL5_11_5          (0x05U << ADC_SMPR1_SAMCTL5_Pos)        ///< 11_5    cycle
#define ADC_SMPR1_SAMCTL5_13_5          (0x06U << ADC_SMPR1_SAMCTL5_Pos)        ///< 13_5    cycle
#define ADC_SMPR1_SAMCTL5_15_5          (0x07U << ADC_SMPR1_SAMCTL5_Pos)        ///< 15_5    cycle
#define ADC_SMPR1_SAMCTL5_19_5          (0x08U << ADC_SMPR1_SAMCTL5_Pos)        ///< 19_5    cycle
#define ADC_SMPR1_SAMCTL5_29_5          (0x09U << ADC_SMPR1_SAMCTL5_Pos)        ///< 29_5    cycle
#define ADC_SMPR1_SAMCTL5_39_5          (0x0AU << ADC_SMPR1_SAMCTL5_Pos)        ///< 39_5    cycle
#define ADC_SMPR1_SAMCTL5_59_5          (0x0BU << ADC_SMPR1_SAMCTL5_Pos)        ///< 59_5    cycle
#define ADC_SMPR1_SAMCTL5_79_5          (0x0CU << ADC_SMPR1_SAMCTL5_Pos)        ///< 79_5    cycle
#define ADC_SMPR1_SAMCTL5_119_5         (0x0DU << ADC_SMPR1_SAMCTL5_Pos)        ///< 119_5   cycle
#define ADC_SMPR1_SAMCTL5_159_5         (0x0EU << ADC_SMPR1_SAMCTL5_Pos)        ///< 159_5   cycle
#define ADC_SMPR1_SAMCTL5_240_5         (0x0FU << ADC_SMPR1_SAMCTL5_Pos)        ///< 240_5   cycle
#define ADC_SMPR1_SAMCTL6_Pos           (24)                                    ///< select the sample time of corresponding channel off_set Position
#define ADC_SMPR1_SAMCTL6_Msk           (0x0FU << ADC_SMPR1_SAMCTL6_Pos)        ///< select the sample time of corresponding channel mask for Value
#define ADC_SMPR1_SAMCTL6_3_5           (0x00U << ADC_SMPR1_SAMCTL6_Pos)        ///< 3_5     cycle
#define ADC_SMPR1_SAMCTL6_4_5           (0x01U << ADC_SMPR1_SAMCTL6_Pos)        ///< 4_5     cycle
#define ADC_SMPR1_SAMCTL6_5_5           (0x02U << ADC_SMPR1_SAMCTL6_Pos)        ///< 5_5     cycle
#define ADC_SMPR1_SAMCTL6_6_5           (0x03U << ADC_SMPR1_SAMCTL6_Pos)        ///< 6_5     cycle
#define ADC_SMPR1_SAMCTL6_7_5           (0x04U << ADC_SMPR1_SAMCTL6_Pos)        ///< 7_5     cycle
#define ADC_SMPR1_SAMCTL6_11_5          (0x05U << ADC_SMPR1_SAMCTL6_Pos)        ///< 11_5    cycle
#define ADC_SMPR1_SAMCTL6_13_5          (0x06U << ADC_SMPR1_SAMCTL6_Pos)        ///< 13_5    cycle
#define ADC_SMPR1_SAMCTL6_15_5          (0x07U << ADC_SMPR1_SAMCTL6_Pos)        ///< 15_5    cycle
#define ADC_SMPR1_SAMCTL6_19_5          (0x08U << ADC_SMPR1_SAMCTL6_Pos)        ///< 19_5    cycle
#define ADC_SMPR1_SAMCTL6_29_5          (0x09U << ADC_SMPR1_SAMCTL6_Pos)        ///< 29_5    cycle
#define ADC_SMPR1_SAMCTL6_39_5          (0x0AU << ADC_SMPR1_SAMCTL6_Pos)        ///< 39_5    cycle
#define ADC_SMPR1_SAMCTL6_59_5          (0x0BU << ADC_SMPR1_SAMCTL6_Pos)        ///< 59_5    cycle
#define ADC_SMPR1_SAMCTL6_79_5          (0x0CU << ADC_SMPR1_SAMCTL6_Pos)        ///< 79_5    cycle
#define ADC_SMPR1_SAMCTL6_119_5         (0x0DU << ADC_SMPR1_SAMCTL6_Pos)        ///< 119_5   cycle
#define ADC_SMPR1_SAMCTL6_159_5         (0x0EU << ADC_SMPR1_SAMCTL6_Pos)        ///< 159_5   cycle
#define ADC_SMPR1_SAMCTL6_240_5         (0x0FU << ADC_SMPR1_SAMCTL6_Pos)        ///< 240_5   cycle
#define ADC_SMPR1_SAMCTL7_Pos           (28)                                    ///< select the sample time of corresponding channel off_set Position
#define ADC_SMPR1_SAMCTL7_Msk           (0x0FU << ADC_SMPR1_SAMCTL7_Pos)        ///< select the sample time of corresponding channel mask for Value
#define ADC_SMPR1_SAMCTL7_3_5           (0x00U << ADC_SMPR1_SAMCTL7_Pos)        ///< 3_5     cycle
#define ADC_SMPR1_SAMCTL7_4_5           (0x01U << ADC_SMPR1_SAMCTL7_Pos)        ///< 4_5     cycle
#define ADC_SMPR1_SAMCTL7_5_5           (0x02U << ADC_SMPR1_SAMCTL7_Pos)        ///< 5_5     cycle
#define ADC_SMPR1_SAMCTL7_6_5           (0x03U << ADC_SMPR1_SAMCTL7_Pos)        ///< 6_5     cycle
#define ADC_SMPR1_SAMCTL7_7_5           (0x04U << ADC_SMPR1_SAMCTL7_Pos)        ///< 7_5     cycle
#define ADC_SMPR1_SAMCTL7_11_5          (0x05U << ADC_SMPR1_SAMCTL7_Pos)        ///< 11_5    cycle
#define ADC_SMPR1_SAMCTL7_13_5          (0x06U << ADC_SMPR1_SAMCTL7_Pos)        ///< 13_5    cycle
#define ADC_SMPR1_SAMCTL7_15_5          (0x07U << ADC_SMPR1_SAMCTL7_Pos)        ///< 15_5    cycle
#define ADC_SMPR1_SAMCTL7_19_5          (0x08U << ADC_SMPR1_SAMCTL7_Pos)        ///< 19_5    cycle
#define ADC_SMPR1_SAMCTL7_29_5          (0x09U << ADC_SMPR1_SAMCTL7_Pos)        ///< 29_5    cycle
#define ADC_SMPR1_SAMCTL7_39_5          (0x0AU << ADC_SMPR1_SAMCTL7_Pos)        ///< 39_5    cycle
#define ADC_SMPR1_SAMCTL7_59_5          (0x0BU << ADC_SMPR1_SAMCTL7_Pos)        ///< 59_5    cycle
#define ADC_SMPR1_SAMCTL7_79_5          (0x0CU << ADC_SMPR1_SAMCTL7_Pos)        ///< 79_5    cycle
#define ADC_SMPR1_SAMCTL7_119_5         (0x0DU << ADC_SMPR1_SAMCTL7_Pos)        ///< 119_5   cycle
#define ADC_SMPR1_SAMCTL7_159_5         (0x0EU << ADC_SMPR1_SAMCTL7_Pos)        ///< 159_5   cycle
#define ADC_SMPR1_SAMCTL7_240_5         (0x0FU << ADC_SMPR1_SAMCTL7_Pos)        ///< 240_5   cycle

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_SMPR2 mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_SMPR2_SAMCTL8_Pos           (0)                                     ///< select the sample time of corresponding channel off_set Position
#define ADC_SMPR2_SAMCTL8_Msk           (0x0FU << ADC_SMPR2_SAMCTL8_Pos)        ///< select the sample time of corresponding channel mask for Value
#define ADC_SMPR2_SAMCTL8_3_5           (0x00U << ADC_SMPR2_SAMCTL8_Pos)        ///< 3_5     cycle
#define ADC_SMPR2_SAMCTL8_4_5           (0x01U << ADC_SMPR2_SAMCTL8_Pos)        ///< 4_5     cycle
#define ADC_SMPR2_SAMCTL8_5_5           (0x02U << ADC_SMPR2_SAMCTL8_Pos)        ///< 5_5     cycle
#define ADC_SMPR2_SAMCTL8_6_5           (0x03U << ADC_SMPR2_SAMCTL8_Pos)        ///< 6_5     cycle
#define ADC_SMPR2_SAMCTL8_7_5           (0x04U << ADC_SMPR2_SAMCTL8_Pos)        ///< 7_5     cycle
#define ADC_SMPR2_SAMCTL8_11_5          (0x05U << ADC_SMPR2_SAMCTL8_Pos)        ///< 11_5    cycle
#define ADC_SMPR2_SAMCTL8_13_5          (0x06U << ADC_SMPR2_SAMCTL8_Pos)        ///< 13_5    cycle
#define ADC_SMPR2_SAMCTL8_15_5          (0x07U << ADC_SMPR2_SAMCTL8_Pos)        ///< 15_5    cycle
#define ADC_SMPR2_SAMCTL8_19_5          (0x08U << ADC_SMPR2_SAMCTL8_Pos)        ///< 19_5    cycle
#define ADC_SMPR2_SAMCTL8_29_5          (0x09U << ADC_SMPR2_SAMCTL8_Pos)        ///< 29_5    cycle
#define ADC_SMPR2_SAMCTL8_39_5          (0x0AU << ADC_SMPR2_SAMCTL8_Pos)        ///< 39_5    cycle
#define ADC_SMPR2_SAMCTL8_59_5          (0x0BU << ADC_SMPR2_SAMCTL8_Pos)        ///< 59_5    cycle
#define ADC_SMPR2_SAMCTL8_79_5          (0x0CU << ADC_SMPR2_SAMCTL8_Pos)        ///< 79_5    cycle
#define ADC_SMPR2_SAMCTL8_119_5         (0x0DU << ADC_SMPR2_SAMCTL8_Pos)        ///< 119_5   cycle
#define ADC_SMPR2_SAMCTL8_159_5         (0x0EU << ADC_SMPR2_SAMCTL8_Pos)        ///< 159_5   cycle
#define ADC_SMPR2_SAMCTL8_240_5         (0x0FU << ADC_SMPR2_SAMCTL8_Pos)        ///< 240_5   cycle
#define ADC_SMPR2_SAMCTL9_Pos           (4)                                     ///< select the sample time of corresponding channel off_set Position
#define ADC_SMPR2_SAMCTL9_Msk           (0x0FU << ADC_SMPR2_SAMCTL9_Pos)        ///< select the sample time of corresponding channel mask for Value
#define ADC_SMPR2_SAMCTL9_3_5           (0x00U << ADC_SMPR2_SAMCTL9_Pos)        ///< 3_5     cycle
#define ADC_SMPR2_SAMCTL9_4_5           (0x01U << ADC_SMPR2_SAMCTL9_Pos)        ///< 4_5     cycle
#define ADC_SMPR2_SAMCTL9_5_5           (0x02U << ADC_SMPR2_SAMCTL9_Pos)        ///< 5_5     cycle
#define ADC_SMPR2_SAMCTL9_6_5           (0x03U << ADC_SMPR2_SAMCTL9_Pos)        ///< 6_5     cycle
#define ADC_SMPR2_SAMCTL9_7_5           (0x04U << ADC_SMPR2_SAMCTL9_Pos)        ///< 7_5     cycle
#define ADC_SMPR2_SAMCTL9_11_5          (0x05U << ADC_SMPR2_SAMCTL9_Pos)        ///< 11_5    cycle
#define ADC_SMPR2_SAMCTL9_13_5          (0x06U << ADC_SMPR2_SAMCTL9_Pos)        ///< 13_5    cycle
#define ADC_SMPR2_SAMCTL9_15_5          (0x07U << ADC_SMPR2_SAMCTL9_Pos)        ///< 15_5    cycle
#define ADC_SMPR2_SAMCTL9_19_5          (0x08U << ADC_SMPR2_SAMCTL9_Pos)        ///< 19_5    cycle
#define ADC_SMPR2_SAMCTL9_29_5          (0x09U << ADC_SMPR2_SAMCTL9_Pos)        ///< 29_5    cycle
#define ADC_SMPR2_SAMCTL9_39_5          (0x0AU << ADC_SMPR2_SAMCTL9_Pos)        ///< 39_5    cycle
#define ADC_SMPR2_SAMCTL9_59_5          (0x0BU << ADC_SMPR2_SAMCTL9_Pos)        ///< 59_5    cycle
#define ADC_SMPR2_SAMCTL9_79_5          (0x0CU << ADC_SMPR2_SAMCTL9_Pos)        ///< 79_5    cycle
#define ADC_SMPR2_SAMCTL9_119_5         (0x0DU << ADC_SMPR2_SAMCTL9_Pos)        ///< 119_5   cycle
#define ADC_SMPR2_SAMCTL9_159_5         (0x0EU << ADC_SMPR2_SAMCTL9_Pos)        ///< 159_5   cycle
#define ADC_SMPR2_SAMCTL9_240_5         (0x0FU << ADC_SMPR2_SAMCTL9_Pos)        ///< 240_5   cycle
#define ADC_SMPR2_SAMCTL10_Pos          (8)                                     ///< select the sample time of corresponding channel off_set Position
#define ADC_SMPR2_SAMCTL10_Msk          (0x0FU << ADC_SMPR2_SAMCTL10_Pos)       ///< select the sample time of corresponding channel mask for Value
#define ADC_SMPR2_SAMCTL10_3_5          (0x00U << ADC_SMPR2_SAMCTL10_Pos)       ///< 3_5     cycle
#define ADC_SMPR2_SAMCTL10_4_5          (0x01U << ADC_SMPR2_SAMCTL10_Pos)       ///< 4_5     cycle
#define ADC_SMPR2_SAMCTL10_5_5          (0x02U << ADC_SMPR2_SAMCTL10_Pos)       ///< 5_5     cycle
#define ADC_SMPR2_SAMCTL10_6_5          (0x03U << ADC_SMPR2_SAMCTL10_Pos)       ///< 6_5     cycle
#define ADC_SMPR2_SAMCTL10_7_5          (0x04U << ADC_SMPR2_SAMCTL10_Pos)       ///< 7_5     cycle
#define ADC_SMPR2_SAMCTL10_11_5         (0x05U << ADC_SMPR2_SAMCTL10_Pos)       ///< 11_5    cycle
#define ADC_SMPR2_SAMCTL10_13_5         (0x06U << ADC_SMPR2_SAMCTL10_Pos)       ///< 13_5    cycle
#define ADC_SMPR2_SAMCTL10_15_5         (0x07U << ADC_SMPR2_SAMCTL10_Pos)       ///< 15_5    cycle
#define ADC_SMPR2_SAMCTL10_19_5         (0x08U << ADC_SMPR2_SAMCTL10_Pos)       ///< 19_5    cycle
#define ADC_SMPR2_SAMCTL10_29_5         (0x09U << ADC_SMPR2_SAMCTL10_Pos)       ///< 29_5    cycle
#define ADC_SMPR2_SAMCTL10_39_5         (0x0AU << ADC_SMPR2_SAMCTL10_Pos)       ///< 39_5    cycle
#define ADC_SMPR2_SAMCTL10_59_5         (0x0BU << ADC_SMPR2_SAMCTL10_Pos)       ///< 59_5    cycle
#define ADC_SMPR2_SAMCTL10_79_5         (0x0CU << ADC_SMPR2_SAMCTL10_Pos)       ///< 79_5    cycle
#define ADC_SMPR2_SAMCTL10_119_5        (0x0DU << ADC_SMPR2_SAMCTL10_Pos)       ///< 119_5   cycle
#define ADC_SMPR2_SAMCTL10_159_5        (0x0EU << ADC_SMPR2_SAMCTL10_Pos)       ///< 159_5   cycle
#define ADC_SMPR2_SAMCTL10_240_5        (0x0FU << ADC_SMPR2_SAMCTL10_Pos)       ///< 240_5   cycle
#define ADC_SMPR2_SAMCTL11_Pos          (12)                                    ///< select the sample time of corresponding channel off_set Position
#define ADC_SMPR2_SAMCTL11_Msk          (0x0FU << ADC_SMPR2_SAMCTL11_Pos)       ///< select the sample time of corresponding channel mask for Value
#define ADC_SMPR2_SAMCTL11_3_5          (0x00U << ADC_SMPR2_SAMCTL11_Pos)       ///< 3_5     cycle
#define ADC_SMPR2_SAMCTL11_4_5          (0x01U << ADC_SMPR2_SAMCTL11_Pos)       ///< 4_5     cycle
#define ADC_SMPR2_SAMCTL11_5_5          (0x02U << ADC_SMPR2_SAMCTL11_Pos)       ///< 5_5     cycle
#define ADC_SMPR2_SAMCTL11_6_5          (0x03U << ADC_SMPR2_SAMCTL11_Pos)       ///< 6_5     cycle
#define ADC_SMPR2_SAMCTL11_7_5          (0x04U << ADC_SMPR2_SAMCTL11_Pos)       ///< 7_5     cycle
#define ADC_SMPR2_SAMCTL11_11_5         (0x05U << ADC_SMPR2_SAMCTL11_Pos)       ///< 11_5    cycle
#define ADC_SMPR2_SAMCTL11_13_5         (0x06U << ADC_SMPR2_SAMCTL11_Pos)       ///< 13_5    cycle
#define ADC_SMPR2_SAMCTL11_15_5         (0x07U << ADC_SMPR2_SAMCTL11_Pos)       ///< 15_5    cycle
#define ADC_SMPR2_SAMCTL11_19_5         (0x08U << ADC_SMPR2_SAMCTL11_Pos)       ///< 19_5    cycle
#define ADC_SMPR2_SAMCTL11_29_5         (0x09U << ADC_SMPR2_SAMCTL11_Pos)       ///< 29_5    cycle
#define ADC_SMPR2_SAMCTL11_39_5         (0x0AU << ADC_SMPR2_SAMCTL11_Pos)       ///< 39_5    cycle
#define ADC_SMPR2_SAMCTL11_59_5         (0x0BU << ADC_SMPR2_SAMCTL11_Pos)       ///< 59_5    cycle
#define ADC_SMPR2_SAMCTL11_79_5         (0x0CU << ADC_SMPR2_SAMCTL11_Pos)       ///< 79_5    cycle
#define ADC_SMPR2_SAMCTL11_119_5        (0x0DU << ADC_SMPR2_SAMCTL11_Pos)       ///< 119_5   cycle
#define ADC_SMPR2_SAMCTL11_159_5        (0x0EU << ADC_SMPR2_SAMCTL11_Pos)       ///< 159_5   cycle
#define ADC_SMPR2_SAMCTL11_240_5        (0x0FU << ADC_SMPR2_SAMCTL11_Pos)       ///< 240_5   cycle
#define ADC_SMPR2_SAMCTL12_Pos          (16)                                    ///< select the sample time of corresponding channel off_set Position
#define ADC_SMPR2_SAMCTL12_Msk          (0x0FU << ADC_SMPR2_SAMCTL12_Pos)       ///< select the sample time of corresponding channel mask for Value
#define ADC_SMPR2_SAMCTL12_3_5          (0x00U << ADC_SMPR2_SAMCTL12_Pos)       ///< 3_5     cycle
#define ADC_SMPR2_SAMCTL12_4_5          (0x01U << ADC_SMPR2_SAMCTL12_Pos)       ///< 4_5     cycle
#define ADC_SMPR2_SAMCTL12_5_5          (0x02U << ADC_SMPR2_SAMCTL12_Pos)       ///< 5_5     cycle
#define ADC_SMPR2_SAMCTL12_6_5          (0x03U << ADC_SMPR2_SAMCTL12_Pos)       ///< 6_5     cycle
#define ADC_SMPR2_SAMCTL12_7_5          (0x04U << ADC_SMPR2_SAMCTL12_Pos)       ///< 7_5     cycle
#define ADC_SMPR2_SAMCTL12_11_5         (0x05U << ADC_SMPR2_SAMCTL12_Pos)       ///< 11_5    cycle
#define ADC_SMPR2_SAMCTL12_13_5         (0x06U << ADC_SMPR2_SAMCTL12_Pos)       ///< 13_5    cycle
#define ADC_SMPR2_SAMCTL12_15_5         (0x07U << ADC_SMPR2_SAMCTL12_Pos)       ///< 15_5    cycle
#define ADC_SMPR2_SAMCTL12_19_5         (0x08U << ADC_SMPR2_SAMCTL12_Pos)       ///< 19_5    cycle
#define ADC_SMPR2_SAMCTL12_29_5         (0x09U << ADC_SMPR2_SAMCTL12_Pos)       ///< 29_5    cycle
#define ADC_SMPR2_SAMCTL12_39_5         (0x0AU << ADC_SMPR2_SAMCTL12_Pos)       ///< 39_5    cycle
#define ADC_SMPR2_SAMCTL12_59_5         (0x0BU << ADC_SMPR2_SAMCTL12_Pos)       ///< 59_5    cycle
#define ADC_SMPR2_SAMCTL12_79_5         (0x0CU << ADC_SMPR2_SAMCTL12_Pos)       ///< 79_5    cycle
#define ADC_SMPR2_SAMCTL12_119_5        (0x0DU << ADC_SMPR2_SAMCTL12_Pos)       ///< 119_5   cycle
#define ADC_SMPR2_SAMCTL12_159_5        (0x0EU << ADC_SMPR2_SAMCTL12_Pos)       ///< 159_5   cycle
#define ADC_SMPR2_SAMCTL12_240_5        (0x0FU << ADC_SMPR2_SAMCTL12_Pos)       ///< 240_5   cycle
#define ADC_SMPR2_SAMCTL13_Pos          (20)                                    ///< select the sample time of corresponding channel off_set Position
#define ADC_SMPR2_SAMCTL13_Msk          (0x0FU << ADC_SMPR2_SAMCTL13_Pos)       ///< select the sample time of corresponding channel mask for Value
#define ADC_SMPR2_SAMCTL13_3_5          (0x00U << ADC_SMPR2_SAMCTL13_Pos)       ///< 3_5     cycle
#define ADC_SMPR2_SAMCTL13_4_5          (0x01U << ADC_SMPR2_SAMCTL13_Pos)       ///< 4_5     cycle
#define ADC_SMPR2_SAMCTL13_5_5          (0x02U << ADC_SMPR2_SAMCTL13_Pos)       ///< 5_5     cycle
#define ADC_SMPR2_SAMCTL13_6_5          (0x03U << ADC_SMPR2_SAMCTL13_Pos)       ///< 6_5     cycle
#define ADC_SMPR2_SAMCTL13_7_5          (0x04U << ADC_SMPR2_SAMCTL13_Pos)       ///< 7_5     cycle
#define ADC_SMPR2_SAMCTL13_11_5         (0x05U << ADC_SMPR2_SAMCTL13_Pos)       ///< 11_5    cycle
#define ADC_SMPR2_SAMCTL13_13_5         (0x06U << ADC_SMPR2_SAMCTL13_Pos)       ///< 13_5    cycle
#define ADC_SMPR2_SAMCTL13_15_5         (0x07U << ADC_SMPR2_SAMCTL13_Pos)       ///< 15_5    cycle
#define ADC_SMPR2_SAMCTL13_19_5         (0x08U << ADC_SMPR2_SAMCTL13_Pos)       ///< 19_5    cycle
#define ADC_SMPR2_SAMCTL13_29_5         (0x09U << ADC_SMPR2_SAMCTL13_Pos)       ///< 29_5    cycle
#define ADC_SMPR2_SAMCTL13_39_5         (0x0AU << ADC_SMPR2_SAMCTL13_Pos)       ///< 39_5    cycle
#define ADC_SMPR2_SAMCTL13_59_5         (0x0BU << ADC_SMPR2_SAMCTL13_Pos)       ///< 59_5    cycle
#define ADC_SMPR2_SAMCTL13_79_5         (0x0CU << ADC_SMPR2_SAMCTL13_Pos)       ///< 79_5    cycle
#define ADC_SMPR2_SAMCTL13_119_5        (0x0DU << ADC_SMPR2_SAMCTL13_Pos)       ///< 119_5   cycle
#define ADC_SMPR2_SAMCTL13_159_5        (0x0EU << ADC_SMPR2_SAMCTL13_Pos)       ///< 159_5   cycle
#define ADC_SMPR2_SAMCTL13_240_5        (0x0FU << ADC_SMPR2_SAMCTL13_Pos)       ///< 240_5   cycle
#define ADC_SMPR2_SAMCTL14_Pos          (24)                                    ///< select the sample time of corresponding channel off_set Position
#define ADC_SMPR2_SAMCTL14_Msk          (0x0FU << ADC_SMPR2_SAMCTL14_Pos)       ///< select the sample time of corresponding channel mask for Value
#define ADC_SMPR2_SAMCTL14_3_5          (0x00U << ADC_SMPR2_SAMCTL14_Pos)       ///< 3_5     cycle
#define ADC_SMPR2_SAMCTL14_4_5          (0x01U << ADC_SMPR2_SAMCTL14_Pos)       ///< 4_5     cycle
#define ADC_SMPR2_SAMCTL14_5_5          (0x02U << ADC_SMPR2_SAMCTL14_Pos)       ///< 5_5     cycle
#define ADC_SMPR2_SAMCTL14_6_5          (0x03U << ADC_SMPR2_SAMCTL14_Pos)       ///< 6_5     cycle
#define ADC_SMPR2_SAMCTL14_7_5          (0x04U << ADC_SMPR2_SAMCTL14_Pos)       ///< 7_5     cycle
#define ADC_SMPR2_SAMCTL14_11_5         (0x05U << ADC_SMPR2_SAMCTL14_Pos)       ///< 11_5    cycle
#define ADC_SMPR2_SAMCTL14_13_5         (0x06U << ADC_SMPR2_SAMCTL14_Pos)       ///< 13_5    cycle
#define ADC_SMPR2_SAMCTL14_15_5         (0x07U << ADC_SMPR2_SAMCTL14_Pos)       ///< 15_5    cycle
#define ADC_SMPR2_SAMCTL14_19_5         (0x08U << ADC_SMPR2_SAMCTL14_Pos)       ///< 19_5    cycle
#define ADC_SMPR2_SAMCTL14_29_5         (0x09U << ADC_SMPR2_SAMCTL14_Pos)       ///< 29_5    cycle
#define ADC_SMPR2_SAMCTL14_39_5         (0x0AU << ADC_SMPR2_SAMCTL14_Pos)       ///< 39_5    cycle
#define ADC_SMPR2_SAMCTL14_59_5         (0x0BU << ADC_SMPR2_SAMCTL14_Pos)       ///< 59_5    cycle
#define ADC_SMPR2_SAMCTL14_79_5         (0x0CU << ADC_SMPR2_SAMCTL14_Pos)       ///< 79_5    cycle
#define ADC_SMPR2_SAMCTL14_119_5        (0x0DU << ADC_SMPR2_SAMCTL14_Pos)       ///< 119_5   cycle
#define ADC_SMPR2_SAMCTL14_159_5        (0x0EU << ADC_SMPR2_SAMCTL14_Pos)       ///< 159_5   cycle
#define ADC_SMPR2_SAMCTL14_240_5        (0x0FU << ADC_SMPR2_SAMCTL14_Pos)       ///< 240_5   cycle
#define ADC_SMPR2_SAMCTL15_Pos          (28)                                    ///< select the sample time of corresponding channel off_set Position
#define ADC_SMPR2_SAMCTL15_Msk          (0x0FU << ADC_SMPR2_SAMCTL15_Pos)       ///< select the sample time of corresponding channel mask for Value
#define ADC_SMPR2_SAMCTL15_3_5          (0x00U << ADC_SMPR2_SAMCTL15_Pos)       ///< 3_5     cycle
#define ADC_SMPR2_SAMCTL15_4_5          (0x01U << ADC_SMPR2_SAMCTL15_Pos)       ///< 4_5     cycle
#define ADC_SMPR2_SAMCTL15_5_5          (0x02U << ADC_SMPR2_SAMCTL15_Pos)       ///< 5_5     cycle
#define ADC_SMPR2_SAMCTL15_6_5          (0x03U << ADC_SMPR2_SAMCTL15_Pos)       ///< 6_5     cycle
#define ADC_SMPR2_SAMCTL15_7_5          (0x04U << ADC_SMPR2_SAMCTL15_Pos)       ///< 7_5     cycle
#define ADC_SMPR2_SAMCTL15_11_5         (0x05U << ADC_SMPR2_SAMCTL15_Pos)       ///< 11_5    cycle
#define ADC_SMPR2_SAMCTL15_13_5         (0x06U << ADC_SMPR2_SAMCTL15_Pos)       ///< 13_5    cycle
#define ADC_SMPR2_SAMCTL15_15_5         (0x07U << ADC_SMPR2_SAMCTL15_Pos)       ///< 15_5    cycle
#define ADC_SMPR2_SAMCTL15_19_5         (0x08U << ADC_SMPR2_SAMCTL15_Pos)       ///< 19_5    cycle
#define ADC_SMPR2_SAMCTL15_29_5         (0x09U << ADC_SMPR2_SAMCTL15_Pos)       ///< 29_5    cycle
#define ADC_SMPR2_SAMCTL15_39_5         (0x0AU << ADC_SMPR2_SAMCTL15_Pos)       ///< 39_5    cycle
#define ADC_SMPR2_SAMCTL15_59_5         (0x0BU << ADC_SMPR2_SAMCTL15_Pos)       ///< 59_5    cycle
#define ADC_SMPR2_SAMCTL15_79_5         (0x0CU << ADC_SMPR2_SAMCTL15_Pos)       ///< 79_5    cycle
#define ADC_SMPR2_SAMCTL15_119_5        (0x0DU << ADC_SMPR2_SAMCTL15_Pos)       ///< 119_5   cycle
#define ADC_SMPR2_SAMCTL15_159_5        (0x0EU << ADC_SMPR2_SAMCTL15_Pos)       ///< 159_5   cycle
#define ADC_SMPR2_SAMCTL15_240_5        (0x0FU << ADC_SMPR2_SAMCTL15_Pos)       ///< 240_5   cycle
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_JOFR0 mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_JOFR0_JOFR                  (0xFFFU)                                ///< Compensates for the A/D conversion results of the injected channel 0
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_JOFR1 mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_JOFR1_JOFR                  (0xFFFU)                                ///< Compensates for the A/D conversion results of the injected channel 1
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_JOFR2 mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_JOFR2_JOFR                  (0xFFFU)                                ///< Compensates for the A/D conversion results of the injected channel 2
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_JOFR3 mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_JOFR3_JOFR                  (0xFFFU)                                ///< Compensates for the A/D conversion results of the injected channel 3
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_JSQR mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_JSQR_JSQ0_Pos               (0)                                     ///< 1st conversion in injected sequence
#define ADC_JSQR_JSQ0                   (0x1FU << ADC_JSQR_JSQ0_Pos)            ///< 0th Conversion for Injected Sequence
#define ADC_JSQR_JSQ0_CH0               (0x00U << ADC_JSQR_JSQ0_Pos)            ///< Configure any channel 0 as injection channel 0
#define ADC_JSQR_JSQ0_CH1               (0x01U << ADC_JSQR_JSQ0_Pos)            ///< Configure any channel 1 as injection channel 0
#define ADC_JSQR_JSQ0_CH2               (0x02U << ADC_JSQR_JSQ0_Pos)            ///< Configure any channel 2 as injection channel 0
#define ADC_JSQR_JSQ0_CH3               (0x03U << ADC_JSQR_JSQ0_Pos)            ///< Configure any channel 3 as injection channel 0
#define ADC_JSQR_JSQ0_CH4               (0x04U << ADC_JSQR_JSQ0_Pos)            ///< Configure any channel 4 as injection channel 0
#define ADC_JSQR_JSQ0_CH5               (0x05U << ADC_JSQR_JSQ0_Pos)            ///< Configure any channel 5 as injection channel 0
#define ADC_JSQR_JSQ0_CH6               (0x06U << ADC_JSQR_JSQ0_Pos)            ///< Configure any channel 6 as injection channel 0
#define ADC_JSQR_JSQ0_CH7               (0x07U << ADC_JSQR_JSQ0_Pos)            ///< Configure any channel 7 as injection channel 0
#define ADC_JSQR_JSQ0_CH8               (0x08U << ADC_JSQR_JSQ0_Pos)            ///< Configure any channel 8 as injection channel 0
#define ADC_JSQR_JSQ0_CH9               (0x09U << ADC_JSQR_JSQ0_Pos)            ///< Configure any channel 9 as injection channel 0
#define ADC_JSQR_JSQ0_CH10              (0x0AU << ADC_JSQR_JSQ0_Pos)            ///< Configure any channel 10 as injection channel 0
#define ADC_JSQR_JSQ0_CH11              (0x0BU << ADC_JSQR_JSQ0_Pos)            ///< Configure any channel 11 as injection channel 0
#define ADC_JSQR_JSQ0_CH12              (0x0CU << ADC_JSQR_JSQ0_Pos)            ///< Configure any channel 12 as injection channel 0
#define ADC_JSQR_JSQ0_CH13              (0x0DU << ADC_JSQR_JSQ0_Pos)            ///< Configure any channel 13 as injection channel 0
#define ADC_JSQR_JSQ0_CH14              (0x0EU << ADC_JSQR_JSQ0_Pos)            ///< Configure any channel 14 as injection channel 0
#define ADC_JSQR_JSQ0_CH15              (0x0FU << ADC_JSQR_JSQ0_Pos)            ///< Configure any channel 15 as injection channel 0
#define ADC_JSQR_JSQ0_0                 (0x01U << ADC_JSQR_JSQ0_Pos)            ///< Bit 0
#define ADC_JSQR_JSQ0_1                 (0x02U << ADC_JSQR_JSQ0_Pos)            ///< Bit 1
#define ADC_JSQR_JSQ0_2                 (0x04U << ADC_JSQR_JSQ0_Pos)            ///< Bit 2
#define ADC_JSQR_JSQ0_3                 (0x08U << ADC_JSQR_JSQ0_Pos)            ///< Bit 3
#define ADC_JSQR_JSQ0_4                 (0x10U << ADC_JSQR_JSQ0_Pos)            ///< Bit 4
#define ADC_JSQR_JSQ1_Pos               (5)                                     ///< 2st conversion in injected sequence
#define ADC_JSQR_JSQ1                   (0x1FU << ADC_JSQR_JSQ1_Pos)            ///< 1th Conversion for Injected Sequence
#define ADC_JSQR_JSQ1_CH0               (0x00U << ADC_JSQR_JSQ1_Pos)            ///< Configure any channel 0 as injection channel 1
#define ADC_JSQR_JSQ1_CH1               (0x01U << ADC_JSQR_JSQ1_Pos)            ///< Configure any channel 1 as injection channel 1
#define ADC_JSQR_JSQ1_CH2               (0x02U << ADC_JSQR_JSQ1_Pos)            ///< Configure any channel 2 as injection channel 1
#define ADC_JSQR_JSQ1_CH3               (0x03U << ADC_JSQR_JSQ1_Pos)            ///< Configure any channel 3 as injection channel 1
#define ADC_JSQR_JSQ1_CH4               (0x04U << ADC_JSQR_JSQ1_Pos)            ///< Configure any channel 4 as injection channel 1
#define ADC_JSQR_JSQ1_CH5               (0x05U << ADC_JSQR_JSQ1_Pos)            ///< Configure any channel 5 as injection channel 1
#define ADC_JSQR_JSQ1_CH6               (0x06U << ADC_JSQR_JSQ1_Pos)            ///< Configure any channel 6 as injection channel 1
#define ADC_JSQR_JSQ1_CH7               (0x07U << ADC_JSQR_JSQ1_Pos)            ///< Configure any channel 7 as injection channel 1
#define ADC_JSQR_JSQ1_CH8               (0x08U << ADC_JSQR_JSQ1_Pos)            ///< Configure any channel 8 as injection channel 1
#define ADC_JSQR_JSQ1_CH9               (0x09U << ADC_JSQR_JSQ1_Pos)            ///< Configure any channel 9 as injection channel 1
#define ADC_JSQR_JSQ1_CH10              (0x0AU << ADC_JSQR_JSQ1_Pos)            ///< Configure any channel 10 as injection channel 1
#define ADC_JSQR_JSQ1_CH11              (0x0BU << ADC_JSQR_JSQ1_Pos)            ///< Configure any channel 11 as injection channel 1
#define ADC_JSQR_JSQ1_CH12              (0x0CU << ADC_JSQR_JSQ1_Pos)            ///< Configure any channel 12 as injection channel 1
#define ADC_JSQR_JSQ1_CH13              (0x0DU << ADC_JSQR_JSQ1_Pos)            ///< Configure any channel 13 as injection channel 1
#define ADC_JSQR_JSQ1_CH14              (0x0EU << ADC_JSQR_JSQ1_Pos)            ///< Configure any channel 14 as injection channel 1
#define ADC_JSQR_JSQ1_CH15              (0x0FU << ADC_JSQR_JSQ1_Pos)            ///< Configure any channel 15 as injection channel 1
#define ADC_JSQR_JSQ1_0                 (0x01U << ADC_JSQR_JSQ1_Pos)            ///< Bit 0
#define ADC_JSQR_JSQ1_1                 (0x02U << ADC_JSQR_JSQ1_Pos)            ///< Bit 1
#define ADC_JSQR_JSQ1_2                 (0x04U << ADC_JSQR_JSQ1_Pos)            ///< Bit 2
#define ADC_JSQR_JSQ1_3                 (0x08U << ADC_JSQR_JSQ1_Pos)            ///< Bit 3
#define ADC_JSQR_JSQ1_4                 (0x10U << ADC_JSQR_JSQ1_Pos)            ///< Bit 4
#define ADC_JSQR_JSQ2_Pos               (10)                                    ///< 3st conversion in injected sequence
#define ADC_JSQR_JSQ2                   (0x1FU << ADC_JSQR_JSQ2_Pos)            ///< 2th Conversion for Injected Sequence
#define ADC_JSQR_JSQ2_CH0               (0x00U << ADC_JSQR_JSQ2_Pos)            ///< Configure any channel 0 as injection channel 2
#define ADC_JSQR_JSQ2_CH1               (0x01U << ADC_JSQR_JSQ2_Pos)            ///< Configure any channel 1 as injection channel 2
#define ADC_JSQR_JSQ2_CH2               (0x02U << ADC_JSQR_JSQ2_Pos)            ///< Configure any channel 2 as injection channel 2
#define ADC_JSQR_JSQ2_CH3               (0x03U << ADC_JSQR_JSQ2_Pos)            ///< Configure any channel 3 as injection channel 2
#define ADC_JSQR_JSQ2_CH4               (0x04U << ADC_JSQR_JSQ2_Pos)            ///< Configure any channel 4 as injection channel 2
#define ADC_JSQR_JSQ2_CH5               (0x05U << ADC_JSQR_JSQ2_Pos)            ///< Configure any channel 5 as injection channel 2
#define ADC_JSQR_JSQ2_CH6               (0x06U << ADC_JSQR_JSQ2_Pos)            ///< Configure any channel 6 as injection channel 2
#define ADC_JSQR_JSQ2_CH7               (0x07U << ADC_JSQR_JSQ2_Pos)            ///< Configure any channel 7 as injection channel 2
#define ADC_JSQR_JSQ2_CH8               (0x08U << ADC_JSQR_JSQ2_Pos)            ///< Configure any channel 8 as injection channel 2
#define ADC_JSQR_JSQ2_CH9               (0x09U << ADC_JSQR_JSQ2_Pos)            ///< Configure any channel 9 as injection channel 2
#define ADC_JSQR_JSQ2_CH10              (0x0AU << ADC_JSQR_JSQ2_Pos)            ///< Configure any channel 10 as injection channel 2
#define ADC_JSQR_JSQ2_CH11              (0x0BU << ADC_JSQR_JSQ2_Pos)            ///< Configure any channel 11 as injection channel 2
#define ADC_JSQR_JSQ2_CH12              (0x0CU << ADC_JSQR_JSQ2_Pos)            ///< Configure any channel 12 as injection channel 2
#define ADC_JSQR_JSQ2_CH13              (0x0DU << ADC_JSQR_JSQ2_Pos)            ///< Configure any channel 13 as injection channel 2
#define ADC_JSQR_JSQ2_CH14              (0x0EU << ADC_JSQR_JSQ2_Pos)            ///< Configure any channel 14 as injection channel 2
#define ADC_JSQR_JSQ2_CH15              (0x0FU << ADC_JSQR_JSQ2_Pos)            ///< Configure any channel 15 as injection channel 2
#define ADC_JSQR_JSQ2_0                 (0x01U << ADC_JSQR_JSQ2_Pos)            ///< Bit 0
#define ADC_JSQR_JSQ2_1                 (0x02U << ADC_JSQR_JSQ2_Pos)            ///< Bit 1
#define ADC_JSQR_JSQ2_2                 (0x04U << ADC_JSQR_JSQ2_Pos)            ///< Bit 2
#define ADC_JSQR_JSQ2_3                 (0x08U << ADC_JSQR_JSQ2_Pos)            ///< Bit 3
#define ADC_JSQR_JSQ2_4                 (0x10U << ADC_JSQR_JSQ2_Pos)            ///< Bit 4
#define ADC_JSQR_JSQ3_Pos               (15)                                    ///< 4st conversion in injected sequence
#define ADC_JSQR_JSQ3                   (0x1FU << ADC_JSQR_JSQ3_Pos)            ///< 3th Conversion for Injected Sequence
#define ADC_JSQR_JSQ3_CH0               (0x00U << ADC_JSQR_JSQ3_Pos)            ///< Configure any channel 0 as injection channel 3
#define ADC_JSQR_JSQ3_CH1               (0x01U << ADC_JSQR_JSQ3_Pos)            ///< Configure any channel 1 as injection channel 3
#define ADC_JSQR_JSQ3_CH2               (0x02U << ADC_JSQR_JSQ3_Pos)            ///< Configure any channel 2 as injection channel 3
#define ADC_JSQR_JSQ3_CH3               (0x03U << ADC_JSQR_JSQ3_Pos)            ///< Configure any channel 3 as injection channel 3
#define ADC_JSQR_JSQ3_CH4               (0x04U << ADC_JSQR_JSQ3_Pos)            ///< Configure any channel 4 as injection channel 3
#define ADC_JSQR_JSQ3_CH5               (0x05U << ADC_JSQR_JSQ3_Pos)            ///< Configure any channel 5 as injection channel 3
#define ADC_JSQR_JSQ3_CH6               (0x06U << ADC_JSQR_JSQ3_Pos)            ///< Configure any channel 6 as injection channel 3
#define ADC_JSQR_JSQ3_CH7               (0x07U << ADC_JSQR_JSQ3_Pos)            ///< Configure any channel 7 as injection channel 3
#define ADC_JSQR_JSQ3_CH8               (0x08U << ADC_JSQR_JSQ3_Pos)            ///< Configure any channel 8 as injection channel 3
#define ADC_JSQR_JSQ3_CH9               (0x09U << ADC_JSQR_JSQ3_Pos)            ///< Configure any channel 9 as injection channel 3
#define ADC_JSQR_JSQ3_CH10              (0x0AU << ADC_JSQR_JSQ3_Pos)            ///< Configure any channel 10 as injection channel 3
#define ADC_JSQR_JSQ3_CH11              (0x0BU << ADC_JSQR_JSQ3_Pos)            ///< Configure any channel 11 as injection channel 3
#define ADC_JSQR_JSQ3_CH12              (0x0CU << ADC_JSQR_JSQ3_Pos)            ///< Configure any channel 12 as injection channel 3
#define ADC_JSQR_JSQ3_CH13              (0x0DU << ADC_JSQR_JSQ3_Pos)            ///< Configure any channel 13 as injection channel 3
#define ADC_JSQR_JSQ3_CH14              (0x0EU << ADC_JSQR_JSQ3_Pos)            ///< Configure any channel 14 as injection channel 3
#define ADC_JSQR_JSQ3_CH15              (0x0FU << ADC_JSQR_JSQ3_Pos)            ///< Configure any channel 15 as injection channel 3
#define ADC_JSQR_JSQ3_0                 (0x01U << ADC_JSQR_JSQ3_Pos)            ///< Bit 0
#define ADC_JSQR_JSQ3_1                 (0x02U << ADC_JSQR_JSQ3_Pos)            ///< Bit 1
#define ADC_JSQR_JSQ3_2                 (0x04U << ADC_JSQR_JSQ3_Pos)            ///< Bit 2
#define ADC_JSQR_JSQ3_3                 (0x08U << ADC_JSQR_JSQ3_Pos)            ///< Bit 3
#define ADC_JSQR_JSQ3_4                 (0x10U << ADC_JSQR_JSQ3_Pos)            ///< Bit 4

#define ADC_JSQR_JNUM_Pos               (20)
#define ADC_JSQR_JNUM                   (0x03U << ADC_JSQR_JNUM_Pos)            ///< Channel Number for Injected Sequence mask
#define ADC_JSQR_JNUM_MODE0             (0x00U << ADC_JSQR_JNUM_Pos)            ///< JSQ0 channel only
#define ADC_JSQR_JNUM_MODE1             (0x01U << ADC_JSQR_JNUM_Pos)            ///< JSQ0~JSQ1 channels
#define ADC_JSQR_JNUM_MODE2             (0x02U << ADC_JSQR_JNUM_Pos)            ///< JSQ0~JSQ2 channels
#define ADC_JSQR_JNUM_MODE3             (0x03U << ADC_JSQR_JNUM_Pos)            ///< JSQ0~JSQ3 channels

#define ADC_JSQR_JNUM_0                 (0x01U << ADC_JSQR_JNUM_Pos)            ///< Channel Number for Injected Sequence bit 0
#define ADC_JSQR_JNUM_1                 (0x02U << ADC_JSQR_JNUM_Pos)            ///< Channel Number for Injected Sequence bit 1
#define ADC_JSQR_JNUM_JSQ0              ADC_JSQR_JNUM_MODE0
#define ADC_JSQR_JNUM_JSQ0_JSQ1         ADC_JSQR_JNUM_MODE1
#define ADC_JSQR_JNUM_JSQ0_JSQ2         ADC_JSQR_JNUM_MODE2
#define ADC_JSQR_JNUM_JSQ0_JSQ3         ADC_JSQR_JNUM_MODE3
#define ADC_JSQR_JL_Pos                 ADC_JSQR_JNUM_Pos
#define ADC_JSQR_JL                     ADC_JSQR_JNUM
#define ADC_JSQR_JL_0                   ADC_JSQR_JNUM_0
#define ADC_JSQR_JL_1                   ADC_JSQR_JNUM_1

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_JDATA mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_JDATA_JDATA_Pos             (0)
#define ADC_JDATA_JDATA                 (0xFFFFU << ADC_JDATA_JDATA_Pos)        ///< Transfer data
#define ADC_JDATA_JCHANNELSEL_Pos       (16)
#define ADC_JDATA_JCHANNELSEL           (0x1FU << ADC_JDATA_JCHANNELSEL_Pos)    ///< Channel selection
#define ADC_JDATA_JCHANNELSEL_CHAN0     (0x00U << ADC_JDATA_JCHANNELSEL_Pos)    ///< conversion data of channel 0
#define ADC_JDATA_JCHANNELSEL_CHAN1     (0x01U << ADC_JDATA_JCHANNELSEL_Pos)    ///< conversion data of channel 1
#define ADC_JDATA_JCHANNELSEL_CHAN2     (0x02U << ADC_JDATA_JCHANNELSEL_Pos)    ///< conversion data of channel 2
#define ADC_JDATA_JCHANNELSEL_CHAN3     (0x03U << ADC_JDATA_JCHANNELSEL_Pos)    ///< conversion data of channel 3
#define ADC_JDATA_JCHANNELSEL_CHAN4     (0x04U << ADC_JDATA_JCHANNELSEL_Pos)    ///< conversion data of channel 4
#define ADC_JDATA_JCHANNELSEL_CHAN5     (0x05U << ADC_JDATA_JCHANNELSEL_Pos)    ///< conversion data of channel 5
#define ADC_JDATA_JCHANNELSEL_CHAN6     (0x06U << ADC_JDATA_JCHANNELSEL_Pos)    ///< conversion data of channel 6
#define ADC_JDATA_JCHANNELSEL_CHAN7     (0x07U << ADC_JDATA_JCHANNELSEL_Pos)    ///< conversion data of channel 7
#define ADC_JDATA_JCHANNELSEL_CHAN8     (0x08U << ADC_JDATA_JCHANNELSEL_Pos)    ///< conversion data of channel 8
#define ADC_JDATA_JCHANNELSEL_CHAN9     (0x09U << ADC_JDATA_JCHANNELSEL_Pos)    ///< conversion data of channel 9
#define ADC_JDATA_JCHANNELSEL_CHAN10    (0x0AU << ADC_JDATA_JCHANNELSEL_Pos)    ///< conversion data of channel 10
#define ADC_JDATA_JCHANNELSEL_CHAN11    (0x0BU << ADC_JDATA_JCHANNELSEL_Pos)    ///< conversion data of channel 11
#define ADC_JDATA_JCHANNELSEL_CHAN12    (0x0CU << ADC_JDATA_JCHANNELSEL_Pos)    ///< conversion data of channel 12
#define ADC_JDATA_JCHANNELSEL_CHAN13    (0x0DU << ADC_JDATA_JCHANNELSEL_Pos)    ///< conversion data of channel 13
#define ADC_JDATA_JCHANNELSEL_CHAN14    (0x0EU << ADC_JDATA_JCHANNELSEL_Pos)    ///< conversion data of channel 14
#define ADC_JDATA_JCHANNELSEL_CHAN15    (0x0FU << ADC_JDATA_JCHANNELSEL_Pos)    ///< conversion data of channel 15
#define ADC_JDATA_JOVERRUN_Pos          (21)
#define ADC_JDATA_JOVERRUN              (0x01U << ADC_JDATA_JOVERRUN_Pos)       ///< Overrun flag
#define ADC_JDATA_JVALID_Pos            (22)
#define ADC_JDATA_JVALID                (0x01U << ADC_JDATA_JVALID_Pos)         ///< Valid flag

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CORRS mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_CORRS_GAINCORR_Pos          (0)
#define ADC_CORRS_GAINCORR              (0xFFFU << ADC_CORRS_GAINCORR_Pos)      ///< 12-bit gain correction parameter
#define ADC_CORRS_OFFSETCORR_Pos        (16)
#define ADC_CORRS_OFFSETCORR            (0xFFFU << ADC_CORRS_OFFSETCORR_Pos)    ///< 12-bit offset correction parameter

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CORRD mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_CORRD_GAINCORR_Pos          (0)
#define ADC_CORRD_GAINCORR              (0xFFFU << ADC_CORRD_GAINCORR_Pos)      ///< 12-bit gain correction parameter
#define ADC_CORRD_OFFSETCORR_Pos        (16)
#define ADC_CORRD_OFFSETCORR            (0xFFFU << ADC_CORRD_OFFSETCORR_Pos)    ///< 12-bit offset correction parameter

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CORRP mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_CORRP_GAINCORR_Pos          (0)
#define ADC_CORRP_GAINCORR              (0xFFFU << ADC_CORRP_GAINCORR_Pos)      ///< 12-bit gain correction parameter
#define ADC_CORRP_OFFSETCORR_Pos        (16)
#define ADC_CORRP_OFFSETCORR            (0xFFFU << ADC_CORRP_OFFSETCORR_Pos)    ///< 12-bit offset correction parameter

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_JDR0 mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_JDR0_JDATA_Pos              (0)
#define ADC_JDR0_JDATA                  (0xFFFFU << ADC_JDR0_JDATA_Pos)         ///< Transfer data
#define ADC_JDR0_JOVERRUN_Pos           (21)
#define ADC_JDR0_JOVERRUN               (0x01U << ADC_JDR0_JOVERRUN_Pos)        ///< Overrun flag
#define ADC_JDR0_JVALID_Pos             (22)
#define ADC_JDR0_JVALID                 (0x01U << ADC_JDR0_JVALID_Pos)          ///< Valid flag

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_JDR1 mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_JDR1_JDATA_Pos              (0)
#define ADC_JDR1_JDATA                  (0xFFFFU << ADC_JDR1_JDATA_Pos)         ///< Transfer data
#define ADC_JDR1_JOVERRUN_Pos           (21)
#define ADC_JDR1_JOVERRUN               (0x01U << ADC_JDR1_JOVERRUN_Pos)        ///< Overrun flag
#define ADC_JDR1_JVALID_Pos             (22)
#define ADC_JDR1_JVALID                 (0x01U << ADC_JDR1_JVALID_Pos)          ///< Valid flag

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_JDR2 mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_JDR2_JDATA_Pos              (0)
#define ADC_JDR2_JDATA                  (0xFFFFU << ADC_JDR2_JDATA_Pos)         ///< Transfer data
#define ADC_JDR2_JOVERRUN_Pos           (21)
#define ADC_JDR2_JOVERRUN               (0x01U << ADC_JDR2_JOVERRUN_Pos)        ///< Overrun flag
#define ADC_JDR2_JVALID_Pos             (22)
#define ADC_JDR2_JVALID                 (0x01U << ADC_JDR2_JVALID_Pos)          ///< Valid flag

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_JDR3 mode enable Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC_JDR3_JDATA_Pos              (0)
#define ADC_JDR3_JDATA                  (0xFFFFU << ADC_JDR3_JDATA_Pos)         ///< Transfer data
#define ADC_JDR3_JOVERRUN_Pos           (21)
#define ADC_JDR3_JOVERRUN               (0x01U << ADC_JDR3_JOVERRUN_Pos)        ///< Overrun flag
#define ADC_JDR3_JVALID_Pos             (22)
#define ADC_JDR3_JVALID                 (0x01U << ADC_JDR3_JVALID_Pos)          ///< Valid flag

/// @}

/// @}

/// @}

#ifdef __cplusplus
}
#endif

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
