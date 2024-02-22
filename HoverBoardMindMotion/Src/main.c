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
#include "../Inc/sim_eeprom.h"
#include "../Inc/hardware.h"


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
uint16_t pinstorage[64]={0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xDCAB, 31, 250, 0, 19200, 8192, 1, 30, 0, 10, 300, 1, 1, 42000, 32000, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t flicker=0;

s32 main(void){
	DELAY_Init();
	if(!restorecfg()){    //if data in eeprom is not valid, do not boot up
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
	if(LATCHPIN<PINCOUNT){    //have latch
		DELAY_Ms(50);    //some board the micro controller can reset in time and turn back on
		digitalWrite(LATCHPIN, 1);
		while(digitalRead(BUTTONPIN)){    //wait while release button
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
  while(1) {
		if(BAT_FULL>20000&&BAT_FULL<65000){
			if(vbat*10>bat_70){
				digitalWrite(LEDRPIN,0);
				digitalWrite(LEDGPIN,1);
				digitalWrite(LEDBPIN,0);
			}else if(vbat*10>bat_60){
				digitalWrite(LEDRPIN,0);
				digitalWrite(LEDGPIN,1);
				digitalWrite(LEDBPIN,1);
			}else if(vbat*10>bat_50){
				digitalWrite(LEDRPIN,0);
				digitalWrite(LEDGPIN,0);
				digitalWrite(LEDBPIN,1);	
			}else if(vbat*10>bat_20){
				digitalWrite(LEDRPIN,1);
				digitalWrite(LEDGPIN,0);
				digitalWrite(LEDBPIN,1);
			}else if(vbat*10>bat_10){
				digitalWrite(LEDRPIN,1);
				digitalWrite(LEDGPIN,0);
				digitalWrite(LEDBPIN,0);
			}else{
				digitalWrite(LEDRPIN,flicker);
				digitalWrite(LEDGPIN,0);
				digitalWrite(LEDBPIN,0);
			}
		}else{
			digitalWrite(LEDRPIN,digitalRead(HALLAPIN));
			digitalWrite(LEDGPIN,digitalRead(HALLBPIN));
			digitalWrite(LEDBPIN,digitalRead(HALLCPIN));
		}
		if(millis-lastupdate>1){//speed pid loop
			speedupdate();
		  lastupdate=millis;
		}
		if(millis-lastflicker>700){//speed pid loop
			flicker=!flicker;
		  lastflicker=millis;
		}
		if(LATCHPIN<PINCOUNT){
			if(digitalRead(BUTTONPIN)){    //button press for shutdown
				TIM1->CCR1=0;    //shut down motor
				TIM1->CCR2=0;
				TIM1->CCR3=0;
				if(BUZZERPIN<PINCOUNT){
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

