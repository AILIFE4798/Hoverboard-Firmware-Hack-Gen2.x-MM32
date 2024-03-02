#ifdef TARGET_MM32SPIN25
#include "HAL_device.h"                 // Device header
#else
#include "mm32_device.h"                // Device header
#endif
#include "hal_uid.h"
#include "hal_conf.h"
#include "hal_gpio.h"
#include "hal_adc.h"
#include "../Inc/autodetect.h"
#include "../Inc/hardware.h"
#include "../Inc/initialize.h"
#include "../Inc/delay.h"
#include "../Inc/uart.h"
#include "../Inc/bldc.h"
#include "../Inc/sim_eeprom.h"
#include "../Inc/pinout.h"
#include "math.h"


extern MM32GPIO pins[PINCOUNT];
extern MM32ADC adcs[ADCCOUNT];
extern uint32_t millis;
modes_t mode=0;
uint8_t test;
int tmp;
uint8_t used(uint8_t pin);
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
char addrstr[16];
char datastr[4];
uint8_t addrparsemode;
uint8_t dataparsemode;
uint8_t addrlen=0;
uint8_t datalen=0;
extern MM32TIM23 halltims[TIMCOUNT];
extern MM32UART1 uarts[UARTCOUNT];
uint8_t receiveuart;

uint8_t hallA[PINCOUNT];
uint8_t hallB[PINCOUNT];
uint8_t hallC[PINCOUNT];
extern uint16_t pinstorage[64];    
//0:halla,1:hallb,2:hallc,3:ledr,4:ledg,5:ledb,6:ledup,7:leddown,8:buzzer,9:button,10:selfhold,11:charger,12:vbat,13:itotal,14:tx,15:rx,16:iphasea,17:iphaseb,18:iphasec,19~22:reserved,23:OCP,24:OCP ref,25:IR_L,26:IR_R,27:serial2tx,28:serial2rx,29~31:reserved,32:0XDCBA,33:vbat divider,34:itotal divider,35:iphase divider,36:baud,37:pwm resolution,38:slave ID,39:windings,40:invert lowside,41:soft current limit,42:hard limit awdg,43:UART,44:pid,45:bat 100%,46:bat0%,47:serial timeout,48~64:reserved 
uint16_t prevpinstorage[64];    

uint8_t banner[]={0X20,0X20,0X5F,0X20,0X20,0X20,0X5F,0X20,0X20,0X5F,0X5F,0X5F,0X5F,0X5F,0X20,0X20,0X20,0X20,0X20,0X5F,0X5F,0X5F,0X5F,0X5F,0X5F,0X5F,0X20,0X5F,0X5F,0X5F,0X5F,0X20,0X20,0X20,0X20,0X5F,0X20,0X20,0X20,0X5F,0X20,0X20,0X20,0X20,0X5F,0X20,0X20,0X20,0X20,0X5F,0X5F,0X5F,0X5F,0X20,0X5F,0X20,0X20,0X5F,0X5F,0X20,0X5F,0X5F,0X20,0X20,0X20,0X20,0X20,0X5F,0X5F,0X5F,0X5F,0X5F,0X5F,0X20,0X20,0X0A,0X0D,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X2F,0X20,0X5F,0X20,0X5C,0X20,0X5C,0X20,0X20,0X20,0X2F,0X20,0X2F,0X20,0X5F,0X5F,0X5F,0X5F,0X7C,0X20,0X20,0X5F,0X20,0X5C,0X20,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X20,0X20,0X2F,0X20,0X5C,0X20,0X20,0X2F,0X20,0X5F,0X5F,0X5F,0X7C,0X20,0X7C,0X2F,0X20,0X2F,0X20,0X5C,0X20,0X5C,0X20,0X20,0X20,0X2F,0X20,0X2F,0X5F,0X5F,0X5F,0X20,0X5C,0X20,0X0A,0X0D,0X20,0X7C,0X20,0X7C,0X5F,0X7C,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X20,0X5C,0X20,0X5C,0X20,0X2F,0X20,0X2F,0X7C,0X20,0X20,0X5F,0X7C,0X20,0X7C,0X20,0X7C,0X5F,0X29,0X20,0X7C,0X20,0X7C,0X20,0X7C,0X5F,0X7C,0X20,0X7C,0X20,0X2F,0X20,0X5F,0X20,0X5C,0X7C,0X20,0X7C,0X20,0X20,0X20,0X7C,0X20,0X27,0X20,0X2F,0X20,0X20,0X20,0X5C,0X20,0X5C,0X20,0X2F,0X20,0X2F,0X20,0X20,0X5F,0X5F,0X29,0X20,0X7C,0X0A,0X0D,0X20,0X7C,0X20,0X20,0X5F,0X20,0X20,0X7C,0X20,0X7C,0X5F,0X7C,0X20,0X7C,0X5C,0X20,0X56,0X20,0X2F,0X20,0X7C,0X20,0X7C,0X5F,0X5F,0X5F,0X7C,0X20,0X20,0X5F,0X20,0X3C,0X20,0X20,0X7C,0X20,0X20,0X5F,0X20,0X20,0X7C,0X2F,0X20,0X5F,0X5F,0X5F,0X20,0X5C,0X20,0X7C,0X5F,0X5F,0X5F,0X7C,0X20,0X2E,0X20,0X5C,0X20,0X20,0X20,0X20,0X5C,0X20,0X56,0X20,0X2F,0X20,0X20,0X2F,0X20,0X5F,0X5F,0X2F,0X20,0X0A,0X0D,0X20,0X7C,0X5F,0X7C,0X20,0X7C,0X5F,0X7C,0X5C,0X5F,0X5F,0X5F,0X2F,0X20,0X20,0X5C,0X5F,0X2F,0X20,0X20,0X7C,0X5F,0X5F,0X5F,0X5F,0X5F,0X7C,0X5F,0X7C,0X20,0X5C,0X5F,0X5C,0X20,0X7C,0X5F,0X7C,0X20,0X7C,0X5F,0X2F,0X5F,0X2F,0X20,0X20,0X20,0X5C,0X5F,0X5C,0X5F,0X5F,0X5F,0X5F,0X7C,0X5F,0X7C,0X5C,0X5F,0X5C,0X20,0X20,0X20,0X20,0X5C,0X5F,0X2F,0X20,0X20,0X7C,0X5F,0X5F,0X5F,0X5F,0X5F,0X7C,0X0A,0X0D,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X20,0X0A,0X0D,0X0A,0X0D};
char PXX[PINCOUNT][5]={"PA0\0","PA1\0","PA2\0","PA3\0","PA4\0","PA5\0","PA6\0","PA7\0","PA11\0","PA12\0","PA13\0","PA14\0","PA15\0","PB0\0","PB1\0","PB2\0","PB3\0","PB4\0","PB5\0","PB6\0","PB7\0","PB8\0","PB9\0","PB10\0","PB11\0","PB12\0","PC13\0","PC14\0","PC15\0","PD0\0","PD1\0","PD2\0","PD3\0"};
char addrdescription[64][14]={
{"halla\0"},
{"hallb\0"},
{"hallc\0"},
{"ledr\0"},
{"ledg\0"},
{"ledb\0"},
{"ledu\0"},
{"ledd\0"},
{"buzzer\0"},
{"button\0"},
{"latch\0"},
{"charge\0"},
{"vbat\0"},
{"itotal\0"},
{"tx\0"},
{"rx\0"},
{"iphasea\0"},
{"iphaseb\0"},
{"reserved\0"},
{"reserved\0"},
{"reserved\0"},
{"reserved\0"},
{"reserved\0"},
{"ocp\0"},
{"ocpref\0"},
{"irl\0"},
{"irr\0"},
{"reserved\0"},
{"reserved\0"},
{"reserved\0"},
{"reserved\0"},
{"reserved\0"},
{"magicnum\0"},
{"vbatdivider\0"},
{"itotaldivider\0"},
{"reserved\0"},
{"baud\0"},
{"pwmres\0"},
{"slaveid\0"},
{"windings\0"},
{"invlowside\0"},
{"softocp\0"},
{"hardocp\0"},
{"reserved\0"},
{"constspeed\0"},
{"batfull\0"},
{"batempty\0"},
{"timeout\0"},
{"reserved\0"},
{"reserved\0"},
{"reserved\0"},
{"reserved\0"},
{"reserved\0"},
{"reserved\0"},
{"reserved\0"},
{"reserved\0"},
{"reserved\0"},
{"reserved\0"},
{"reserved\0"},
{"reserved\0"},
{"reserved\0"},
{"reserved\0"},
{"reserved\0"},
{"reserved\0"},
};
	
void autoDetectInit();

void selfhold(){
	for(uint8_t i=0;i<PINCOUNT;i++){
		if(!used(i)){
			pinMode(i,INPUT_PULLUP);    //pull up insted of output high to protect micro controller
		}
	}
}

uint8_t detectSelfHold(){
	vref_Init();    //uses internal 1.2v refrence to detect vcc voltage
	DELAY_Ms(100);    //wait for adc stablize
	uint8_t havelatch=0;
	for(uint8_t i=0;i<PINCOUNT;i++){
		if(!used(i)){
			uint32_t timeout = millis+200;    //10ms not enough for capacitor to discharge
			uint32_t treshold = (uint16_t)ADC1->ADDR15+10;    //refrence is very stable, 10 is enough to detect change(0.05v drop)
			if(!havelatch){
				LATCHPIN = i;
				EEPROM_Write((u8*)pinstorage, 2 * 64);    //if the detection failed, the pin is still saved
			}
			pinMode(i,INPUT);    //release latch
			while(1){
				tmp = (uint16_t)ADC1->ADDR15;
				if(tmp>treshold){
					pinMode(i,INPUT_PULLUP);    //set it back quickly
					LATCHPIN = i;    //save the pin
					havelatch=1;
					DELAY_Ms(10);    //capacitor charge back up
				}
				if(millis>timeout){    //wrong pin
					break;
				}
			}
	  }
	}	
	if(!havelatch){
		LATCHPIN = 65535;
		EEPROM_Write((u8*)pinstorage, 2 * 64);    //slave board
	}
	uint16_t adcval = ADC1->ADDR15;
	vcc=(double)4915.2/adcval;    //vcc saved to calculate accurate vbat
	return havelatch;
}
	
	
uint8_t used(uint8_t pin){
	if(pin==PA13||pin==PA14){
		return 1;    //swd cannot be used
	}
	for(uint8_t i=0;i<16;i++){
		if(pinstorage[i]==pin){
			return 1;    //pin already used
		}
	}
	return 0;
}
	
	
void autoDetectSerialIt(){    //serial dma interrupt
	switch (mode){
		case MODE_WAIT_UART :
			if(sRxBuffer[0]=='\n'||sRxBuffer[0]=='\r'){    //go to main menu after enter pressed
				mode=MODE_MENU;
				init=1;
				sTimingDelay=0;
			}
			break;
		case MODE_MENU :
			switch(sRxBuffer[0]){    //choose action in menu
				case '1':    //(1)-Auto detect all pins.
					mode=MODE_HALL;
					init=1;
					detectall=1;    //only exit to main menu after all step completed 
				break;
				case '2':    //(2)-Auto detect HALL sensor.
					mode=MODE_HALL;
					init=1;
					detectall=0;
					doinloop=1;
				break;
				case '3':    //(3)-Auto detect LED and buzzer.
					mode=MODE_LED;
					init=1;
					detectall=0;
				break;
				case '4':    //(4)-Auto detect battery voltage.
					mode=MODE_VBAT;
					init=1;
					detectall=0;
				break;
				case '5':    //(5)-Auto detect total current.
					UART_SendString("Feature not implemented.");
				break;
				case '6':    //(6)-Auto detect power button.
					if(masterslave){
						mode=MODE_BUTTON;
						init=1;
						detectall=0;
					}else{
						UART_SendString("I'm a Slave board.");
					}
				break;
				case '7':    //(7)-Modify configurations manually by command line.
					mode=MODE_CLI;
					init=1;
					detectall=0;
				break;
				case '8':    //(8)-Test motor rotation.
					if(HALLAPIN<PINCOUNT&&HALLBPIN<PINCOUNT&&HALLCPIN<PINCOUNT){
						mode=MODE_TESTROTATE;
						init=1;
						detectall=0;
					}else{
						UART_SendString("HALL sensor not configured, please detect it first.");
					}
				break;
				case '9':    //(9)-Power off.
					if(masterslave){
						UART_SendString("Thanks for choosing my firmware,goodbye.");
						pinMode(LATCHPIN,INPUT);
					}else{
						UART_SendString("I'm a Slave board.");
					}
				break;
				
			}
			break;
		case MODE_HALL :
			if(sRxBuffer[0]=='\n'||sRxBuffer[0]=='\r'){
				if(detectall){
					mode=MODE_LED;    //next step
					init=1;
					sTimingDelay=0;
				}else{
					saveNexit();    //save config if it is changed
				}
				wait=0;
			}else if(sRxBuffer[0]=='y'){
				wait=0;    //continue running after user confirmed
			}else if(sRxBuffer[0]=='i'){
				INVERT_LOWSIDE = !INVERT_LOWSIDE;
				UART_SendString("\n\rlowside ");
				UART_SendString(INVERT_LOWSIDE ? "inverted" : "normal");
				TIM1_init(PWM_RES_AD, 0);
				if(!wait){
					TIM_CtrlPWMOutputs(TIM1, ENABLE);
					TIM1->CCR1=4000;    //spin motor at 50% pwm
					TIM1->CCR2=4000;
					TIM1->CCR3=4000;
				}
			}
			break;
		case MODE_LED :
			switch(sRxBuffer[0]){
				case '\n':
				case '\r':
					if(detectall){
						mode=MODE_VBAT;
						init=1;
						sTimingDelay=0;
					}else{
						saveNexit();
					}
					for(uint8_t i=0;i<PINCOUNT;i++){
						if(!used(i)){
							pinMode(i,INPUT);    //turn all pins back off after leaving
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
					pinMode(selpin, sRxBuffer[0]=='w' ? INPUT_PULLUP : INPUT);
					//if pin is saved turn it off, if its not left it on so easy to see what led is still left
					switch(sRxBuffer[0]){
						case 'r':
							LEDRPIN=selpin;
							UART_SendString("\r\nLEDR:");
							UART_SendString(&PXX[selpin][0]);
						break;
						case 'g':
							LEDGPIN=selpin;
							UART_SendString("\r\nLEDG:");
							UART_SendString(&PXX[selpin][0]);
						break;
						case 'b':
							LEDBPIN=selpin;
							UART_SendString("\r\nLEDB:");
							UART_SendString(&PXX[selpin][0]);
						break;
						case 'u':
							LEDUPIN=selpin;
							UART_SendString("\r\nUpper LED:");
							UART_SendString(&PXX[selpin][0]);
						break;
						case 'l':
							LEDDPIN=selpin;
							UART_SendString("\r\nLower LED:");
							UART_SendString(&PXX[selpin][0]);
						break;
						case 'z':
							BUZZERPIN=selpin;
							UART_SendString("\r\nBuzzer:");
							UART_SendString(&PXX[selpin][0]);
						break;
					}
					if(sRxBuffer[0]!='w'){
						UART_SendString("\r\n");
					}
					do{
						if(selpin==PINCOUNT-1){
							selpin=0;
						}else{
							selpin++;
						}
					}while(used(selpin));    //find next unused pin
				break;
				case 's':
					pinMode(selpin,INPUT_PULLUP);
					do{
						if(selpin==0){
							selpin=PINCOUNT-1;
						}else{
							selpin--;
						}
					}while(used(selpin));
				break;
			}
			UART_SendString("\rNow trying:");
			UART_SendString(&PXX[selpin][0]);
			UART_SendString("  ");
			break;
			case MODE_VBAT :
			if(sRxBuffer[0]=='\n'||sRxBuffer[0]=='\r'){
				if(detectall&&masterslave){    //slave cannot detect button
					mode=MODE_BUTTON;
					init=1;
					sTimingDelay=0;
				}else{
					sTimingDelay=0;
					saveNexit();
				}
			}else if(sRxBuffer[0]=='f'){
				showalladc=!showalladc;    //toggle extreme value filtering
			}else if(sRxBuffer[0]>='0'&&sRxBuffer[0]<='9'){    //number pressed
				VBATPIN=adcs[sRxBuffer[0]-'0'].io;    //save pin
				UART_SendString("\r\nVBAT:");
				UART_SendString(&PXX[VBATPIN][0]);
			}
			break;
			case MODE_BUTTON :
				if(sRxBuffer[0]=='\n'||sRxBuffer[0]=='\r'){
					saveNexit();    //last stage always exit
				}else if(sRxBuffer[0]=='e'){	
					doinloop=1;    //button pin latch pin workaround
				}
			break;
			case MODE_CLI :
				switch(sRxBuffer[0]){
					case '\r':    //run command entered before
					case '\n':
						switch(command){
							case 'r':    //read address
								if(addrparsemode==2){
									addrstr[addrlen]='\0';
									uint8_t parsedata=255;
									for(uint8_t i=0;i<64;i++){
										if(!strcmp((const char *)addrstr,(const char *)addrdescription[i])){
											parsedata=i;
											break;
										}
									}
									if(parsedata!=255){
										address=parsedata;
									}else{
										UART_SendString("\r\naddress \"");
										UART_SendString(&addrstr[0]);
										UART_SendString("\" does not exist");
										break;
									}
								}
								if(address<64){
									printstorage(address);
								}else{
									UART_SendString("\r\nInvalid address");
								}
							break;
							case 'w':    //write to address
								if(addrparsemode==2){
									addrstr[addrlen]='\0';
									uint8_t parsedata=255;
									for(uint8_t i=0;i<64;i++){
										if(!strcmp((const char *)addrstr,(const char *)addrdescription[i])){
											parsedata=i;
											break;
										}
									}
									if(parsedata!=255){
										address=parsedata;
									}else{
										UART_SendString("\r\naddress \"");
										UART_SendString(&addrstr[0]);
										UART_SendString("\" does not exist");
										break;
									}
								}
								if(dataparsemode==2){
									datastr[datalen]='\0';
									uint8_t parsedata=255;
									for(uint8_t i=0;i<PINCOUNT;i++){
										if(!strcmp((const char *)datastr,(const char *)PXX[i])){
											parsedata=i;
											break;
										}
									}
									if(parsedata!=255){
										data=parsedata;
									}else{
										UART_SendString("\r\npin \"");
										UART_SendString(&datastr[0]);
										UART_SendString("\" does not exist");
										break;
									}
								}
								if(address<64){
									pinstorage[address]=data;
									printstorage(address);
								}else{
									UART_SendString("\r\nInvalid address");
								}
								
							break;
							case 'h':    //help
								UART_SendString("\r\n\nThis tool allow you to modify and view all saved pinouts and settings\n\r\n\rUsage:  [command] <address> <value>\n\r\n\rCommands: \n\r\n\r r     read saved data\n\r w     write data\n\r h     display this help page\n\r l     list all data\n\r g     generate pinstorage variable initializer to copy in firmware\n\r e     erase all data\n\r x     exit command line tool and go back to main menu\n\r\n\rAddresses:\r\n\n");
								for(uint8_t i=0;i<64;i++){
									char buffer[16];
									sprintf(&buffer[0],"index %i: ",i);
									UART_SendString(&buffer[0]);
									UART_SendString(&addrdescription[i][0]);
									UART_SendString("\r\n");
								}
							break;
							case 'l':    //list all values
								for(uint8_t i=0;i<64;i++){
									printstorage(i);
								}
							break;
							case 'g':    //generate pinout file to compile custom firmware
								UART_SendString("\r\nuint16_t pinstorage[64]={");
								for(uint8_t i=0;i<64;i++){			
									char buffer[16];
									sprintf(&buffer[0],"%i, ",pinstorage[i]);
									UART_SendString(&buffer[0]);
								}
								UART_SendString("\b\b};");    //\b to delete extra ,
							break;
							case 'e':{    //write all ff to eeprom to erase it
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
								saveNexit();    //leave terminal
							break;
							case 0:
								__NOP();    //display new line only if no command is entered
							break;
							default:    //command not found
								UART_SendString("\r\nCommand\"");
								UART_Send_Byte(command);
								UART_SendString("\"does not exist");
							break;
						}
						UART_SendString("\r\npinfinder~$ ");
						command=0;    //reset for next time
						address=0;
						data=0;
						stage=0;
						datalen=0;
						addrlen=0;
						dataparsemode=0;
						addrparsemode=0;
					break;
					case ' ':    //space as seperator for command
						stage++;
					break;
					default:    //parse command without using sscanf
						switch(stage){
							case 0 :    //command
								if(command==0){    //only capture first digit
									command=sRxBuffer[0];
								}
							break;
							case 1 :    //address
								if(!(sRxBuffer[0]>='0'&&sRxBuffer[0]<='9')||addrparsemode==2){
									addrstr[addrlen++]=sRxBuffer[0];
									addrparsemode=2;
								}else{
									address=address*10+(sRxBuffer[0]-'0');    //shift left and add new value
									addrparsemode=1;
								}
							break;
							case 2 :    //value
								if(!(sRxBuffer[0]>='0'&&sRxBuffer[0]<='9')||dataparsemode==2){
									datastr[datalen++]=sRxBuffer[0];
									dataparsemode=2;
								}else{
									data=data*10+(sRxBuffer[0]-'0');
									dataparsemode=1;
								}
							break;
						}
					break;
				}
			break;
			case MODE_TESTROTATE :
				switch(sRxBuffer[0]){
					case '\r':
					case '\n':
						TIM1->CCR1=0;
						TIM1->CCR2=0;
						TIM1->CCR3=0;
						TIM_CtrlPWMOutputs(TIM1, DISABLE);    //stop motor after exit
						step=0;
						commutate();
						mode=MODE_MENU;
						init=1;
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
			case MODE_SAVE :
				switch(sRxBuffer[0]){
					case 'y':
						if(EEPROM_Write((u8*)pinstorage, 2 * 64)){
							UART_SendString("\r\nconfiguration saved\r\n");
							mode=MODE_MENU;
							init=1;
						}else{
							UART_SendString("\r\nEEPROM write failed\r\n");
						}
					case 'n':
						mode=MODE_MENU;
						init=1;
					break;
					default:
						UART_SendString("\r\nY/N?");    //prevent acidently cancellation you have to press y or n
					break;
				}
			break;
	}
}
	

void simhallupdate(){    
	while(HALLAPIN==255||HALLBPIN==255||HALLCPIN==255){    //wait till every sensor is found
		for(uint8_t i=1;i<7;i++){
			step=i;    //sensorless drive
			commutate();
			DELAY_Ms(30);
			for(uint8_t i=0;i<PINCOUNT;i++){
				if(!used(i)){    //check every possible pin
					switch (step){
						case 1:    //if current state does not match what it should,remove from possible pins list
							hallA[i]=!digitalRead(i)&&hallA[i];
							hallB[i]=digitalRead(i)&&hallB[i];
							hallC[i]=digitalRead(i)&&hallC[i];
						break;
						case 2:    //if a pin have been removed not add it back in next step
							hallA[i]=!digitalRead(i)&&hallA[i];
							hallB[i]=!digitalRead(i)&&hallB[i];
							hallC[i]=digitalRead(i)&&hallC[i];
						break;
						case 3:
							hallA[i]=digitalRead(i)&&hallA[i];
							hallB[i]=!digitalRead(i)&&hallB[i];
							hallC[i]=digitalRead(i)&&hallC[i];
						break;
						case 4:
							hallA[i]=digitalRead(i)&&hallA[i];
							hallB[i]=!digitalRead(i)&&hallB[i];
							hallC[i]=!digitalRead(i)&&hallC[i];
						break;
						case 5:
							hallA[i]=digitalRead(i)&&hallA[i];
							hallB[i]=digitalRead(i)&&hallB[i];
							hallC[i]=!digitalRead(i)&&hallC[i];
						break;
						case 6:
							hallA[i]=!digitalRead(i)&&hallA[i];
							hallB[i]=digitalRead(i)&&hallB[i];
							hallC[i]=!digitalRead(i)&&hallC[i];
						break;
					}
				}
			}
		}
		
		for(uint8_t i=0;i<PINCOUNT;i++){
			if(hallA[i]){
				HALLAPIN=i;    //save and print found pin
				UART_SendString("\r\nHALLA:");
				UART_SendString(&PXX[i][0]);
			}
			if(hallB[i]){
				HALLBPIN=i;
				UART_SendString("\r\nHALLB:");
				UART_SendString(&PXX[i][0]);
			}
			if(hallC[i]){
				HALLCPIN=i;
				UART_SendString("\r\nHALLC:");
				UART_SendString(&PXX[i][0]);
			}
			
		}
		for(uint8_t i=0;i<PINCOUNT;i++){    //everything is possible
			hallA[i] = 1;
			hallB[i] = 1;
			hallC[i] = 1;
		}
		for(uint8_t i=0;i<PINCOUNT;i++){    //remove used pins from possible pins
			if(used(i)){
				hallA[i]=0;
				hallB[i]=0;
				hallC[i]=0;
			}
		}
	}
	TIM1->CCR1=0;    //disable motor after all pins is found
	TIM1->CCR2=0;
	TIM1->CCR3=0;
	if(doinloop){
		UART_SendString("\r\nDetection sucessful");
		uint8_t avalid,bvalid,cvalid,timnum=0;
		for(uint8_t i=0;i<TIMCOUNT;i++){ 
			if(halltims[i].io == HALLAPIN){
				avalid=1;
				timnum+=halltims[i].tim2;
			}
			if(halltims[i].io == HALLBPIN){
				bvalid=1;
				timnum+=halltims[i].tim2;
			}
			if(halltims[i].io == HALLCPIN){
				cvalid=1;
				timnum+=halltims[i].tim2;
			}
		}
		if(!(avalid&&bvalid&&cvalid)){
			UART_SendString("\r\nWarning:pinmodeAF of HALL pin ");
			if(avalid){
				UART_SendString(&PXX[HALLAPIN][0]);
			}
			if(bvalid){
				UART_SendString(&PXX[HALLBPIN][0]);
			}
			if(cvalid){
				UART_SendString(&PXX[HALLCPIN][0]);
			}
			UART_SendString(" is not found, it is sugessted to redo the detection");
		}else if(!(timnum==0||timnum==3)){
			UART_SendString("\r\nWarning:HALL sensor pin timer mapping is invalid, it is sugessted to redo the detection");
		}
		doinloop=0;
	}
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
		case MODE_MENU :
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
		case MODE_HALL :
			UART_SendString("\n\rthis will spin motor slowly to detect hall sensor pins,if it takes too long please increase input voltage to 42v, if the motor does not move at all or a short circuit occured press I to invert lowside drive signal\n\rpress Y to start,Enter to return to menu\n\r");
			wait=1;
			while(wait){
				__NOP();
				__NOP();
			}
			if(mode==MODE_HALL){
				TIM_CtrlPWMOutputs(TIM1, ENABLE);
				TIM1->CCR1=4000;    //spin motor at 50% pwm
				TIM1->CCR2=4000;
				TIM1->CCR3=4000;
				for(uint8_t i=0;i<PINCOUNT;i++){
					hallA[i] = 1;
					hallB[i] = 1;
					hallC[i] = 1;
				}
				for(uint8_t i=0;i<PINCOUNT;i++){    //remove used pins from hall array
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
		case MODE_LED :
			UART_SendString("\n\rAll pins will be set high, the selected pin will blink, the already saved pins will remain off. If a LED does not light up, it is broken.\r\npress W to go to next pin\r\npress S to go to previous pin\n\rPress R to save as red LED\r\nPress G to save as green LED\r\nPress B to save as blue LED(or orange on some board)\r\nPress U to save as upper LED\r\nPress L to save as lower LED\r\nPress Z to save as buzzer\r\npress Enter to go back to main menu\r\n");
			for(uint8_t i=0;i<PINCOUNT;i++){
				if(!used(i)){
					pinMode(i,INPUT_PULLUP);
				}
			}
			selpin=0;
			while(used(selpin)){    //find the first unused pin to start
				selpin++;
			}
			UART_SendString("\rNow trying:");
			UART_SendString(&PXX[selpin][0]);
			UART_SendString("  ");
		break;
		case MODE_VBAT :
			UART_SendString("\r\nA list of pin and voltage will be displayed, check the board input voltage with multimeter and select the closest one.\r\npress F to toggle automatic pin filtering\r\npress the number at the front of pin to save it\r\npress enter to return to main menu\r\n");
			TIM_CtrlPWMOutputs(TIM1, ENABLE);
			TIM1->CCR1=8192;
			TIM1->CCR2=8192;
			TIM1->CCR3=8192;
			step=0;    //close all low side mosfet to prevent reading phase current
			commutate();
			ADCALL_Init();    //enable every adc pins to be scanned at same time
			for(uint8_t i=0;i<ADCCOUNT;i++){
				if(!used(adcs[i].io)){    //coresponding gpio is free
					ADC_RegularChannelConfig(ADC1, adcs[i].channel, 0, ADC_SampleTime_7_5Cycles);
					pinMode(adcs[i].io,INPUT_ADC);
					adcleft[i]=1;
				}else{
					adcleft[i]=0;
				}
			}
			ADC_SoftwareStartConvCmd(ADC1, ENABLE);    //enable adc
		break;
		case MODE_BUTTON :
			UART_SendString("\r\nPress and release power button once to detect automaticly\r\nIf button press is not registered,press E to enable fix, the board may acidently power off\r\npress Enter to return to main menu\r\n");
			for(uint8_t i=0;i<PINCOUNT;i++){
				if(!used(i)){
					hallA[i]=digitalRead(i);    //hall array reused to detect change in io state for button
				}
			}
		break;
		case MODE_CLI :
			UART_SendString("\r\nWelcome to command line interface,type h for help\n\rpinfinder~$ ");
			command=0;    //initialize command
			address=0;
			data=0;
			stage=0;
		break;
		case MODE_TESTROTATE :
			UART_SendString("\r\nTest the motor with hall sensor commutation\r\npress + to increase speed\r\npress - to decrease speed\r\nnegative speed to spin backward\r\npress Enter to return to main menu\n\n\r");
			TIM_CtrlPWMOutputs(TIM1, ENABLE);
			TIM1->CCR1=0; 
			TIM1->CCR2=0;
			TIM1->CCR3=0;
			testrotatespeed=0;
			pinMode(HALLAPIN,INPUT);    //hall sensor floating input
			pinMode(HALLBPIN,INPUT);
			pinMode(HALLCPIN,INPUT);
		break;
		case MODE_SAVE :
			UART_SendString("\r\nChanges were made to the configurations, do you want to save it permanantly?Y/N\r\n>");
		break;
	}		
}
	
void blinkLEDupdate(){
	if(millis-lastblink>200){
		pinMode(selpin,blinkstate ? INPUT : INPUT_PULLUP);    //toggle pullup pulldown to blink
		blinkstate=!blinkstate;
		lastblink=millis;
	}
	
}
	

void printvoltage(){
	for(uint8_t i=0;i<ADCCOUNT;i++){
		if(adcleft[i]){
			float vbattmp = (double)analogRead(adcs[i].io)*vcc*31/4096;    //auto calibrate for 5v and 3.3v board
			if(showalladc||(vbattmp>20&&vbattmp<45)){    //max battery voltage is 42v and some tollarance 45v, 20v is needed for gate driver to work
				char buffer[32];
				sprintf(&buffer[0],"%i->",i);
				UART_SendString(&buffer[0]);
				UART_SendString(&PXX[adcs[i].io][0]);
				sprintf(&buffer[0],":%fV\n\r",vbattmp);
				UART_SendString(&buffer[0]);
			}
		}
	}
	UART_SendString("================\n\r");
	DELAY_Ms(2000);
}	
	
	
void checkbutton(){
	if(doinloop){    //workaround
		BUTTONPIN=LATCHPIN;    //the current latch pin is actually buttonpin, so swap it
		LATCHPIN=255;
		pinMode(BUTTONPIN,INPUT);    //release fake latch pin
		selfhold();    //detect self hold again with remaining pin
		masterslave = detectSelfHold();
		if(masterslave){
			UART_SendString("\r\nButton:");
			UART_SendString(&PXX[BUTTONPIN][0]);
			UART_SendString("\r\nLatch:");
			UART_SendString(&PXX[LATCHPIN][0]);
		}else{
			UART_SendString("Workaround failed");
		}
		doinloop=0;
	}else{
		for(uint8_t i=0;i<PINCOUNT;i++){
			if(!used(i)){
				if(!hallA[i]&&digitalRead(i)){    //pin start as low and state changed to high
					BUTTONPIN=i;
					UART_SendString("\r\nButton:");
					UART_SendString(&PXX[i][0]);
				}
			}
		}
	}
}


uint8_t restorecfg(){
	uint16_t tmp[64];
	EEPROM_Read((u8*)tmp, 2 * 64);
	if(tmp[MAGICNUM_POS]==MAGIC_NUMBER){    //verify config is valid
		for(uint8_t i=0;i<64;i++){
			pinstorage[i]=tmp[i];
		}
		return 1;
	}else{
		return 0;
	}
}

void testrotateloop(){    //adc is not initialized in pinfinder, so commutation done in main loop
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

void saveNexit(){    //check if saving is required
	for(uint8_t i=0;i<64;i++){
		if(prevpinstorage[i]!=pinstorage[i]){
			mode=MODE_SAVE;
			init=1;
			detectall=0;
			return;
		}
	}
	mode=MODE_MENU;
	init=1;
	return;
}

void printstorage(uint8_t i){
	UART_SendString("\r\n");
	UART_SendString(&addrdescription[i][0]);
	for(uint8_t j=0;j<(13-strlen(addrdescription[i]));j++){
		UART_Send_Byte(' ');
	}
	char buffer[32];
	sprintf(&buffer[0],"(%2i): %5i ",i,pinstorage[i]);
	UART_SendString(&buffer[0]);
	if(i<32){
		UART_Send_Byte('(');
		if(pinstorage[i]<PINCOUNT){
			UART_SendString(&PXX[pinstorage[i]][0]);
		}else{
			UART_SendString("not set");
		}
		UART_Send_Byte(')');
	}
}

void finduartloop(){
	char teststr[] = "HelloWorld";
	uint8_t txs[UARTCOUNT/2], rxs[UARTCOUNT/2];
	uint8_t tindex=0;
	uint8_t rindex=0;
	uint8_t found=0;
	for(uint8_t i=0;i<UARTCOUNT;i++){
		if(uarts[i].tx){
			txs[tindex++]=i;
		}else{
			rxs[rindex++]=i;
		}
	}
	for(uint8_t r=0;r<UARTCOUNT/2;r++){
		for(uint8_t t=0;t<UARTCOUNT/2;t++){
			for(uint8_t i=0;i<UARTCOUNT;i++){
				pinMode(uarts[i].io, INPUT_PULLUP);
		    pinModeAF(uarts[i].io,uarts[i].af+1);
			}
			found=1;
			pinModeAF(uarts[txs[t]].io,uarts[txs[t]].af);
			pinModeAF(uarts[rxs[r]].io,uarts[rxs[r]].af);
			pinMode(uarts[txs[t]].io, OUTPUT_AF);
			pinMode(uarts[rxs[r]].io, INPUT);
			for(uint8_t i=0;i<10;i++){
				receiveuart=0;
        UART_Send_Byte((u8)(teststr[i]));
				DELAY_Ms(10);
				if(receiveuart!=teststr[i]){
					for(uint8_t j=0;j<PINCOUNT;j++){
						if(!(used(j)||j==uarts[txs[t]].io||j==uarts[rxs[r]].io)){
							pinMode(j, INPUT_PULLUP);
						}
					}
					DELAY_Ms(10);
					for(uint8_t j=0;j<PINCOUNT;j++){
						if(!(used(j)||j==uarts[txs[t]].io||j==uarts[rxs[r]].io)){
							pinMode(j, INPUT);
						}
					}
					found=0;
					DELAY_Ms(100);
					break;
				}
			}
			if(found){
				TXPIN=uarts[txs[t]].io;
				RXPIN=uarts[rxs[r]].io;
				EEPROM_Write((u8*)pinstorage, 2 * 64);
				t=100;
				r=100;
				mode=MODE_WAIT_UART;
				for(uint8_t j=0;j<PINCOUNT;j++){
					if(!(used(j)||j==uarts[txs[t]].io||j==uarts[rxs[r]].io)){
						pinMode(j, INPUT_PULLUP);
					}
				}
				DELAY_Ms(1000);
				for(uint8_t i=0;i<PINCOUNT;i++){
					if(!used(i)){
						pinMode(i, INPUT);
					}
				}	
				UART_GPIO_Init();
			}
		}
	}
}
	

