# This repo is for split hoverboard with MM32SPIN0X MCU

 Check https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x for guide and support

 You can help us by testing this code on actual hardware

 Pre-compiled binary is available
 
## Working features

The firmware is already 90% functional, basic motor control should all work, but more testing is needed

https://youtu.be/hCaIlEKzI3A

* working method to unlock and flash the mcu
* motor
* RemoteUartBus protocol(used by gen2.x gd32)
* PID loop for constant speed
* self hold
* voltage and total current
## todo
* optimizations
* constant torque
* autodetect pins
* phase current
* foc
