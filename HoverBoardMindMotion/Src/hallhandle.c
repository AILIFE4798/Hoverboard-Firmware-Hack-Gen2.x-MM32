/*-------------------- Includes -----------------------*/
#include "../Inc/HallHandle.h"
#include "../Inc/bldc.h"
#ifdef TARGET_MM32SPIN25
#include "HAL_device.h"                 // Device header
#else
#include "mm32_device.h"                // Device header
#endif

/*------------------- Private variables ---------------*/
HALLType HALL1;
int16_t CWShift = 0;
extern uint8_t dir;

/*------------------ Private functions ----------------*/
void HALLModuleInit(HALLType *u);
void HALLModuleCalc(HALLType *u);


/****************************************************************
	Function Name£ºHALLModuleInit
	Description£ºInitialize HALLModule Parameter
	Input£ºnone
	Output£ºnone
****************************************************************/
void HALLModuleInit(HALLType *u)
{
	uint8_t i;
	
	u->RunHallValue = hallpos(dir);
	u->PreHallValue = u->RunHallValue;
	u->CMDDIR = MOTORDIR;
	u->IncAngle = 5;
	u->IncAngleMax = 10922;
	u->SpeedTemp = 0;
	u->Time100msCNT = 0;
	u->HallTimeSum = 60000;
	
	u->CWAngleTab[5] = 32767;
	u->CWAngleTab[1] = 43688;
	u->CWAngleTab[3] = 54610;
	u->CWAngleTab[2] = 0;
	u->CWAngleTab[6] = 10922;
	u->CWAngleTab[4] = 21844;



		u->Angle = u->CWAngleTab[HALL1.RunHallValue] + CWShift;
	
	for(i=0;i<8;i++)
	{
		u->HallTime[i] = 10000;
	}
}

/****************************************************************
	Function Name£ºHALLModuleCalc
	Description£ºUpdate the rotor electrical angle and motor speed
	Input£ºHALL--Structure HALLType
	Output£ºnone
****************************************************************/
uint32_t ChangeTime = 0;

void HALLModuleCalc(HALLType *u)
{
	static uint8_t i = 0;
	uint8_t j = 0;
	
	u->RunHallValue = hallpos(dir);
	
	if(u->PreHallValue != u->RunHallValue){
		i++;
		if(i >= 6)
		{
			i = 0;
		}
		
		//Save hall capture time from TIM2 capture/compare register 1
		u->HallTime[i] = TIM2->CCR1;	 
		ChangeTime = u->HallTime[i];
				
		//Calculate rotor electrical angle speed and mechanical speed
		u->HallTimeSum = 0;
		for(j=0;j<6;j++)
		{
			u->HallTimeSum += u->HallTime[j];
		}
		
		u->SpeedTemp = SPEEDX/u->HallTimeSum;
		
		//Calculate the electrical angle increment,unit is 62.5us.
		u->IncAngle = 4096000/u->HallTimeSum;
		u->IncAngleMax = 10922;
		
		u->Angle = u->CWAngleTab[u->RunHallValue] + CWShift;

	}
	
	u->PreHallValue = u->RunHallValue;
	
	//Incremental value limit
	if((u->IncAngleMax - u->IncAngle)>=0)
	{
		u->IncAngleMax = u->IncAngleMax - u->IncAngle;
		u->Angle = u->Angle + u->CMDDIR * u->IncAngle;
	}
	else
	{}
}

