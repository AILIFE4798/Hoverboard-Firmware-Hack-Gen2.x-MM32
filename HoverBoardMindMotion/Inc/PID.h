#ifndef PID_h
#define PID_h

#ifdef TARGET_MM32SPIN25
#include "HAL_device.h"                 // Device header
#else
#include "mm32_device.h"                // Device header
#endif

#define DUTY_OUTMAX  2249    					//占空比输出最大值
#define DUTY_OUTMIN  20             	//占空比输出最小值


typedef struct {
	   signed   long  qdSum;
	   signed   int   qKp;
	   signed   int   qKi;
	   signed   int   qOutMax;
	   signed   int   qOutMin;
	   signed   int   qInRef;
	   signed   int   qInMeas;
	   signed   int   qOut;
}tPIParm;

extern tPIParm CurID;
extern tPIParm CurIQ;
extern tPIParm Speed;

extern void InitPI(void); //PI初始化程序
extern void CalcPI(tPIParm *pParm); //PI运算程序

#endif
