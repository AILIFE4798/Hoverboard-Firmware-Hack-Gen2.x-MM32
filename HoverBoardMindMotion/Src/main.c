#ifdef TARGET_MM32SPIN25
#include "HAL_device.h"                 // Device header
#include "spin25-redefine.h" 
#else
#include "mm32_device.h"                // Device header
#endif
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
#include "../Inc/sim_eeprom.h"
#include "../Inc/hardware.h"

#include "../Inc/ipark.h"
#include "../Inc/FOC_Math.h"
#include "../Inc/pwm_gen.h"

uint8_t step=1;//very importatnt to set to 1 or it will not work
uint32_t millis;
uint32_t lastCommutation;
uint32_t lastupdate;
uint32_t lastflicker;
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
uint8_t flicker=0;
uint8_t uarten=1;
////////////////////////////////////////////////////////////////////////////////////////////
//  compile device specefic firmware for mass produce
//  change EEPROMEN to 0
#define EEPROMEN 1
//  copy pinstorage initializer from autodetect and replace the default line below
uint16_t pinstorage[64]={0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xDCAB, 31, 250, 0, 19200, 8192, 1, 30, 0, 10, 300, 1, 1, 42000, 32000, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
////////////////////////////////////////////////////////////////////////////////////////////


s32 main(void){
	DELAY_Init();
	if(!restorecfg()&&EEPROMEN){    //if data in eeprom is not valid, do not boot up
		RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
		RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, ENABLE);
		RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOC, ENABLE);
		RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOD, ENABLE);
		while(1){
			for(uint8_t i=0;i<33;i++){
				if(i!=10&&i!=11){
					pinMode(i, INPUT_PULLUP);
				}
			}	
			DELAY_Ms(1000);
			for(uint8_t i=0;i<33;i++){
				if(i!=10&&i!=11){
					pinMode(i, INPUT_PULLDOWN);
				}
			}	
			DELAY_Ms(1000);
		}
	}
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
	//timer1 commutation interrupt config
	NVIC_Configure(TIM1_BRK_UP_TRG_COM_IRQn, 1);
	//vbat
	adc_Init();
	//adc interrupt
	NVIC_Configure(ADC_COMP_IRQn, 0);
	#ifdef WATCHDOG//watchdog
	Iwdg_Init(IWDG_Prescaler_32, 0xff);
	#endif
	//serial1.begin(19200);
	uarten=UART_GPIO_Init();
	UARTX_Init((uint32_t)BAUD,uarten);
	//uart interrupt
	//uart dma
	if(uarten==1){
		DMA_NVIC_Config(DMA1_Channel3, (u32)&UART1->RDR, (u32)sRxBuffer, 1);
		NVIC_Configure(DMA1_Channel2_3_IRQn, 1);
	}else{
		DMA_NVIC_Config(DMA1_Channel5, (u32)&UART2->RDR, (u32)sRxBuffer, 1);
		NVIC_Configure(DMA1_Channel4_5_IRQn, 1);
	}
	//latch on power
	if(LATCHPIN<PINCOUNT&&EEPROMEN){    //have latch
		DELAY_Ms(100);    //some board the micro controller can reset in time and turn back on
		digitalWrite(LATCHPIN, 1);
		while(digitalRead(BUTTONPIN)&&BUTTONPIN<PINCOUNT){    //wait while release button
			if(BUZZERPIN<PINCOUNT){    //have buzzer
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
	}
	if(BUZZERPIN<PINCOUNT){
		for(int i=0;i<5;i++){    //power on melody
			digitalWrite(BUZZERPIN, 1);
			DELAY_Ms(50);
			digitalWrite(BUZZERPIN, 0);
			DELAY_Ms(50);
		}
	}
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);    //Software start conversion
	UART_SendString("hello World\n\r");    //debug uart
	uint16_t bat_0 = BAT_EMPTY;
	uint16_t bat_10 = BAT_EMPTY+((float)(BAT_FULL-BAT_EMPTY)/100*10);
	uint16_t bat_20 = BAT_EMPTY+((float)(BAT_FULL-BAT_EMPTY)/100*20);
	uint16_t bat_50 = BAT_EMPTY+((float)(BAT_FULL-BAT_EMPTY)/100*50);
	uint16_t bat_60 = BAT_EMPTY+((float)(BAT_FULL-BAT_EMPTY)/100*60);
	uint16_t bat_70 = BAT_EMPTY+((float)(BAT_FULL-BAT_EMPTY)/100*70);
	uint16_t bat_100 = BAT_FULL;
	PWM_GEN_init(&pwm_gen);
	InitNormalization(300,4000,4000,&RP);
  while(1) {
		
		digitalWrite(LEDRPIN,digitalRead(HALLAPIN));
		digitalWrite(LEDGPIN,digitalRead(HALLBPIN));
		digitalWrite(LEDBPIN,digitalRead(HALLCPIN));
		

		
  }//main loop	
}

