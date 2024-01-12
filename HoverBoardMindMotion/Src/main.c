#include "mm32_device.h"                // Device header
#include "RTE_Components.h"             // Component selection
#include "hal_gpio.c"
#include "hal_gpio.h"
#include "hal_rcc.h"
#include "delay.h"

#define LEDPIN GPIO_PinSource5
#define LEDPORT GPIO_PortSourceGPIOA

s32 main(void){
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOD, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LEDPORT, &GPIO_InitStruct);
	DELAY_Init();
  while(1) {
    GPIO_WriteBit(LEDPORT, LEDPIN, 1);
		DELAY_Ms(1000);
		GPIO_WriteBit(LEDPORT, LEDPIN, 0);
		DELAY_Ms(1000);
  }
	
}


