/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                 Remote UARTBus protocol by robo                 ////
////                                                                 ////
////  https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x  ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
#include "mm32_device.h"                
#include "math.h" 
#include "../Src/pinout.h"
#include "../Src/bldc.h"
#include "stdio.h"
#include "string.h"
#include "../Src/remoteUartBus.h"
#include "hal_crc.h"

#pragma pack(1)

extern uint32_t millis;
extern uint8_t sRxBuffer[10];


static int16_t iReceivePos = 0;	

extern int32_t speed;
extern uint8_t  wState;

extern int32_t iOdom;
extern float vbat; 							// global variable for battery voltage
extern float itotal; 									// global variable for current dc
extern int realspeed; 									// global variable for real Speed

typedef struct {			// ´#pragma pack(1)´ needed to get correct sizeof()
   uint8_t cStart;			//  = '/';
   //uint16_t cStart;		//  = #define START_FRAME         0xABCD
   uint8_t  iDataType;  //  0 = unique id for this data struct
   uint8_t iSlave;			//  contains the slave id this message is intended for
   int16_t  iSpeed;
   uint8_t  wState;   // 1=ledGreen, 2=ledOrange, 4=ledRed, 8=ledUp, 16=ledDown   , 32=Battery3Led, 64=Disable, 128=ShutOff
   uint16_t checksum;
} SerialServer2Hover;
typedef struct {			// ´#pragma pack(1)´ needed to get correct sizeof()
   uint8_t cStart;			//  = '/';
   //uint16_t cStart;		//  = #define START_FRAME         0xABCD
   uint8_t  iDataType;  //  1 = unique id for this data struct
   uint8_t 	iSlave;			//  contains the slave id this message is intended for
   int16_t  iSpeed;
   int16_t  iSteer;
   uint8_t  wState;   // 1=ledGreen, 2=ledOrange, 4=ledRed, 8=ledUp, 16=ledDown   , 32=Battery3Led, 64=Disable, 128=ShutOff
   uint8_t  wStateSlave;   // 1=ledGreen, 2=ledOrange, 4=ledRed, 8=ledUp, 16=ledDown   , 32=Battery3Led, 64=Disable, 128=ShutOff
   uint16_t checksum;
} SerialServer2HoverMaster;
typedef struct {			// ´#pragma pack(1)´ needed to get correct sizeof()
   uint8_t cStart;			//  = '/';
   //uint16_t cStart;		//  = #define START_FRAME         0xABCD
   uint8_t  iDataType;  //  2 = unique id for this data struct
   uint8_t 	iSlave;			//  contains the slave id this message is intended for
   float  fBatteryVoltage;	// 10s LiIon = 10*3.6 = 36;
   uint8_t 	iDivemode;			//  0=pwm, 1=speed/10, 3=torque, 4=iOdometer
   uint16_t checksum;
} SerialServer2HoverConfig;

static uint8_t aReceiveBuffer[255];	//sizeof(SerialServer2Hover)

#define START_FRAME         0xABCD       // [-] Start frme definition for reliable serial communication
typedef struct{				// ´#pragma pack(1)´ needed to get correct sizeof()
   uint16_t cStart;
   uint8_t iSlave;		//  the slave id this message is sent from
   int16_t iSpeed;		// 100* km/h
   uint16_t iVolt;		// 100* V
   int16_t iAmp;			// 100* A
   int32_t iOdom;		// hall steps
   uint16_t checksum;
} SerialHover2Server;




uint32_t iTimeLastRx = 0;


uint16_t CalcCRC(uint8_t *ptr, int count){    //file checksum calculation
	
  uint16_t  crc;
  uint8_t i;
  crc = 0;
  while (--count >= 0)
  {
    crc = crc ^ (uint16_t) *ptr++ << 8;
    i = 8;
    do
    {
      if (crc & 0x8000)
      {
        crc = crc << 1 ^ 0x1021;
      }
      else
      {
        crc = crc << 1;
      }
    } while(--i);
  }
  return (crc);
}


// Send frame to steer device
void RemoteUpdate(void)
{
	if (millis - iTimeLastRx > SREIALTIMEOUT){
		speed = 0;
	}
}

extern 	uint32_t steerCounter;

uint32_t iAnswerMaster = 0;

void AnswerMaster(void)
{
	
	// Ask for steer input
	SerialHover2Server oData;
	oData.cStart = START_FRAME;
	oData.iSlave = SLAVEID;
	oData.iVolt = (uint16_t)	(vbat * 100);
	oData.iAmp = (int16_t) 	(itotal * 100);
	oData.iSpeed = (int16_t) (realspeed * 100);
	oData.iOdom = (int32_t) iOdom;
	oData.iOdom = iAnswerMaster++;

	oData.checksum = 	CalcCRC((uint8_t*) &oData, sizeof(oData) - 2);	// (first bytes except crc)

	#ifdef USART0_REMOTE
		SendBuffer(USART0, (uint8_t*) &oData, sizeof(oData));
	#endif
	#ifdef USART1_REMOTE
		SendBuffer(USART1, (uint8_t*) &oData, sizeof(oData));
	#endif

}

extern uint32_t steerCounter;								// Steer counter for setting update rate

uint8_t iRxDataType;
uint8_t iRxDataSize;

// Update USART steer input
// static int16_t iReceivePos = -1;		// if >= 0 incoming bytes are recorded until message size reached
void RemoteCallback(void)
{

	#ifdef UART1EN
		uint8_t cRead = sRxBuffer[0];
	#endif
	//DEBUG_LedSet((steerCounter%20) < 10,0)	// 	
	
	if (iReceivePos < 0)		// data reading not yet begun
	{
		if (cRead == '/')	// Start character is captured, start record
			iReceivePos = 0;
		else	
			return;
	}
	
	aReceiveBuffer[iReceivePos++] = cRead;
	
	if (iReceivePos == 1)	// '/' read
			return;

	if (iReceivePos == 2)	// iDataType read
	{
		iRxDataType = aReceiveBuffer[1];
		switch (iRxDataType)
		{
			case 0: iRxDataSize = sizeof(SerialServer2Hover);	break;
			case 1: iRxDataSize = sizeof(SerialServer2HoverMaster);	break;
			case 2: iRxDataSize = sizeof(SerialServer2HoverConfig);	break;
		}
		return;
	}
	
	if (iReceivePos < iRxDataSize)
		return;
		
		
	uint16_t iCRC = (aReceiveBuffer[iReceivePos-1] << 8) | aReceiveBuffer[iReceivePos-2];
	iReceivePos = -1;
	if (iCRC == CalcCRC(aReceiveBuffer, iRxDataSize - 2))	//  first bytes except crc
	{
		if (aReceiveBuffer[2] == SLAVEID)
		{
			iTimeLastRx = millis;
			
			switch (iRxDataType)
			{
				case 0:
				{
					SerialServer2Hover* pData = (SerialServer2Hover*) aReceiveBuffer;
					speed = pData->iSpeed;
					wState = pData->wState;
					break;
				}
				case 1: 
				{
					SerialServer2HoverMaster* pData = (SerialServer2HoverMaster*) aReceiveBuffer;
					speed = pData->iSpeed;
					wState = pData->wState;
					break;
				}
				case 2: 
				{
					SerialServer2HoverConfig* pData = (SerialServer2HoverConfig*) aReceiveBuffer;
					break;
				}
			}
			
			//if (speed > 300) speed = 300;	else if (speed < -300) speed = -300;		// for testing this function
			AnswerMaster();
			iTimeLastRx = millis;  	// Reset the pwm timout to avoid stopping motors
		}
	}
}


