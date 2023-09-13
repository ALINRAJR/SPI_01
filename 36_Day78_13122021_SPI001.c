/*
===============================================================================
 Name        : 36_Day78_13122021_SPI001.c

 Description : Program to interface SSD1306 with lpc1768 using SPI

 Layered Architecture for Coding
 ************************************
 Application layer-36_Day78_13122021_SPI001.c, ssd1306test.c/.h
 ************************************
 Board layer - pinmux.c/.h, ssd1306.c/.h ssd1306fonts.c/.h
 ************************************
 Low level drivers or chip level -spi.c/h gpio.c/h
 ************************************
 Hardware
 ************************************

===============================================================================
*/

/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/
/* Header includes */
#include "pinmux.h"
#include "spi.h"
#include "ssd1306.h"
#include "ssd1306test.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* SysTick Counter */
volatile unsigned long SysTickCnt;

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/


/**
  * @brief  System Tick time interrupt handler function
  * @retval none
  */
void SysTick_Handler(void)
{
	SysTickCnt++;

}

/**
  * @brief  Initialize all the hardware connected
  * @retval none
  */
void vAppHardwareInit(void) {

	vPinmuxInitialize();
	vSPIInitialize();
	vSSD1306Initialize();
}

/**
  * @brief  Crude Delay implementation for generating a delay
  * @retval none
  */
void vAppDelay(uint32_t count)
{
	int i,j;
	for(i=0;i<count;i++)
		for(j=0;j<0xA00;j++);
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {

	/* MCU Configuration--------------------------------------------------------*/
	/* Variable declarations and initializations */
	SysTick_Config(SystemCoreClock/1000 - 1);  /* Generate interrupt each 1 ms   */
	/* Hardware Initialization */
	vAppHardwareInit();
	/* Infinite loop */
	while (1) {
		vSSD1306TestAll();
	}
	/* Code will never reach here */
}
