//initialize all pheberals
#include "../Inc/pinout.h"
#include "hal_gpio.h"
#include "hal_rcc.h"
#include "hal_comp.h"
#include "hal_tim.h"
#include "../Inc/initialize.h"
#include "hal_conf.h"
#include "../Inc/hardware.h"
#ifdef TARGET_MM32SPIN25
#include "spin25-redefine.h"
#include "HAL_device.h"
#endif

extern MM32GPIO pins[PINCOUNT];
extern MM32UART uarts[UARTCOUNT];
extern MM32ADC adcs[ADCCOUNT];
extern MM32TIM23 halltims[TIMCOUNT];
extern MM32TIMBK ocps[TIMBKCOUNT];

//normal io
void io_init(){
	//enable gpio clock
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOD, ENABLE);
	if(LEDRPIN<PINCOUNT){
		pinMode(LEDRPIN, OUTPUT);
	}
	if(LEDGPIN<PINCOUNT){
		pinMode(LEDGPIN, OUTPUT);
	}
	if(LEDBPIN<PINCOUNT){
		pinMode(LEDBPIN, OUTPUT);
	}
	if(LATCHPIN<PINCOUNT){
		pinMode(LATCHPIN, OUTPUT);
	}
	if(BUTTONPIN<PINCOUNT){
		pinMode(BUTTONPIN, INPUT);
	}
	if(BUZZERPIN<PINCOUNT){
		pinMode(BUZZERPIN, OUTPUT);
	}
}

void HALL_Init(){
	pinMode(HALLAPIN, INPUT);
	pinMode(HALLBPIN, INPUT);
	pinMode(HALLCPIN, INPUT);
}

void HALLTIM_Init(u32 arr, u16 psc){    //hall sensor hardware speed sensing
	int tim2;
	for(uint8_t i=0;i<TIMCOUNT;i++){
		if(halltims[i].io==HALLAPIN||halltims[i].io==HALLBPIN||halltims[i].io==HALLCPIN){
			pinModeAF(halltims[i].io,halltims[i].af);
			tim2=halltims[i].tim2;
		}
	}
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStruct;
	TIM_ICInitTypeDef  TIM_ICInitStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);      
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStruct);
	TIM_TimeBaseStruct.TIM_Period = arr;
	TIM_TimeBaseStruct.TIM_Prescaler = psc;
	//Setting Clock Segmentation
	TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStruct.TIM_RepetitionCounter = 0;
	///TIM Upward Counting Mode
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(tim2 ? TIM2 : TIM3, &TIM_TimeBaseStruct);

	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_TRC;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICFilter = 0x0;
	TIM_ICInit(tim2 ? TIM2 : TIM3, &TIM_ICInitStruct); 
	TIM_ITConfig(tim2 ? TIM2 : TIM3, TIM_IT_CC1, ENABLE);
	
	TIM_SelectHallSensor(tim2 ? TIM2 : TIM3,ENABLE);
	TIM_UpdateRequestConfig(tim2 ? TIM2 : TIM3,TIM_UpdateSource_Regular);
	TIM_SelectInputTrigger(tim2 ? TIM2 : TIM3, TIM_TS_TI1F_ED);
	TIM_SelectSlaveMode(tim2 ? TIM2 : TIM3, TIM_SlaveMode_Reset);
	TIM_SelectMasterSlaveMode(tim2 ? TIM2 : TIM3, TIM_MasterSlaveMode_Enable);
	
	TIM_Cmd(tim2 ? TIM2 : TIM3, ENABLE);
	NVIC_Configure(tim2 ? TIM2_IRQn : TIM3_IRQn, 1);
}


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
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 1;
	///TIM Upward Counting Mode
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCNPolarity = INVERT_LOWSIDE ? TIM_OCNPolarity_Low : TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_Pulse = 1; 							//0% duty cycle
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);

	TIM_CCPreloadControl(TIM1, ENABLE);
	TIM_ITConfig(TIM1, TIM_IT_COM, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);

	TIM_BDTRStructInit(&TIM_BDTRInitStructure);
	// Automatic Output enable, Break, dead time and lock configuration
	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
	TIM_BDTRInitStructure.TIM_BreakPolarity = AWDG ? TIM_BreakPolarity_High : TIM_BreakPolarity_Low ;
	TIM_BDTRInitStructure.TIM_DeadTime = 1;
	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
	if(!AWDG){
		if(OCPREFPIN<PINCOUNT){
			/*
			RCC_APB2PeriphClockCmd(RCC_APB2ENR_COMP, ENABLE);
			GPIO_InitTypeDef GPIO_InitStruct;
			GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStruct.GPIO_Pin = HARD_ILIMIT_PIN;
			GPIO_Init(HARD_ILIMIT_PORT, &GPIO_InitStruct);
			GPIO_InitStruct.GPIO_Pin = HARD_ILIMIT_COMP_REF_PIN;
			GPIO_Init(HARD_ILIMIT_COMP_REF_PORT, &GPIO_InitStruct);
			
			COMP_InitTypeDef COMP_InitStructure;
			COMP_DeInit(COMP1); 
			COMP_InitStructure.COMP_InvertingInput 		= HARD_ILIMIT_COMP_INVERTING;
			COMP_InitStructure.COMP_NonInvertingInput = HARD_ILIMIT_COMP_NONINVERTING;
			COMP_InitStructure.COMP_Output    				= COMP_Output_TIM1BKIN;
			COMP_InitStructure.COMP_OutputPol 				= COMP_OutputPol_NonInverted;
			COMP_InitStructure.COMP_Hysteresis  			= COMP_Hysteresis_High; 
			COMP_InitStructure.COMP_Mode        			= COMP_Mode_HighSpeed;
			COMP_InitStructure.COMP_Filter      			= COMP_Filter_4_Period;
			COMP_Init(COMP1, &COMP_InitStructure);
			COMP_Cmd(COMP1, ENABLE);
			*/
		}else if(OCPPIN<PINCOUNT){
			pinMode(OCPPIN, INPUT);
			for(uint8_t i=0;i<TIMBKCOUNT;i++){
				if(ocps[i].io==OCPPIN){
					pinModeAF(OCPPIN, ocps[i].af);
				}
			}
		}	
	}
	TIM_Cmd(TIM1, ENABLE);
}

//interrupt
void NVIC_Configure(u8 ch, u8 pri){
	NVIC_InitTypeDef  NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = ch;
	NVIC_InitStruct.NVIC_IRQChannelPriority = pri;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}
//uart
void UARTX_Init(u32 baudrate,uint8_t uart){
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
	UART_Init(uart==1 ? UART1 : UART2, &UART_InitStructure);
	UART_Cmd(uart==1 ? UART1 : UART2, ENABLE);
	UART_DMACmd(uart==1 ? UART1 : UART2, UART_DMAReq_EN, ENABLE);
}

uint8_t UART_GPIO_Init(){
	uint8_t uart=1;
	for(uint8_t i=0;i<UARTCOUNT;i++){
		if(uarts[i].io==TXPIN||uarts[i].io==RXPIN){
			pinModeAF(uarts[i].io,uarts[i].af);
			if(uarts[i].tx){
				pinMode(uarts[i].io, OUTPUT_AF);
			}else{
				pinMode(uarts[i].io, INPUT);
			}
			uart=uarts[i].uart;
		}
	}
	return uart;
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
	DMA_Init(dam_chx, &DMA_InitStructure);
	// Enable UARTy_DMA1_Channel Transfer complete interrupt
	DMA_ITConfig(dam_chx, DMA_IT_TC, ENABLE);
	// UARTy_DMA1_Channel enable
	DMA_Cmd(dam_chx, ENABLE);
}

void adc_Init(void){
	ADC_InitTypeDef  ADC_InitStructure;    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 
	ADC_InitStructure.ADC_PRESCALE = ADC_PCLK2_PRESCALE_6;							//for 72MHz
	ADC_InitStructure.ADC_Mode = ADC_Mode_Single_Period;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC4;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_ExternalTrigConvCmd(ADC1,ENABLE);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_VoltReference, 0, ADC_SampleTime_7_5Cycles);
	ADC_VrefintCmd(ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	if(VBATPIN<PINCOUNT){
		pinMode(VBATPIN, INPUT_ADC);
		for(uint8_t i=0;i<ADCCOUNT;i++){
			if(adcs[i].io==VBATPIN){
				ADC_RegularChannelConfig(ADC1, adcs[i].channel, 0, ADC_SampleTime_7_5Cycles);
				break;
			}
		}
	}
	if(ITOTALPIN<PINCOUNT){
		pinMode(ITOTALPIN, INPUT_ADC);
		for(uint8_t i=0;i<ADCCOUNT;i++){
			if(adcs[i].io==ITOTALPIN){
				ADC_RegularChannelConfig(ADC1, adcs[i].channel, 0, ADC_SampleTime_7_5Cycles);
				break;
			}
		}
	}
	if(IPHASEAPIN<PINCOUNT&&IPHASEBPIN<PINCOUNT){
		pinMode(IPHASEAPIN, INPUT_ADC);
		pinMode(IPHASEBPIN, INPUT_ADC);
		for(uint8_t i=0;i<ADCCOUNT;i++){
			if(adcs[i].io==IPHASEAPIN||adcs[i].io==IPHASEBPIN){
				ADC_RegularChannelConfig(ADC1, adcs[i].channel, 0, ADC_SampleTime_7_5Cycles);
			}
		}
	}

	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
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













