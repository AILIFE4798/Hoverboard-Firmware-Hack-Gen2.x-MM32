#include "mm32_device.h"
#include  "stdio.h"
void UART1_Send_Byte(u8 dat);
void UART1_Send_Group(u8* buf, u16 len);
void UART1_SendString(u8* str);