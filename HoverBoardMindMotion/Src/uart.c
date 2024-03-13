#include "hal_uart.h"
#include "../Inc//pinout.h"

extern uint8_t uarten;

void UART_Send_Byte(u8 dat){
    UART_SendData(uarten==1 ? UART1 : UART2, dat);
    while(!UART_GetFlagStatus(uarten==1 ? UART1 : UART2, UART_CSR_TXC));
}

void UART_Send_Group(u8* buf, u16 len){
    while(len--)
        UART_Send_Byte(*buf++);
}

void UART_SendString(char* str){
    while(*str)
        UART_Send_Byte((u8)(*str++));
}























