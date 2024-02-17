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
extern __IO u32 sTimingDelay;
extern u8 sRxBuffer[10];
uint16_t revolutions=0;
//uint8_t scan=0;
//uint8_t halltmp[3];
//uint8_t laststate[33];
//uint32_t lastchange[33];
uint8_t selpin=0;
uint8_t blinkstate=0;
uint32_t lastblink;

uint8_t hallA[33];
uint8_t hallB[33];
uint8_t hallC[33];

const uint8_t banner[]={0X20,0X20,0X5F,0X20,0X20,0X20,0X5F,0X20,0X20,0X5F,0X5F,0X5F,0X5F,0X5F,0X20,0X20,0X20,0X20,0X20,0X5F,0X5F,0X5F,0X5F,0X5F,0X5F,0X5F,0X20,0X5F,0X5F,0X5F,0X5F,0X20,0X20,0X20,0X20,0X5F,0X20,0X20,0X20,0X5F,0X20,0X20,0X20,0X20,0X5F,0X20,0X20,0X20,0X20,0X5F,0X5F,0X5F,0X5F,0X20,0X5F,0X20,0X20,0X5F,0X5F,0X20,0X5F,0X5F,0X20,0X20,0X20,0X20,0X20,0X5F,0X5F,0X5F,0X5F,0X5F,0X5F,0X20,0X20,0X0A,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X2F,0X20,0X5F,0X20,0X5C,0X20,0X5C,0X20,0X20,0X20,0X2F,0X20,0X2F,0X20,0X5F,0X5F,0X5F,0X5F,0X7C,0X20,0X20,0X5F,0X20,0X5C,0X20,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X20,0X20,0X2F,0X20,0X5C,0X20,0X20,0X2F,0X20,0X5F,0X5F,0X5F,0X7C,0X20,0X7C,0X2F,0X20,0X2F,0X20,0X5C,0X20,0X5C,0X20,0X20,0X20,0X2F,0X20,0X2F,0X5F,0X5F,0X5F,0X20,0X5C,0X20,0X0A,0X20,0X7C,0X20,0X7C,0X5F,0X7C,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X20,0X5C,0X20,0X5C,0X20,0X2F,0X20,0X2F,0X7C,0X20,0X20,0X5F,0X7C,0X20,0X7C,0X20,0X7C,0X5F,0X29,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X5F,0X7C,0X20,0X7C,0X20,0X2F,0X20,0X5F,0X20,0X5C,0X7C,0X20,0X7C,0X20,0X20,0X20,0X7C,0X20,0X27,0X20,0X2F,0X20,0X20,0X20,0X5C,0X20,0X5C,0X20,0X2F,0X20,0X2F,0X20,0X20,0X5F,0X5F,0X29,0X20,0X7C,0X0A,0X20,0X7C,0X20,0X20,0X5F,0X20,0X20,0X7C,0X20,0X7C,0X5F,0X7C,0X20,0X7C,0X5C,0X20,0X56,0X20,0X2F,0X20,0X7C,0X20,0X7C,0X5F,0X5F,0X5F,0X7C,0X20,0X20,0X5F,0X20,0X3C,0X20,0X20,0X7C,0X20,0X20,0X5F,0X20,0X20,0X7C,0X2F,0X20,0X5F,0X5F,0X5F,0X20,0X5C,0X20,0X7C,0X5F,0X5F,0X5F,0X7C,0X20,0X2E,0X20,0X5C,0X20,0X20,0X20,0X20,0X5C,0X20,0X56,0X20,0X2F,0X20,0X20,0X2F,0X20,0X5F,0X5F,0X2F,0X20,0X0A,0X20,0X7C,0X5F,0X7C,0X20,0X7C,0X5F,0X7C,0X5C,0X5F,0X5F,0X5F,0X2F,0X20,0X20,0X5C,0X5F,0X2F,0X20,0X20,0X7C,0X5F,0X5F,0X5F,0X5F,0X5F,0X7C,0X5F,0X7C,0X20,0X5C,0X5F,0X5C,0X20,0X7C,0X5F,0X7C,0X20,0X7C,0X5F,0X2F,0X5F,0X2F,0X20,0X20,0X20,0X5C,0X5F,0X5C,0X5F,0X5F,0X5F,0X5F,0X7C,0X5F,0X7C,0X5C,0X5F,0X5C,0X20,0X20,0X20,0X20,0X5C,0X5F,0X2F,0X20,0X20,0X7C,0X5F,0X5F,0X5F,0X5F,0X5F,0X7C,0X0A,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X0A,0X0A};
uint8_t PXX[33][4]={"PA0 ","PA1 ","PA2 ","PA3 ","PA4 ","PA5 ","PA6 ","PA7 ","PA11","PA12","PA13","PA14","PA15","PB0 ","PB1 ","PB2 ","PB3 ","PB4 ","PB5 ","PB6 ","PB7 ","PB8 ","PB9 ","PB10","PB11","PB12","PC13","PC14","PC15","PD0 ","PD1 ","PD2 ","PD3 "};

	
void autoDetectInit();

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
			if(sRxBuffer[0]=='\n'){
				mode=3;
				init=1;
				sTimingDelay=0;
			}
			break;
		case 3 :
			if(sRxBuffer[0]=='\n'){
				mode=4;
				init=1;
				sTimingDelay=0;
			}
			break;
		case 4 :
			switch(sRxBuffer[0]){
				case '\n':
					mode=3;
					init=1;
					sTimingDelay=0;
				break;
				case 'w':
				case 'r':
				case 'g':
				case 'b':
				case 'u':
				case 'l':
				case 'z':
					pinMode(pins[selpin][0],pins[selpin][1],sRxBuffer[0]=='w' ? GPIO_Mode_IPU : GPIO_Mode_FLOATING);
					switch(sRxBuffer[0]){
						case 'r':
							pinstorage[3]=selpin;
						break;
						case 'g':
							pinstorage[4]=selpin;
						break;
						case 'b':
							pinstorage[5]=selpin;
						break;
						case 'u':
							pinstorage[6]=selpin;
						break;
						case 'l':
							pinstorage[7]=selpin;
						break;
						case 'z':
							pinstorage[8]=selpin;
						break;
					}
					do{
						if(selpin==32){
							selpin=0;
						}else{
							selpin++;
						}
					}while(used(selpin));
				break;
				case 's':
					pinMode(pins[selpin][0],pins[selpin][1],GPIO_Mode_IPU);
					do{
						if(selpin==0){
							selpin=32;
						}else{
							selpin--;
						}
					}while(used(selpin));
				break;
			}
			
			break;
	}
}
	

void simhallupdate(){    
	while(pinstorage[0]==255||pinstorage[1]==255||pinstorage[2]==255){
		for(uint8_t i=1;i<7;i++){
			step=i;
			commutate();
			DELAY_Ms(30);
			for(uint8_t i=0;i<33;i++){
				if(!used(i)){
					switch (step){
						case 1:
							hallA[i]=!digitalRead(pins[i][0],pins[i][1])&&hallA[i];
							hallB[i]=digitalRead(pins[i][0],pins[i][1])&&hallB[i];
							hallC[i]=digitalRead(pins[i][0],pins[i][1])&&hallC[i];
						break;
						case 2:
							hallA[i]=!digitalRead(pins[i][0],pins[i][1])&&hallA[i];
							hallB[i]=!digitalRead(pins[i][0],pins[i][1])&&hallB[i];
							hallC[i]=digitalRead(pins[i][0],pins[i][1])&&hallC[i];
						break;
						case 3:
							hallA[i]=digitalRead(pins[i][0],pins[i][1])&&hallA[i];
							hallB[i]=!digitalRead(pins[i][0],pins[i][1])&&hallB[i];
							hallC[i]=digitalRead(pins[i][0],pins[i][1])&&hallC[i];
						break;
						case 4:
							hallA[i]=digitalRead(pins[i][0],pins[i][1])&&hallA[i];
							hallB[i]=!digitalRead(pins[i][0],pins[i][1])&&hallB[i];
							hallC[i]=!digitalRead(pins[i][0],pins[i][1])&&hallC[i];
						break;
						case 5:
							hallA[i]=digitalRead(pins[i][0],pins[i][1])&&hallA[i];
							hallB[i]=digitalRead(pins[i][0],pins[i][1])&&hallB[i];
							hallC[i]=!digitalRead(pins[i][0],pins[i][1])&&hallC[i];
						break;
						case 6:
							hallA[i]=!digitalRead(pins[i][0],pins[i][1])&&hallA[i];
							hallB[i]=digitalRead(pins[i][0],pins[i][1])&&hallB[i];
							hallC[i]=!digitalRead(pins[i][0],pins[i][1])&&hallC[i];
						break;
					}
				}
			}
		}
		
		for(uint8_t i=0;i<33;i++){
			if(hallA[i]){
				pinstorage[0]=i;
				UART_SendString("\nHALLA:");
				UART_Send_Group(&PXX[i][0],4);
			}
			if(hallB[i]){
				pinstorage[1]=i;
				UART_SendString("\nHALLB:");
				UART_Send_Group(&PXX[i][0],4);
			}
			if(hallC[i]){
				pinstorage[2]=i;
				UART_SendString("\nHALLC:");
				UART_Send_Group(&PXX[i][0],4);
			}
			
		}
		for(uint8_t i=0;i<33;i++){
			hallA[i] = 1;
			hallB[i] = 1;
			hallC[i] = 1;
		}
		for(uint8_t i=0;i<33;i++){    //remove used pins from hall array
			if(used(i)){
				hallA[i]=0;
				hallB[i]=0;
				hallC[i]=0;
			}
		}
	}
	TIM1->CCR1=0;
	TIM1->CCR2=0;
	TIM1->CCR3=0;
}	


/*
void simhallupdate(){    //does not work : (
	for(uint8_t i=0;i<33;i++){
		if(!used(i)){
			laststate[i]=digitalRead(pins[i][0],pins[i][1]);
		}
	}
	while(halltmp[2]==255){
		uint8_t tmpindex=0;
		for(uint8_t i=0;i<33;i++){
			if(millis-lastCommutation>30){
				step++;
				if(step>6){
					step=1;
					revolutions++;
				}
				commutate();
				lastCommutation=millis;
			}
			if(!used(i)){
				TIM_CtrlPWMOutputs(TIM1, DISABLE);
				if(laststate[i]!=digitalRead(pins[i][0],pins[i][1])){
					TIM_CtrlPWMOutputs(TIM1, ENABLE);
					char buffer[16];
					uint32_t halltime=millis-lastchange[i];
					sprintf(&buffer,"\nhalltime:%i",halltime);
					UART_Send_Group(&buffer[0],16);
					if(halltime>20&&halltime<100){
						pinstorage[tmpindex] = halltmp[tmpindex] = i;
						tmpindex++;
						UART_Send_Group(&PXX[i][0],4);
					}
					lastchange[i]=millis;
				}
				TIM_CtrlPWMOutputs(TIM1, ENABLE);
				DELAY_Ms(1);
			}
		}
	}
}
*/

void autoDetectInit(){
	switch (mode){
		case 3 :
			TIM1->CCR1=4000;    //spin motor at 50% pwm
			TIM1->CCR2=4000;
			TIM1->CCR3=4000;
			for(uint8_t i=0;i<33;i++){
				hallA[i] = 1;
				hallB[i] = 1;
				hallC[i] = 1;
			}
			for(uint8_t i=0;i<33;i++){    //remove used pins from hall array
				if(used(i)){
					hallA[i]=0;
					hallB[i]=0;
					hallC[i]=0;
				}
			}
			pinstorage[0]=pinstorage[1]=pinstorage[2]=255;
		/*
			halltmp[0]=halltmp[1]=halltmp[2]=255;
			revolutions=0;
		*/
		break;
		case 4 :
			for(uint8_t i=0;i<33;i++){    //find the first unused pin to start
				if(!used(i)){
					pinMode(pins[i][0],pins[i][1],GPIO_Mode_IPU);
				}
			}
			selpin=0;
			while(used(selpin)){
				selpin++;
			}
		break;
	
	
	
	
	
	}
}
	
void blinkLEDupdate(){
	if(millis-lastblink>200){
		pinMode(pins[selpin][0],pins[selpin][1],blinkstate ? GPIO_Mode_IPU : GPIO_Mode_IPD);
		blinkstate=!blinkstate;
		lastblink=millis;
	}
	
}
	
	
	
	
	
