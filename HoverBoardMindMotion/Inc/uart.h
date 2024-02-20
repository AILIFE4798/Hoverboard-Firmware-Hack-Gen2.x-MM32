#include "mm32_device.h"
#include  "stdio.h"
void UART_Send_Byte(u8 dat);
void UART_Send_Group(u8* buf, u16 len);
void UART_SendString(char* str);