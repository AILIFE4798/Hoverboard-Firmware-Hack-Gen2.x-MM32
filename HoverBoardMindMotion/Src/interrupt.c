#include "hal_tim.h"
#include "hal_conf.h"
#include "hal_adc.h"
#include "stdio.h"
#include "../Inc/pinout.h"
#include "../Inc/bldc.h"
#include "../Inc/remoteUartBus.h"
#include "../Inc/calculation.h"
#include "../Inc/autodetect.h"

extern uint8_t step;
extern bool uart;
extern bool adc;
extern bool comm;
extern bool dir;
extern double rpm;
extern uint32_t lastcommutate;
extern uint32_t millis;
extern int vbat;
extern int itotal;
extern int realspeed;
extern int frealspeed;
extern uint8_t hallposprev;
extern int32_t iOdom;
uint32_t itotaloffset=0;
uint8_t poweron=0;
uint16_t iphasea;
uint16_t iphaseb;
uint32_t iphaseaoffset=0;
uint32_t iphaseboffset=0;
extern uint8_t receiveuart;
extern modes_t mode;

extern u8 sRxBuffer[10];
#include "../Inc/uart.h"

void DMA1_Channel2_3_IRQHandler(void){
	if(DMA_GetITStatus(DMA1_IT_TC3)) {
		DMA_ClearITPendingBit(DMA1_IT_GL3);
		if(mode==MODE_UART){
			receiveuart=sRxBuffer[0];
		}else{
			UART_SendString("\x1b[35m");
			UART_Send_Byte(sRxBuffer[0]);
			UART_SendString("\x1b[36m");
			autoDetectSerialIt();
		}
	}
}	
void DMA1_Channel4_5_IRQHandler(void){
	if(DMA_GetITStatus(DMA1_IT_TC5)) {
		DMA_ClearITPendingBit(DMA1_IT_GL5);
		if(mode==MODE_UART){
			receiveuart=sRxBuffer[0];
		}else{
			UART_SendString("\x1b[35m");
			UART_Send_Byte(sRxBuffer[0]);
			UART_SendString("\x1b[36m");
			autoDetectSerialIt();
		}
	}
}		
void ADC1_COMP_IRQHandler(void){

}	










	