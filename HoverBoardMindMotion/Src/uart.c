#include "hal_uart.h"
#include "../Inc//pinout.h"

void UART_Send_Byte(u8 dat)
{
    UART_SendData(UART1, dat);
    UART_SendData(UART2, dat);
    while(!(UART_GetFlagStatus(UART1, UART_CSR_TXC)&&UART_GetFlagStatus(UART2, UART_CSR_TXC)));
}

void UART_Send_Group(u8* buf, u16 len)
{
    while(len--)
        UART_Send_Byte(*buf++);
}

void UART_SendString(char* str)
{
    while(*str)
        UART_Send_Byte((u8)(*str++));
}























