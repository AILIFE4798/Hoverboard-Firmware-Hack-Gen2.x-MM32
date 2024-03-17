/*-------------------- Includes -----------------------*/
#include "../Inc/HallHandle.h"
#include "mm32_device.h"                // Device header


/*------------------- Private variables ---------------*/
HALLType HALL1;
int16_t CWShift = -5000;
int16_t CCWShift = 3000;

/*------------------ Private functions ----------------*/
void HALLModuleInit(HALLType *u);
void HALLModuleCalc(HALLType *u);
uint8_t HALL_JudgeState(void);
uint8_t HALL_ReadHallPorts(void);

/****************************************************************
	Function Name£ºHALLModuleInit
	Description£ºInitialize HALLModule Parameter
	Input£ºnone
	Output£ºnone
****************************************************************/
void HALLModuleInit(HALLType *u)
{
	uint8_t i;
	
	u->RunHallValue = HALL_JudgeState();
	u->PreHallValue = u->RunHallValue;
	u->CMDDIR = MOTORDIR;
	u->IncAngle = 5;
	u->IncAngleMax = 10922;
	u->SpeedTemp = 0;
	u->Time100msCNT = 0;
	u->HallTimeSum = 60000;
	
	u->CWAngleTab[5] = 10922;
	u->CWAngleTab[1] = 21844;
	u->CWAngleTab[3] = 32767;
	u->CWAngleTab[2] = -21844;
	u->CWAngleTab[6] = -10922;
	u->CWAngleTab[4] = 0;
	
	u->CCWAngleTab[5] = 10922;
	u->CCWAngleTab[1] = 21844;
	u->CCWAngleTab[3] = 32767;
	u->CCWAngleTab[2] = -21844;
	u->CCWAngleTab[6] = -10922;
	u->CCWAngleTab[4] = 0;
	

	if(u->CMDDIR == -1)
	{
		u->Angle = u->CCWAngleTab[HALL1.RunHallValue] + CCWShift;
	}
	else
	{
		u->Angle = u->CWAngleTab[HALL1.RunHallValue] + CWShift;
	}
	
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
	
	u->RunHallValue = HALL_JudgeState();
	
	if(u->PreHallValue != u->RunHallValue)
	{
		u->Time100msCNT = 0;
		
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
		
		if(u->CMDDIR == -1)
		{
			u->Angle = u->CCWAngleTab[u->RunHallValue] + CCWShift;
		}
		else
		{
			u->Angle = u->CWAngleTab[u->RunHallValue] + CWShift;
		}
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

/****************************************************************
	Function Name£ºHALL_JudgeState
	Description£ºRead Hall Value 4times
	Input£ºnone
	Output£ºnone
****************************************************************/
uint8_t HALL_JudgeState(void)
{
 uint8_t bReadValue1;
 uint8_t bReadValue2;
 uint8_t i,j;

	bReadValue1 = HALL_ReadHallPorts();
	
	for (i = 4,j=8; i > 0; i--)
	{
		if (--j == 0) 
				return bReadValue1; 
		
		bReadValue2 = HALL_ReadHallPorts();
		
		if (bReadValue1 != bReadValue2)
		{
			i = 4;
			bReadValue1 = bReadValue2;
		}
	}
	
	return bReadValue1;    
} 

/****************************************************************
	Function Name£ºHALL_JudgeState
	Description£ºRead Hall Value
	Input£ºnone
	Output£ºnone
****************************************************************/
uint8_t HALL_ReadHallPorts(void)
{
	uint8_t HallA;
	uint8_t HallB;
	uint8_t HallC;
	uint8_t HallValue;
	
	HallA = GPIO_ReadInputDataBit(HALL_PORT,HALLU_PIN);
	HallB = GPIO_ReadInputDataBit(HALL_PORT,HALLV_PIN);
	HallC = GPIO_ReadInputDataBit(HALL_PORT,HALLW_PIN);
	
	if(HALL1.CMDDIR == 1)
	{
		HallValue = HallC*4 + HallB*2 + HallA;
	}
	else
	{
		HallValue = 7-(HallC*4 + HallB*2 + HallA);
	}
	
	return HallValue;
}


