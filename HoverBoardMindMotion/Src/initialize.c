//initialize all pheberals
#include "../Inc/pinout.h"
#include "hal_gpio.h"
#include "hal_rcc.h"
#include "hal_comp.h"
#include "hal_tim.h"
#include "../Inc/initialize.h"
#include "hal_conf.h"
#include "mm32_reg_redefine_v1.h"


//normal io
void io_init(){
	//enable gpio clock
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOD, ENABLE);
	//LED output
	GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	#ifdef LEDRPIN
  GPIO_InitStruct.GPIO_Pin = LEDRPIN;
	GPIO_Init(LEDRPORT, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = LEDGPIN;
	GPIO_Init(LEDGPORT, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = LEDBPIN;
	GPIO_Init(LEDBPORT, &GPIO_InitStruct);
	#endif
	#ifdef LATCHPIN
	//latch output
	GPIO_InitStruct.GPIO_Pin = LATCHPIN;
	GPIO_Init(LATCHPORT, &GPIO_InitStruct);
	//button input
	GPIO_InitStruct.GPIO_Pin = BTNPIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_FLOATING;
	GPIO_Init(BTNPORT, &GPIO_InitStruct);
	#endif
	#ifdef BZPIN
	//bz output
	GPIO_InitStruct.GPIO_Pin = BZPIN;
	GPIO_Init(BZPORT, &GPIO_InitStruct);
	#endif
}
void HALL_Init(){
	#ifdef HALLAPIN
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_PinAFConfig(HALLAPORT, HALLAPINSRC, HALLAAF);
	GPIO_PinAFConfig(HALLBPORT, HALLBPINSRC, HALLBAF);
	GPIO_PinAFConfig(HALLCPORT, HALLCPINSRC, HALLCAF);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = HALLAPIN;
	GPIO_Init(HALLAPORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = HALLBPIN;
	GPIO_Init(HALLBPORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = HALLCPIN;
	GPIO_Init(HALLCPORT, &GPIO_InitStructure);	
	#endif
}
#ifdef HALLTIM
//hall sensor hardware speed sensing
void HALLTIM_Init(u32 arr, u16 psc){
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
	TIM_TimeBaseInit(HALLTIM, &TIM_TimeBaseStruct);

	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICFilter = 0x0;
	TIM_ICInit(HALLTIM, &TIM_ICInitStruct); 
	TIM_ITConfig(HALLTIM, TIM_IT_CC1, ENABLE);
	
	TIM_SelectHallSensor(HALLTIM,ENABLE);
	
	TIM_UpdateRequestConfig(HALLTIM,TIM_UpdateSource_Regular);

	TIM_SelectInputTrigger(HALLTIM, TIM_TS_TI1F_ED);
	TIM_SelectSlaveMode(HALLTIM, TIM_SlaveMode_Reset);
	TIM_SelectMasterSlaveMode(HALLTIM, TIM_MasterSlaveMode_Enable);
	
	TIM_Cmd(HALLTIM, ENABLE);
}
#endif

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
	TIM_OCInitStructure.TIM_Pulse = 2047;
	TIM_OCInitStructure.TIM_OCNPolarity = INVERT_LOWSIDE;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;

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
	TIM_BDTRInitStructure.TIM_BreakPolarity = HARD_LIMIT_POLARITY;
	TIM_BDTRInitStructure.TIM_DeadTime = 1;
	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
	
	#ifdef HARD_ILIMIT_COMP_REF_PIN
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

	#else
	#ifdef HARD_ILIMIT_PIN
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_FLOATING;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStruct.GPIO_Pin = HARD_ILIMIT_PIN;
		GPIO_Init(HARD_ILIMIT_PORT, &GPIO_InitStruct);
		GPIO_PinAFConfig(HARD_ILIMIT_PORT, HARD_ILIMIT_PINSRC, HARD_ILIMIT_AF);
	#endif	
	#endif
	TIM_Cmd(TIM1, ENABLE);
}

//commutation interrupt
void NVIC_Configure(u8 ch, u8 pri){
	NVIC_InitTypeDef  NVIC_InitStruct;

	NVIC_InitStruct.NVIC_IRQChannel = ch;
	NVIC_InitStruct.NVIC_IRQChannelPriority = pri;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
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
#ifdef UARTEN
void UARTX_Init(u32 baudrate)
{
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

	UART_Init(UARTEN, &UART_InitStructure);
	UART_Cmd(UARTEN, ENABLE);

	UART_GPIO_Init();
}

void UART_GPIO_Init(){
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_PinAFConfig(SERIALTXPORT, SERIALTXPINSRC, SERIALTXAF);
	GPIO_PinAFConfig(SERIALRXPORT, SERIALRXPINSRC, SERIALRXAF);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = SERIALTXPIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(SERIALTXPORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SERIALRXPIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_FLOATING;
	GPIO_Init(SERIALRXPORT, &GPIO_InitStructure);
}
#endif
void DMA_NVIC_Config(DMA_Channel_TypeDef* dam_chx, u32 cpar, u32 cmar, u16 cndtr)
{
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

	UART_DMACmd(UARTEN, UART_DMAReq_EN, ENABLE);

	// UARTy_DMA1_Channel enable
	DMA_Cmd(dam_chx, ENABLE);

}

void adc_Init(void){
	#ifdef VBATPIN
	ADC_InitTypeDef  ADC_InitStructure;    
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;

	GPIO_InitStructure.GPIO_Pin = VBATPIN;
	GPIO_Init(VBATPORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = ITOTALPIN;
	GPIO_Init(ITOTALPORT, &GPIO_InitStructure);    

	/* Initialize the ADC_PRESCALE values */
	ADC_InitStructure.ADC_PRESCALE = ADC_PCLK2_PRESCALE_6;							//for 72MHz

	/* Initialize the ADC_Mode member */
	ADC_InitStructure.ADC_Mode = ADC_Mode_Single_Period;

	/* Initialize the ADC_DataAlign member */
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	
	/* Initialize the ADC_ExternalTrigConv member */
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC4;
	//TIM1->CCR4 = 0;//triger ADC by saw bottom
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_ExternalTrigConvCmd(ADC1,ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_RegularChannelConfig(ADC1, VBATADC, 0, ADC_SampleTime_7_5Cycles);
	ADC_RegularChannelConfig(ADC1, ITOTALADC, 1, ADC_SampleTime_7_5Cycles);
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	#endif
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













