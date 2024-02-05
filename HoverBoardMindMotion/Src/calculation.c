#include "mm32_device.h"                // Device header


uint16_t max = 4095;
uint16_t min = -4095;
uint16_t Kp = 8000;		
uint16_t Ki = 50;
uint16_t qdSum = 0;
uint16_t qInMeas = 0;
uint16_t qOut = 0;
uint16_t qIn = 0;




uint16_t PID(uint16_t speed,uint16_t realspeed){
	
	signed int   Error;
	signed long  Up;
	signed long  Ui;
	//Calc Error
	Error = speed - realspeed;
	//Calc proportional
	Up = (Kp * Error)>>15;
	//Calc integral
	qdSum = qdSum + Ki * Error;
	//Limit integral 
	if(qdSum >= (max<<15)){
		qdSum = (max<<15);
	}else if(qdSum <= min<<15){
		qdSum = (min<<15);
	}
	Ui = qdSum>>15;
	//Out = Up + Ui 
	qOut = Up + Ui;		
	//Out Limit
	if(qOut > max){
		qOut =max ;
	}else if(qOut < min){
		qOut = min;
	}
	return qOut;
}






