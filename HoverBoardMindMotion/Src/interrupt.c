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
extern int vbat;
extern int itotal;
extern int realspeed;
extern uint8_t hallposprev;

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
		
			if(hallpos(dir)!=hallposprev){//commutation needed
				hallposprev=hallpos(dir);
				step=hallposprev;
				commutate();
				comm = 1;
				realspeed=(double)(96000000/TIM2->CCR1)/60;
			}
		
    }
}	

void TIM2_IRQHandler(void) {

__NOP();
}




	