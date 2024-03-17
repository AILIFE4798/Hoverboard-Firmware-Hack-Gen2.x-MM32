/*-------------------- Includes -----------------------*/
#include "../Inc/PID.h"

/*------------------- Private variables ---------------*/
tPIParm CurID;		//ID»·
tPIParm CurIQ;		//IQ»·
tPIParm Speed;

/****************************************************************
	Function Name£ºInitPI
	Description£ºInitialize PID coefficients for torque, flux and speed loop.
	Input£ºnone
	Output£ºnone
****************************************************************/
void InitPI(void)
{
	CurID.qKp = 2048;				//Q15
	CurID.qKi = 50;
	CurID.qOutMax = 30000;
	CurID.qOutMin = -30000;
	CurID.qdSum = 0;
	CurID.qInMeas = 0;
	CurID.qOut = 0;
	
	CurIQ.qKp = 2048;
	CurIQ.qKi = 50;
	CurIQ.qOutMax = 30000;
	CurIQ.qOutMin = 0;
	CurIQ.qdSum = 0;
	CurIQ.qInMeas = 0;
	CurIQ.qOut = 0;
	
	Speed.qOutMax = 30000;
	Speed.qOutMin = -30000;
	Speed.qKp = 8000;		
	Speed.qKi = 50;
	Speed.qdSum = 0;
	Speed.qInMeas = 0;
	Speed.qOut = 0;
}

/****************************************************************
	Function Name£ºCalcPI1
	Description£ºCompute the PI(D) output for a PI(D) regulation.
	Input£ºpParm---PI Structure
	Output£ºnone
****************************************************************/
void CalcPI(tPIParm *pParm)
{
	signed int   Error;
	signed long  Up;
	signed long  Ui;
	
	//Calc Error
	Error = pParm->qInRef - pParm->qInMeas;
	
	//Calc proportional
	Up = (pParm-> qKp * Error)>>15;
	
	//Calc integral
	pParm->qdSum = pParm->qdSum + pParm->qKi* Error;
	
	//Limit integral 
	if(pParm->qdSum >= (pParm->qOutMax<<15))		//CurIQ.qOutMax<<15
	{
		pParm->qdSum = (pParm->qOutMax<<15);
	}
	else if(pParm->qdSum <= (pParm->qOutMin<<15))
	{
		pParm->qdSum = (pParm->qOutMin<<15);
	}
	else
	{}
	
	Ui = pParm->qdSum>>15;
	
	//Out = Up + Ui 
	pParm->qOut = Up + Ui;
		
	//Out Limit
	if(pParm->qOut > pParm->qOutMax)
	{
		pParm->qOut = pParm->qOutMax ;
	}
	else if(pParm->qOut < pParm->qOutMin)
	{
		pParm->qOut = pParm->qOutMin;
	}
	else
	{
		
	}
}

