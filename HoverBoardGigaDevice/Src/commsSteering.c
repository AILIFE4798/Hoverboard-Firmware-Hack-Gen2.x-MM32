/*
// improved and unified serial communication by Robo Durden :-)

#include "../Inc/target.h"
#include "../Inc/it.h"
#include "../Inc/comms.h"
#include "../Inc/commsSteering.h"
#include "../Inc/setup.h"
#include "../Inc/config.h"
#include "../Inc/defines.h"
#include "../Inc/bldc.h"
#include "stdio.h"
#include "string.h"

#pragma pack(1)

// Only master communicates with steerin device
#ifdef MASTER
//#define USART_STEER_TX_BYTES 2   // Transmit byte count including start '/' and stop character '\n'
#define USART_STEER_RX_BYTES 7   // Receive byte count including start '/' and stop character '\n'

extern uint8_t usartSteer_COM_rx_buf[USART_STEER_COM_RX_BUFFERSIZE];
//static uint8_t aReceiveBuffer[USART_STEER_RX_BYTES];
static int16_t iReceivePos = 0;	

extern int32_t steer;
extern int32_t speed;

extern int32_t iOdom;
extern float batteryVoltage; 							// global variable for battery voltage
extern float currentDC; 									// global variable for current dc
extern float realSpeed; 									// global variable for real Speed
extern DataSlave oDataSlave;

typedef struct {			// �#pragma pack(1)� needed to get correct sizeof()
   uint8_t cStart;		//  = '/';
   //uint16_t cStart;		//  = #define START_FRAME         0xABCD
   int16_t  iSpeed;
   int16_t  iSteer;
   uint16_t checksum;
} SerialServer2Hover;

static uint8_t aReceiveBuffer[sizeof(SerialServer2Hover)];

#define START_FRAME         0xABCD       // [-] Start frme definition for reliable serial communication
typedef struct{				// �#pragma pack(1)� needed to get correct sizeof()
   uint16_t cStart;
   int16_t iSpeedL;		// 100* km/h
   int16_t iSpeedR;		// 100* km/h
   uint16_t iVolt;		// 100* V
   int16_t iAmpL;			// 100* A
   int16_t iAmpR;			// 100* A
   int32_t iOdomL;		// hall steps
   int32_t iOdomR;		// hall steps
   uint16_t checksum;
} SerialHover2Server;



//static uint8_t aDebug[sizeof(SerialServer2Hover)];


#ifdef USART_CRSF
//modified from  https://github.com/kkbin505/Simple_RX

uint8_t inBuffer[CRSF_PACKET_SIZE];
uint8_t crsfData[CRSF_PACKET_SIZE];
int16_t channels[CRSF_MAX_CHANNEL];
uint8_t failsafe_status;
uint8_t frameLength;
uint8_t bufferIndex;
uint8_t inData;


void crsfInit(){
	uint8_t loc_crsfData[CRSF_PACKET_SIZE] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	int16_t loc_channels[16]  = {1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023};
  
	//USART_Steer_COM_init(); called in main()
  //initial data;
	memcpy(crsfData,loc_crsfData,CRSF_PACKET_SIZE);
	memcpy(channels,loc_channels,CRSF_MAX_CHANNEL);
	bufferIndex = 0;
}

int16_t getChannel(uint8_t ch) {
  // Read channel data
  if ((ch>=0)&&(ch<16)){
    return channels[ch];
  }
  else{
    return CRSF_CHANNEL_MID;
  }
}

void updateChannels(void) {
  if(crsfData[1] == 24){
    channels[0]  = ((crsfData[3]|crsfData[4]<< 8) & 0x07FF);
    channels[1]  = ((crsfData[4]>>3|crsfData[5]<<5) & 0x07FF);
    channels[2]  = ((crsfData[5]>>6|crsfData[6]<<2|crsfData[7]<<10) & 0x07FF);
    channels[3]  = ((crsfData[7]>>1|crsfData[8]<<7) & 0x07FF);
    channels[4]  = ((crsfData[8]>>4|crsfData[9]<<4) & 0x07FF);
    channels[5]  = ((crsfData[9]>>7|crsfData[10]<<1|crsfData[11]<<9) & 0x07FF);
    channels[6]  = ((crsfData[11]>>2|crsfData[12]<<6) & 0x07FF);
    channels[7]  = ((crsfData[12]>>5|crsfData[13]<<3) & 0x07FF); // & the other 8 + 2 channels if you need them
    channels[8]  = ((crsfData[14]|crsfData[15]<< 8) & 0x07FF);
    channels[9]  = ((crsfData[15]>>3|crsfData[16]<<5) & 0x07FF);
    channels[10] = ((crsfData[16]>>6|crsfData[17]<<2|crsfData[18]<<10) & 0x07FF);
    channels[11] = ((crsfData[18]>>1|crsfData[19]<<7) & 0x07FF);
    channels[12] = ((crsfData[19]>>4|crsfData[20]<<4) & 0x07FF);
    channels[13] = ((crsfData[20]>>7|crsfData[21]<<1|crsfData[22]<<9) & 0x07FF);
    channels[14] = ((crsfData[22]>>2|crsfData[23]<<6) & 0x07FF);
    channels[15] = ((crsfData[23]>>5|crsfData[24]<<3) & 0x07FF);
  }

}

//Crc8 _crc;
static uint8_t crsf_crc8tab[256] = {
	0x00, 0xD5, 0x7F, 0xAA, 0xFE, 0x2B, 0x81, 0x54, 0x29, 0xFC, 0x56, 0x83, 0xD7, 0x02, 0xA8, 0x7D,
	0x52, 0x87, 0x2D, 0xF8, 0xAC, 0x79, 0xD3, 0x06, 0x7B, 0xAE, 0x04, 0xD1, 0x85, 0x50, 0xFA, 0x2F,
	0xA4, 0x71, 0xDB, 0x0E, 0x5A, 0x8F, 0x25, 0xF0, 0x8D, 0x58, 0xF2, 0x27, 0x73, 0xA6, 0x0C, 0xD9,
	0xF6, 0x23, 0x89, 0x5C, 0x08, 0xDD, 0x77, 0xA2, 0xDF, 0x0A, 0xA0, 0x75, 0x21, 0xF4, 0x5E, 0x8B,
	0x9D, 0x48, 0xE2, 0x37, 0x63, 0xB6, 0x1C, 0xC9, 0xB4, 0x61, 0xCB, 0x1E, 0x4A, 0x9F, 0x35, 0xE0,
	0xCF, 0x1A, 0xB0, 0x65, 0x31, 0xE4, 0x4E, 0x9B, 0xE6, 0x33, 0x99, 0x4C, 0x18, 0xCD, 0x67, 0xB2,
	0x39, 0xEC, 0x46, 0x93, 0xC7, 0x12, 0xB8, 0x6D, 0x10, 0xC5, 0x6F, 0xBA, 0xEE, 0x3B, 0x91, 0x44,
	0x6B, 0xBE, 0x14, 0xC1, 0x95, 0x40, 0xEA, 0x3F, 0x42, 0x97, 0x3D, 0xE8, 0xBC, 0x69, 0xC3, 0x16,
	0xEF, 0x3A, 0x90, 0x45, 0x11, 0xC4, 0x6E, 0xBB, 0xC6, 0x13, 0xB9, 0x6C, 0x38, 0xED, 0x47, 0x92,
	0xBD, 0x68, 0xC2, 0x17, 0x43, 0x96, 0x3C, 0xE9, 0x94, 0x41, 0xEB, 0x3E, 0x6A, 0xBF, 0x15, 0xC0,
	0x4B, 0x9E, 0x34, 0xE1, 0xB5, 0x60, 0xCA, 0x1F, 0x62, 0xB7, 0x1D, 0xC8, 0x9C, 0x49, 0xE3, 0x36,
	0x19, 0xCC, 0x66, 0xB3, 0xE7, 0x32, 0x98, 0x4D, 0x30, 0xE5, 0x4F, 0x9A, 0xCE, 0x1B, 0xB1, 0x64,
	0x72, 0xA7, 0x0D, 0xD8, 0x8C, 0x59, 0xF3, 0x26, 0x5B, 0x8E, 0x24, 0xF1, 0xA5, 0x70, 0xDA, 0x0F,
	0x20, 0xF5, 0x5F, 0x8A, 0xDE, 0x0B, 0xA1, 0x74, 0x09, 0xDC, 0x76, 0xA3, 0xF7, 0x22, 0x88, 0x5D,
	0xD6, 0x03, 0xA9, 0x7C, 0x28, 0xFD, 0x57, 0x82, 0xFF, 0x2A, 0x80, 0x55, 0x01, 0xD4, 0x7E, 0xAB,
	0x84, 0x51, 0xFB, 0x2E, 0x7A, 0xAF, 0x05, 0xD0, 0xAD, 0x78, 0xD2, 0x07, 0x53, 0x86, 0x2C, 0xF9};

			
uint8_t crsf_crc8(const uint8_t *ptr, uint8_t len) {
	uint8_t  crc = 0;
	uint8_t i;
	for (i=0; i < len; i++) {
			crc = crsf_crc8tab[crc ^ *ptr++];
	}
	return crc;
}


void GetCrsfPacket(void){
	uint8_t crc;
	uint8_t inData = usartSteer_COM_rx_buf[0];
	if (bufferIndex==0){
		if(inData == CRSF_ADDRESS_FLIGHT_CONTROLLER){
			inBuffer[bufferIndex++] = inData;
		}else{  //I'm not sure this else in needed
			bufferIndex=0;
		}
	}else if(bufferIndex==1){
		frameLength = inData;
		inBuffer[bufferIndex++] = inData;
	}else if(bufferIndex >1 && bufferIndex < frameLength + 1){
			inBuffer[bufferIndex++] = inData;
	}else if(bufferIndex == frameLength + 1){
		//calculate received packet crc
		inBuffer[bufferIndex++] = inData;
		//uint8_t inCrc=inBuffer[CRSF_FRAME_LENGTH-1];
		uint8_t crc=crsf_crc8(&inBuffer[2],inBuffer[1]-1);
		inBuffer[24]=crc;
		//If crc is correct copy buffer data to crsfData
		if( frameLength==CRSF_FRAME_LENGTH && inBuffer[0]== CRSF_ADDRESS_FLIGHT_CONTROLLER){
			if(crc == inBuffer[25]){
				memcpy(crsfData,inBuffer,CRSF_PACKET_SIZE);
				failsafe_status = CRSF_SIGNAL_OK;
			}else{
				failsafe_status = CRSF_SIGNAL_LOST;
			}
		}
		bufferIndex = 0;
	}
}
#endif

// Send frame to steer device
void SendSteerDevice(void)
{
	// Ask for steer input
	SerialHover2Server oData;
	oData.cStart = START_FRAME;
	oData.iVolt = (uint16_t)	(batteryVoltage * 100);
	oData.iAmpL = (int16_t) 	(currentDC * 100);
	oData.iAmpR = (int16_t) 	(oDataSlave.currentDC * 100);
	oData.iSpeedL = (int16_t) (realSpeed * 100);
	oData.iSpeedR = (int16_t) (oDataSlave.realSpeed * 100);
	oData.iOdomL = (int32_t) iOdom;
	oData.iOdomR = (int32_t) oDataSlave.iOdom;

	//oData.iVolt = aDebug[0];
	//oData.iAmpL = aDebug[1];
	//oData.iAmpR = aDebug[2];
	//oData.iSpeedL = aDebug[3];
	//oData.iSpeedR = (int16_t) sizeof(SerialServer2Hover);	// speed
	
	// oDataSlave.wState;

	oData.checksum = 	CalcCRC((uint8_t*) &oData, sizeof(oData) - 2);	// (first bytes except crc)

	#ifdef USART_STEER_COM
		SendBuffer(USART_STEER_COM, (uint8_t*) &oData, sizeof(oData));
	#endif
	
	//oDataSlave.wState = 11;
}

extern uint32_t steerCounter;								// Steer counter for setting update rate


// Update USART steer input
// static int16_t iReceivePos = -1;		// if >= 0 incoming bytes are recorded until message size reached
void UpdateUSARTSteerInput(void)
{
	uint8_t cRead = usartSteer_COM_rx_buf[0];
	if (cRead == '/')	// Start character is captured, start record
	{
		iReceivePos = 0;
	}

	if (iReceivePos >= 0)		// data reading has begun
	{
		aReceiveBuffer[iReceivePos++] = cRead;
		if (iReceivePos == sizeof(SerialServer2Hover))
		{
			iReceivePos = -1;
			SerialServer2Hover* pData = (SerialServer2Hover*) aReceiveBuffer;
				
			//memcpy(aDebug,aReceiveBuffer,sizeof(SerialServer2Hover));
			
			//if (1)
			if (pData->checksum == CalcCRC(aReceiveBuffer, sizeof(SerialServer2Hover) - 2))	//  first bytes except crc
			{
				//DEBUG_LedSet(SET) // 		(steerCounter%2) < 1
				#ifndef TEST_SPEED	// only use received uart command if NOT in TEST_SPEED mode
					speed = pData->iSpeed;
					steer = pData->iSteer;
				#endif
				//if (speed > 300) speed = 300;	else if (speed < -300) speed = -300;		// for testing this function

				ResetTimeout();	// Reset the pwm timout to avoid stopping motors
			}
		}
	}
}

// Update USART steer input
void UpdateUSARTSteerInputNew(void)	// get rid of this stupid struct __attribute__((packed, aligned(1))) "bug" by not using uint8_t in struct
{
	uint8_t cRead = aReceiveBuffer[iReceivePos] = usartSteer_COM_rx_buf[0];
	switch (iReceivePos)
	{
	case 0:	// waiting for first byte of cStart
		if (cRead == (START_FRAME >> 8)	)	
		{
			iReceivePos++;
			//DEBUG_LedSet(RESET)
		}
		break;
	case 1:	// expecting second byte of START_FRAME
		if (cRead == (START_FRAME & 0xff)	)	
		{
			iReceivePos++;	// next reading data from 2 on
		}
		else
			iReceivePos--;	// back to 0
		break;
	default:	// data reading has begun
		if (iReceivePos < sizeof(SerialServer2Hover))
			iReceivePos++;	// not yet finished reading
		else
		{
			iReceivePos = 0;	// reading finished, reset iReceivePos for next transmission
			SerialServer2Hover* pData = (SerialServer2Hover*) aReceiveBuffer;
				
			if (1)	// disable checksum for testing ONLY !
			//if (pData->checksum == CalcCRC(aReceiveBuffer, sizeof(SerialServer2Hover) - 2))	//  first bytes except crc
			{
				//DEBUG_LedSet(SET) // 		(steerCounter%2) < 1
				#ifndef TEST_SPEED	// only use received uart command if NOT in TEST_SPEED mode
					speed = pData->iSpeed;
					steer = pData->iSteer;
				#endif
				if (speed > 300) speed = 300;	else if (speed < -300) speed = -300;		// for testing this function

				ResetTimeout();	// Reset the pwm timout to avoid stopping motors
			}
		}
	}
}

#endif
*/
