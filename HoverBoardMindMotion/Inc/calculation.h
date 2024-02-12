#include "mm32_device.h"                // Device header

#define Kp 12
#define Ki 1000
#define Kd 500



int PID(int setpoint,int real);
void avgspeed();
int PID2PWM(int pid);
void avgItotal();
void avgvbat();
