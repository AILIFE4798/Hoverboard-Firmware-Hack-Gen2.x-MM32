#include "mm32_device.h"                // Device header
#include "hal_gpio.h"
#include "../Inc/pinout.h"
#include "../Inc/remoteUartBus.h"
#include "../Inc/bldc.h"
#include "../Inc/calculation.h"
#include "hal_tim.h"
#include "hal_conf.h"
#include "math.h"


extern uint8_t step;
extern int speed;
extern int pwm;
extern bool dir;
extern int realspeed;
extern int frealspeed;
extern int itotal;
extern uint32_t millis;
uint32_t lastcommutate;
uint32_t lasttestrotate;
int testrotatedir=1;
uint8_t hallpos(uint8_t dir);
bool lastdir=0;
extern uint8_t poweron;



const uint8_t hall_to_pos[8] =
{
	// annotation: for example SA=0 means hall sensor pulls SA down to Ground
  0, // hall position [-] - No function (access from 1-6) 
  3, // hall position [1] (SA=1, SB=0, SC=0) -> PWM-position 3
  5, // hall position [2] (SA=0, SB=1, SC=0) -> PWM-position 5
  4, // hall position [3] (SA=1, SB=1, SC=0) -> PWM-position 4
  1, // hall position [4] (SA=0, SB=0, SC=1) -> PWM-position 1
  2, // hall position [5] (SA=1, SB=0, SC=1) -> PWM-position 2
  6, // hall position [6] (SA=0, SB=1, SC=1) -> PWM-position 6
  0, // hall position [-] - No function (access from 1-6) 
};


uint8_t hallpos(uint8_t dir){
	#ifdef HALLAPIN
	uint8_t HallA;
	uint8_t HallB;
	uint8_t HallC;
	uint8_t HallValue;
	
	HallA = digitalRead(HALLAPIN);
	HallB = digitalRead(HALLBPIN);
	HallC = digitalRead(HALLCPIN);
	
	if(dir == 1)
	{
		HallValue = HallC*4 + HallB*2 + HallA;
	}
	else
	{
		HallValue = 7-(HallC*4 + HallB*2 + HallA);
	}
	
	return hall_to_pos[HallValue];
	#else
	return 0;
	#endif
}

void commutate(){
//U,V,W(A,B,C)
		if(step == 1) {//1,0,-1
			TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
			TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);
			TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
			TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable);
			TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);
			TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
			TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
			TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Enable);
		}else if(step == 2) {//0,1,-1
			TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
			TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);
			TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
			TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Enable);
			TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);
			TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
			TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
			TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Enable);		
		}else if(step == 3) {//-1,1,0
			TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
			TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);
			TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
			TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Enable);
			TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);
			TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
			TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
			TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Enable);			
	  }else if(step == 4) {//-1,0,1
			TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
			TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);
			TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
			TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Enable);
			TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);
			TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
			TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
			TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Enable);	
		}else if(step == 5) {//0,-1,1
			TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
			TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);
			TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
			TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Enable);
			TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);
			TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
			TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
			TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Enable);	
		}else if(step == 6) {//1,-1,0
			TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
			TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);
			TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
			TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable);
			TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);
			TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
			TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
			TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Enable);  
		}else{//0,0,0
			TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
			TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);
			TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
			TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);
			TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
			TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);
		}

	TIM_GenerateEvent(TIM1, TIM_EventSource_COM);//apply changes
}




void speedupdate(){
	if(poweron>127){
		RemoteUpdate();	
		avgspeed();//speed filter prevent oscilation
		if(millis-lastcommutate>500){//zero out speed
			realspeed=0;
			frealspeed=0;
		}	
		if(CONSTSPEED){	
			pwm= PID2PWM((PID(speed,frealspeed)/50));// command the required RPM
			if(speed==0){
				pwm=0;
			}
		}else{
			pwm=speed*PWM_RES/1000;//1000~-1000 for all pwm resolution
		}
		
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
}





















