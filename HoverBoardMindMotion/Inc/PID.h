#ifndef PID_h
#define PID_h

#include "mm32_device.h"                // Device header


#define DUTY_OUTMAX  2249    					//ռ�ձ�������ֵ
#define DUTY_OUTMIN  20             	//ռ�ձ������Сֵ


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

extern void InitPI(void); //PI��ʼ������
extern void CalcPI(tPIParm *pParm); //PI�������

#endif
