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
#include "../Inc/autodetect.h"

uint8_t step=1;//very importatnt to set to 1 or it will not work
uint32_t millis;
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



GPIO_InitTypeDef GPIO_InitStruct;
uint8_t  masterslave;
extern uint8_t banner;
extern uint8_t pinstorage[16];
extern uint8_t mode;
extern uint8_t init;


s32 main(void){	
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOD, ENABLE);
	selfhold();    //pull every pin high
	pinstorage[14] = 17;    //serial tx rx is used,do not modify
	pinstorage[15] = 19;
	DELAY_Init();    //delay needed in autodetect
	BLDC_init();    //motor pin is always the same so initialize it first
	TIM1_init(PWM_RES, 0);
	UARTX_Init(BAUD);    //uart used for autodetect, only 4 possible pin combination on uart1
	exNVIC_Configure(DMA1_Channel2_3_IRQn, 0, 0);
	DMA_NVIC_Config(DMA1_Channel3, (u32)&UART1->RDR, (u32)sRxBuffer, 1);
	DELAY_Ms(2000);    //give time to release button 
	masterslave = detectSelfHold();    //no self hold pin=slave, will release all other pins to floating
	mode=1;
	while(1){
		if(init){
			init=0;
			autoDetectInit();
		}
		switch (mode){
			case 1 :
				UART_Send_Group(&banner,457);
				UART_SendString("Welcome to PinFinder\n\r");
				UART_SendString("press enter to continue...\n\n\n\n\r");
				DELAY_Ms(5000);
			break;
			case 3 :
				simhallupdate();
			break;
		}
  }
}

