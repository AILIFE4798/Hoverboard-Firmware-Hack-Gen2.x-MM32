#include "mm32_device.h"                // Device header
#include "hal_gpio.h"
#include "hal_adc.h"
#include "hal_conf.h"
#include "../Inc/hardware.h"
#include "../Inc/initialize.h"
#include "../Inc/delay.h"

extern uint32_t pins[33][3];
extern uint32_t millis;
uint8_t test;
int tmp;





void selfhold(){
	for(uint8_t i=0;i<33;i++){
		pinMode(pins[i][0],pins[i][1],GPIO_Mode_IPU);
	}
}

uint8_t detectSelfHold(){
	vref_Init();
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	DELAY_Ms(500);
	float vcc;
	for(uint8_t i=0;i<33;i++){
		uint32_t timeout = millis+50;
		uint32_t treshold = (uint16_t)ADC1->CH15DR+10;
		pinMode(pins[i][0],pins[i][1],GPIO_Mode_IPD);
		while(1){
			tmp = (uint16_t)ADC1->CH15DR;
			if(tmp>treshold){
				pinMode(pins[i][0],pins[i][1],GPIO_Mode_IPU);
				test=i;
			}
			if(millis>timeout){
				break;
			}
		}
	}	
	return test;
}
	
	
	
	
	
	
	
	
	


