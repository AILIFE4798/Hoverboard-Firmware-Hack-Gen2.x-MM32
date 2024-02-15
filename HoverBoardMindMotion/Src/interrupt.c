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

//commutation interrupt
void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
  TIM_ClearITPendingBit(TIM1, TIM_IT_COM);
	
    
}

void DMA1_Channel2_3_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC3)) {
        DMA_ClearITPendingBit(DMA1_IT_GL3);
        // Check the received buffer
			  #ifdef UARTEN
        serialit();
				#endif
    }
}	
	
void ADC1_COMP_IRQHandler(void){
	if(ADC_GetFlagStatus(ADC1, ADC_IT_AWD) != RESET) {
    ADC_ClearFlag(ADC1, ADC_IT_AWD);
		TIM_GenerateEvent(TIM1, TIM_EventSource_Break);
  }
	if(RESET != ADC_GetITStatus(ADC1, ADC_IT_EOC)) {
		if(poweron<127){//cancel out adc offset
			itotaloffset+=(uint16_t)ADC1->ITOTALADC2;
			#ifdef IPHASEAPIN
			iphaseaoffset+=(uint16_t)ADC1->IPHASEAADC2;
			iphaseboffset+=(uint16_t)ADC1->IPHASEBADC2;
			#endif
			poweron++;
		}else if(poweron==127){//divide by 128
			itotaloffset = itotaloffset>>7;
			#ifdef IPHASEAPIN
			iphaseaoffset = iphaseaoffset>>7;
			iphaseboffset = iphaseboffset>>7;
			#endif
			#ifdef HARD_ILIMIT_AWDG
				ADC_AnalogWatchdogCmd(ADC1, ENABLE);
				ADC_AnalogWatchdogThresholdsConfig(ADC1, (uint16_t)(HARD_ILIMIT_AWDG+itotaloffset), 0);
				ADC_AnalogWatchdogSingleChannelConfig(ADC1, ITOTALADC);
				ADC_ITConfig(ADC1, ADC_IT_AWD, ENABLE);
			#endif
			poweron++;
		}else{
			vbat = (double)VBAT_DIVIDER*(uint16_t)ADC1->VBATADC2*100;//read adc register
			int tmp = (uint16_t)ADC1->ITOTALADC2;//prevent overflow on negative value
			itotal = (double)ITOTAL_DIVIDER*(tmp-itotaloffset)*100;
			#ifdef IPHASEAPIN
			tmp = (uint16_t)ADC1->IPHASEAADC2;
			iphasea = (double)IPHASE_DIVIDER*(tmp-iphaseaoffset)*100;
			tmp = (uint16_t)ADC1->IPHASEBADC2;
			iphaseb = (double)IPHASE_DIVIDER*(tmp-iphaseboffset)*100;
			#endif
			avgvbat();
			avgItotal();
			#ifdef SOFT_ILIMIT
				if(itotal>SOFT_ILIMIT){
					TIM_CtrlPWMOutputs(TIM1, DISABLE);
				}else{
					TIM_CtrlPWMOutputs(TIM1, ENABLE);
				}
			#endif
			#ifdef HALLAPIN
			if(hallpos(dir)!=hallposprev){
				hallposprev=hallpos(dir);
				step=hallposprev;
				commutate();
			}
    	#endif
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
  if (dir == 0){ // negative speed spinning backward
    realspeed *= -1;
	}
  lastcommutate = millis;
  if (dir == 1){
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
  if (dir == 0){ // negative speed spinning backward
    realspeed *= -1;
	}
  lastcommutate = millis;
  if (dir == 1){
    iOdom++;
  }else{
    iOdom--;
	}
}







	