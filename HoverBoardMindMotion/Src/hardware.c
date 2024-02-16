#include "../Inc/hardware.h"

extern GPIO_InitTypeDef GPIO_InitStruct;


uint32_t pins[33][3] = {   // port,pin,pinsrc,ADC,ADC2,HALL AF,HALL TIM,UART AF
{IOA,GPIO_Pin_0,GPIO_PinSource0},
{IOA,GPIO_Pin_1,GPIO_PinSource1},
{IOA,GPIO_Pin_2,GPIO_PinSource2},
{IOA,GPIO_Pin_3,GPIO_PinSource3},
{IOA,GPIO_Pin_4,GPIO_PinSource4},
{IOA,GPIO_Pin_5,GPIO_PinSource5},
{IOA,GPIO_Pin_6,GPIO_PinSource6},
{IOA,GPIO_Pin_7,GPIO_PinSource7},
{IOA,GPIO_Pin_11,GPIO_PinSource11},
{IOA,GPIO_Pin_12,GPIO_PinSource12},
{IOA,GPIO_Pin_13,GPIO_PinSource13},
{IOA,GPIO_Pin_14,GPIO_PinSource14},
{IOA,GPIO_Pin_15,GPIO_PinSource15},
{IOB,GPIO_Pin_0,GPIO_PinSource0},
{IOB,GPIO_Pin_1,GPIO_PinSource1},
{IOB,GPIO_Pin_2,GPIO_PinSource2},
{IOB,GPIO_Pin_3,GPIO_PinSource3},
{IOB,GPIO_Pin_4,GPIO_PinSource4},
{IOB,GPIO_Pin_5,GPIO_PinSource5},
{IOB,GPIO_Pin_6,GPIO_PinSource6},
{IOB,GPIO_Pin_7,GPIO_PinSource7},
{IOB,GPIO_Pin_8,GPIO_PinSource8},
{IOB,GPIO_Pin_8,GPIO_PinSource9},
{IOB,GPIO_Pin_10,GPIO_PinSource10},
{IOB,GPIO_Pin_11,GPIO_PinSource11},
{IOB,GPIO_Pin_12,GPIO_PinSource12},
{IOC,GPIO_Pin_13,GPIO_PinSource13},
{IOC,GPIO_Pin_14,GPIO_PinSource14},
{IOC,GPIO_Pin_15,GPIO_PinSource15},
{IOD,GPIO_Pin_0,GPIO_PinSource0},
{IOD,GPIO_Pin_1,GPIO_PinSource1},
{IOD,GPIO_Pin_2,GPIO_PinSource2},
{IOD,GPIO_Pin_3,GPIO_PinSource3},
};




void pinMode(uint8_t port,uint16_t pin,uint8_t state){
	switch (port){
		case IOA:
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStruct.GPIO_Mode = state;
			GPIO_InitStruct.GPIO_Pin = pin;
			GPIO_Init(GPIOA, &GPIO_InitStruct);
		break;
		case IOB:
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStruct.GPIO_Mode = state;
			GPIO_InitStruct.GPIO_Pin = pin;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
		break;
		case IOC:
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStruct.GPIO_Mode = state;
			GPIO_InitStruct.GPIO_Pin = pin;
			GPIO_Init(GPIOC, &GPIO_InitStruct);
		break;
		case IOD:
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStruct.GPIO_Mode = state;
			GPIO_InitStruct.GPIO_Pin = pin;
			GPIO_Init(GPIOD, &GPIO_InitStruct);
		break;
		
	}
}


uint8_t digitalRead(uint8_t port,uint16_t pin){
	switch (port){
		case IOA:
			return GPIO_ReadInputDataBit(GPIOA, pin);
		break;
		case IOB:
			return GPIO_ReadInputDataBit(GPIOB, pin);
		break;
		case IOC:
			return GPIO_ReadInputDataBit(GPIOC, pin);
		break;
		case IOD:
			return GPIO_ReadInputDataBit(GPIOD, pin);
		break;
		default:
			return 0;
	}
}

