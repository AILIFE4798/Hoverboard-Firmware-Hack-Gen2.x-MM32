#include "mm32_device.h"                // Device header
#include "hal_gpio.h"
#include "hal_adc.h"
#include "hal_conf.h"
#include "../Inc/hardware.h"
#include "../Inc/initialize.h"
#include "../Inc/delay.h"
#include "../Inc/uart.h"
#include "../Inc/bldc.h"

extern uint32_t pins[33][3];
extern uint32_t millis;
uint8_t test;
int tmp;
uint8_t pinstorage[16];    //halla,hallb,hallc,ledr,ledg,ledb,ledup,leddown,buzzer,button,selfhold,charger,vbat,itotal,tx,rx
uint8_t used(uint8_t pin);
uint8_t mode=0;//0=startup,1=wait for serial,2=idle
uint32_t lastCommutation;
extern uint8_t step;
uint8_t init=0;

const uint8_t banner[]={0X20,0X20,0X5F,0X20,0X20,0X20,0X5F,0X20,0X20,0X5F,0X5F,0X5F,0X5F,0X5F,0X20,0X20,0X20,0X20,0X20,0X5F,0X5F,0X5F,0X5F,0X5F,0X5F,0X5F,0X20,0X5F,0X5F,0X5F,0X5F,0X20,0X20,0X20,0X20,0X5F,0X20,0X20,0X20,0X5F,0X20,0X20,0X20,0X20,0X5F,0X20,0X20,0X20,0X20,0X5F,0X5F,0X5F,0X5F,0X20,0X5F,0X20,0X20,0X5F,0X5F,0X20,0X5F,0X5F,0X20,0X20,0X20,0X20,0X20,0X5F,0X5F,0X5F,0X5F,0X5F,0X5F,0X20,0X20,0X0A,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X2F,0X20,0X5F,0X20,0X5C,0X20,0X5C,0X20,0X20,0X20,0X2F,0X20,0X2F,0X20,0X5F,0X5F,0X5F,0X5F,0X7C,0X20,0X20,0X5F,0X20,0X5C,0X20,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X20,0X20,0X2F,0X20,0X5C,0X20,0X20,0X2F,0X20,0X5F,0X5F,0X5F,0X7C,0X20,0X7C,0X2F,0X20,0X2F,0X20,0X5C,0X20,0X5C,0X20,0X20,0X20,0X2F,0X20,0X2F,0X5F,0X5F,0X5F,0X20,0X5C,0X20,0X0A,0X20,0X7C,0X20,0X7C,0X5F,0X7C,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X20,0X5C,0X20,0X5C,0X20,0X2F,0X20,0X2F,0X7C,0X20,0X20,0X5F,0X7C,0X20,0X7C,0X20,0X7C,0X5F,0X29,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X5F,0X7C,0X20,0X7C,0X20,0X2F,0X20,0X5F,0X20,0X5C,0X7C,0X20,0X7C,0X20,0X20,0X20,0X7C,0X20,0X27,0X20,0X2F,0X20,0X20,0X20,0X5C,0X20,0X5C,0X20,0X2F,0X20,0X2F,0X20,0X20,0X5F,0X5F,0X29,0X20,0X7C,0X0A,0X20,0X7C,0X20,0X20,0X5F,0X20,0X20,0X7C,0X20,0X7C,0X5F,0X7C,0X20,0X7C,0X5C,0X20,0X56,0X20,0X2F,0X20,0X7C,0X20,0X7C,0X5F,0X5F,0X5F,0X7C,0X20,0X20,0X5F,0X20,0X3C,0X20,0X20,0X7C,0X20,0X20,0X5F,0X20,0X20,0X7C,0X2F,0X20,0X5F,0X5F,0X5F,0X20,0X5C,0X20,0X7C,0X5F,0X5F,0X5F,0X7C,0X20,0X2E,0X20,0X5C,0X20,0X20,0X20,0X20,0X5C,0X20,0X56,0X20,0X2F,0X20,0X20,0X2F,0X20,0X5F,0X5F,0X2F,0X20,0X0A,0X20,0X7C,0X5F,0X7C,0X20,0X7C,0X5F,0X7C,0X5C,0X5F,0X5F,0X5F,0X2F,0X20,0X20,0X5C,0X5F,0X2F,0X20,0X20,0X7C,0X5F,0X5F,0X5F,0X5F,0X5F,0X7C,0X5F,0X7C,0X20,0X5C,0X5F,0X5C,0X20,0X7C,0X5F,0X7C,0X20,0X7C,0X5F,0X2F,0X5F,0X2F,0X20,0X20,0X20,0X5C,0X5F,0X5C,0X5F,0X5F,0X5F,0X5F,0X7C,0X5F,0X7C,0X5C,0X5F,0X5C,0X20,0X20,0X20,0X20,0X5C,0X5F,0X2F,0X20,0X20,0X7C,0X5F,0X5F,0X5F,0X5F,0X5F,0X7C,0X0A,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X0A,0X0A};
const uint8_t PXX[33][4]={"PA0","PA1","PA2","PA3","PA4","PA5","PA6","PA7","PA11","PA12","PA13","PA14","PA15","PB0","PB1","PB2","PB3","PB4","PB5","PB6","PB7","PB8","PB9","PB10","PB11","PB12","PC13","PC14","PC15","PD0","PD1","PD2","PD3"};

	
	

void selfhold(){
	for(uint8_t i=0;i<33;i++){
		if(!used(i)){
			pinMode(pins[i][0],pins[i][1],GPIO_Mode_IPU);    //pull up insted of output high to protect micro controller
		}
	}
}

uint8_t detectSelfHold(){
	vref_Init();    //uses internal 1.2v refrence to detect vcc voltage
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	DELAY_Ms(100);    //wait for adc stablize
	float vcc;
	uint8_t havelatch=0;
	for(uint8_t i=0;i<33;i++){
		if(!used(i)){
			uint32_t timeout = millis+50;    //10ms not enough for capacitor to discharge
			uint32_t treshold = (uint16_t)ADC1->CH15DR+10;
			pinMode(pins[i][0],pins[i][1],GPIO_Mode_FLOATING);    //release latch
			while(1){
				tmp = (uint16_t)ADC1->CH15DR;
				if(tmp>treshold){
					pinMode(pins[i][0],pins[i][1],GPIO_Mode_IPU);    //set it back quickly
					pinstorage[10] = i;    //save the pin
					havelatch=1;
					DELAY_Ms(10);    //capacitor charge back up
				}
				if(millis>timeout){
					break;
				}
			}
	  }
	}	
	return havelatch;
}
	
	
uint8_t used(uint8_t pin){
	for(uint8_t j=0;j<16;j++){
		if(pinstorage[j]==pin){
			return 1;    //pin already used
		}
	}
	return 0;
}
	
	
void autoDetectSerialIt(){
	switch (mode){
		case 1 :
			mode=3;
			init=1;
			break;
		case 3 :
			
			break;
	}
}
	
	
void simhallupdate(){
	if(millis-lastCommutation>30){
		step++;
		if(step>6){
			step=1;
		}
		commutate();
		lastCommutation=millis;
	}
}	

void autoDetectInit(){
	switch (mode){
		case 3 :
			TIM1->CCR1=4000;
			TIM1->CCR2=4000;
			TIM1->CCR3=4000;
		break;
	
	
	
	
	
	
	}
}
	
	
	
	
	
	
	
