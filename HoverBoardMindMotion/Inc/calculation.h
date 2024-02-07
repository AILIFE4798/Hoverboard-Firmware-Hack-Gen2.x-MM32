#include "mm32_device.h"                // Device header

#define Kp 15
#define Ki 0
#define Kd 40
#define DYNKp 30
//#define DYNKi 1
#define DYNKd 50


int PID(int setpoint,int real);
void avgspeed();
