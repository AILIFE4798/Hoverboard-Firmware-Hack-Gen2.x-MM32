//file for setting custom pinout before autodetect
//pinout is for Layout2.8.1

//3LED
#define LEDRPIN GPIO_Pin_12
#define LEDGPIN GPIO_Pin_2
#define LEDBPIN GPIO_Pin_3
#define LEDRPORT GPIOA
#define LEDGPORT GPIOD
#define LEDBPORT GPIOD
//hall sensor
#define HALLAPIN GPIO_Pin_13
#define HALLBPIN GPIO_Pin_14
#define HALLCPIN GPIO_Pin_15
#define HALLAPORT GPIOC
#define HALLBPORT GPIOC
#define HALLCPORT GPIOC
#define HALLAAF GPIO_AF_6
#define HALLBAF GPIO_AF_6
#define HALLCAF GPIO_AF_6
#define HALLAPINSRC GPIO_PinSource13
#define HALLBPINSRC GPIO_PinSource14
#define HALLCPINSRC GPIO_PinSource15
//self hold
#define LATCHPIN GPIO_Pin_2
#define LATCHPORT GPIOB
//power button
#define BTNPIN GPIO_Pin_5
#define BTNPORT GPIOB
//buzzer
#define BZPIN GPIO_Pin_9
#define BZPORT GPIOB
//serial1
#define SERIAL1TXPIN GPIO_Pin_6
#define SERIAL1TXPINSRC GPIO_PinSource6
#define SERIAL1TXPORT GPIOB
#define SERIAL1TXAF GPIO_AF_0
#define SERIAL1RXPIN GPIO_Pin_4
#define SERIAL1RXPINSRC GPIO_PinSource4
#define SERIAL1RXPORT GPIOB
#define SERIAL1RXAF GPIO_AF_3
//ADC
#define VBATPIN GPIO_Pin_1
#define VBATPORT GPIOB
#define VBATADC ADC_Channel_2
#define VBATADC2 ADDR2
#define ITOTALPIN GPIO_Pin_7
#define ITOTALPORT GPIOA
#define ITOTALADC ADC_Channel_6
#define ITOTALADC2 ADDR6

//extra parameter
#define MCUVCC 5000    //mcu voltage in mv,used for adc,mm32spin support2.5-5.5v
#define VBAT_DEVIDER 0.026    //for calculating vbat voltage

