#include "mm32_device.h"                // Device header

#define Kp 8
#define Ki 10
#define Kd 400



int PID(int setpoint,int real);
void avgspeed();
int PID2PWM(int pid);


