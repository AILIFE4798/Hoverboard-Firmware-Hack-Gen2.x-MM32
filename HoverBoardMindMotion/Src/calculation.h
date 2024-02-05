#include "mm32_device.h"                // Device header

#define Kp 20

#define Ki 0
#define Kd 8

int PID(int setpoint,int real);
void avgspeed();
