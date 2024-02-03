#include "mm32_device.h"                // Device header
#include "RTE_Components.h"             // Component selection
#include "hal_gpio.h"
#include "hal_rcc.h"
#include "delay.h"
#include "pinout.h"             
#include "hal_tim.h"
#include "../Src/initialize.h"

#define HALL2LED
uint8_t step;
uint32_t millis;
uint32_t lastCommutation;
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
	TIM1->CCR1=200;
	TIM1->CCR2=200;
	TIM1->CCR3=200;
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
		if(millis-lastCommutation>100){
			TIM_GenerateEvent(TIM1, TIM_EventSource_COM);
			lastCommutation=millis;
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

