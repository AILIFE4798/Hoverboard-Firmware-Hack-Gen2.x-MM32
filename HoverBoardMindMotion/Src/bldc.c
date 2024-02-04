#include "mm32_device.h"                // Device header
#include "hal_gpio.h"
#include "../Src/pinout.h"



uint8_t hallpos(uint8_t dir){
	
	uint8_t HallA;
	uint8_t HallB;
	uint8_t HallC;
	uint8_t HallValue;
	
	HallA = GPIO_ReadInputDataBit(HALLAPORT,HALLAPIN);
	HallB = GPIO_ReadInputDataBit(HALLBPORT,HALLBPIN);
	HallC = GPIO_ReadInputDataBit(HALLCPORT,HALLCPIN);
	
	if(dir == 1)
	{
		HallValue = HallC*4 + HallB*2 + HallA;
	}
	else
	{
		HallValue = 7-(HallC*4 + HallB*2 + HallA);
	}
	
	return HallValue;
}


























