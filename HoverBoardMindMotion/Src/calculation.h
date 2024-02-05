#include "mm32_device.h"                // Device header

#define Kp 30

#define Ki 0
#define Kd 12

int PID(int setpoint,int real);
void avgspeed();
