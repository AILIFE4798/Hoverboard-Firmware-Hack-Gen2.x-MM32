#include "mm32_device.h"                // Device header
#include "RTE_Components.h"             // Component selection
#include "hal_gpio.h"
#include "hal_rcc.h"
#include "hal_adc.h"
#include "delay.h"
#include "pinout.h"             
#include "hal_tim.h"
#include "../Src/initialize.h"
#include "../Src/uart.h"

#define HALL2LED  //sequence through led or rotate acording to motor
#define UART1EN  //enable uart1

uint8_t step=1;//very importatnt to set to 1 or it will not work
uint32_t millis;
uint32_t lastCommutation;
bool uart;
bool adc;
uint8_t uartBuffer=0;
u8 sRxBuffer[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int vbat;
int itotal;


s32 main(void){
	//initialize normal gpio
	io_init();
	//initialize 6 bldc pins
	BLDC_init();
	//initialize timer
	TIM1_init(4095, 0);
	//systick config
	DELAY_Init();
	//interrupt config
	NVIC_Configure(TIM1_BRK_UP_TRG_COM_IRQn, 1);
	//vbat
	adc_Init();
	//adc interrupt
	exNVIC_Configure(ADC_COMP_IRQn, 0, 1);

	#ifdef UART1EN
	//serial1.begin(19200);
	UART1_Init(19200);
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
		DELAY_Ms(5);		
		#else
		//blink in sequence
		GPIO_WriteBit(LEDRPORT, LEDRPIN, 1);
		GPIO_WriteBit(LEDBPORT, LEDBPIN, 0);
		DELAY_Ms(500);
		GPIO_WriteBit(LEDGPORT, LEDGPIN, 1);
		GPIO_WriteBit(LEDRPORT, LEDRPIN, 0);
		DELAY_Ms(500);
		GPIO_WriteBit(LEDBPORT, LEDBPIN, 1);
		GPIO_WriteBit(LEDGPORT, LEDGPIN, 0);
		DELAY_Ms(500);
		#endif
		
		#ifdef UART1EN
		//serial loopback
		if(uart){
		  UART1_Send_Byte(sRxBuffer[0]);
			uart=0;
		}
		#endif	
		
		//simulated hall sensor for commutation
		if(millis-lastCommutation>100){
			TIM_GenerateEvent(TIM1, TIM_EventSource_COM);
			lastCommutation=millis;
			//testing serial
			#ifdef UART1EN
			UART1_SendString("helloWorld\r\n");
			#endif
		}
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
	    }
			//last line to ever be executed
			GPIO_WriteBit(LATCHPORT, LATCHPIN, 0);
		}
  }
	
}

