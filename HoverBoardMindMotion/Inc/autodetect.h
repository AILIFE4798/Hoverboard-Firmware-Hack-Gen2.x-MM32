#ifdef TARGET_MM32SPIN25
#include "HAL_device.h"                 // Device header
#else
#include "mm32_device.h"                // Device header
#endif

void selfhold();
uint8_t detectSelfHold();
void autoDetectSerialIt();
void simhallupdate();
void autoDetectInit();
void blinkLEDupdate();
uint8_t used(uint8_t pin);
void printvoltage();
void checkbutton();
uint8_t restorecfg();
void testrotateloop();
void saveNexit();
void printstorage(uint8_t i);



typedef enum{
  MODE_UART=0,
  MODE_WAIT_UART=1,
  MODE_MENU=2,
  MODE_HALL=3,
  MODE_LED=4,
  MODE_VBAT=5,
  MODE_ITOTAL=6,
  MODE_BUTTON=7,
  MODE_CLI=8,
  MODE_TESTROTATE=9,
  MODE_SAVE=10,
}modes_t;









