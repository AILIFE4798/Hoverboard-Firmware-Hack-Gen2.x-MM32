#ifndef FOC_Math_h
#define FOC_Math_h

#ifdef TARGET_MM32SPIN25
#include "HAL_device.h"                 // Device header
#else
#include "mm32_device.h"                // Device header
#endif

typedef struct
{
	int16_t hCos;
	int16_t hSin;
} Trig_Components;

typedef struct
{
	int16_t	NewData;
	uint8_t	Index;
	int16_t DataARR[32];
	int32_t DataSum;
	int16_t	Out;
}MovingAvgData;

typedef struct
{
	int16_t Dest;		//参考目标量
	int16_t Act;		//实际使用量
	int16_t Max;		//最大限制值
	int16_t Min;		//最小限制值
	int16_t Inc;		//加速步距
	int16_t Dec;		//加速步距
}LoopCMP_T; 

typedef struct
{
	uint16_t In;             //输入值
	uint16_t MaxIn;          //最大值有效值
	uint16_t MinIn;          //最小值有效值		
	uint16_t MaxOut;         //对应允许最大输出值
	uint16_t Out;            //输出值
	uint8_t  OutEn;          //输出使能标志
	uint8_t  State;          //输入状态
	float Kslope;       //对应斜率
}
NormalizationType; //参数归一化的相关变量

extern NormalizationType RP;
extern LoopCMP_T RPValue;
extern MovingAvgData IDData;
extern MovingAvgData IQData;
extern MovingAvgData SpdData;
extern MovingAvgData SpeedFdk;

extern Trig_Components MCM_Trig_Functions(int16_t hAngle);
extern int32_t MCM_Sqrt(int32_t wInput);
extern int16_t arctan2(int16_t y1,int16_t x1);
extern void MovingAvgInit(MovingAvgData *Data);
extern void MovingAvgCal(MovingAvgData *Data);
extern void LoopCmp_Init(void);
extern void LoopCmp_Cal(LoopCMP_T *u1);
extern void InitNormalization(uint16_t Lowdata,uint16_t highdata,uint16_t maxout,NormalizationType *u);
extern void CalcNormalization(uint16_t value,NormalizationType *u);

#endif
