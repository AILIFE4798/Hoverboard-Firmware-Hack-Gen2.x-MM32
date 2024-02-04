
#include "delay.h"
#include "hal_rcc.h"

extern u32 SystemCoreClock;
static __IO u32 sTimingDelay;
extern uint32_t millis;


void DELAY_Init(void)
{
    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1);
    }
    NVIC_SetPriority(SysTick_IRQn, 0x0);
}

static void TimingDelayDecrement(void)
{
    if (sTimingDelay != 0x00) {
        sTimingDelay--;
    }
}

void SysTick_Handler(void)
{
    TimingDelayDecrement();
	millis++;
}

void DELAY_Ms(__IO u32 count)
{
    sTimingDelay = count;

    while(sTimingDelay != 0);
}
