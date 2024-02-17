#include "mm32_device.h"                // Device header
#include "hal_conf.h"
#include "hal_gpio.h" 
#include "hal_adc.h" 

#define IOA 1
#define IOB 2
#define IOC 3
#define IOD 4











void pinMode(uint8_t port,uint16_t pin,uint8_t state);
uint8_t digitalRead(uint8_t port,uint16_t pin);
uint16_t analogRead(uint16_t channel);
void digitalWrite(uint8_t port,uint16_t pin,uint8_t state);

