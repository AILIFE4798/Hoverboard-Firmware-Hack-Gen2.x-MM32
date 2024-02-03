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

