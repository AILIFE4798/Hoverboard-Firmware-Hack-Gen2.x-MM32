#include "mm32_device.h"  

void io_init();
void TIM1_init(u16 arr, u16 psc);
void BLDC_init();
void NVIC_Configure(u8 ch, u8 pri);
void exNVIC_Configure(u8 ch, u8 pri, u8 sub);
void UARTX_Init(u32 baudrate);
void DMA_NVIC_Config(DMA_Channel_TypeDef* dam_chx, u32 cpar, u32 cmar, u16 cndtr);
void adc_Init(void);
void HALLTIM_Init(u32 arr, u16 psc);
void HALL_Init(void);
void Iwdg_Init(u16 IWDG_Prescaler, u16 Reload);
void UART_GPIO_Init();