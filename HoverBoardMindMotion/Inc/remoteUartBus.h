#ifdef TARGET_MM32SPIN25
#include "HAL_device.h"                 // Device header
#else
#include "mm32_device.h"                // Device header
#endif

#define SREIALTIMEOUT 500   //stop when serial is disconnected

void AnswerMaster(void);
void RemoteUpdate(void);
