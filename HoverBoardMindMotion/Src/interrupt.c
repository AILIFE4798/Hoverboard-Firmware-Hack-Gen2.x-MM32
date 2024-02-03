#include "hal_tim.h"
extern uint8_t step;

//commutation interrupt
void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
    TIM_ClearITPendingBit(TIM1, TIM_IT_COM);
    if(step == 1) {
        TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);

        //  Channel1 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable);
        TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);

        //  Channel2 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Enable);
        step++;


    }
    else if(step == 2) {
        // Next step: Step 3 Configuration
        //  Channel1 configuration
        TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);

        //  Channel3 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Enable);
        TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);

        //  Channel2 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Enable);
        step++;
    }
    else if(step == 3) {
        // Next step: Step 4 Configuration
        //  Channel2 configuration
        TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);

        //  Channel3 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Enable);
        TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);

        //  Channel1 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Enable);
        step++;
    }
    else if(step == 4) {
        // Next step: Step 5 Configuration
        //  Channel3 configuration
        TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);

        //  Channel2 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Enable);
        TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);

        //  Channel1 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Enable);
        step++;
    }
    else if(step == 5) {
        // Next step: Step 6 Configuration
        //  Channel1 configuration
        TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);

        //  Channel3 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Enable);
        TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);

        //  Channel3 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Enable);
        step++;
    }
    else if(step == 6) {
        // Next step: Step 1 Configuration ----------------------------
        //  Channel2 configuration
        TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);

        //  Channel1 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable);
        TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);

        //  Channel3 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Enable);
        step = 1;
    }
}