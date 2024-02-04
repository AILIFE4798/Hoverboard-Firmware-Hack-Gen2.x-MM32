#include "hal_tim.h"
#include "hal_conf.h"
#include "stdio.h"
#include "pinout.h"
#include "bldc.h"

extern uint8_t step;
extern bool uart;
extern bool adc;
extern int vbat;
extern int itotal;
extern uint8_t hallposprev;

//commutation interrupt
void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
  TIM_ClearITPendingBit(TIM1, TIM_IT_COM);
	commutate();
    
}

void DMA1_Channel2_3_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC3)) {
        DMA_ClearITPendingBit(DMA1_IT_GL3);
        // Check the received buffer
        uart = 1;
    }
}	
	
void ADC1_COMP_IRQHandler(void)
{
    if(RESET != ADC_GetITStatus(ADC1, ADC_IT_EOC)) {
			ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
			//ADC_SoftwareStartConvCmd(ADC1, DISABLE);
			vbat = ADC1->VBATADC2;
			itotal = ADC1->ITOTALADC2;
			adc = 1;
		
			if(hallpos(1)!=hallposprev){
				hallposprev=hallpos(1);
				step=hallposprev;
				commutate();
			}
		
    }
}	

void TIM2_IRQHandler(void) {

__NOP();
}




	