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
* software and hardware over current protection
## todo
* optimizations
* constant torque
* autodetect pins
* phase current
* foc
## Hardware
any board equippted with MM32SPIN0X microcontroller should be supported, as of now you will nee to trace the pins of the boar manually like below, but im working on autodetect layout

if you are buying a brand new board online, please get a board that have comparators for sensing phase current, so it may support foc in the future

### [Layout 2.8.1](https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/59)
![301605486-a523f7cc-a34a-4567-8c74-eb735d45fe0a](https://github.com/AILIFE4798/Hoverboard-Firmware-Hack-Gen2.x-MM32/assets/142502122/8d725b8a-ae16-4200-9281-23d509e72d12)

### [Layout 2.21](https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/61)
![303005959-978f0a8c-0b84-4eb5-9011-176705d9b6e9](https://github.com/AILIFE4798/Hoverboard-Firmware-Hack-Gen2.x-MM32/assets/142502122/c4e70bda-5ef6-4b0c-80b7-7830203dcfcc)

## Contributions
if you had any feature request or bug report please create issue, because im working on this project actively now dont use pr unless you asked me first because it will get desynced and cannot merge






