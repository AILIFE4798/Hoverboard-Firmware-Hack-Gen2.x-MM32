#include "../Inc/hardware.h"

extern GPIO_InitTypeDef GPIO_InitStruct;




#ifdef TARGET_MM32SPIN25

const MM32GPIO pins[PINCOUNT] = {   // port,pin,pinsrc
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
{IOD,GPIO_Pin_7,GPIO_PinSource7},
};

const MM32ADC adcs[ADCCOUNT] = {
{PA0,ADC_Channel_0},
{PA1,ADC_Channel_1},
{PA2,ADC_Channel_2},
{PA3,ADC_Channel_3},
{PA4,ADC_Channel_4},
{PA5,ADC_Channel_5},
{PA6,ADC_Channel_6},
{PA7,ADC_Channel_7},
{PB0,ADC_Channel_8},
{PB1,ADC_Channel_9},
{PB2,ADC_Channel_10},
{PB10,ADC_Channel_11},
};

const MM32TIM23 halltims[TIMCOUNT] = {
{PA0,GPIO_AF_2,1},
{PA1,GPIO_AF_2,1},
{PA2,GPIO_AF_2,1},
{PA5,GPIO_AF_2,1},
{PA11,GPIO_AF_4,1},
{PA12,GPIO_AF_4,1},
{PA15,GPIO_AF_2,1},
{PB1,GPIO_AF_4,1},
{PB3,GPIO_AF_2,1},
{PB10,GPIO_AF_2,1},
{PC13,GPIO_AF_6,1},
{PC14,GPIO_AF_6,1},
{PC15,GPIO_AF_6,1},
{PA6,GPIO_AF_1,0},
{PA7,GPIO_AF_1,0},
{PB0,GPIO_AF_1,0},
{PB4,GPIO_AF_1,0},
{PB5,GPIO_AF_1,0},
{PB8,GPIO_AF_6,0},
{PB9,GPIO_AF_6,0},
{PD7,GPIO_AF_5,0},
};

const MM32UART uarts[UARTCOUNT] = {
{PB6,GPIO_AF_0,1},
{PB7,GPIO_AF_0,0},
{PB8,GPIO_AF_0,0},
{PB9,GPIO_AF_0,1},
{PD0,GPIO_AF_3,1},
{PD1,GPIO_AF_3,0},
{PA2,GPIO_AF_1,1,2},
{PA3,GPIO_AF_1,0,2},
{PA6,GPIO_AF_3,0,2},
{PA15,GPIO_AF_1,0,2},
};

const MM32TIMBK ocps[TIMBKCOUNT] = {
{PA6,GPIO_AF_2},
{PA11,GPIO_AF_6},
{PB12,GPIO_AF_2},
{PD1,GPIO_AF_0},
};

#else

const MM32GPIO pins[PINCOUNT] = {   // port,pin,pinsrc
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

const MM32ADC adcs[ADCCOUNT] = {
{PA0,ADC_Channel_0},
{PA1,ADC_Channel_1},
{PA2,ADC_Channel_2},
{PA3,ADC_Channel_3},
{PA4,ADC_Channel_4},
{PA5,ADC_Channel_5},
{PA6,ADC_Channel_6},
{PA7,ADC_Channel_7},
{PB0,ADC_Channel_8},
{PB1,ADC_Channel_9},
};

const MM32TIM23 halltims[TIMCOUNT] = {
{PA0,GPIO_AF_4,1},
{PA1,GPIO_AF_2,1},
{PA2,GPIO_AF_2,1},
{PA6,GPIO_AF_1,0},
{PA7,GPIO_AF_1,0},
{PB0,GPIO_AF_1,0},
{PB3,GPIO_AF_7,1},
{PB4,GPIO_AF_7,1},
{PB5,GPIO_AF_7,1},
{PB6,GPIO_AF_4,1},
{PB10,GPIO_AF_2,1},
{PC13,GPIO_AF_6,1},
{PC14,GPIO_AF_6,1},
{PC15,GPIO_AF_6,1},
};

const MM32UART uarts[UARTCOUNT] = {
{PB3,GPIO_AF_3,1,1},
{PB4,GPIO_AF_3,0,1},
{PB6,GPIO_AF_0,1,1},
{PB7,GPIO_AF_0,0,1},
{PA2,GPIO_AF_1,1,2},
{PA3,GPIO_AF_1,0,2},
{PA6,GPIO_AF_3,0,2},
{PA15,GPIO_AF_1,0,2},
{PB7,GPIO_AF_4,1,2},
{PB8,GPIO_AF_4,0,2},
};

const MM32TIMBK ocps[TIMBKCOUNT] = {
{PA4,GPIO_AF_3},
{PA6,GPIO_AF_2},
{PA13,GPIO_AF_7},
{PB12,GPIO_AF_2},
};

#endif



void pinMode(uint8_t io,uint8_t state){
	switch (pins[io].port){
		case IOA:
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStruct.GPIO_Mode = state;
			GPIO_InitStruct.GPIO_Pin = pins[io].pin;
			GPIO_Init(GPIOA, &GPIO_InitStruct);
		break;
		case IOB:
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStruct.GPIO_Mode = state;
			GPIO_InitStruct.GPIO_Pin = pins[io].pin;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
		break;
		case IOC:
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStruct.GPIO_Mode = state;
			GPIO_InitStruct.GPIO_Pin = pins[io].pin;
			GPIO_Init(GPIOC, &GPIO_InitStruct);
		break;
		case IOD:
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStruct.GPIO_Mode = state;
			GPIO_InitStruct.GPIO_Pin = pins[io].pin;
			GPIO_Init(GPIOD, &GPIO_InitStruct);
		break;
		
	}
}

void pinModeAF(uint8_t io,uint8_t af){
	switch (pins[io].port){
		case IOA:
			GPIO_PinAFConfig(GPIOA, pins[io].pinSrc, af);
		break;
		case IOB:
			GPIO_PinAFConfig(GPIOB, pins[io].pinSrc, af);
		break;
		case IOC:
			GPIO_PinAFConfig(GPIOC, pins[io].pinSrc, af);
		break;
		case IOD:
			GPIO_PinAFConfig(GPIOD, pins[io].pinSrc, af);
		break;
	}
}


uint8_t digitalRead(uint8_t io){
	switch (pins[io].port){
		case IOA:
			return GPIO_ReadInputDataBit(GPIOA, pins[io].pin);
		break;
		case IOB:
			return GPIO_ReadInputDataBit(GPIOB, pins[io].pin);
		break;
		case IOC:
			return GPIO_ReadInputDataBit(GPIOC, pins[io].pin);
		break;
		case IOD:
			return GPIO_ReadInputDataBit(GPIOD, pins[io].pin);
		break;
		default:
			return 0;
	}
}

void digitalWrite(uint8_t io, uint8_t state){
	switch (pins[io].port){
		case IOA:
			GPIO_WriteBit(GPIOA, pins[io].pin, state);
		break;
		case IOB:
			GPIO_WriteBit(GPIOB, pins[io].pin, state);
		break;
		case IOC:
			GPIO_WriteBit(GPIOC, pins[io].pin, state);
		break;
		case IOD:
			GPIO_WriteBit(GPIOD, pins[io].pin, state);
		break;
	}
}


uint16_t analogRead(uint8_t io){
	uint8_t adcch;
	for(uint8_t i=0;i<ADCCOUNT;i++){
		if(adcs[i].io==io){
			adcch=i;
			break;
		}
	}
	switch (adcs[adcch].channel){
		case ADC_Channel_0:
			return ADC1->ADDR0;
		break;
		case ADC_Channel_1:
			return ADC1->ADDR1;
		break;
		case ADC_Channel_2:
			return ADC1->ADDR2;
		break;
		case ADC_Channel_3:
			return ADC1->ADDR3;
		break;
		case ADC_Channel_4:
			return ADC1->ADDR4;
		break;
		case ADC_Channel_5:
			return ADC1->ADDR5;
		break;
		case ADC_Channel_6:
			return ADC1->ADDR6;
		break;
		case ADC_Channel_7:
			return ADC1->ADDR7;
		break;
		case ADC_Channel_8:
			return ADC1->ADDR8;
		break;
		case ADC_Channel_9:
			return ADC1->ADDR9;
		break;
		default:
			return 0;
	}
}



