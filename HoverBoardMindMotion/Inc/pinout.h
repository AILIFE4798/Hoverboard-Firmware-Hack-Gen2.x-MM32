//¦¦+  ¦¦+ ¦¦¦¦¦¦+ ¦¦+   ¦¦+¦¦¦¦¦¦¦+¦¦¦¦¦¦+     ¦¦+  ¦¦+ ¦¦¦¦¦+  ¦¦¦¦¦¦+¦¦+  ¦¦+    ¦¦+   ¦¦+¦¦¦¦¦¦+ 
//¦¦¦  ¦¦¦¦¦+---¦¦+¦¦¦   ¦¦¦¦¦+----+¦¦+--¦¦+    ¦¦¦  ¦¦¦¦¦+--¦¦+¦¦+----+¦¦¦ ¦¦++    ¦¦¦   ¦¦¦+----¦¦+
//¦¦¦¦¦¦¦¦¦¦¦   ¦¦¦¦¦¦   ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦¦++    ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦     ¦¦¦¦¦++     ¦¦¦   ¦¦¦ ¦¦¦¦¦++
//¦¦+--¦¦¦¦¦¦   ¦¦¦+¦¦+ ¦¦++¦¦+--+  ¦¦+--¦¦+    ¦¦+--¦¦¦¦¦+--¦¦¦¦¦¦     ¦¦+-¦¦+     +¦¦+ ¦¦++¦¦+---+ 
//¦¦¦  ¦¦¦+¦¦¦¦¦¦++ +¦¦¦¦++ ¦¦¦¦¦¦¦+¦¦¦  ¦¦¦    ¦¦¦  ¦¦¦¦¦¦  ¦¦¦+¦¦¦¦¦¦+¦¦¦  ¦¦+     +¦¦¦¦++ ¦¦¦¦¦¦¦+
//+-+  +-+ +-----+   +---+  +------++-+  +-+    +-+  +-++-+  +-+ +-----++-+  +-+      +---+  +------+
//version 118 : fix adc overflow
//file for setting custom pinout
//pinout is for Layout2.8.1

//3LED
#define LEDRPIN GPIO_Pin_3
#define LEDGPIN GPIO_Pin_2
#define LEDBPIN GPIO_Pin_12
#define LEDRPORT GPIOD
#define LEDGPORT GPIOD
#define LEDBPORT GPIOA
//hall sensor
#define HALLAPIN GPIO_Pin_13    //comment out to use simulated hall sensor!
#define HALLBPIN GPIO_Pin_14
#define HALLCPIN GPIO_Pin_15
#define HALLAPORT GPIOC
#define HALLBPORT GPIOC
#define HALLCPORT GPIOC
#define HALLAAF GPIO_AF_6    //timer2 alternate function
#define HALLBAF GPIO_AF_6    //timer2 alternate function
#define HALLCAF GPIO_AF_6    //timer2 alternate function
#define HALLAPINSRC GPIO_PinSource13
#define HALLBPINSRC GPIO_PinSource14
#define HALLCPINSRC GPIO_PinSource15
//self hold
#define LATCHPIN GPIO_Pin_2		//comment out to disable button&latch!
#define LATCHPORT GPIOB
//power button
#define BTNPIN GPIO_Pin_5
#define BTNPORT GPIOB
//buzzer
#define BZPIN GPIO_Pin_9    //comment out to disable buzzer!
#define BZPORT GPIOB
//ADC
#define VBATPIN GPIO_Pin_1    //comment out to disable ADC! the code will no longer run because the timer is driven by ADC interrupt
#define VBATPORT GPIOB
#define VBATADC ADC_Channel_9
#define VBATADC2 ADDR9
#define ITOTALPIN GPIO_Pin_0
#define ITOTALPORT GPIOB
#define ITOTALADC ADC_Channel_8
#define ITOTALADC2 ADDR8
//#define IPHASEAPIN GPIO_Pin_7    //comment out to disable phase current and foc
#define IPHASEAPORT GPIOA
#define IPHASEAADC ADC_Channel_7
#define IPHASEAADC2 ADDR7
#define IPHASEBPIN GPIO_Pin_7
#define IPHASEBPORT GPIOA
#define IPHASEBADC ADC_Channel_7
#define IPHASEBADC2 ADDR7

//extra parameter
#define MCUVCC 5000    //mcu voltage in mv,used for adc,mm32spin support2.5-5.5v
#define VBAT_DIVIDER 0.038    //for calculating vbat voltage, my board have a 1:31 voltage divider and 5v vcc
//#define VBAT_DIVIDER MCUVCC/4096/1000*31    //supply voltage/12bit adc/mv to v*divider percentage
#define ITOTAL_DIVIDER 0.3    //for calculating Itotal,most board have R004=0.004ohm current shunt
//#define ITOTAL MCUVCC/4096/1000*(1000/4)    //supply voltage/12bit adc/mv to v*shunt resistance invert(/0.004 == *250)
#define IPHASE_DIVIDER 0.3    //for calculating Itotal,most board have R004=0.004ohm current shunt
#define SLAVEID 1    //for remoteuartbus protol, compatiable with gen2 gd32
#define BAUD 19200
#define INVERT_LOWSIDE TIM_OCNPolarity_High   //when the low side gate driver is active HIGH
//#define INVERT_LOWSIDE TIM_OCNPolarity_Low   //when the low side gate driver is active LOW
#define PWM_RES 8192   //the higher the resolution, the lower the frequency
#define WINDINGS 30

//test
#define SOFT_ILIMIT 1000    //software current limit, default to 10a, new plastic motor may need to be lowered
#define HARD_ILIMIT_AWDG 300    //using analog watchdog interrupt for timer emergency break, use comparator or external transistor if you can

#ifndef HARD_ILIMIT_AWDG
  #define HARD_LIMIT_POLARITY TIM_BreakPolarity_Low
	#define HARD_ILIMIT_COMP_REF_PIN GPIO_Pin_3    //uses comparator for emergency stop, comment out to use external transistor
	#define HARD_ILIMIT_COMP_REF_PORT GPIOA
	#define HARD_ILIMIT_COMP_INVERTING COMP_NonInvertingInput_IO2
	#define HARD_ILIMIT_COMP_NONINVERTING COMP_InvertingInput_IO2
	#define HARD_ILIMIT_PIN GPIO_Pin_7    //this pin is used for both analog and comparator input
	#define HARD_ILIMIT_PINSRC GPIO_PinSource12    //not needed for comp
	#define HARD_ILIMIT_PORT GPIOA
	#define HARD_ILIMIT_AF GPIO_AF_6    //not needed for comp
#else
#define HARD_LIMIT_POLARITY TIM_BreakPolarity_High
#endif
#define UARTEN UART1 //enable uart, PA2 PA3=UART2, PB4 PB6=UART1
//#define TESTROTATE  //spin motor foward and backward automaticly
//#define WATCHDOG    //enable watchdog, to debug you must disable it
#ifdef HALLAPIN    //no way to know real speed without hall!
	#ifdef LEDRPIN
		#define HALL2LED  //sequence through led or rotate acording to motor
	#endif
	#define HALLTIM TIM2    //timer for counting speed of hall sensor
  #define CONSTSPEED    //PID loop to attempt keeping constant speed
#endif

//serial1
#ifdef UARTEN 
#define SERIALTXPIN GPIO_Pin_6
#define SERIALTXPINSRC GPIO_PinSource6
#define SERIALTXPORT GPIOB
#define SERIALTXAF GPIO_AF_0    //serial alternate function
#define SERIALRXPIN GPIO_Pin_4
#define SERIALRXPINSRC GPIO_PinSource4
#define SERIALRXPORT GPIOB
#define SERIALRXAF GPIO_AF_3    //serial alternate function 
#endif

