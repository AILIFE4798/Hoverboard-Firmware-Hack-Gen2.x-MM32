#include "mm32_device.h"                // Device header
#include "RTE_Components.h"             // Component selection
#include "hal_gpio.h"
#include "hal_rcc.h"
#include "hal_adc.h"           
#include "hal_tim.h"
#include "hal_iwdg.h"
#include "../Inc/delay.h"
#include "../Inc/pinout.h"  
#include "../Inc/initialize.h"
#include "../Inc/uart.h"
#include "../Inc/bldc.h"


uint8_t step=1;//very importatnt to set to 1 or it will not work
uint32_t millis;
uint32_t lastCommutation;
uint32_t lastupdate;
uint32_t iOdom;
bool uart;
bool adc;
bool comm=1;
bool dir=1;
uint8_t uartBuffer=0;
u8 sRxBuffer[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int vbat;
int itotal;
int fvbat;
int fitotal;
uint8_t hallposprev=1;
int speed=0;
int pwm=0;
int realspeed=0;
int frealspeed=0;
uint8_t  wState;
extern u32 SystemCoreClock;



s32 main(void){
	//initialize normal gpio
	io_init();
	//hall gpio init
	HALL_Init();
	//hall timer init
	HALLTIM_Init(65535, SystemCoreClock/100000);//sysclock is 72mhz
	//initialize 6 bldc pins
	BLDC_init();
	//initialize timer
	TIM1_init(PWM_RES, 0);
	//systick config
	DELAY_Init();
	//timer1 commutation interrupt config
	NVIC_Configure(TIM1_BRK_UP_TRG_COM_IRQn, 1);
	//vbat
	adc_Init();
	//adc interrupt
	exNVIC_Configure(ADC_COMP_IRQn, 0, 1);
	#ifdef WATCHDOG//watchdog
	Iwdg_Init(IWDG_Prescaler_32, 0xff);
	#endif
	//serial1.begin(19200);
	UARTX_Init((uint32_t)BAUD);
	//uart interrupt
	exNVIC_Configure(DMA1_Channel2_3_IRQn, 0, 0);
	//uart dma
	DMA_NVIC_Config(DMA1_Channel3, (u32)&UART1->RDR, (u32)sRxBuffer, 1);
	//latch on power
	if(LATCHPIN<PINCOUNT-1){    //have latch
		DELAY_Ms(50);    //some board the micro controller can reset in time and turn back on
		digitalWrite(LATCHPIN, 1);
		while(digitalRead(BUTTONPIN)){    //wait while release button
			if(BUZZERPIN<PINCOUNT-1){    //have buzzer
				digitalWrite(BUZZERPIN, 1);
				DELAY_Ms(2);
				digitalWrite(BUZZERPIN, 0);
				DELAY_Ms(2);
			}else{
				__NOP();
				__NOP();
			}
			IWDG_ReloadCounter();
		}
		if(BUZZERPIN<PINCOUNT-1){
			for(int i=0;i<5;i++){    //power on melody
				digitalWrite(BUZZERPIN, 1);
				DELAY_Ms(50);
				digitalWrite(BUZZERPIN, 0);
				DELAY_Ms(50);
			}
		}
	}
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);    //Software start conversion
	UART_SendString("hello World\n\r");    //debug uart
  while(1) {
		#ifdef HALL2LED
		//rotating led
    GPIO_WriteBit(LEDRPORT, LEDRPIN, GPIO_ReadInputDataBit(HALLAPORT, HALLAPIN));
		GPIO_WriteBit(LEDGPORT, LEDGPIN, GPIO_ReadInputDataBit(HALLBPORT, HALLBPIN));
		GPIO_WriteBit(LEDBPORT, LEDBPIN, GPIO_ReadInputDataBit(HALLCPORT, HALLCPIN));		
		#endif
		
		if(millis-lastupdate>1){//speed pid loop
			speedupdate();
		  lastupdate=millis;
		}
		
		if(LATCHPIN<PINCOUNT-1){
			if(digitalRead(BUTTONPIN)){    //button press for shutdown
				TIM1->CCR1=0;    //shut down motor
				TIM1->CCR2=0;
				TIM1->CCR3=0;
				if(BUZZERPIN<PINCOUNT-1){
					for(int i=0;i<3;i++){    //power off melody
					digitalWrite(BUZZERPIN, 1);
					DELAY_Ms(150);
					digitalWrite(BUZZERPIN, 0);
					DELAY_Ms(150);
					}
				}
				while(digitalRead(BUTTONPIN)) {    //wait for release
					__NOP();
					IWDG_ReloadCounter();
				}
				digitalWrite(LATCHPIN, 0);    //last line to ever be executed
				while(1);//incase the hardware failed...
			}
		}
		IWDG_ReloadCounter();    //feed the watchdog
  }//main loop	
}

