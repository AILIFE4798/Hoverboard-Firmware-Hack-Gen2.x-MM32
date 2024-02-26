/**
******************************************************************************
* @file     HAL_adc.c
* @author   AE team
* @version  V1.1.0
* @date     09/09/2019
* @brief    This file provides all the ADC firmware functions.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2019 MindMotion</center></h2>
*/

/* Includes ------------------------------------------------------------------*/
#include "HAL_adc.h"
#include "HAL_rcc.h"

/** @addtogroup StdPeriph_Driver
* @{
*/

/** @defgroup ADC
* @brief ADC driver modules
* @{
*/

/** @defgroup ADC_Private_TypesDefinitions
* @{
*/

/**
* @}
*/

/** @defgroup ADC_Private_Defines
* @{
*/

/* ADCR register Mask */
#define ADCR_CLEAR_Mask              ((uint32_t)0xFF000080)

/* ADCFG register Mask */
#define ADCFG_CLEAR_Mask             ((uint32_t)0xFFFF8000)
#define ADCFG_SAMCTL_Set             ((uint32_t)0x3c00)
#define ADCFG_TSEN_Set               ((uint32_t)0x00000004)
#define ADCFG_VSEN_Set               ((uint32_t)0x00000008)

/* ADC ADEN mask */
#define ADCFG_ADEN_Set               ((uint32_t)0x00000001)
#define ADCFG_ADEN_Reset             ((uint32_t)0xFFFFFFFE)

/* ADC DMA mask */
#define ADCR_DMA_Set                 ((uint32_t)0x00000008)
#define ADCR_DMA_Reset               ((uint32_t)0xFFFFFFF7)

/* ADC Software start mask */
#define ADCR_SWSTART_Set             ((uint32_t)0x00000100)
#define ADCR_SWSTART_Reset           ((uint32_t)0xFFFFFEFF)

/* ADC EXTTRIG mask */
#define ADCR_EXTTRIG_Set             ((uint32_t)0x00000004)
#define ADCR_EXTTRIG_Reset           ((uint32_t)0xFFFFFFFB)

/* ADC ExternalTrigShiftTime mask */
#define ADC_ExternalTrigShiftTimeMask           ((uint32_t)0x00380000)

/*seletec channle enable */
#define CHEN0_ENABLE								((uint32_t)0x00000001)
#define CHEN1_ENABLE								((uint32_t)0x00000002)
#define CHEN2_ENABLE								((uint32_t)0x00000004)
#define CHEN3_ENABLE								((uint32_t)0x00000008)
#define CHEN4_ENABLE								((uint32_t)0x00000010)
#define CHEN5_ENABLE								((uint32_t)0x00000020)
#define CHEN6_ENABLE								((uint32_t)0x00000040)
#define CHEN7_ENABLE								((uint32_t)0x00000080)
#define CHEN8_ENABLE								((uint32_t)0x00000100)
#define CHEN9_ENABLE								((uint32_t)0x00000200)
#define CHEN10_ENABLE								((uint32_t)0x00000400)
#define CHEN11_ENABLE								((uint32_t)0x00000800)
#define CHEN12_ENABLE				                ((uint32_t)0x00001000)
#define CHEN13_ENABLE				                ((uint32_t)0x00002000)
#define CHEN14_ENABLE								((uint32_t)0x00004000)
#define CHEN15_ENABLE								((uint32_t)0x00008000)

#define CHALL_ENABLE                				((uint32_t)0x0000cfff)

#define TempSensor_ENABLE               CHEN14_ENABLE
#define Vrefint_ENABLE                  CHEN15_ENABLE

#define CHEN_DISABLE								((uint32_t)0xFFFF0000)

/* ADC EXTSEL mask */
#define ADCR_EXTSEL_Reset           				((uint32_t)0xFFF9FF8F)

/* ADC Analog watchdog enable mode mask */
#define ADCFG_AWDMode_Reset           				((uint32_t)0xFFFFFFFD)
#define ADCFG_AWDMode_Set                           ((uint32_t)0x00000002)

/* ADC AWDCH mask */
#define ADCR_AWDCH_Reset             				((uint32_t)0xFFFF0FFF)

/* ADC TSPD mask */
#define ADCHS_TSVREFE_Set ((uint32_t)0x00004000)
#define ADCHS_TSVREFE_Reset ((uint32_t)0xFFFFBFFF)

#define ADCHS_VSVREFE_Set ((uint32_t)0x00008000)
#define ADCHS_VSVREFE_Reset ((uint32_t)0xFFFF7FFF)

/* ADC1 DATA register base address */
#define ADDATA_ADDRESS                  			((uint32_t)0x40012400)
/**
* @}
*/

/** @defgroup ADC_Private_Macros
* @{
*/

/**
* @}
*/

/** @defgroup ADC_Private_Variables
* @{
*/

/**
* @}
*/

/** @defgroup ADC_Private_FunctionPrototypes
* @{
*/

/**
* @}
*/

/** @defgroup ADC_Private_Functions
* @{
*/

/**
* @brief  Deinitializes the ADCx peripheral registers to their default
*   reset values.
* @param ADCx: where x can be 1, 2  to select the ADC peripheral.
* @retval : None
*/
void ADC_DeInit(ADC_TypeDef *ADCx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    if (ADC1 == ADCx)
    {
        /* Enable ADC1 reset state */
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);
        /* Release ADC1 from reset state */
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);
    }
    else if(ADC2 == ADCx)
    {
        /* Enable ADC1 reset state */
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2, ENABLE);
        /* Release ADC1 from reset state */
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2, DISABLE);
    }
}

/**
* @brief  Initializes the ADCx peripheral according to the specified parameters
*   in the ADC_InitStruct.
* @param ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
* @param ADC_InitStruct: pointer to an ADC_InitTypeDef structure that
*   contains the configuration information for the specified
*   ADC peripheral.
* @retval : None
*/
void ADC_Init(ADC_TypeDef *ADCx, ADC_InitTypeDef *ADC_InitStruct)
{
    uint32_t tmpreg1 = 0;

    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_MODE(ADC_InitStruct->ADC_Mode));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_ScanConvMode));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_ContinuousConvMode));
    assert_param(IS_ADC_EXT_TRIG(ADC_InitStruct->ADC_ExternalTrigConv));
    assert_param(IS_ADC_DATA_ALIGN(ADC_InitStruct->ADC_DataAlign));
    /*---------------------------- ADCx ADCFG Configuration -----------------*/
    /* Get the ADCx ADCFG value */
    tmpreg1 = ADCx->ADCFG;
    /* Clear ADCPRE bits */
    tmpreg1 &= ADCFG_CLEAR_Mask;
    /* Configure ADCx: AD convertion PRESCALE*/
    /* Set ADCPRE bit according to ADC_PRESCALE value */
    tmpreg1 |= (uint32_t)(ADC_InitStruct->ADC_PRESCALE) | ADC_InitStruct->ADC_Resolution;

    /* Write to ADCx ADCFG */
    ADCx->ADCFG = tmpreg1;

    /*---------------------------- ADCx ADCR Configuration -----------------*/
    /* Get the ADCx ADCR value */
    tmpreg1 = ADCx->ADCR;
    /* Clear ALIGN , ADMD, TRGSEL, DMAEN,TRGEN,ADWIE and ADIE bits */
    tmpreg1 &= ADCR_CLEAR_Mask;
    /* Configure ADCx: external trigger event and AD conversion mode and ALIGN*/
    /* Set ALIGN bit according to ADC_DataAlign value */
    /* Set TRGEN bits according to ADC_ContinuousConvMode value */
    /* Set TRGSEL bits according to ADC_ExternalTrigConv value */
    /* Set ADMD bit according to ADC_Mode value */
    tmpreg1 |= ((uint32_t)ADC_InitStruct->ADC_DataAlign) | ADC_InitStruct->ADC_ExternalTrigConv |
               ((uint32_t)ADC_InitStruct->ADC_Mode);

    /* Write to ADCx ADCR */
    ADCx->ADCR = tmpreg1;
}

/**
* @brief  Fills each ADC_InitStruct member with its default value.
* @param ADC_InitStruct : pointer to an ADC_InitTypeDef structure
*   which will be initialized.
* @retval : None
*/
void ADC_StructInit(ADC_InitTypeDef *ADC_InitStruct)
{
    /* Initialize the ADC_PRESCALE values */
    ADC_InitStruct->ADC_PRESCALE = ADC_PCLK2_PRESCALE_2;
    /* Initialize the ADC_Mode member */
    ADC_InitStruct->ADC_Mode = ADC_Mode_Single;
    /* Initialize the ADC_ExternalTrigConv member */
    ADC_InitStruct->ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    /* Initialize the ADC_DataAlign member */
    ADC_InitStruct->ADC_DataAlign = ADC_DataAlign_Right;
    /* Initialize the ADC_Resolution member */
    ADC_InitStruct->ADC_Resolution = ADC_Resolution_12b;
}

/**
* @brief  Enables or disables the specified ADC peripheral.
* @param ADCx: where x can be 1, 2 to select the ADC peripheral.
* @param NewState: new state of the ADCx peripheral. This parameter
*   can be: ENABLE or DISABLE.
* @retval : None
*/
void ADC_Cmd(ADC_TypeDef *ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Set the ADEN bit */
        ADCx->ADCFG |= ADCFG_ADEN_Set;
    }
    else
    {
        /* Disable the selected ADC peripheral */
        ADCx->ADCFG &= ADCFG_ADEN_Reset;
    }
}

/**
* @brief  Enables or disables the specified ADC DMA request.
* @param ADCx: where x can be 1 or 2 to select the ADC peripheral.
* @param NewState: new state of the selected ADC DMA transfer.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void ADC_DMACmd(ADC_TypeDef *ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_DMA_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable the selected ADC DMA request */
        ADCx->ADCR |= ADCR_DMA_Set;
    }
    else
    {
        /* Disable the selected ADC DMA request */
        ADCx->ADCR &= ADCR_DMA_Reset;
    }
}

/**
* @brief  Enables or disables the specified ADC interrupts.
* @param ADCx: where x can be 1, 2 to select the ADC peripheral.
* @param ADC_IT: specifies the ADC interrupt sources to be enabled
*   or disabled.
*   This parameter can be any combination of the following values:
* @arg ADC_IT_EOC: End of conversion interrupt mask
* @arg ADC_IT_AWD: Analog watchdog interrupt mask
* @param NewState: new state of the specified ADC interrupts.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void ADC_ITConfig(ADC_TypeDef *ADCx, uint16_t ADC_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_ADC_IT(ADC_IT));
    /* Get the ADC IT index */
    if (NewState != DISABLE)
    {
        /* Enable the selected ADC interrupts */
        ADCx->ADCR |= ADC_IT;
    }
    else
    {
        /* Disable the selected ADC interrupts */
        ADCx->ADCR &= (~(uint32_t)ADC_IT);
    }
}

/**
* @brief  Enables or disables the selected ADC software start conversion .
* @param ADCx: where x can be 1, 2 to select the ADC peripheral.
* @param NewState: new state of the selected ADC software start conversion.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void ADC_SoftwareStartConvCmd(ADC_TypeDef *ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable the selected ADC conversion on external event and start the selected
        ADC conversion */
        /*Set ADST bit*/
        ADCx->ADCR |= ADCR_SWSTART_Set;
    }
    else
    {
        /* Disable the selected ADC conversion on external event and stop the selected
        ADC conversion */
        ADCx->ADCR &= ADCR_SWSTART_Reset;
    }
}

/**
* @brief  Gets the selected ADC Software start conversion Status.
* @param ADCx: where x can be 1, 2 to select the ADC peripheral.
* @retval : The new state of ADC software start conversion (SET or RESET).
*/
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef *ADCx)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    /* Check the status of ADST bit */
    if ((ADCx->ADCR & ADCR_SWSTART_Set) != (uint32_t)RESET)
    {
        /* ADST bit is set */
        bitstatus = SET;
    }
    else
    {
        /* ADST bit is reset */
        bitstatus = RESET;
    }
    /* Return the ADST bit status */
    return bitstatus;
}

/**
* @brief  Configures for the selected ADC  channel its corresponding
*   rank in the sequencer and its sample time.
* @param ADCx: where x can be 1, 2 to select the ADC peripheral.
* @param ADC_Channel: the ADC channel to configure.
*   This parameter can be one of the following values:
* @arg ADC_Channel_0: ADC Channel0 selected
* @arg ADC_Channel_1: ADC Channel1 selected
* @arg ADC_Channel_2: ADC Channel2 selected
* @arg ADC_Channel_3: ADC Channel3 selected
* @arg ADC_Channel_4: ADC Channel4 selected
* @arg ADC_Channel_5: ADC Channel5 selected
* @arg ADC_Channel_6: ADC Channel6 selected
* @arg ADC_Channel_7: ADC Channel7 selected
* @arg ADC_Channel_8: ADC Channel8 selected
* @retval : None
*/
void ADC_RegularChannelConfig(ADC_TypeDef *ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL(ADC_Channel));
    assert_param(IS_ADC_REGULAR_RANK(Rank));
    assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));
    tmpreg = ADCx->ADCFG;
    tmpreg &= ~(ADCFG_SAMCTL_Set);
    tmpreg |= ADC_SampleTime << 10;
    ADCx->ADCFG = tmpreg;
    if(ADC_Channel < 32)
    {
        ADCx->ADCHS |= 0x01 << ADC_Channel;
    }
    else if (ADC_Channel_All == ADC_Channel)
    {
        ADCx->ADCHS |= CHALL_ENABLE;
    }
    else if ( ADC_Channel_DisableAll  == ADC_Channel )
    {
        ADCx->ADCHS &= CHEN_DISABLE;
    }
}

/**
* @brief  Enables or disables the ADCx conversion through external trigger.
* @param ADCx: where x can be 1, 2 to select the ADC peripheral.
* @param NewState: new state of the selected ADC external trigger
*   start of conversion.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void ADC_ExternalTrigConvCmd(ADC_TypeDef *ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable the selected ADC conversion on external event */
        ADCx->ADCR |= ADCR_EXTTRIG_Set;
    }
    else
    {
        /* Disable the selected ADC conversion on external event */
        ADCx->ADCR &= ADCR_EXTTRIG_Reset;
    }
}

/**
* @brief  Enables or disables the ADCx conversion through external trigger.
* @param ADCx: where x can be 1, 2 to select the ADC peripheral.
* @param NewState: new state of the selected ADC external trigger
*   start of conversion.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void ADC_ExternalTrigShiftTimeSet(ADC_TypeDef* ADCx, u32 ADC_ExternalTrigShiftTime_x_Cycles)
{
    ADCx->ADCR &= ~ADC_ExternalTrigShiftTimeMask;
    ADCx->ADCR |= ADC_ExternalTrigShiftTime_x_Cycles;
}

/**
* @brief  Returns the last ADCx conversion result data for regular channel.
* @param ADCx: where x can be 1, 2 to select the ADC peripheral.
* @retval : The Data conversion value.
*/
uint16_t ADC_GetConversionValue(ADC_TypeDef *ADCx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    /* Return the selected ADC conversion value */
    if (((ADCx->ADCFG & 0x000000380) >> 7) == 0)
        return (uint16_t)ADCx->ADDATA;
    else if (((ADCx->ADCFG & 0x000000380) >> 7) == 1)
        return (uint16_t)(ADCx->ADDATA >> 1);
    else if (((ADCx->ADCFG & 0x000000380) >> 7) == 2)
        return (uint16_t)(ADCx->ADDATA >> 2);
    else if (((ADCx->ADCFG & 0x000000380) >> 7) == 3)
        return (uint16_t)(ADCx->ADDATA >> 3);
    else if (((ADCx->ADCFG & 0x000000380) >> 7) == 4)
        return (uint16_t)(ADCx->ADDATA >> 4);
    return (uint16_t)ADCx->ADDATA;
}

/**
* @brief  Enables or disables the ADCx conversion through external trigger.
* @param ADCx: where x can be 1, 2 to select the ADC peripheral.
* @param NewState: new state of the selected ADC external trigger
*   start of conversion.
*   This parameter can be: Direction_Low_to_High or Direction_High_to_Low.
* @retval : None
*/
void ADC_Scan_Direction(ADC_TypeDef* ADCx, uint8_t Direction_x_to_x)
{
    ADCx->ADCR &=  ~Direction_MASK ;
    ADCx->ADCR |= Direction_x_to_x;
}

/**
* @brief  Enables or disables the analog watchdog on single/all regular
*   or channels
* @param ADCx: where x can be 1, 2 to select the ADC peripheral.
* @param ADC_AnalogWatchdog: the ADC analog watchdog configuration.
*   This parameter can be one of the following values:
* @arg ADC_AnalogWatchdog_SingleRegEnable: Analog watchdog on
*   a single regular channel
* @arg ADC_AnalogWatchdog_None: No channel guarded by the
*   analog watchdog
*   analog watchdog
* @retval : None
*/
void ADC_AnalogWatchdogCmd(ADC_TypeDef *ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable the selected ADC window comparison */
        ADCx->ADCFG |= ADCFG_AWDMode_Set;
    }
    else
    {
        /* Disable the selected ADC window comparison */
        ADCx->ADCFG &= ADCFG_AWDMode_Reset;
    }
}

/**
* @brief  Configures the high and low thresholds of the analog watchdog.
* @param ADCx: where x can be 1, 2 to select the ADC peripheral.
* @param HighThreshold: the ADC analog watchdog High threshold value.
*   This parameter must be a 12bit value.
* @param LowThreshold: the ADC analog watchdog Low threshold value.
*   This parameter must be a 12bit value.
* @retval : None
*/
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef *ADCx, uint16_t HighThreshold,
                                        uint16_t LowThreshold)
{
    uint32_t tempThreshold;
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_THRESHOLD(HighThreshold));
    assert_param(IS_ADC_THRESHOLD(LowThreshold));
    /* Get the ADCx high threshold */
    tempThreshold = HighThreshold;
    /* Set the ADCx high threshold and the ADCx low threshold */
    ADCx->ADCMPR = (tempThreshold << 16) | LowThreshold;
}

/**
* @brief  Configures the analog watchdog guarded single channel
* @param ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
* @param ADC_Channel: the ADC channel to configure for the analog
*   watchdog.
*   This parameter can be one of the following values:
* @arg ADC_Channel_0: ADC Channel0 selected
* @arg ADC_Channel_1: ADC Channel1 selected
* @arg ADC_Channel_2: ADC Channel2 selected
* @arg ADC_Channel_3: ADC Channel3 selected
* @arg ADC_Channel_4: ADC Channel4 selected
* @arg ADC_Channel_5: ADC Channel5 selected
* @arg ADC_Channel_6: ADC Channel6 selected
* @arg ADC_Channel_7: ADC Channel7 selected
* @arg ADC_Channel_8: ADC Channel8 selected
* @arg ADC_Channel_9: ADC Channel9 selected
* @arg ADC_Channel_10: ADC Channel10 selected
* @arg ADC_Channel_11: ADC Channel11 selected
* @arg ADC_Channel_All: ADC all Channel selected
* @retval : None
*/
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef *ADCx, uint8_t ADC_Channel)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL(ADC_Channel));
    /* Get the old register value */
    tmpreg = ADCx->ADCR;
    /* Clear the Analog watchdog channel select bits */
    tmpreg &= ADCR_AWDCH_Reset;
    /* Set the Analog watchdog channel */
    tmpreg |= (ADC_Channel << 12);
    /* Store the new register value */
    ADCx->ADCR = tmpreg;
}

/**
* @brief  Enables or disables the temperature sensor and Vrefint channel.
* @param NewState: new state of the temperature sensor.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/

void ADC_TempSensorCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable temperature sensor */
        ADC1->ADCFG |= ADCFG_TSEN_Set;

        /* Enable the temperature sensor channel*/
        ADC1->ADCHS |= ADCHS_TSVREFE_Set;
    }
    else
    {
        /* Disbale temperature sensor */
        ADC1->ADCFG &= ~ADCFG_TSEN_Set;

        /* Disable the temperature sensor channel*/
        ADC1->ADCHS &= ADCHS_TSVREFE_Reset;
    }
}

/**
* @brief  Enables or disables the temperature sensor and Vrefint channel.
* @param NewState: new state of the temperature sensor.
*   This parameter can be: ENABLE or DISABLE.
* @retval : None
*/
void ADC_VrefintCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable temperature sensor */
        ADC1->ADCFG |= ADCFG_VSEN_Set;

        /* Enable the temperature sensor and Vrefint channel*/
        ADC1->ADCHS |= ADCHS_VSVREFE_Set;
    }
    else
    {
        /* Disbale temperature sensor */
        ADC1->ADCFG &= ~ADCFG_VSEN_Set;

        /* Disable the temperature sensor and Vrefint channel*/
        ADC1->ADCHS &= ADCHS_VSVREFE_Reset;
    }
}

/**
* @brief  Checks whether the specified ADC flag is set or not.
* @param ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
* @param ADC_FLAG: specifies the flag to check.
*   This parameter can be one of the following values:
* @arg ADC_FLAG_AWD: Analog watchdog flag
* @arg ADC_FLAG_EOC: End of conversion flag
* @arg ADC_FLAG_BUSY: AD conversion busy flag
* @retval : The new state of ADC_FLAG (SET or RESET).
*/
FlagStatus ADC_GetFlagStatus(ADC_TypeDef *ADCx, uint8_t ADC_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_GET_FLAG(ADC_FLAG));
    /* Check the status of the specified ADC flag */
    if ((ADCx->ADSTA & ADC_FLAG) != (uint8_t)RESET)
    {
        /* ADC_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_FLAG is reset */
        bitstatus = RESET;
    }

    /* Return the ADC_FLAG status */
    return bitstatus;
}

/**
* @brief  Clears the ADCx  pending flags.
* @param ADCx: where x can be 1, 2 to select the ADC peripheral.
* @param ADC_FLAG: specifies the flag to clear.
*   This parameter can be any combination of the following values:
* @arg ADC_FLAG_AWD: Analog watchdog flag
* @arg ADC_FLAG_EOC: End of conversion flag
* @retval : None
*/
void ADC_ClearFlag(ADC_TypeDef *ADCx, uint8_t ADC_FLAG)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CLEAR_FLAG(ADC_FLAG));
    /* Clear the selected ADC flags */
    ADCx->ADSTA |= ADC_FLAG;
}

/**
* @brief  Checks whether the specified ADC interrupt has occurred or not.
* @param ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
* @param ADC_IT: specifies the ADC interrupt source to check.
*   This parameter can be one of the following values:
* @arg ADC_IT_EOC: End of conversion interrupt mask
* @arg ADC_IT_AWD: Analog watchdog interrupt mask
* @retval : The new state of ADC_IT (SET or RESET).
*/
ITStatus ADC_GetITStatus(ADC_TypeDef *ADCx, uint16_t ADC_IT)
{
    ITStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_GET_IT(ADC_IT));

    /* Check the status of the specified ADC interrupt */
    if (((ADCx->ADSTA & ADC_IT)) != (uint32_t)RESET)
    {
        /* ADC_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_IT is reset */
        bitstatus = RESET;
    }
    /* Return the ADC_IT status */
    return bitstatus;
}

/**
* @brief  Clears the ADCx�s interrupt pending bits.
* @param ADCx: where x can be 1, 2 or 3 to select the ADC peripheral.
* @param ADC_IT: specifies the ADC interrupt pending bit to clear.
*   This parameter can be any combination of the following values:
* @arg ADC_IT_EOC: End of conversion interrupt mask
* @arg ADC_IT_AWD: Analog watchdog interrupt mask
* @retval : None
*/
void ADC_ClearITPendingBit(ADC_TypeDef *ADCx, uint16_t ADC_IT)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_IT(ADC_IT));
    /* Clear the selected ADC interrupt pending bits */
    ADCx->ADSTA = ADC_IT;
}

/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2019 MindMotion ----------------------*/

