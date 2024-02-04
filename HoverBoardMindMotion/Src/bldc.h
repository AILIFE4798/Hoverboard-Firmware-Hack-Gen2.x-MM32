#include "mm32_device.h"                // Device header
#include "hal_tim.h"
#include "hal_conf.h"

extern uint8_t step;

uint8_t hallpos(uint8_t dir);

void commutate(){

	if(step == 1) {
		TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
		TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);
		TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
		TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable);
		TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);
		TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
		TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
		TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Enable);     
	}
	else if(step == 2) {
		TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
		TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);
		TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
		TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Enable);
		TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);
		TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
		TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
		TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Enable);
  }
	else if(step == 3) {
		TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
		TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);
		TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
		TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Enable);
		TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);
		TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
		TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
		TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Enable);
		step++;
	}
	else if(step == 4) {
		TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
		TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);
		TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
		TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Enable);
		TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);
		TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
		TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
		TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Enable);
  }
	else if(step == 5) {
		TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
		TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);
		TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
		TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Enable);
		TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);
		TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
		TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
		TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Enable);
	}
	else if(step == 6) {
		TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
		TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);
		TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
		TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable);
		TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);
		TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
		TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
		TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Enable);
  }else{
		TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
		TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);
		TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
		TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);
		TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
		TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);
	}
	
	
	
	
	
	
	
	
	
}














