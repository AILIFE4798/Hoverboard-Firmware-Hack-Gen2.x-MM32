#ifdef TARGET_MM32SPIN25
#include "HAL_device.h"                 // Device header
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
#include "../Inc/autodetect.h"
#include "../Inc/hardware.h"

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
uint16_t pinstorage[64]={0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xDCAB, 31, 250, 0, 19200, 8192, 1, 30, 0, 10, 300, 1, 1, 42000, 32000, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
extern modes_t mode;
extern uint8_t init;
extern uint8_t wait;
float vcc;
extern MM32GPIO pins[PINCOUNT];
extern MM32ADC adcs[ADCCOUNT];

s32 main(void){	
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOD, ENABLE);
	TXPIN = TX_AD;    //serial tx rx is used,do not modify
	RXPIN = RX_AD;
	DELAY_Init();    //delay needed in autodetect
	BLDC_init();    //motor pin is always the same so initialize it first
	TIM1_init(PWM_RES_AD, 0);
	UARTX_Init(BAUD_AD);    //uart used for autodetect, only 4 possible pin combination on uart1
	exNVIC_Configure(DMA1_Channel2_3_IRQn, 0, 0);
	DMA_NVIC_Config(DMA1_Channel3, (u32)&UART1->RDR, (u32)sRxBuffer, 1);
	if(restorecfg()){    //valid config is present
		if(LATCHPIN<PINCOUNT){
			pinMode(LATCHPIN,INPUT_PULLUP);
			masterslave = 1;
		}
		vref_Init();    //uses internal 1.2v refrence to detect vcc voltage
		DELAY_Ms(100);
		uint16_t adcval = ADC1->ADDR15;
		vcc=(double)4915.2/adcval;    //vcc saved to calculate accurate vbat
	}else{
		selfhold();    //pull every pin high
		DELAY_Ms(1000);    //give time to release button 
		masterslave = detectSelfHold();    //no self hold pin=slave, will release all other pins to floating
	}
	mode=MODE_WAIT_UART;
	while(1){
		if(init){    //initialization or startup message needed
			init=0;
			autoDetectInit();
		}
		switch (mode){
			case MODE_WAIT_UART :
				UART_SendString("\n\n\n\n\r");
				UART_Send_Group(&banner,464);
				UART_SendString("Welcome to PinFinder\n\r");
				UART_SendString("press enter to continue");
				for(uint8_t i=0;i<50;i++){    //keep printing to help find tx rx line
					if(mode!=1){
						break;
					}
					UART_SendString(".");
					DELAY_Ms(100);
				}
			break;
			case MODE_HALL :
				simhallupdate();
			break;
			case MODE_LED :
				blinkLEDupdate();
			break;
			case MODE_VBAT :
				printvoltage();
			break;
			case MODE_BUTTON :
				checkbutton();
			break;
			case MODE_TESTROTATE :
				testrotateloop();
			break;
		}
	}
}

