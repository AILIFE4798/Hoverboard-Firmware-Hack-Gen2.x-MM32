////////////////////////////////////////////////////////////////////////////////
/// @file     hal_adc.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE ADC
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
#ifndef __HAL_ADC_H
#define __HAL_ADC_H

// Files includes
#include "types.h"
#include "reg_adc.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup ADC_HAL
/// @brief ADC HAL modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup ADC_Exported_Types
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Channels
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_Channel_0 = 0x00,                   ///< ADC Channel 0
    ADC_Channel_1 = 0x01,                   ///< ADC Channel 1
    ADC_Channel_2 = 0x02,                   ///< ADC Channel 2
    ADC_Channel_3 = 0x03,                   ///< ADC Channel 3
    ADC_Channel_4 = 0x04,                   ///< ADC Channel 4
    ADC_Channel_5 = 0x05,                   ///< ADC Channel 5
    ADC_Channel_6 = 0x06,                   ///< ADC Channel 6
    ADC_Channel_7 = 0x07,                   ///< ADC Channel 7


    ADC_Channel_8               = 0x08,     ///< ADC Channel 8
    ADC_Channel_9               = 0x09,     ///< ADC Channel 9
    ADC_Channel_TempSensor      = 0x0E,     ///< Temperature sensor channel
    ADC_Channel_VoltReference   = 0x0F,     ///< Internal reference voltage(ADC1) channel
    ADC_Channel_Vrefint         = 0x0F,     ///< Internal reference voltage(ADC1) channel
    ADC_Channel_10              = 0x0A,     ///< ADC Channel 10
    ADC_Channel_11              = 0x0B,     ///< ADC Channel 11
    ADC_Channel_12              = 0x0C,     ///< ADC Channel 12
} ADCCHANNEL_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Sampling_Times
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_Samctl_2_5 = ADC_CFGR_SAMCTL_2_5,  ///< ADC sample time select 2.5t
    ADC_Samctl_3_5 = ADC_CFGR_SAMCTL_3_5,  ///< ADC sample time select 3.5t
    ADC_Samctl_4_5 = ADC_CFGR_SAMCTL_4_5,  ///< ADC sample time select 4.5t
    ADC_Samctl_5_5 = ADC_CFGR_SAMCTL_5_5,  ///< ADC sample time select 5.5t
    ADC_Samctl_6_5 = ADC_CFGR_SAMCTL_6_5,  ///< ADC sample time select 6.5t

    ADC_Samctl_1_5   = ADC_CFGR_SAMCTL_1_5,   ///< ADC sample time select 1.5t
    ADC_Samctl_7_5   = ADC_CFGR_SAMCTL_7_5,   ///< ADC sample time select 7.5t
    ADC_Samctl_13_5  = ADC_CFGR_SAMCTL_13_5,  ///< ADC sample time select 13.5t
    ADC_Samctl_28_5  = ADC_CFGR_SAMCTL_28_5,  ///< ADC sample time select 28.5t
    ADC_Samctl_41_5  = ADC_CFGR_SAMCTL_41_5,  ///< ADC sample time select 41.5t
    ADC_Samctl_55_5  = ADC_CFGR_SAMCTL_55_5,  ///< ADC sample time select 55.5t
    ADC_Samctl_71_5  = ADC_CFGR_SAMCTL_71_5,  ///< ADC sample time select 71.5t
    ADC_Samctl_239_5 = ADC_CFGR_SAMCTL_239_5  ///< ADC sample time select 239.5t
} ADCSAM_TypeDef;


////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Resolution
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_Resolution_12b = ADC_CFGR_RSLTCTL_12,  ///< ADC resolution select 12bit
    ADC_Resolution_11b = ADC_CFGR_RSLTCTL_11,  ///< ADC resolution select 11bit
    ADC_Resolution_10b = ADC_CFGR_RSLTCTL_10,  ///< ADC resolution select 10bit
    ADC_Resolution_9b  = ADC_CFGR_RSLTCTL_9,   ///< ADC resolution select 9bit
    ADC_Resolution_8b  = ADC_CFGR_RSLTCTL_8    ///< ADC resolution select 8bit
} ADCRSL_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_PRESCALE
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_PCLK2_PRESCALE_3  = ADC_CFGR_PRE_3,   ///< ADC preclk 3
    ADC_PCLK2_PRESCALE_5  = ADC_CFGR_PRE_5,   ///< ADC preclk 5
    ADC_PCLK2_PRESCALE_7  = ADC_CFGR_PRE_7,   ///< ADC preclk 7
    ADC_PCLK2_PRESCALE_9  = ADC_CFGR_PRE_9,   ///< ADC preclk 9
    ADC_PCLK2_PRESCALE_11 = ADC_CFGR_PRE_11,  ///< ADC preclk 11
    ADC_PCLK2_PRESCALE_13 = ADC_CFGR_PRE_13,  ///< ADC preclk 13
    ADC_PCLK2_PRESCALE_15 = ADC_CFGR_PRE_15,  ///< ADC preclk 15
    ADC_PCLK2_PRESCALE_17 = ADC_CFGR_PRE_17,  ///< ADC preclk 17

    ADC_PCLK2_PRESCALE_2  = ADC_CFGR_PRE_2,   ///< ADC preclk 2
    ADC_PCLK2_PRESCALE_4  = ADC_CFGR_PRE_4,   ///< ADC preclk 4
    ADC_PCLK2_PRESCALE_6  = ADC_CFGR_PRE_6,   ///< ADC preclk 6
    ADC_PCLK2_PRESCALE_8  = ADC_CFGR_PRE_8,   ///< ADC preclk 8
    ADC_PCLK2_PRESCALE_10 = ADC_CFGR_PRE_10,  ///< ADC preclk 10
    ADC_PCLK2_PRESCALE_12 = ADC_CFGR_PRE_12,  ///< ADC preclk 12
    ADC_PCLK2_PRESCALE_14 = ADC_CFGR_PRE_14,  ///< ADC preclk 14
    ADC_PCLK2_PRESCALE_16 = ADC_CFGR_PRE_16   ///< ADC preclk 16
} ADCPRE_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Conversion_Mode
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_Mode_Imm        = ADC_CR_IMM,       ///< ADC single convert mode
    ADC_Mode_Scan       = ADC_CR_SCAN,      ///< ADC single period convert mode
    ADC_Mode_Continue   = ADC_CR_CONTINUE   ///< ADC continue scan convert mode
} ADCMODE_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Extrenal_Trigger_Sources_For_Regular_Channels_Conversion
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC1_ExternalTrigConv_T1_CC1        = ADC_CR_T1_CC1,
    ADC1_ExternalTrigConv_T1_CC2        = ADC_CR_T1_CC2,
    ADC1_ExternalTrigConv_T1_CC3        = ADC_CR_T1_CC3,
    ADC1_ExternalTrigConv_T2_CC2        = ADC_CR_T2_CC2,
    ADC1_ExternalTrigConv_T3_TRIG       = ADC_CR_T3_TRIG,
    ADC1_ExternalTrigConv_T3_CC1        = ADC_CR_T3_CC1,
    ADC1_ExternalTrigConv_EXTI_11       = ADC_CR_EXTI_11,
    ADC1_ExternalTrigConv_T1_CC4_CC5    = ADC_CR_T1_CC4_CC5,
    ADC1_ExternalTrigConv_T1_TRIG       = ADC_CR_T1_TRIG,
    ADC1_ExternalTrigConv_T2_CC1        = ADC_CR_T2_CC1,
    ADC1_ExternalTrigConv_T3_CC4        = ADC_CR_T3_CC4,
    ADC1_ExternalTrigConv_T2_TRIG       = ADC_CR_T2_TRIG,
    ADC1_ExternalTrigConv_EXTI_15       = ADC_CR_EXTI_15,
    ADC1_ExternalTrigConv_T1_CC4        = ADC_CR_TIM1_CC4,
    ADC1_ExternalTrigConv_T1_CC5        = ADC_CR_TIM1_CC5
} EXTERTRIG_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Data_Align
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_DataAlign_Right = ADC_CR_RIGHT,     ///< ADC data left align
    ADC_DataAlign_Left  = ADC_CR_LEFT       ///< ADC data right align
} ADCDATAALI_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Flags_Definition
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_IT_EOC = 1,                            ///< ADC conversion flag
    ADC_FLAG_EOC = 1,
    ADC_IT_AWD = 2,                            ///< ADC window comparator flag
    ADC_FLAG_AWD = 2
} ADCFLAG_TypeDef;



////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Scan_Direct
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_Scan_Direct_Up = ADC_CR_SCANDIR,     ///< ADC scan from low channel to high channel
    ADC_Scan_Direct_Down  = 0                ///< ADC scan from High channel to low channel
} ADCSCANDIRECT_TypeDef;
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_Trig_Shift
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    ADC_ADC_Trig_Shift_0    = ADC_CR_TRGSHIFT_0,     ///< ADC trig shift bit is 0
    ADC_ADC_Trig_Shift_4    = ADC_CR_TRGSHIFT_4,     ///< ADC trig shift bit is 4
    ADC_ADC_Trig_Shift_16   = ADC_CR_TRGSHIFT_16,    ///< ADC trig shift bit is 16
    ADC_ADC_Trig_Shift_32   = ADC_CR_TRGSHIFT_32,    ///< ADC trig shift bit is 32
    ADC_ADC_Trig_Shift_64   = ADC_CR_TRGSHIFT_64,    ///< ADC trig shift bit is 64
    ADC_ADC_Trig_Shift_128  = ADC_CR_TRGSHIFT_128,   ///< ADC trig shift bit is 128
    ADC_ADC_Trig_Shift_256  = ADC_CR_TRGSHIFT_256,   ///< ADC trig shift bit is 256
    ADC_ADC_Trig_Shift_512  = ADC_CR_TRGSHIFT_512,   ///< ADC trig shift bit is 512
} ADCTRIGSHIFT_TypeDef;
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC Init Structure definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    u32                     ADC_Resolution;             ///< Convert data resolution
    u32                     ADC_PRESCALE;               ///< Clock prescaler
    u32                     ADC_Mode;                   ///< ADC conversion mode
    FunctionalState         ADC_ContinuousConvMode;     ///< Useless just for compatibility
    u32                     ADC_ExternalTrigConv;       ///< External trigger source selection
    u32                     ADC_DataAlign;              ///< Data alignmentn
} ADC_InitTypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief Extern ADC Init Structure definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    ADCRSL_TypeDef          ADC_Resolution;             ///< Convert data resolution
    ADCPRE_TypeDef          ADC_PRESCALE;               ///< Clock prescaler
    ADCMODE_TypeDef         ADC_Mode;                   ///< ADC conversion mode
    EXTERTRIG_TypeDef       ADC_ExternalTrigConv;       ///< External trigger source selection
    ADCDATAALI_TypeDef      ADC_DataAlign;              ///< Data alignmentn
} exADC_InitTypeDef;

/// @}






////////////////////////////////////////////////////////////////////////////////
/// @defgroup ADC_Exported_Variables
/// @{
#ifdef _HAL_ADC_C_

#define GLOBAL
#else
#define GLOBAL extern
#endif

#undef GLOBAL
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup ADC_Exported_Functions
/// @{
void ADC_DeInit(ADC_TypeDef* adc);
void ADC_Init(ADC_TypeDef* adc, ADC_InitTypeDef* init_struct);
void ADC_StructInit(ADC_InitTypeDef* init_struct);
void ADC_Cmd(ADC_TypeDef* adc, FunctionalState state);
void ADC_DMACmd(ADC_TypeDef* adc, FunctionalState state);
void ADC_ITConfig(ADC_TypeDef* adc, ADCFLAG_TypeDef adc_interrupt, FunctionalState state);
void ADC_SoftwareStartConvCmd(ADC_TypeDef* adc, FunctionalState state);
void ADC_RegularChannelConfig(ADC_TypeDef* adc, u32 channel, u8 rank, u32 sample_time);//ADCSAM_TypeDef
void ADC_ExternalTrigConvCmd(ADC_TypeDef* adc, FunctionalState state);
void ADC_ExternalTrigInjectedConvConfig(ADC_TypeDef* adc, EXTERTRIG_TypeDef adc_external_trig_source);
void ADC_AnalogWatchdogCmd(ADC_TypeDef* adc, FunctionalState state);
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* adc, u16 high_threshold, u16 low_threshold);
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* adc, ADCCHANNEL_TypeDef channel);
void ADC_TempSensorVrefintCmd(FunctionalState state);
void ADC_ClearITPendingBit(ADC_TypeDef* adc, ADCFLAG_TypeDef adc_interrupt);
void ADC_ClearFlag(ADC_TypeDef* adc, ADCFLAG_TypeDef adc_flag);

u32 ADC_GetConversionValue(ADC_TypeDef* adc);

FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* adc);
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* adc, ADCFLAG_TypeDef adc_flag);
ITStatus   ADC_GetITStatus(ADC_TypeDef* adc, ADCFLAG_TypeDef adc_interrupt);
void ADC_TempSensorCmd(FunctionalState state);
void ADC_VrefintCmd(FunctionalState state);
void exADC_TempSensorVrefintCmd(u32 chs, FunctionalState state);

/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

