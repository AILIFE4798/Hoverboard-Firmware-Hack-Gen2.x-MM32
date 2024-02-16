#include "hal_uart.h"
#include "../Inc//pinout.h"

void UART_Send_Byte(u8 dat)
{
	#ifdef UARTEN
    UART_SendData(UARTEN, dat);
    while(!UART_GetFlagStatus(UARTEN, UART_CSR_TXC));
	#endif
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























