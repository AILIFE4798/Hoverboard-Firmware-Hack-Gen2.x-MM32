#include "hal_tim.h"
#include "hal_conf.h"
#include "hal_adc.h"
#include "stdio.h"
#include "../Inc/pinout.h"
#include "../Inc/bldc.h"
#include "../Inc/remoteUartBus.h"
#include "../Inc/calculation.h"

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
extern MM32ADC adcs[10];
float vcc;
uint8_t realdir=0;

//commutation interrupt
void TIM1_BRK_UP_TRG_COM_IRQHandler(void){
  TIM_ClearITPendingBit(TIM1, TIM_IT_COM);
}

void DMA1_Channel2_3_IRQHandler(void){
  if(DMA_GetITStatus(DMA1_IT_TC3)) {
    DMA_ClearITPendingBit(DMA1_IT_GL3);
    serialit();
  }
}	
	
void ADC1_COMP_IRQHandler(void){
	if(ADC_GetFlagStatus(ADC1, ADC_IT_AWD) != RESET) {
    ADC_ClearFlag(ADC1, ADC_IT_AWD);
		TIM_GenerateEvent(TIM1, TIM_EventSource_Break);
  }
	if(RESET != ADC_GetITStatus(ADC1, ADC_IT_EOC)) {
		if(poweron<127){//cancel out adc offset
			itotaloffset+=analogRead(ITOTALPIN);
			poweron++;
		}else if(poweron==127){//divide by 128
			itotaloffset = itotaloffset>>7;
			if(AWDG){
				ADC_AnalogWatchdogCmd(ADC1, ENABLE);
				ADC_AnalogWatchdogThresholdsConfig(ADC1, (uint16_t)(AWDG+itotaloffset), 0);
				for(uint8_t i=0;i<ADCCOUNT;i++){
					if(adcs[i].io==ITOTALPIN){
						ADC_AnalogWatchdogSingleChannelConfig(ADC1, adcs[i].channel);
						break;
					}
				}
				ADC_ITConfig(ADC1, ADC_IT_AWD, ENABLE);
			}
			poweron++;
		}else{
			if(hallpos(dir)!=hallposprev){
				step=hallpos(dir);
				commutate();
				if(hallpos(dir)>hallposprev||(hallpos(dir)==1&&hallposprev==6)){
					realdir=0;
				}else{
					realdir=1;
				}
				hallposprev=hallpos(dir);
			}
			uint16_t tmp = ADC1->CH15DR;
			vcc=(double)4915.2/tmp;
			vbat = (double)VBAT_DIVIDER*analogRead(VBATPIN)*vcc*100/4096;//read adc register
			tmp = analogRead(ITOTALPIN);//prevent overflow on negative value
			itotal = (double)ITOTAL_DIVIDER*(tmp-itotaloffset)*vcc*100/4096;
			avgvbat();
			avgItotal();
			if(SOFT_ILIMIT>1&&SOFT_ILIMIT<30&&itotal>SOFT_ILIMIT){
				TIM_CtrlPWMOutputs(TIM1, DISABLE);
			}else if(BAT_EMPTY>20&&BAT_EMPTY<100&&vbat<BAT_EMPTY*100){	
				TIM_CtrlPWMOutputs(TIM1, DISABLE);
			}else{
				TIM_CtrlPWMOutputs(TIM1, ENABLE);
			}

		}
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
	}
}	

void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET){
		
    realspeed = updateMotorRPM(TIM2->CCR1); // rpm is correct			
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
  }
  //realspeed = (long)80000 / (long)(TIM2->CCR1); // not correct
  if (realdir == 0){ // negative speed spinning backward
    realspeed *= -1;
	}
  lastcommutate = millis;
  if (realdir == 1){
    iOdom++;
  }else{
    iOdom--;
	}
}

void TIM3_IRQHandler(void) {
	if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET){
		
    realspeed = updateMotorRPM(TIM3->CCR1); // rpm is correct		
		TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
  }
  //realspeed = (long)80000 / (long)(TIM2->CCR1); // not correct
  if (realdir == 0){ // negative speed spinning backward
    realspeed *= -1;
	}
  lastcommutate = millis;
  if (realdir == 1){
    iOdom++;
  }else{
    iOdom--;
	}
}







	