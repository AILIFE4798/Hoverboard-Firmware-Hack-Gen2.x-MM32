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





GPIO_InitTypeDef GPIO_InitStruct;
uint8_t  masterslave;




s32 main(void){	
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOD, ENABLE);
	selfhold();
	DELAY_Init();
	DELAY_Ms(2000);
	masterslave = detectSelfHold();
	while(1);
}

