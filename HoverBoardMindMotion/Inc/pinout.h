/*  _   _  _____     _______ ____    _   _    _    ____ _  __ __     ______  */
/* | | | |/ _ \ \   / / ____|  _ \  | | | |  / \  / ___| |/ / \ \   / /___ \ */
/* | |_| | | | \ \ / /|  _| | |_) | | |_| | / _ \| |   | ' /   \ \ / /  __) |*/
/* |  _  | |_| |\ V / | |___|  _ <  |  _  |/ ___ \ |___| . \    \ V /  / __/ */
/* |_| |_|\___/  \_/  |_____|_| \_\ |_| |_/_/   \_\____|_|\_\    \_/  |_____|*/
/*                                                                           */
#define VERSION_INFO "\r\nPinFinder beta v173\r\nchangelog:set slaveid mode, backspace support in CLI"
#include "../Inc/hardware.h"
extern MM32GPIO pins[PINCOUNT];
extern uint16_t pinstorage[64];
	


#define BAUD_AD 19200
#define PWM_RES_AD 8192    //the higher the resolution, the lower the frequency



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
#define DRIVEMODE pinstorage[44]
#define BAT_FULL pinstorage[45]
#define BAT_EMPTY pinstorage[46]
#define SERIAL_TIMEOUT pinstorage[47]


#define MAGICNUM_POS 32
#define MAGIC_NUMBER 0xDCAB
