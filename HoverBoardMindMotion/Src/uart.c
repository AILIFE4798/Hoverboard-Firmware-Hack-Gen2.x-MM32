#include "hal_uart.h"




void UART1_Send_Byte(u8 dat)
{
    UART_SendData(UART1, dat);
    while(!UART_GetFlagStatus(UART1, UART_CSR_TXC));
}

void UART1_Send_Group(u8* buf, u16 len)
{
    while(len--)
        UART1_Send_Byte(*buf++);
}

void UART1_SendString(s8* str)
{
    while(*str)
        UART1_Send_Byte((u8)(*str++));
}























