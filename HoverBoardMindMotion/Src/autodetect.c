#include "mm32_device.h"                // Device header
#include "hal_gpio.h"
#include "hal_adc.h"
#include "hal_conf.h"
#include "hal_uid.h"
#include "../Inc/hardware.h"
#include "../Inc/initialize.h"
#include "../Inc/delay.h"
#include "../Inc/uart.h"
#include "../Inc/bldc.h"
#include "../Inc/sim_eeprom.h"

extern uint32_t pins[33][3];
extern uint32_t adcs[10][3];
extern uint32_t millis;
uint8_t test;
int tmp;
uint8_t used(uint8_t pin);
uint8_t mode=0;//0=startup,1=wait for serial,2=menu,3=hall,4=led,5=adc
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
extern float vcc;
uint8_t adcleft[10];
uint8_t showalladc=0;
uint8_t detectall=0;
extern uint8_t masterslave;
extern u8 device_id_data[12];
uint8_t wait;
uint8_t doinloop=0;

uint8_t hallA[33];
uint8_t hallB[33];
uint8_t hallC[33];
uint8_t pinstorage[16]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};    
//halla,hallb,hallc,ledr,ledg,ledb,ledup,leddown,buzzer,button,selfhold,charger,vbat,itotal,tx,rx

uint8_t banner[]={0X20,0X20,0X5F,0X20,0X20,0X20,0X5F,0X20,0X20,0X5F,0X5F,0X5F,0X5F,0X5F,0X20,0X20,0X20,0X20,0X20,0X5F,0X5F,0X5F,0X5F,0X5F,0X5F,0X5F,0X20,0X5F,0X5F,0X5F,0X5F,0X20,0X20,0X20,0X20,0X5F,0X20,0X20,0X20,0X5F,0X20,0X20,0X20,0X20,0X5F,0X20,0X20,0X20,0X20,0X5F,0X5F,0X5F,0X5F,0X20,0X5F,0X20,0X20,0X5F,0X5F,0X20,0X5F,0X5F,0X20,0X20,0X20,0X20,0X20,0X5F,0X5F,0X5F,0X5F,0X5F,0X5F,0X20,0X20,0X0A,0X0D,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X2F,0X20,0X5F,0X20,0X5C,0X20,0X5C,0X20,0X20,0X20,0X2F,0X20,0X2F,0X20,0X5F,0X5F,0X5F,0X5F,0X7C,0X20,0X20,0X5F,0X20,0X5C,0X20,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X20,0X20,0X2F,0X20,0X5C,0X20,0X20,0X2F,0X20,0X5F,0X5F,0X5F,0X7C,0X20,0X7C,0X2F,0X20,0X2F,0X20,0X5C,0X20,0X5C,0X20,0X20,0X20,0X2F,0X20,0X2F,0X5F,0X5F,0X5F,0X20,0X5C,0X20,0X0A,0X0D,0X20,0X7C,0X20,0X7C,0X5F,0X7C,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X20,0X5C,0X20,0X5C,0X20,0X2F,0X20,0X2F,0X7C,0X20,0X20,0X5F,0X7C,0X20,0X7C,0X20,0X7C,0X5F,0X29,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X5F,0X7C,0X20,0X7C,0X20,0X2F,0X20,0X5F,0X20,0X5C,0X7C,0X20,0X7C,0X20,0X20,0X20,0X7C,0X20,0X27,0X20,0X2F,0X20,0X20,0X20,0X5C,0X20,0X5C,0X20,0X2F,0X20,0X2F,0X20,0X20,0X5F,0X5F,0X29,0X20,0X7C,0X0A,0X0D,0X20,0X7C,0X20,0X20,0X5F,0X20,0X20,0X7C,0X20,0X7C,0X5F,0X7C,0X20,0X7C,0X5C,0X20,0X56,0X20,0X2F,0X20,0X7C,0X20,0X7C,0X5F,0X5F,0X5F,0X7C,0X20,0X20,0X5F,0X20,0X3C,0X20,0X20,0X7C,0X20,0X20,0X5F,0X20,0X20,0X7C,0X2F,0X20,0X5F,0X5F,0X5F,0X20,0X5C,0X20,0X7C,0X5F,0X5F,0X5F,0X7C,0X20,0X2E,0X20,0X5C,0X20,0X20,0X20,0X20,0X5C,0X20,0X56,0X20,0X2F,0X20,0X20,0X2F,0X20,0X5F,0X5F,0X2F,0X20,0X0A,0X0D,0X20,0X7C,0X5F,0X7C,0X20,0X7C,0X5F,0X7C,0X5C,0X5F,0X5F,0X5F,0X2F,0X20,0X20,0X5C,0X5F,0X2F,0X20,0X20,0X7C,0X5F,0X5F,0X5F,0X5F,0X5F,0X7C,0X5F,0X7C,0X20,0X5C,0X5F,0X5C,0X20,0X7C,0X5F,0X7C,0X20,0X7C,0X5F,0X2F,0X5F,0X2F,0X20,0X20,0X20,0X5C,0X5F,0X5C,0X5F,0X5F,0X5F,0X5F,0X7C,0X5F,0X7C,0X5C,0X5F,0X5C,0X20,0X20,0X20,0X20,0X5C,0X5F,0X2F,0X20,0X20,0X7C,0X5F,0X5F,0X5F,0X5F,0X5F,0X7C,0X0A,0X0D,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X0A,0X0D,0X0A,0X0D};
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
	uint16_t adcval = ADC1->CH15DR;
	vcc=(double)4915.2/adcval;
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
			if(sRxBuffer[0]=='\n'||sRxBuffer[0]=='\r'){
				mode=2;
				init=1;
				sTimingDelay=0;
			}
			break;
		case 2 :
			switch(sRxBuffer[0]){
				case '1':
					mode=3;
					init=1;
					detectall=1;
				break;
				case '2':
					mode=3;
					init=1;
					detectall=0;
				break;
				case '3':
					mode=4;
					init=1;
					detectall=0;
				break;
				case '4':
					mode=5;
					init=1;
					detectall=0;
				break;
				case '5':
					UART_SendString("Feature not implemented.");
				break;
				case '6':
					mode=7;
					init=1;
					detectall=0;
				break;
				case '7':
					EEPROM_Write((u8*)pinstorage, 2 * 16);
					UART_SendString("Written to Flash");
				break;
				case '8':
					EEPROM_Read((u8*)pinstorage, 2 * 16);
					UART_SendString("Read from Flash");
					char buffer[80];
					sprintf(&buffer[0],"%i,%i,%i",pinstorage[0],pinstorage[1],pinstorage[2]);
					UART_SendString(&buffer[0]);
				break;
				case '9':
					if(masterslave){
						UART_SendString("Thanks for choosing my firmware,goodbye.");
						pinMode(pins[pinstorage[10]][0],pins[pinstorage[10]][1],GPIO_Mode_FLOATING);
					}else{
						UART_SendString("I'm a Slave board.");
					}
				break;
				
			}
			break;
		case 3 :
			if(sRxBuffer[0]=='\n'||sRxBuffer[0]=='\r'){
				if(detectall){
					mode=4;
					init=1;
					sTimingDelay=0;
				}else{
					mode=2;
					init=1;
				}
				wait=0;
			}else if(sRxBuffer[0]=='y'){
				wait=0;
			}
			break;
		case 4 :
			switch(sRxBuffer[0]){
				case '\n':
				case '\r':
					if(detectall){
						mode=5;
						init=1;
						sTimingDelay=0;
					}else{
						mode=2;
						init=1;
					}
					for(uint8_t i=0;i<33;i++){
						if(!used(i)){
						pinMode(pins[i][0],pins[i][1],GPIO_Mode_FLOATING);
						}
					}
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
							UART_SendString("\r\nLEDR:");
							UART_Send_Group(&PXX[selpin][0],4);
						break;
						case 'g':
							pinstorage[4]=selpin;
							UART_SendString("\r\nLEDG:");
							UART_Send_Group(&PXX[selpin][0],4);
						break;
						case 'b':
							pinstorage[5]=selpin;
							UART_SendString("\r\nLEDB:");
							UART_Send_Group(&PXX[selpin][0],4);
						break;
						case 'u':
							pinstorage[6]=selpin;
							UART_SendString("\r\nUpper LED:");
							UART_Send_Group(&PXX[selpin][0],4);
						break;
						case 'l':
							pinstorage[7]=selpin;
							UART_SendString("\r\nLower LED:");
							UART_Send_Group(&PXX[selpin][0],4);
						break;
						case 'z':
							pinstorage[8]=selpin;
							UART_SendString("\r\nBuzzer:");
							UART_Send_Group(&PXX[selpin][0],4);
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
			case 5 :
			if(sRxBuffer[0]=='\n'||sRxBuffer[0]=='\r'){
				if(detectall){
					mode=7;
					init=1;
					sTimingDelay=0;
				}else{
					mode=2;
					init=1;
					sTimingDelay=0;
				}
			}else if(sRxBuffer[0]=='f'){
				showalladc=!showalladc;
			}else if(sRxBuffer[0]>='0'&&sRxBuffer[0]<='9'){
				pinstorage[12]=adcs[sRxBuffer[0]-'0'][0];
				UART_SendString("\r\nVBAT:");
				UART_Send_Group(&PXX[pinstorage[12]][0],4);
			}
			break;
			case 7 :
				if(sRxBuffer[0]=='\n'||sRxBuffer[0]=='\r'){
					mode=2;
					init=1;
					sTimingDelay=0;
				}else if(sRxBuffer[0]=='e'){	
					doinloop=1;
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
				UART_SendString("\r\nHALLA:");
				UART_Send_Group(&PXX[i][0],4);
			}
			if(hallB[i]){
				pinstorage[1]=i;
				UART_SendString("\r\nHALLB:");
				UART_Send_Group(&PXX[i][0],4);
			}
			if(hallC[i]){
				pinstorage[2]=i;
				UART_SendString("\r\nHALLC:");
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
		case 2 :
			GetChipUID();
			UART_SendString("\n\n\n\n\r");
			UART_Send_Group(&banner[0],464);
			UART_SendString("Board type:");
			UART_SendString(masterslave?"Master":"Slave");
			char buffer[80];
			sprintf(&buffer[0],"  MCU Voltage:%fV  Serial number:%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n\r",vcc,device_id_data[0],device_id_data[1],device_id_data[2],device_id_data[3],device_id_data[4],device_id_data[5],device_id_data[6],device_id_data[7],device_id_data[8],device_id_data[9],device_id_data[10],device_id_data[11]);
			UART_SendString(&buffer[0]);
			UART_SendString("Welcome to PinFinder, press number key to choose action.\n\r");
			UART_SendString("  (1)-Auto detect all pins.\n\r");
			UART_SendString("  (2)-Auto detect HALL sensor.\n\r");
			UART_SendString("  (3)-Auto detect LED and buzzer.\n\r");
			UART_SendString("  (4)-Auto detect battery voltage.\n\r");
			UART_SendString("  (5)-Auto detect total current.\n\r");
			UART_SendString("  (6)-Auto detect power button.\n\r");
			UART_SendString("  (7)-Enter command line interface.\n\r");
			UART_SendString("  (8)-Erase all saved configurations.\n\r");
			UART_SendString("  (9)-Power off.\n\r>");
		break;
		case 3 :
			UART_SendString("\n\rthis will spin motor slowly to detect hall sensor pins,if it takes too long please increase input voltage to 42v.\n\rpress Y to start,Enter to return to menu\n\r");
			wait=1;
			while(wait){
				__NOP();
				__NOP();
			}
			if(mode==3){
				TIM_CtrlPWMOutputs(TIM1, ENABLE);
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
			}
		break;
		case 4 :
			UART_SendString("\n\rAll pins will be set high, the selected pin will blink, the already saved pins will remain off. If a LED does not light up, it is broken.\r\npress W to go to next pin\r\npress S to go to previous pin\n\rPress R to save as red LED\r\nPress G to save as green LED\r\nPress B to save as blue LED(or orange on some board)\r\nPress U to save as upper LED\r\nPress L to save as lower LED\r\npress Enter to go back to main menu\r\n");
			for(uint8_t i=0;i<33;i++){
				if(!used(i)){
					pinMode(pins[i][0],pins[i][1],GPIO_Mode_IPU);
				}
			}
			selpin=0;
			while(used(selpin)){    //find the first unused pin to start
				selpin++;
			}
		break;
		case 5 :
			UART_SendString("\r\nA list of pin and voltage will be displayed, check the board input voltage with multimeter and select the closest one.\r\npress F to toggle automatic pin filtering\r\npress the number at the front of pin to save it\r\npress enter to return to main menu\r\n");
			TIM_CtrlPWMOutputs(TIM1, ENABLE);
			TIM1->CCR1=8192;
			TIM1->CCR2=8192;
			TIM1->CCR3=8192;
			step=0;    //close all low side mosfet to prevent reading phase current
			commutate();
			ADCALL_Init();
			for(uint8_t i=0;i<10;i++){
				if(!used(adcs[i][0])){
					ADC_RegularChannelConfig(ADC1, adcs[i][1], 0, ADC_SampleTime_7_5Cycles);
					pinMode(pins[adcs[i][0]][0],pins[adcs[i][0]][1],GPIO_Mode_AIN);
					adcleft[i]=1;
				}else{
					adcleft[i]=0;
				}
			}
			ADC_SoftwareStartConvCmd(ADC1, ENABLE);
		break;
		case 7 :
			UART_SendString("\r\nPress and release power button once to detect automaticly\r\nIf button press is not registered,press E to enable fix, the board may acidently power off\r\npress Enter to return to main menu\r\n");
			for(uint8_t i=0;i<33;i++){
				if(!used(i)){
					hallA[i]=digitalRead(pins[i][0],pins[i][1]);
				}
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
	

void printvoltage(){
	for(uint8_t i=0;i<10;i++){
		if(adcleft[i]){
			float vbattmp = (double)analogRead(adcs[i][2])*vcc*31/4096;
			if(showalladc||(vbattmp>20&&vbattmp<45)){
				char buffer[32];
				sprintf(&buffer[0],"%i->",i);
				UART_SendString(&buffer[0]);
				UART_Send_Group(&PXX[adcs[i][0]][0],4);
				sprintf(&buffer[0],":%fV\n\r",vbattmp);
				UART_SendString(&buffer[0]);
			}
		}
	}
	UART_SendString("================\n\r");
	DELAY_Ms(2000);
}	
	
	
void checkbutton(){
	if(doinloop){
		pinstorage[9]=pinstorage[10];
		pinstorage[10]=255;
		pinMode(pins[pinstorage[9]][0],pins[pinstorage[9]][1],GPIO_Mode_FLOATING);
		selfhold();
		masterslave = detectSelfHold();
		if(masterslave){
			UART_SendString("\r\nButton:");
			UART_Send_Group(&PXX[pinstorage[9]][0],4);
			UART_SendString("\r\nLatch:");
			UART_Send_Group(&PXX[pinstorage[10]][0],4);
		}else{
			UART_SendString("Workaround failed");
		}
		doinloop=0;
	}else{
		for(uint8_t i=0;i<33;i++){
			if(!used(i)){
				if(!hallA[i]&&digitalRead(pins[i][0],pins[i][1])){
					pinstorage[9]=i;
					UART_SendString("\r\nButton:");
					UART_Send_Group(&PXX[i][0],4);
				}
			}
		}
	}
}

