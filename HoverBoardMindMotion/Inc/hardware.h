#ifdef TARGET_MM32SPIN25
#include "HAL_device.h"                 // Device header
#include "spin25-redefine.h"
#else
#include "mm32_device.h"                // Device header
#endif
#include "hal_conf.h"
#include "hal_gpio.h" 
#include "hal_adc.h" 

#ifndef _HARDWARE_H
#define _HARDWARE_H    //keil bug workaround typedef redefinition with different types



#define IOA 1
#define IOB 2
#define IOC 3
#define IOD 4

#if(defined TARGET_MM32SPIN25)
#define PINCOUNT 34
#define ADCCOUNT 13
#define TIMCOUNT 22
#define UARTCOUNT 10
#define TIMBKCOUNT 4
#elif (defined TARGET_MM32SPIN0280)
#define PINCOUNT 34
#define ADCCOUNT 13
#define TIMCOUNT 22
#define UARTCOUNT 13
#define TIMBKCOUNT 4
#else
#define PINCOUNT 33
#define ADCCOUNT 10
#define TIMCOUNT 14
#define UARTCOUNT 10
#define TIMBKCOUNT 4
#endif


#define OUTPUT GPIO_Mode_Out_PP
#define OUTPUT_AF GPIO_Mode_AF_PP
#define OUTPUT_OD GPIO_Mode_Out_OD
#define INPUT GPIO_Mode_FLOATING
#define INPUT_PULLUP GPIO_Mode_IPU
#define INPUT_PULLDOWN GPIO_Mode_IPD
#define INPUT_ADC GPIO_Mode_AIN

enum{
	PA0=0,
	PA1=1,
	PA2=2,
	PA3=3,
	PA4=4,
	PA5=5,
	PA6=6,
	PA7=7,
	PA11=8,
	PA12=9,
	PA13=10,
	PA14=11,
	PA15=12,	
	PB0=13,
	PB1=14,
	PB2=15,
	PB3=16,
	PB4=17,
	PB5=18,
	PB6=19,
	PB7=20,
	PB8=21,
	PB9=22,
	PB10=23,
	PB11=24,
	PB12=25,
	PC13=26,
	PC14=27,
	PC15=28,
	PD0=29,
	PD1=30,
	PD2=31,
	PD3=32,
	PD7=33,
};

typedef struct{
  uint8_t port;
  uint16_t pin;
  uint8_t pinSrc;
}MM32GPIO;
typedef struct{
  uint8_t io;
  uint16_t channel;
}MM32ADC;
typedef struct{
  uint8_t io;
  uint8_t af;
  uint8_t tim2;
}MM32TIM23;
typedef struct{
  uint8_t io;
  uint8_t af;
  uint8_t tx;
  uint8_t uart;
}MM32UART;
typedef struct{
  uint8_t io;
  uint16_t af;
}MM32TIMBK;


void pinMode(uint8_t io,uint8_t state);
uint8_t digitalRead(uint8_t io);
uint16_t analogRead(uint8_t io);
void digitalWrite(uint8_t io, uint8_t state);
void pinModeAF(uint8_t io,uint8_t af);




#endif