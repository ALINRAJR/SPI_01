
#ifndef SPI_H_
#define SPI_H_

/* Includes ----------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

/* Private includes ----------------------------------------------------------*/
#include "pinmux.h"
#include "configboard.h"

/* Private typedef -----------------------------------------------------------*/
enum{EIGHT_BIT=0,NOT_EIGHT_BIT};
enum{FIRST_CLOCKEDGE=0,SECOND_CLOCKEDGE};
enum{SCK_RISINGEDGE=0,SCK_FALLINGEDGE};
enum{SLAVE_MODE=0,MASTER_MODE};
enum{MSB_FIRST=0,LSB_FIRST};
enum{INT_DISABLE=0,INT_ENABLE};
enum{SIXTEEN_BIT=0,EIGHTBIT=0x08,NINE_BIT=0x09,TEN_BIT=0x0A,ELEVEN_BIT=0x0B,TWELVE_BIT=0x0C,THIRTEEN_BIT=0x0D,FOURTEEN_BIT=0x0E,FIFTEEN_BIT=0x0F};

/* Private define ------------------------------------------------------------*/

/* Bits in SPI Control Register*/
#define BIT_SPCR_BitEnable   2
#define BIT_SPCR_CPHA        3
#define BIT_SPCR_CPOL        4
#define BIT_SPCR_MSTR        5
#define BIT_SPCR_LSBF        6
#define BIT_SPCR_SPIE        7
#define BIT_SPCR_BITS        8

/* Bits in SPI Data Register*/
#define BIT_SPDR_DataLow  0
#define BIT_SPDR_DataHigh 0

/* Bits in SPI Clock Counter Register*/
#define BIT_SPCCR_Counter  0

/* Bits in SPI Interrupt Register*/
#define BIT_SPINT_SPIF  0

/* Bits in SPI Test Status Register*/
#define BIT_SPSR_ABRT             3
#define BIT_SPSR_MODF             4
#define BIT_SPSR_ROVR             5
#define BIT_SPSR_WCOL             6
#define BIT_SPSR_SPIF             7

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/**
  * @brief     Setting power ON/OFF for SPI Peripheral
  * @param[in] mode value can be either POWERON/ POWEROFF
  * @return    No return value
  **/
void vSPIPowerControl(uint8_t mode);

/**
 * @brief     Setting clock for SPI Peripheral
 * @param[in] clockmode value can be ONEFOURTH,SAME,HALF,ONEEIGTH
 * @return    No return value
 **/
void vSPIClockControl(uint8_t clockmode);

/**
 * @brief      Setting clock frequency (baud rate) for SPI SCL
 * @param[in] sckclk value of the desired frequency from the device
 * @return    No return value
 **/
void vSPISerialClkFreq(uint8_t sckclk);

/**
* @brief     Selecting number of bits per data transfer
* @param[in] BitNum value can be either EIGHT_BIT or NOT_EIGHT_BIT
* @return    No return value
**/
void vSPIBitNumSelect(uint8_t BitNum);

/**
* @brief     Selecting method of clock phase control of data transfer
* @param[in] clknum value can be either FIRST_CLOCKEDGE or SECOND_CLOCKEDGE
* @return    No return value
**/
void vSPIClockPhaseControl(uint8_t clknum);

/**
* @brief     Selecting method of clock polarity control
* @param[in] clk value can be either SCK_RISINGEDGE or SCK_FALLINGEDGE
* @return    No return value
**/
void vSPIClockPolarityControl(uint8_t  clk);

/**
* @brief     Selecting operating mode of SPI Peripheral
* @param[in] mode value can be either SLAVE_MODE or MASTER_MODE
* @return    No return value
**/
void vSPIModeSelect(uint8_t mode);

/**
* @brief     Selecting shift direction  of each bit for data transfer in SPI Peripheral
* @param[in] direction value can be either MSB_FIRST or LSB_FIRST
* @return    No return value
**/
void vSPIShiftDirectionSelect(uint8_t direction);

/**
* @brief     Enabling interrupt  for  SPI Peripheral
* @param[in] mode value can be either INT_DISABLE or INT_ENABLE
* @return    No return value
**/
void vSPIInterruptEnable(uint8_t mode);

/**
* @brief     Enabling interrupt  for  SPI Peripheral
* @param[in] bitnum value can be SIXTEEN_BIT,EIGHT_BIT,NINE_BIT,TEN_BIT,ELEVEN_BIT,TWELVE_BIT,THIRTEEN_BIT,FOURTEEN_BIT,FIFTEEN_BIT.
* @return    No return value
**/
void vSPIBitNumber(uint8_t bitnum);


/**
* @brief     Initializing SPI Peripheral
* @return    No return value
**/
void vSPISlaveSelect(void);

/**
* @brief     Initializing SPI Peripheral
* @param[in] mode
* @return    No return value
**/
void vSPISlaveDeSelect(void);


/**
* @brief     Initializing SPI Peripheral
* @param[in] mode
* @return    No return value
**/
uint8_t ucSPITransfer(LPC_SPI_TypeDef *SPIx, uint8_t bytetowrite);


/**
* @brief     Initializing SPI Peripheral
* @param[in] mode
* @return    No return value
**/
void vSPIInitialize(void);


#endif /* SPI_H_ */
