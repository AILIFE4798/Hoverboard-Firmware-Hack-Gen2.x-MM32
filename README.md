# This repo is for split hoverboard with MM32SPIN0X MCU
 You can help us by testing this code on actual hardware

 Pre-compiled binary is available

## Installation 
Check [here](https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/wiki/MM32SPIN05PF%E2%80%90Layout-2.8) for step by step toturial on how to install this firmware on your board
## Control methods
you must use a ESP32 to control the hacked hoverboard

you can find example control methods in this repo

https://github.com/reed-dan/hoverboard_hack_esp32_manualspeed
## Working features

The firmware is already 90% functional, basic motor control should all work, but more testing is needed

https://youtu.be/hCaIlEKzI3A
* compatiable with 99.9% of boards without recompile
* working method to unlock and flash the mcu
* motor and hall sensor commutation
* RemoteUartBus protocol(used by gen2.x gd32)
* PID loop for constant speed
* self hold
* voltage and total current
* software and hardware over current protection
## auto detect

1. first flash the [pinfinder](https://github.com/AILIFE4798/Hoverboard-Firmware-Hack-Gen2.x-MM32/tree/pin-finder) firmware, make sure to choose the correct serial pin version
2. use autodetect for pins it can detect, and use command line to edit other parameters, there is full guide of how to use auto detect in the serial terminal to guide you through all steps
3. save the configurations permanantly to eeprom
4. flash the normal firmware, make sure to choose erase pages and not erase full chip so the configuration remains
5. now the board should use your configuration file, if all the leds are blinking together it cannot parse the config file you have done something wrong
6. if auto detect fail to detect your layout please use command line to added it manually
## todo
* optimizations
* constant torque
* phase current
* foc
## Hardware
any board equippted with MM32SPIN0X microcontroller should be supported

if you are buying a brand new board online, please get a board that have comparators for sensing phase current, so it may support foc in the future

### [Layout 1](https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/59)
![301605486-a523f7cc-a34a-4567-8c74-eb735d45fe0a](https://github.com/AILIFE4798/Hoverboard-Firmware-Hack-Gen2.x-MM32/assets/142502122/8d725b8a-ae16-4200-9281-23d509e72d12)

### [Layout 2](https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/61)
![303005959-978f0a8c-0b84-4eb5-9011-176705d9b6e9](https://github.com/AILIFE4798/Hoverboard-Firmware-Hack-Gen2.x-MM32/assets/142502122/c4e70bda-5ef6-4b0c-80b7-7830203dcfcc)

## support
join this server to get support

https://discord.gg/dvrKS9uyV7

## Contributions
if you had any feature request or bug report please create issue or use the [discussions](https://github.com/AILIFE4798/Hoverboard-Firmware-Hack-Gen2.x-MM32/discussions) feature, because im working on this project actively now dont use pr unless you asked me first because it will get desynced and cannot merge






