#ifdef TARGET_MM32SPIN25
#include "HAL_device.h"                 // Device header
#else
#include "mm32_device.h"                // Device header
#endif

void commutate();
uint8_t hallpos(uint8_t dir);
void speedupdate();
void serialit(void);
void TIMOCInit();


enum{
	COM_VOLT=0,
	COM_SPEED=1,
	SINE_VOLT=2,
	SINE_SPEED=3,
	FOC_VOLT=4,
	FOC_SPEED=5,
	FOC_TORQUE=6,
};









