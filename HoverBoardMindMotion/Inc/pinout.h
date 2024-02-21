/*  _   _  _____     _______ ____    _   _    _    ____ _  __ __     ______  */
/* | | | |/ _ \ \   / / ____|  _ \  | | | |  / \  / ___| |/ / \ \   / /___ \ */
/* | |_| | | | \ \ / /|  _| | |_) | | |_| | / _ \| |   | ' /   \ \ / /  __) |*/
/* |  _  | |_| |\ V / | |___|  _ <  |  _  |/ ___ \ |___| . \    \ V /  / __/ */
/* |_| |_|\___/  \_/  |_____|_| \_\ |_| |_/_/   \_\____|_|\_\    \_/  |_____|*/
/*                                                                           */
//version 132 : PID retune(again)
//file for setting custom pinout
//pinout is for Layout2.8.1


#define BAUD_AD 19200
#define INVERT_LOWSIDE_AD TIM_OCNPolarity_High   //when the low side gate driver is active HIGH
//#define INVERT_LOWSIDE TIM_OCNPolarity_Low   //when the low side gate driver is active LOW
#define PWM_RES_AD 8192    //the higher the resolution, the lower the frequency



#define HARD_LIMIT_POLARITY TIM_BreakPolarity_High
#define UARTEN UART1 //enable uart, PA2 PA3=UART2, PB4 PB6=UART1
#define SERIALTXPIN GPIO_Pin_6
#define SERIALTXPINSRC GPIO_PinSource6
#define SERIALTXPORT GPIOB
#define SERIALTXAF GPIO_AF_0    //serial alternate function
#define SERIALRXPIN GPIO_Pin_4
#define SERIALRXPINSRC GPIO_PinSource4
#define SERIALRXPORT GPIOB
#define SERIALRXAF GPIO_AF_3    //serial alternate function 



#include "../Inc/hardware.h"
extern MM32GPIO pins[33];
extern uint16_t pinstorage[64];
	

#define HALLAPIN pinstorage[0]
#define HALLBPIN pinstorage[1]
#define HALLCPIN pinstorage[2]
#define LEDRPIN pinstorage[3]
#define LEDGPIN pinstorage[4]
#define LEDBPIN pinstorage[5]
#define LEDUPIN pinstorage[6]
#define LEDDPIN pinstorage[7]
#define BUZZERPIN pinstorage[8]
#define BUTTONPIN pinstorage[9]
#define LATCHPIN pinstorage[10]
#define VBATPIN pinstorage[12]
#define ITOTALPIN pinstorage[13]
#define TXPIN pinstorage[14]
#define RXPIN pinstorage[15]
#define OCPPIN pinstorage[23]
#define OCPREFPIN pinstorage[24]

#define VBAT_DIVIDER pinstorage[33]
#define ITOTAL_DIVIDER pinstorage[34]
#define BAUD pinstorage[36]
#define PWM_RES pinstorage[37]
#define SLAVE_ID pinstorage[38]
#define WINDINGS pinstorage[39]
#define INVERT_LOWSIDE pinstorage[40]
#define SOFT_ILIMIT pinstorage[41]
#define AWDG pinstorage[42]
#define CONSTSPEED pinstorage[44]
#define BAT_FULL pinstorage[45]
#define BAT_EMPTY pinstorage[46]
#define SERIAL_TIMEOUT pinstorage[47]


#define MAGICNUM_POS 32
#define MAGIC_NUMBER 0xDCAB



//#define WATCHDOG