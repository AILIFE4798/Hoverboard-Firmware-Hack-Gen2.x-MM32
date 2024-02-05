# This repo is for split board with MM32SPIN0X MCU

 check https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x for guide and support

 you can help by testing this code on actual hardware

 i can compile binary for you
 
## current support status

you can already use this firmware in production, it can be controled by the same uartbus protocol, but more testing is needed

https://youtu.be/hCaIlEKzI3A

* working method to unlock and flash the mcu
* hall2led
* self hold
* timer1 automatic output
* uart
* adc
* iwdg
* TESTROTATE(spin back and forth, works on real motor)

## todo

* optimizations
* eeprom (autodetect)
* ws2812
* comparator (foc)
