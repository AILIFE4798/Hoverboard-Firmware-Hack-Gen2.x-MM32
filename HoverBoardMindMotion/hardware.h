#include "mm32_device.h"                // Device header
#include "hal_conf.h"
#include "hal_gpio.h" 
#include "hal_adc.h" 

#define IOA 1
#define IOB 2
#define IOC 3
#define IOD 4

GPIO_InitTypeDef GPIO_InitStruct;

uint32_t pins[33][3] = {   // port,pin,pinsrc,ADC,ADC2,HALL AF,HALL TIM,UART AF
{IOA,GPIO_Pin_0,GPIO_PinSource0},
{IOA,GPIO_Pin_1,GPIO_PinSource1},
{IOA,GPIO_Pin_2,GPIO_PinSource2},
{IOA,GPIO_Pin_3,GPIO_PinSource3},
{IOA,GPIO_Pin_4,GPIO_PinSource4},
{IOA,GPIO_Pin_5,GPIO_PinSource5},
{IOA,GPIO_Pin_6,GPIO_PinSource6},
{IOA,GPIO_Pin_7,GPIO_PinSource7},
{IOA,GPIO_Pin_11,GPIO_PinSource11},
{IOA,GPIO_Pin_12,GPIO_PinSource12},
{IOA,GPIO_Pin_13,GPIO_PinSource13},
{IOA,GPIO_Pin_14,GPIO_PinSource14},
{IOA,GPIO_Pin_15,GPIO_PinSource15},
{IOB,GPIO_Pin_0,GPIO_PinSource0},
{IOB,GPIO_Pin_1,GPIO_PinSource1},
{IOB,GPIO_Pin_2,GPIO_PinSource2},
{IOB,GPIO_Pin_3,GPIO_PinSource3},
{IOB,GPIO_Pin_4,GPIO_PinSource4},
{IOB,GPIO_Pin_5,GPIO_PinSource5},
{IOB,GPIO_Pin_6,GPIO_PinSource6},
{IOB,GPIO_Pin_7,GPIO_PinSource7},
{IOB,GPIO_Pin_8,GPIO_PinSource8},
{IOB,GPIO_Pin_9,GPIO_PinSource9},
{IOB,GPIO_Pin_10,GPIO_PinSource10},
{IOB,GPIO_Pin_11,GPIO_PinSource11},
{IOB,GPIO_Pin_12,GPIO_PinSource12},
{IOC,GPIO_Pin_13,GPIO_PinSource13},
{IOC,GPIO_Pin_14,GPIO_PinSource14},
{IOC,GPIO_Pin_15,GPIO_PinSource15},
{IOD,GPIO_Pin_0,GPIO_PinSource0},
{IOD,GPIO_Pin_1,GPIO_PinSource1},
{IOD,GPIO_Pin_2,GPIO_PinSource2},
{IOD,GPIO_Pin_3,GPIO_PinSource3},
};







