#ifdef TARGET_MM32SPIN25
#include "HAL_device.h"                 // Device header
#else
#include "mm32_device.h"                // Device header
#endif
#include "../Inc/calculation.h"   
#include "../Inc/pinout.h"   

int max = 4000;
int min = -4000;
int qdSum = 0;
int lasterr=0;
int prevpwm=0;

uint8_t index;
int datasum;
int avgarr[32];
extern int realspeed;
extern int frealspeed;
uint8_t vindex;
int vdatasum;
int vavgarr[32];
extern int vbat;
extern int fvbat;
uint8_t aindex;
int adatasum;
int aavgarr[64];
extern int itotal;
extern int fitotal;


int PID(int setpoint,int real){
	
	int qOut = 0;
	int Error;
	signed long  Up;
	signed long  Ui;
	signed long  Ud;
	//Calc Error
	Error = setpoint - real;
	//Calc proportional
	Up = (Kp * Error);
	//Calc integral
	#ifdef DYNKi
	qdSum = qdSum + Ki * Error;
	#else
	qdSum=0;
	#endif
	//Limit integral 
	if(qdSum >= (max)){
		qdSum = (max);
	}else if(qdSum <= min){
		qdSum = (min);
	}
	Ui = qdSum;
	Ud=(Error-lasterr)*Kd;
	lasterr=Error;
	qOut = Up + Ui + Ud;		
	//Out Limit
	if(qOut > max){
		qOut =max ;
	}else if(qOut < min){
		qOut = min;
	}
	return qOut;
	
}

void avgspeed(){
	
	if(index >= 32){
    index = 0;
  } 
  datasum = datasum + realspeed - avgarr[index];
  avgarr[index] = realspeed;
  frealspeed = (int)(datasum>>5);
  index++;
}
void avgvbat(){
	
	if(vindex >= 32){
    vindex = 0;
  } 
  vdatasum = vdatasum + vbat - vavgarr[vindex];
  vavgarr[vindex] = vbat;
  fvbat = (int)(vdatasum>>5);
  vindex++;
}
void avgItotal(){
	
	if(aindex >= 64){
    aindex = 0;
  } 
  adatasum = adatasum + itotal - aavgarr[aindex];
  aavgarr[aindex] = itotal;
  fitotal = (int)(adatasum>>6);
  aindex++;
}
int PID2PWM(int pid){
	int pwm = prevpwm += pid;
	if(pwm > max){
		pwm =max ;
	}else if(pwm < min){
		pwm = min;
	}
	if(prevpwm > max){
		prevpwm =max ;
	}else if(prevpwm < min){
		prevpwm = min;
	}
	return pwm*PWM_RES/4000;
}

uint32_t updateMotorRPM(uint32_t halltime){
    return  60000000 / (halltime * 10 * WINDINGS);
}



