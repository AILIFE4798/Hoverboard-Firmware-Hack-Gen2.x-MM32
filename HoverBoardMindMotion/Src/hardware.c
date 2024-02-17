#include "../Inc/hardware.h"

extern GPIO_InitTypeDef GPIO_InitStruct;


const uint32_t pins[33][3] = {   // port,pin,pinsrc,ADC,ADC2,HALL AF,HALL TIM,UART AF
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
{IOB,GPIO_Pin_9,GPIO_PinSource9},
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

const uint32_t adcs[10][3] = {
{0,ADC_Channel_0,0},
{1,ADC_Channel_1,1},
{2,ADC_Channel_2,2},
{3,ADC_Channel_3,3},
{4,ADC_Channel_4,4},
{5,ADC_Channel_5,5},
{6,ADC_Channel_6,6},
{7,ADC_Channel_7,7},
{13,ADC_Channel_8,8},
{14,ADC_Channel_9,9}};



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

void digitalWrite(uint8_t port,uint16_t pin,uint8_t state){
	switch (port){
		case IOA:
			GPIO_WriteBit(GPIOA, pin, state);
		break;
		case IOB:
			GPIO_WriteBit(GPIOA, pin, state);
		break;
		case IOC:
			GPIO_WriteBit(GPIOA, pin, state);
		break;
		case IOD:
			GPIO_WriteBit(GPIOA, pin, state);
		break;
	}
}


uint16_t analogRead(uint16_t channel){
	switch (channel){
		case 0:
			return ADC1->ADDR0;
		break;
		case 1:
			return ADC1->ADDR1;
		break;
		case 2:
			return ADC1->ADDR2;
		break;
		case 3:
			return ADC1->ADDR3;
		break;
		case 4:
			return ADC1->ADDR4;
		break;
		case 5:
			return ADC1->ADDR5;
		break;
		case 6:
			return ADC1->ADDR6;
		break;
		case 7:
			return ADC1->ADDR7;
		break;
		case 8:
			return ADC1->ADDR8;
		break;
		case 9:
			return ADC1->ADDR9;
		break;
		default:
			return 0;
	}
}



