#include "mm32_device.h"                // Device header
#include "hal_conf.h"
#include "hal_gpio.h" 
#include "hal_adc.h" 

#ifndef _HARDWARE_H
#define _HARDWARE_H    //keil bug workaround typedef redefinition with different types



#define IOA 1
#define IOB 2
#define IOC 3
#define IOD 4

#define PINCOUNT 33
#define ADCCOUNT 10
#define TIMCOUNT 14
#define UARTCOUNT 4
#define TIMBKCOUNT 4

#define OUTPUT GPIO_Mode_Out_PP
#define OUTPUT_AF GPIO_Mode_AF_PP
#define OUTPUT_OD GPIO_Mode_Out_OD
#define INPUT GPIO_Mode_FLOATING
#define INPUT_PULLUP GPIO_Mode_IPU
#define INPUT_PULLDOWN GPIO_Mode_IPD
#define INPUT_ADC GPIO_Mode_AIN


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
}MM32UART1;
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