#include "hal_tim.h"
#include "hal_conf.h"
#include "stdio.h"
#include "pinout.h"
#include "bldc.h"
#include "../Src/remoteUartBus.h"

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
        serialit();
    }
}	
	
void ADC1_COMP_IRQHandler(void)
{
    if(RESET != ADC_GetITStatus(ADC1, ADC_IT_EOC)) {
			ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
			vbat = ADC1->VBATADC2;//read adc register
			itotal = ADC1->ITOTALADC2;
			adc = 1;//handle in main loop
			#ifdef HALLAPIN
			if(hallpos(dir)!=hallposprev){
				hallposprev=hallpos(dir);
				step=hallposprev;
				commutate();
			}
			#endif
			millis++;
    }
}	

void TIM2_IRQHandler(void) {
	realspeed = (long)80000/(long)(TIM2->CCR1);
	if(dir==0){    //negative speed spinning backward
		realspeed*=-1;
	}

  lastcommutate = millis;
	if(dir==1){
		iOdom++;
	}else{
		iOdom--;
	}
	

}




	