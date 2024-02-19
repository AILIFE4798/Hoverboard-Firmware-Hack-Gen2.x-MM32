#include "mm32_device.h"                // Device header
#include "hal_gpio.h"
#include "hal_adc.h"
#include "hal_conf.h"
#include "hal_uid.h"
#include "../Inc/autodetect.h"
#include "../Inc/hardware.h"
#include "../Inc/initialize.h"
#include "../Inc/delay.h"
#include "../Inc/uart.h"
#include "../Inc/bldc.h"
#include "../Inc/sim_eeprom.h"
#include "../Inc/pinout.h"
#include "math.h"

extern uint32_t pins[33][3];
extern uint32_t adcs[10][3];
extern uint32_t millis;
uint8_t test;
int tmp;
uint8_t used(uint8_t pin);
uint8_t mode=0;//0=startup,1=wait for serial,2=menu,3=hall,4=led,5=vbat,6=itotal,7=button,8=cmd,9=testrotate,10=writeEE
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
extern uint8_t hallposprev;
extern bool dir;
int testrotatespeed;
uint8_t command;
uint8_t address;
uint16_t data;
uint8_t stage;

uint8_t hallA[33];
uint8_t hallB[33];
uint8_t hallC[33];
extern uint16_t pinstorage[64];    
//0:halla,1:hallb,2:hallc,3:ledr,4:ledg,5:ledb,6:ledup,7:leddown,8:buzzer,9:button,10:selfhold,11:charger,12:vbat,13:itotal,14:tx,15:rx,16:iphasea,17:iphaseb,18:iphasec,19~22:reserved,23:OCP,24:OCP ref,25:IR_L,26:IR_R,27:serial2tx,28:serial2rx,29~31:reserved,32:0XDCBA,33:vbat divider,34:itotal divider,35:iphase divider,36:baud,37:pwm resolution,38:slave ID,39:windings,40:invert lowside,41:soft current limit,42:hard limit awdg,43:UART,44:pid,45:bat 100%,46:bat0%,47:serial timeout,48~64:reserved 
uint16_t prevpinstorage[64];    

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
					mode=8;
					init=1;
					detectall=0;
				break;
				case '8':
					mode=9;
					init=1;
					detectall=0;
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
					saveNexit();
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
						saveNexit();
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
					saveNexit();
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
					saveNexit();
				}else if(sRxBuffer[0]=='e'){	
					doinloop=1;
				}
			break;
			case 8 :
				switch(sRxBuffer[0]){
					case '\r':
					case '\n':
						switch(command){
							case 'r':
								if(address<64){
									char buffer[16];
									sprintf(&buffer[0],"\r\nindex %i : %i",address,pinstorage[address]);
									UART_SendString(&buffer[0]);
								}else{
									UART_SendString("\r\nInvalid address");
								}
							break;
							case 'w':
								if(address<64){
									pinstorage[address]=data;
									char buffer[16];
									sprintf(&buffer[0],"\r\nindex %i : %i",address,pinstorage[address]);
									UART_SendString(&buffer[0]);
								}else{
									UART_SendString("\r\nInvalid address");
								}
							break;
							case 'h':
								UART_SendString("\r\n\nThis tool allow you to modify and view all saved pinouts and settings\n\r\n\rUsage:  [command] <address> <value>\n\r\n\rCommands: \n\r\n\r r     read saved data\n\r w     write data\n\r h     display this help page\n\r l     list all data\n\r g     generate pinstorage variable initializer to copy in firmware\n\r e     erase all data\n\r x     exit command line tool and go back to main menu\n\r\n\rAddress description:\n\r\n\r0 : HALL sensor A pin\n\r1 : HALL sensor B pin\n\r2 : HALL sensor B pin\n\r3 : red LED pin\n\r4 : green LED pin\n\r5 : blue LED pin\n\r6 : upper LED pin\n\r7 : lower LED pin\n\r8 : Buzzer pin\n\r9 : Button pin\n\r10 : latch pin\n\r11 : charger pin\n\r12 : battery voltage pin\n\r13 : total current DC pin\n\r14 : UART TX pin\n\r15 : UART RX pin\n\r16~22 : reserved\n\r23 : over current protection pin\n\r24 : over current protection comparator refrence pin\n\r25~31:reserved\n\r\n\r33 : vbat divider\n\r34 : itotal divider\n\r35 : iphase divider\n\r36 : baud\n\r37 : pwm resolution\n\r38 : slave ID\n\r39 : windings\n\r40 : invert lowside\n\r41 : soft current limit\n\r42 : hard limit awdg\n\r43 : UART\n\r44 : pid\n\r45 : bat 100%\n\r46 : bat 0%\n\r47 : serial timeout\n\r48~64 : reserved\n");
							break;
							case 'l':
								for(uint8_t i=0;i<64;i++){			
									char buffer[16];
									sprintf(&buffer[0],"\r\nindex %i : %i",i,pinstorage[i]);
									UART_SendString(&buffer[0]);
								}
							break;
							case 'g':
								UART_SendString("\r\nuint16_t pinstorage[64]={");
								for(uint8_t i=0;i<64;i++){			
									char buffer[16];
									sprintf(&buffer[0],"%i, ",pinstorage[i]);
									UART_SendString(&buffer[0]);
								}
								UART_SendString("\b\b};");
							break;
							case 'e':{
								uint16_t tmperase[64];
								for(uint8_t i=0;i<64;i++){
									tmperase[i]=0xffff;
								}
								if(EEPROM_Write((u8*)tmperase, 2 * 64)){
									UART_SendString("\r\nEEPROM erase complete,reboot needed without saving to take effect");
								}else{
									UART_SendString("\r\nEEPROM erase failed");
								}
							}
							break;
							case 'x':
								saveNexit();
							break;
							case 0:
								__NOP();
							break;
							default:
								UART_SendString("\r\nCommand\"");
								UART_Send_Byte(command);
								UART_SendString("\"does not exist");
							break;
						}
						UART_SendString("\r\npinfinder~$ ");
						command=0;
						address=0;
						data=0;
						stage=0;
					break;
					case ' ':
						stage++;
					break;
					default:
						switch(stage){
							case 0 :
								if(command==0){
									command=sRxBuffer[0];
								}
							break;
							case 1 :
								if(sRxBuffer[0]>='0'&&sRxBuffer[0]<='9'){
									address=address*10+(sRxBuffer[0]-'0');
								}
							break;
							case 2 :
								if(sRxBuffer[0]>='0'&&sRxBuffer[0]<='9'){
									data=data*10+(sRxBuffer[0]-'0');
								}
							break;
						}
					break;
				}
			break;
			case 9 :
				switch(sRxBuffer[0]){
					case '\r':
					case '\n':
						mode=2;
						init=1;
						TIM_CtrlPWMOutputs(TIM1, DISABLE);
					break;
					case '+':
						testrotatespeed+=100;
						if(testrotatespeed>1000){
							testrotatespeed=1000;
						}
						char buffer2[16];
						sprintf(&buffer2[0],"\rSpeed:%i   ",testrotatespeed);
						UART_SendString(&buffer2[0]);
					break;
					case '-':
						testrotatespeed-=100;
						if(testrotatespeed<-1000){
							testrotatespeed=-1000;
						}
						char buffer[16];
						sprintf(&buffer[0],"\rSpeed:%i   ",testrotatespeed);
						UART_SendString(&buffer[0]);					
					break;
				}	
			break;	
			case 10 :
				switch(sRxBuffer[0]){
					case 'y':
						if(EEPROM_Write((u8*)pinstorage, 2 * 64)){
							UART_SendString("\r\nconfiguration saved\r\n");
						}else{
							UART_SendString("\r\nEEPROM write failed\r\n");
						}
					case 'n':
						mode=2;
						init=1;
					break;
					default:
						UART_SendString("\r\nY/N?");
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
			UART_SendString("  (7)-Modify configurations manually by command line.\n\r");
			UART_SendString("  (8)-Test motor rotation.\n\r");
			UART_SendString("  (9)-Power off.\n\r>");
			for(uint8_t i=0;i<64;i++){
				prevpinstorage[i]=pinstorage[i];
			}
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
		case 8 :
			UART_SendString("\r\nWelcome to command line interface,type h for help\n\rpinfinder~$ ");
			command=0;
			address=0;
			data=0;
			stage=0;
		break;
		case 9 :
			UART_SendString("\r\nTest the motor with hall sensor commutation\r\npress + to increase speed\r\npress - to decrease speed\r\nnegative speed to spin backward\r\npress Enter to return to main menu\n\n\r");
			TIM_CtrlPWMOutputs(TIM1, ENABLE);
			TIM1->CCR1=0; 
			TIM1->CCR2=0;
			TIM1->CCR3=0;
			testrotatespeed=0;
			pinMode(pins[pinstorage[0]][0],pins[pinstorage[0]][1],GPIO_Mode_FLOATING);
			pinMode(pins[pinstorage[1]][0],pins[pinstorage[1]][1],GPIO_Mode_FLOATING);
			pinMode(pins[pinstorage[2]][0],pins[pinstorage[2]][1],GPIO_Mode_FLOATING);
		break;
		case 10 :
			UART_SendString("\r\nChanges were made to the configurations, do you want to save it permanantly?Y/N\r\n>");
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


uint8_t restorecfg(){
	uint16_t tmp[64];
	EEPROM_Read((u8*)tmp, 2 * 64);
	if(tmp[32]==0xDCAB){    //verify config is valid
		for(uint8_t i=0;i<64;i++){
			pinstorage[i]=tmp[i];
		}
		return 1;
	}else{
		return 0;
	}
}

void testrotateloop(){
	if(hallpos(dir)!=hallposprev){
		hallposprev=hallpos(dir);
		step=hallposprev;
		commutate();
	}
	int pwm=testrotatespeed*PWM_RES/1000;//1000~-1000 for all pwm resolution
	if(pwm>0){
	dir=1;
	}else{
	dir=0;
	}
	unsigned int abspeed=fabs((double)pwm);    // 4095~-4095
	TIM1->CCR1=abspeed;
	TIM1->CCR2=abspeed;
	TIM1->CCR3=abspeed;
}

void saveNexit(){
	for(uint8_t i=0;i<64;i++){
		if(prevpinstorage[i]!=pinstorage[i]){
			mode=10;
			init=1;
			detectall=0;
			return;
		}
	}
	mode=2;
	init=1;
	return;
}


