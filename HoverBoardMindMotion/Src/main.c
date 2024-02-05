#include "mm32_device.h"                // Device header
#include "RTE_Components.h"             // Component selection
#include "hal_gpio.h"
#include "hal_rcc.h"
#include "hal_adc.h"           
#include "hal_tim.h"
#include "hal_iwdg.h"
#include "../Src/delay.h"
#include "../Src/pinout.h"  
#include "../Src/initialize.h"
#include "../Src/uart.h"
#include "../Src/bldc.h"


uint8_t step=1;//very importatnt to set to 1 or it will not work
uint32_t millis;
uint32_t lastCommutation;
uint32_t lastupdate;
bool uart;
bool adc;
bool comm=1;
bool dir=1;
uint8_t uartBuffer=0;
u8 sRxBuffer[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int vbat;
int itotal;
uint8_t hallposprev=1;
int speed=0;
float realspeed=0;
uint8_t  wState;




s32 main(void){
	//initialize normal gpio
	io_init();
	//hall gpio init
	HALL_Init();
	//hall timer init
	TIM2_Init(65535, 100);
	//initialize 6 bldc pins
	BLDC_init();
	//initialize timer
	TIM1_init(4095, 0);
	//systick config
	DELAY_Init();
	//timer1 commutation interrupt config
	NVIC_Configure(TIM1_BRK_UP_TRG_COM_IRQn, 1);
	//timer2 hall change interrupt config
	NVIC_Configure(TIM2_IRQn, 1);
	//vbat
	adc_Init();
	//adc interrupt
	exNVIC_Configure(ADC_COMP_IRQn, 0, 1);
	
	//watchdog
	//Iwdg_Init(IWDG_Prescaler_32, 0xff);
	
	#ifdef UART1EN
	//serial1.begin(19200);
	UART1_Init(BAUD);
	//uart interrupt
	exNVIC_Configure(DMA1_Channel2_3_IRQn, 0, 0);
	//uart dma
	DMA_NVIC_Config(DMA1_Channel3, (u32)&UART1->RDR, (u32)sRxBuffer, 1);
	#endif
	
	//latch on power
	GPIO_WriteBit(LATCHPORT, LATCHPIN, 1);
	//wait while release button
	while(GPIO_ReadInputDataBit(BTNPORT, BTNPIN)) {
		GPIO_WriteBit(BZPORT, BZPIN, 1);
		DELAY_Ms(1);
		GPIO_WriteBit(BZPORT, BZPIN, 0);
		DELAY_Ms(1);
		IWDG_ReloadCounter();
	}
	//prevent turning back off imidiately
	DELAY_Ms(5);	
	
	//25% PWM for test
	TIM1->CCR1=1000;
	TIM1->CCR2=1000;
	TIM1->CCR3=1000;
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);                                     //Software start conversion
  ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	
  while(1) {
		#ifdef HALL2LED
		//rotating led
    GPIO_WriteBit(LEDRPORT, LEDRPIN, GPIO_ReadInputDataBit(HALLAPORT, HALLAPIN));
		GPIO_WriteBit(LEDGPORT, LEDGPIN, GPIO_ReadInputDataBit(HALLBPORT, HALLBPIN));
		GPIO_WriteBit(LEDBPORT, LEDBPIN, GPIO_ReadInputDataBit(HALLCPORT, HALLCPIN));		
		#endif
		

		//speed pid loop
		if(millis-lastupdate>3){
			speedupdate();
			lastupdate=millis;
		}	
/*	
		//simulated hall sensor for commutation
		if(millis-lastCommutation>3){
			step++;
			if(step>6){
				step=1;
			}
			commutate();
			lastCommutation=millis;
		}
*/		
		
		//button press for shutdown
		if(GPIO_ReadInputDataBit(BTNPORT, BTNPIN)){
			//power off melody
			for(int i=0;i<3;i++){
			GPIO_WriteBit(BZPORT, BZPIN, 1);
		  DELAY_Ms(10);
		  GPIO_WriteBit(BZPORT, BZPIN, 0);
		  DELAY_Ms(10);
			}
			//wait for release
			while(GPIO_ReadInputDataBit(BTNPORT, BTNPIN)) {
		    __NOP();
				IWDG_ReloadCounter();
	    }
			//last line to ever be executed
			GPIO_WriteBit(LATCHPORT, LATCHPIN, 0);
		}
		//feed the watchdog
		IWDG_ReloadCounter();
  }//main loop
	
}

