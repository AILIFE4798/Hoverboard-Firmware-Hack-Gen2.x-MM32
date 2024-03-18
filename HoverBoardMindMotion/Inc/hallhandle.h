#ifndef __HALLHANDLE_H
#define __HALLHANDLE_H
#include <string.h>
#include <stdint.h>

#define	POLEPAIRS		2
#define SPEEDX			60000000/POLEPAIRS			//RPM

#define 	CW				1  //电机逆时针
#define 	CCW				-1 //电机顺时针
#define 	MOTORDIR		CW

#define 	COMPLETED			0
#define 	INCOMPLETED		1
#define 	SAVE					2

typedef struct
{
  uint8_t RunHallValue;   	
  uint8_t PreHallValue;   
	int8_t	CMDDIR;
	int16_t	Angle;
	int16_t IncAngle;
	int16_t IncAngleMax;
	int16_t SpeedTemp;
	uint8_t Time100msCNT;
	uint32_t HallTime[8];		
	uint32_t HallTimeSum;
	int16_t CWAngleTab[8];
	int16_t CCWAngleTab[8];
}
HALLType;

typedef struct
{ 
	int16_t VSP;
	int16_t	VdcValue;
	int16_t IdcValue;
	int16_t IaValue;
	int16_t IbValue;
	int16_t IcValue;
}ADC_components; 

extern ADC_components ADC_Structure; 

extern HALLType HALL1;					

extern void HALLModuleInit(HALLType *u);
extern void HALLModuleCalc(HALLType *u);



#endif

