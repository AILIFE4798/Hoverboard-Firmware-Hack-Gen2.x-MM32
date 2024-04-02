/*-------------------- Includes -----------------------*/
#ifdef TARGET_MM32SPIN25
#include "HAL_device.h"                 // Device header
#else
#include "mm32_device.h"                // Device header
#endif
#include "../Inc/clarke.h"

/*------------------- Private variables ---------------*/
/*-----------------------------------------------------------------------------
	Default initalizer for the CLARKE object.
-----------------------------------------------------------------------------*/                     
#define CLARKE_DEFAULTS { 0, \
                          0, \
                          0, \
                          0, \
                          0, \
              			} 

CLARKE_T clarke1 = CLARKE_DEFAULTS;
CLARKE_T Emf_AB = CLARKE_DEFAULTS;

/*------------------ Private functions ----------------*/
void CLARKE_MACRO1(CLARKE_T *u1);

/****************************************************************
	Function Name£ºCLARKE_MACRO1
	Description£ºThis function transforms stator currents qIas and 
	qIbs into currents Ialpha and Ibeta in a stationary Alpha Beta
	reference frame.
	Input£º*u1---Structure CLARKE_T
	Output£ºnone
****************************************************************/
void CLARKE_MACRO1(CLARKE_T *u1)
{
	int32_t TempA;
	int32_t TempB;
	
	TempA = u1->As;											//Ialpha = IA
	TempB	= (INV_SQRT3 * (u1->As + 2 * u1->Bs)) >> 10;	//Ibeta = (IA + 2*IB)/sqrt(3)
	
	//Output limitation
	if(TempA >=32767)
	{
		TempA = 32767;
	}
	else if(TempA <= -32768)
	{
		TempA = -32768;
	}
	else
	{}
	
	//Output limitation
	if(TempB >=32767)
	{
		TempB = 32767;
	}
	else if(TempB <= -32768)
	{
		TempB = -32768;
	}
	else
	{}
		
	u1->Alpha = TempA;
	u1->Beta = TempB;
}
