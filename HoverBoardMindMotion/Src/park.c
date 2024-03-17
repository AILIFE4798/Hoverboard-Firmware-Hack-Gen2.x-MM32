/*-------------------- Includes -----------------------*/

#include "../Inc/park.h"
#include "../Inc/FOC_Math.h"

/*------------------- Private variables ---------------*/
PARK_T park1 = PARK_DEFAULTS;

/*------------------ Private functions ----------------*/
void PARK_MACRO1(PARK_T *u1);


/*************************************
	Function Name£ºPARK_MACRO1
	Description£ºThis function transforms Ialpha¡¢Ibeta to Id¡¢Iq.
	Input£º*u1---PARK_T Structure
	Output£ºnone
**************************************/
void PARK_MACRO1(PARK_T *u1)
{
	Trig_Components Local_Vector_Components;
	
	Local_Vector_Components = MCM_Trig_Functions(u1->Theta);
	u1->Sin = Local_Vector_Components.hSin;
	u1->Cos = Local_Vector_Components.hCos;
	
	u1->Ds = (u1->Alpha * u1->Cos + u1->Beta * u1->Sin) >> 15;	//Isd = Ialpha*Cos + Ibeta*Sin
	u1->Qs = (u1->Beta * u1->Cos - u1->Alpha * u1->Sin) >> 15;	//Isq = -Ialpha*Sin + Ibeta*Cos
}

