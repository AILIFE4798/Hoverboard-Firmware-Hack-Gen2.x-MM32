#include "hal_tim.h"
#include "hal_conf.h"
#include "hal_adc.h"
#include "stdio.h"
#include "../Inc/pinout.h"
#include "../Inc/bldc.h"
#include "../Inc/remoteUartBus.h"
#include "../Inc/calculation.h"

#include "../Inc/ipark.h"
#include "../Inc/FOC_Math.h"
#include "../Inc/pwm_gen.h"

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

int16_t	TestAngle = 0;

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

void DMA1_Channel4_5_IRQHandler(void){
  if(DMA_GetITStatus(DMA1_IT_TC5)) {
    DMA_ClearITPendingBit(DMA1_IT_GL5);
    serialit();
  }
}	
void ADC1_COMP_IRQHandler(void){
	if(ADC_GetFlagStatus(ADC1, ADC_IT_AWD) != RESET) {
    ADC_ClearFlag(ADC1, ADC_IT_AWD);
		TIM_GenerateEvent(TIM1, TIM_EventSource_Break);
  }
	if(RESET != ADC_GetITStatus(ADC1, ADC_IT_EOC)) {
			TestAngle += 30;
			ipark1.Ds = 3000;
			ipark1.Qs = 0;		//CurIQ.qOut;
			ipark1.Theta = TestAngle;    
			IPARK_MACRO1(&ipark1);
			//SVPWM
			pwm_gen.Mode = FIVEMODE;
			pwm_gen.Alpha = ipark1.Alpha;
			pwm_gen.Beta  = ipark1.Beta;
			PWM_GEN_calc(&pwm_gen);

			//Update duty cycle
			Update_PWM(&pwm_gen);
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







	