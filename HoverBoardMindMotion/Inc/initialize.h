#ifdef TARGET_MM32SPIN25
#include "HAL_device.h"                 // Device header
#else
#include "mm32_device.h"                // Device header
#endif

void io_init();
void TIM1_init(u16 arr, u16 psc);
void BLDC_init();
void NVIC_Configure(u8 ch, u8 pri);
void UARTX_Init(u32 baudrate,uint8_t uart);
void DMA_NVIC_Config(DMA_Channel_TypeDef* dam_chx, u32 cpar, u32 cmar, u16 cndtr);
void adc_Init(void);
void HALLTIM_Init(u32 arr, u16 psc);
void HALL_Init(void);
void Iwdg_Init(u16 IWDG_Prescaler, u16 Reload);
uint8_t UART_GPIO_Init();