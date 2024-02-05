# This repo is for split board with MM32SPIN0X MCU

 check https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x for guide and support

 you can help us by testing this code on actual hardware

 pre-compiled binary is available
 
## current support status

The firmware is already 80% functional, basic motor control should all work, but more testing is needed

https://youtu.be/hCaIlEKzI3A

* working method to unlock and flash the mcu
* motor
* RemoteUartBus protocol(used by gen2.x gd32)
* PID loop for constant speed
* self hold
* iwdg
## todo
* adc (half working)
* optimizations
* eeprom (autodetect)
* ws2812
* comparator (foc)
