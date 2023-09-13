
#ifndef CONFIGBOARD_H_
#define CONFIGBOARD_H_


/* Private includes ----------------------------------------------------------*/
#include <LPC17xx.h>
#include "pinmux.h"
#include "gpio.h"


/* Board defines ------------------------------------------------------------*/
#define configLED    		0
#define configButton  		0
#define configClock   		0
#define configSevenSeg		0
#define configLCD			0
#define configPS2			0
#define CONFIG_SPI          1
#define CONFIG_SSD1306      1


#if CONFIG_SSD1306
#define SSD1306CLKFREQ        400000UL
#define SSD1306_SPI_PORT      LPC_SPI
#define SSD1306_CS_PORT       LPC_GPIO0
#define SSD1306_CS_PIN        PIN16
#define SSD1306_RESET_PORT    LPC_GPIO0
#define SSD1306_RESET_PIN     PIN4
#define SSD1306_DC_PORT       LPC_GPIO0
#define SSD1306_DC_PIN        PIN5
#define SSD1306_INCLUDE_FONT_6x8
#define SSD1306_INCLUDE_FONT_7x10
#define SSD1306_INCLUDE_FONT_11x18
#define SSD1306_INCLUDE_FONT_16x26
#endif

#if CONFIG_SPI
#define SPIPERIPHERALFREQ   25000000
#define SPIPORT 			LPC_GPIO0
#define SCKPIN				SCK
#define MISOPIN   			MISO
#define MOSIPIN             MOSI
#define SSELPIN				P0_16
#endif

#if configPS2
#define PS2CLKPORT  	PORT2
#define PS2CLKPIN   	PIN11
#define PS2DATAPORT  	PORT0
#define PS2DATAPIN   	PIN10
#endif



#if configLCD
#define LCDDATAPORT    	  PORT1
#define LCDDATAPIN_D0     PIN19
#define LCDDATAPIN_D1     PIN20
#define LCDDATAPIN_D2     PIN21
#define LCDDATAPIN_D3     PIN22
#define LCDDATAPIN_D4     PIN23
#define LCDDATAPIN_D5     PIN24
#define LCDDATAPIN_D6     PIN25
#define LCDDATAPIN_D7     PIN26

#define LCDCTRLPORT		  PORT0
#define LCDCTRLPIN_RS     PIN4
#define LCDCTRLPIN_RW     PIN5
#define LCDCTRLPIN_EN     PIN6
#endif


#if configClock
#define SEL_IRC       0
#define SEL_MAINOSC   1
#define SEL_RTC		  2

#define CLKOUTSEL_CCLK  	0
#define CLKOUTSEL_MAINOSC   1
#define CLKOUTSEL_IRC		2
#define CLKOUTSEL_USBCLK  	3
#define CLKOUTSEL_RTCCLK  	4
#define CLKOUTDIV			2

#define CURRENT_OSCSEL  		SEL_MAINOSC

#define TODOTESTCASE0   	0
#define TODOTESTCASE1   	0
#define TODOTESTCASE2   	0
#define TODOTESTCASE3   	0
#define TODOTESTCASE4   	0
#define TODOTESTCASE5   	0

#if TODOTESTCASE0
/* PLL Calculations for Fcco = 400 MHz, Fin = 12MHz, CCLK = 100 MHz and Peripheral clock = 100/4 =25 MHz */
#define CURRENT_MSEL
#define CURRENT_NSEL
#define CURRENT_CCLKSEL
#define CURRENT_PCLKSEL0
#define CURRENT_PCLKSEL1

#elif TODOTESTCASE1
/* PLL Calculations for Fcco = 384 MHz, Fin = 12MHz, CCLK = 96 MHz and Peripheral clock = 96/4 =24 MHz */
#define CURRENT_MSEL
#define CURRENT_NSEL
#define CURRENT_CCLKSEL
#define CURRENT_PCLKSEL0
#define CURRENT_PCLKSEL1

#elif TODOTESTCASE2
/* PLL Calculations for Fcco = 384 MHz, Fin = 12MHz, CCLK = 48 MHz and Peripheral clock = 96/4 =24 MHz */
#define CURRENT_MSEL
#define CURRENT_NSEL
#define CURRENT_CCLKSEL
#define CURRENT_PCLKSEL0
#define CURRENT_PCLKSEL1

#elif TODOTESTCASE3
/* PLL Calculations for Fcco = 288 MHz, Fin = 12MHz, CCLK = 96 MHz and Peripheral clock = 96/2 =48 MHz */
#define CURRENT_MSEL
#define CURRENT_NSEL
#define CURRENT_CCLKSEL
#define CURRENT_PCLKSEL0
#define CURRENT_PCLKSEL1

#elif TODOTESTCASE4
/* PLL Calculations for Fcco = 288 MHz, Fin = 12MHz, CCLK = 96 MHz and Peripheral clock = 96/2 =48 MHz */
#define CURRENT_MSEL
#define CURRENT_NSEL
#define CURRENT_CCLKSEL
#define CURRENT_PCLKSEL0
#define CURRENT_PCLKSEL1

#elif TODOTESTCASE5
/* PLL Calculations for	Fcco = 396 MHz, Fin = 12MHz, CCLK = 12 MHz and Peripheral clock = 12/1 =12 MHz */
#define CURRENT_MSEL
#define CURRENT_NSEL
#define CURRENT_CCLKSEL
#define CURRENT_PCLKSEL0
#define CURRENT_PCLKSEL1
#else
/* PLL Calculations for Fcco = 300 MHz, Fin = 12MHz, CCLK = 100 MHz and Peripheral clock = 100/4 =25 MHz */
#define CURRENT_MSEL  			25
#define CURRENT_NSEL  			2
#define CURRENT_CCLKSEL   		3
#define CURRENT_PCLKSEL0		0x00000000
#define CURRENT_PCLKSEL1		0x00000000
#endif

#define CURRENT_CLKOUTSEL		CLKOUTSEL_IRC
#define CURRENT_CLKOUTDIV		CLKOUTDIV


#endif




#if configButton
#define BUTTON0PORT  PORT2
#define BUTTON0PIN   PIN10
#endif




#if configLED
#define LED0PORT  PORT1
#define LED1PORT  PORT1
#define LED2PORT  PORT1

/* TODO : Update the #defines for PORT for 6 more LEDs */

#define LED0PIN   PIN29
#define LED1PIN   PIN20
#define LED2PIN   PIN21

/* TODO : Update the #defines for PINs for 6more LEDs */

#endif





#endif /* CONFIGBOARD_H_ */
