/*-------------------- Includes -----------------------*/
#ifdef TARGET_MM32SPIN25
#include "HAL_device.h"                 // Device header
#else
#include "mm32_device.h"                // Device header
#endif
#include "../Inc/pwm_gen.h"

/*------------------- Private variables ---------------*/
PWM_GEN_T pwm_gen;
	
/*------------------ Private functions ----------------*/
void PWM_GEN_init(PWM_GEN_T *u1);
void PWM_GEN_calc(PWM_GEN_T *u1);
void Update_PWM(PWM_GEN_T *u1);

/*************************************
	Function Name£ºPWM_GEN_init
	Description£ºIt initializes SVPWM structure
	Input£º*u1 --- Structure PWM_GEN_T 
	Output£ºnone
**************************************/
void PWM_GEN_init(PWM_GEN_T *u1)
{
	u1->Alpha = 0;
	u1->Beta	= 0;
	u1->CompA	= 0;
	u1->CompB	= 0;
	u1->CompC	= 0;
	u1->Mode	= SEVENMODE;
	u1->Sector	= 0;
	u1->N_halfPeriod	= 8192;
}

/*************************************
	Function Name£ºPWM_GEN_calc
	Description£ºComputes duty cycle values 
	Input£º*u1 --- Structure PWM_GEN_T 
	Output£ºnone
**************************************/
void PWM_GEN_calc(PWM_GEN_T *u1)
{
	int32_t	tempA = 0;
	int32_t tempB = 0;
	
	int32_t Vref1 = 0;
	int32_t Vref2 = 0;
	int32_t Vref3 = 0;
	int32_t X = 0;
	int32_t Y = 0;
	int32_t Z = 0;
	
	uint8_t sector = 0;

	int32_t t1on = 0;
	int32_t t2on = 0;
	int32_t taon = 0;
	int32_t tbon = 0;
	int32_t tcon = 0;
	
	tempA = (28378*(s32)u1->Alpha)>>15;//Valpha*sqrt(3)/2
	tempB = (u1->Beta)>>1;//Vbeta/2
	
	Vref1 = u1->Beta;
	Vref2 = tempA - tempB;		//Valpha*sqrt(3)/2 - Vbeta/2 
	Vref3 = -tempA - tempB;		//-Valpha*sqrt(3)/2 - Vbeta/2   
	
	// Sector calculation
	sector = 0;
	if(Vref1>=0)
	{
		sector = sector + 1;
	}
	if(Vref2>=0)
	{
		sector = sector + 2;
	}
	if(Vref3>=0)
	{
		sector = sector + 4;
	}
	
	// Duty cycles computation 
	X = u1->Beta;					//Vbeta
	Y = tempB + tempA;		//Vbeta/2 + Valpha*sqrt(3)/2
	Z = tempB - tempA;		//Vbeta/2 - Valpha*sqrt(3)/2
	
	//Compute the duration of two basis vector
	switch(sector)
	{
		case 1:
			t1on = Z;
			t2on = Y;
			break;
		
		case 2:
			t1on = Y;
			t2on = -X;
			break;
		
		case 3:
			t1on = -Z;
			t2on = X;
			break;
		
		case 4:
			t1on = -X;
			t2on = Z;
			break;
		
		case 5:
			t1on = X;
			t2on = -Y;
			break;
		
		case 6:
			t1on = -Y;
			t2on = -Z;
			break;
	}

	//Compute the change time
	taon = (32768-t1on-t2on)>>1;		//(1-t1-t2)/2,Q15¸ñÊ½
	tbon = taon + t1on;							//taon+t1
	tcon = tbon + t2on;							//tbon+t2
		

	//Compute the duty cycle
	taon = (taon * u1->N_halfPeriod)>>15;

	if(taon >= u1->N_halfPeriod)
	{
		taon = u1->N_halfPeriod - 1;
	}
	else if(taon<=0)
	{
		taon = 0;
	}
	else
	{ }
		
	tbon = (tbon * u1->N_halfPeriod)>>15;

	if(tbon >= u1->N_halfPeriod)
	{
		tbon = u1->N_halfPeriod - 1;
	}
	else if(tbon<=0)
	{
		tbon = 0;
	}
	else
	{ }	

	tcon = (tcon * u1->N_halfPeriod)>>15;

	if(tcon >= u1->N_halfPeriod)
	{
		tcon = u1->N_halfPeriod - 1;
	}
	else if(tcon<=0)
	{
		tcon = 0;
	}
	else
	{ }

		
	//Prepare load compare values
	if(u1->Mode == SEVENMODE)
	{
		switch(sector)	//Seven-step modulation
		{
			case 1:
				u1->CompA = tbon;
				u1->CompB = taon;
				u1->CompC = tcon;
				break;
			
			case 2:
				u1->CompA = taon;
				u1->CompB = tcon;
				u1->CompC = tbon;
				break;
			
			case 3:
				u1->CompA = taon;
				u1->CompB = tbon;
				u1->CompC = tcon;
				break;
			
			case 4:
				u1->CompA = tcon;
				u1->CompB = tbon;
				u1->CompC = taon;
				break;
			
			case 5:
				u1->CompA = tcon;
				u1->CompB = taon;
				u1->CompC = tbon;
				break;
			
			case 6:
				u1->CompA = tbon;
				u1->CompB = tcon;
				u1->CompC = taon;
				break;
			
			default:
				u1->CompA = 0;
				u1->CompB = 0;
				u1->CompC = 0;
				break;
		}
	}
	else if(u1->Mode == FIVEMODE)
	{
		switch(sector)	//Five-step modulation
		{
			case 1:
				u1->CompA = tbon-taon;
				u1->CompB = 0;
				u1->CompC = tcon-taon;
				break;
			
			case 2:
				u1->CompA = 0;
				u1->CompB = tcon-taon;
				u1->CompC = tbon-taon;
				break;
			
			case 3:
				u1->CompA = 0;
				u1->CompB = tbon-taon;
				u1->CompC = tcon-taon;
				break;
			
			case 4:
				u1->CompA = tcon-taon;
				u1->CompB = tbon-taon;
				u1->CompC = 0;
				break;
			
			case 5:
				u1->CompA = tcon-taon;
				u1->CompB = 0;
				u1->CompC = tbon-taon;
				break;
			
			case 6:
				u1->CompA = tbon-taon;
				u1->CompB = tcon-taon;
				u1->CompC = 0;
				break;
			
			default:
				u1->CompA = 0;
				u1->CompB = 0;
				u1->CompC = 0;
				break;
		}
	}
	else
	{
		u1->CompA = 0;
		u1->CompB = 0;
		u1->CompC = 0;
	}
	
	u1->Sector = sector;
}

/****************************************************************
	Function Name£ºUpdate_PWM
	Description£ºUpdate duty cycle values
	Input: *u1 --- Structure PWM_GEN_T
	Output£ºnone
****************************************************************/
void Update_PWM(PWM_GEN_T *u1)
{
	TIM1->CCR1 = u1->CompA;
	TIM1->CCR2 = u1->CompB;
	TIM1->CCR3 = u1->CompC;
}
