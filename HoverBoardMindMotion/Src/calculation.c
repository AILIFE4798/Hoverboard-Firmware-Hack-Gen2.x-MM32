#include "mm32_device.h"                // Device header
#include "../Inc/calculation.h"   

int max = 4095;
int min = -4095;
int qdSum = 0;
int lasterr=0;
int prevpwm=0;
uint8_t index;
int datasum;
int avgarr[32];
extern int realspeed;
extern int frealspeed;

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

int PID2PWM(int pid){
	int pwm = prevpwm += pid;
	if(pwm > max){
		pwm =max ;
	}else if(pwm < min){
		pwm = min;
	}
	return pwm;
}





