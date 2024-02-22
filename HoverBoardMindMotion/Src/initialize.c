//initialize all pheberals
#include "../Inc/pinout.h"
#include "hal_gpio.h"
#include "hal_rcc.h"
#include "hal_comp.h"
#include "hal_tim.h"
#include "../Inc/initialize.h"
#include "hal_conf.h"
#include "mm32_reg_redefine_v1.h"
#include "../Inc/autodetect.h"
#include "../Inc/hardware.h"


extern MM32GPIO pins[33];
extern MM32UART1 uarts[4];
extern MM32ADC adcs[10];
extern MM32TIM23 halltims[18];
extern MM32TIMBK ocps[4];




//6 bldc pin
void BLDC_init(){
	GPIO_InitTypeDef GPIO_InitStructure;
	//high side
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_2);
	//low side
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_2);
	GPIO_StructInit(&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

//timer1 automatic output
void TIM1_init(u16 arr, u16 psc){
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_BDTRInitTypeDef  TIM_BDTRInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM1, ENABLE);

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	//Setting Clock Segmentation
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	///TIM Upward Counting Mode
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCNPolarity = INVERT_LOWSIDE_AD;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);

	TIM_CCPreloadControl(TIM1, ENABLE);
	TIM_ITConfig(TIM1, TIM_IT_COM, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);

	TIM_BDTRStructInit(&TIM_BDTRInitStructure);
	// Automatic Output enable, Break, dead time and lock configuration
	TIM_BDTRInitStructure.TIM_OSSIState = (TIMOSSI_Typedef) TIM_OSSRState_Enable;
	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
	TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
	TIM_BDTRInitStructure.TIM_DeadTime = 1;
	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);

	TIM_Cmd(TIM1, ENABLE);
}


void exNVIC_Configure(u8 ch, u8 pri, u8 sub)
{
	exNVIC_Init_TypeDef  NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = ch;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = pri;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = sub;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

	exNVIC_Init(&NVIC_InitStruct);
}
//uart
void UARTX_Init(u32 baudrate){
	UART_InitTypeDef UART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_UART1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART2, ENABLE);
	//Baud rate
	UART_StructInit(&UART_InitStructure);
	UART_InitStructure.BaudRate = baudrate;
	UART_InitStructure.WordLength = UART_WordLength_8b;
	UART_InitStructure.StopBits = UART_StopBits_1;
	UART_InitStructure.Parity = UART_Parity_No;
	UART_InitStructure.HWFlowControl = UART_HWFlowControl_None;
	UART_InitStructure.Mode = UART_Mode_Rx | UART_Mode_Tx;
	UART_Init(UART1, &UART_InitStructure);
	UART_Cmd(UART1, ENABLE);
	UART_GPIO_Init();
}

void UART_GPIO_Init(){
	for(uint8_t i=0;i<UARTCOUNT;i++){
		if(uarts[i].io==TXPIN||uarts[i].io==RXPIN){
			pinModeAF(uarts[i].io,uarts[i].af);
			if(uarts[i].tx){
				pinMode(uarts[i].io, OUTPUT_AF);
			}else{
				pinMode(uarts[i].io, INPUT);
			}
		}
	}
}

void DMA_NVIC_Config(DMA_Channel_TypeDef* dam_chx, u32 cpar, u32 cmar, u16 cndtr){
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_DeInit(dam_chx);
	DMA_StructInit(&DMA_InitStructure);
	//DMA transfer peripheral address
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;
	//DMA transfer memory address
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;
	//DMA transfer direction from peripheral to memory
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	//DMA cache size
	DMA_InitStructure.DMA_BufferSize = cndtr;
	//After receiving the data, the peripheral address is forbidden to move
	//backward
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	//After receiving the data, the memory address is shifted backward
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	//Define the peripheral data width to 8 bits
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
	//M2M mode is disabled
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStructure.DMA_Auto_reload = DMA_Auto_Reload_Disable;
	DMA_Init(dam_chx, &DMA_InitStructure);
	// Enable UARTy_DMA1_Channel Transfer complete interrupt
	DMA_ITConfig(dam_chx, DMA_IT_TC, ENABLE);
	UART_DMACmd(UART1, UART_DMAReq_EN, ENABLE);
	// UARTy_DMA1_Channel enable
	DMA_Cmd(dam_chx, ENABLE);
}



void Iwdg_Init(u16 IWDG_Prescaler, u16 Reload){
	//Start the internal low-speed clock and wait for the clock to be ready
	RCC_LSICmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);

	//Setting Clock Pre-division Frequency
	PVU_CheckStatus();
	IWDG_WriteAccessCmd(0x5555);
	IWDG_SetPrescaler(IWDG_Prescaler);

	//Setting overload register values
	RVU_CheckStatus();
	IWDG_WriteAccessCmd(0x5555);
	IWDG_SetReload(Reload);

	//Loading and Enabling Counter
	IWDG_ReloadCounter();
	IWDG_Enable();
}

void vref_Init(){
	ADC_DeInit(ADC1);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_InitTypeDef  ADC_InitStructure;
	ADC_InitStructure.ADC_PRESCALE = ADC_PCLK2_PRESCALE_6;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Continue;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC4;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_Cmd(ADC1, ENABLE);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_VoltReference, 0, ADC_SampleTime_7_5Cycles);
	ADC_TempSensorVrefintCmd(ENABLE);
}
void ADCALL_Init(){
	ADC_DeInit(ADC1);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_InitTypeDef  ADC_InitStructure;
	ADC_InitStructure.ADC_PRESCALE = ADC_PCLK2_PRESCALE_6;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Continue;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC4;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_Cmd(ADC1, ENABLE);
}
	










