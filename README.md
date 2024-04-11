# This repo is for split hoverboard with MM32SPIN0X/2X MCU
 You can help us by testing this code on actual hardware

 Pre-compiled binary is available

### if you can see this text, that probably means this repo is not maintained any more

## Installation 
Check [here](https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/wiki/MM32SPIN05PF%E2%80%90Layout-2.8) for step by step toturial on how to install this firmware on your board

please also check the autodetect&configuration section
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
* sine wave mode to drive the motor with more torque and higher effiency
## Autodetect&configuration

https://github.com/AILIFE4798/Hoverboard-Firmware-Hack-Gen2.x-MM32/wiki/How-to-use-PinFinder-firmware

## todo
* optimizations
* constant torque
* phase current
* foc
## Hardware
any board equippted with MM32SPIN0X or MM32SPIN2X microcontroller should be supported

now with the pinfinder firmware, any board type is supported, but below are some example

### [MM32SPIN05PF](https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/59)
![301605486-a523f7cc-a34a-4567-8c74-eb735d45fe0a](https://github.com/AILIFE4798/Hoverboard-Firmware-Hack-Gen2.x-MM32/assets/142502122/8d725b8a-ae16-4200-9281-23d509e72d12)

### [MM32SPIN06PF](https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/61)
![303005959-978f0a8c-0b84-4eb5-9011-176705d9b6e9](https://github.com/AILIFE4798/Hoverboard-Firmware-Hack-Gen2.x-MM32/assets/142502122/c4e70bda-5ef6-4b0c-80b7-7830203dcfcc)

### MM32SPIN25PF
![Gen2 6 1](https://github.com/AILIFE4798/Hoverboard-Firmware-Hack-Gen2.x-MM32/assets/142502122/7c34e631-0be7-4276-aa93-18d8b7d5c52e)


## support
join this server to get support

discord: https://discord.gg/dvrKS9uyV7

matrix: https://matrix.to/#/#hoverboard-firmware-hack:matrix.ai-life.xyz

## Contributions
if you had any feature request or bug report please create issue or use the [discussions](https://github.com/AILIFE4798/Hoverboard-Firmware-Hack-Gen2.x-MM32/discussions) feature, because im working on this project actively now dont use pr unless you asked me first because it will get desynced and cannot merge






