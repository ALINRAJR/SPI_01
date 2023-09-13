

/* Includes -----------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/
#include "powercontrol.h"
#include "clock.h"
#include "spi.h"
#include "gpio.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/**
  * @brief     Setting power ON/OFF for SPI Peripheral
  * @param[in] mode value can be either POWERON/ POWEROFF
  * @return    No return value
  **/
void vSPIPowerControl(uint8_t mode) {
	if (mode == POWERON)
		LPC_SC->PCONP |= 1 << BIT_PCONP_PCSPI;
	else if (mode == POWEROFF)
		LPC_SC->PCONP &= ~(1 << BIT_PCONP_PCSPI);
}

/**
  * @brief     Setting clock for SPI Peripheral
  * @param[in] clockmode value can be ONEFOURTH,SAME,HALF,ONEEIGTH
  * @return    No return value
 **/
void vSPIClockControl(uint8_t clockmode) {
	LPC_SC->PCLKSEL0 &= ~(3 << BIT_PCLKSEL0_PCLK_SPI);
	LPC_SC->PCLKSEL0 |= clockmode << BIT_PCLKSEL0_PCLK_SPI;
}

/**
  * @brief     Setting clock frequency (baud rate) for SPI SCL
  * @param[in] sckclk value of the desired frequency from the device
  * @return    No return value
 **/
void vSPISerialClkFreq(uint8_t sckclk) {
	LPC_SPI->SPCCR = SPIPERIPHERALFREQ / sckclk;
}

/**
  * @brief     Selecting number of bits per data transfer
  * @param[in] BitNum value can be either EIGHT_BIT or NOT_EIGHT_BIT
 * @return    No return value
 **/
void vSPIBitNumSelect(uint8_t BitNum) {
	if (BitNum == NOT_EIGHT_BIT)
		LPC_SPI->SPCR |= 1 << BIT_SPCR_BitEnable;
	else if (BitNum == EIGHT_BIT)
		LPC_SPI->SPCR &= ~(1 << BIT_SPCR_BitEnable);
}

/**
  * @brief     Selecting method of clock phase control of data transfer
  * @param[in] clknum value can be either FIRST_CLOCKEDGE or SECOND_CLOCKEDGE
  * @return    No return value
  **/
void vSPIClockPhaseControl(uint8_t clknum) {
	if (clknum == SECOND_CLOCKEDGE)
		LPC_SPI->SPCR |= 1 << BIT_SPCR_CPHA;
	else if (clknum == FIRST_CLOCKEDGE)
		LPC_SPI->SPCR &= ~(1 << BIT_SPCR_CPHA);
}

/**
  * @brief     Selecting method of clock polarity control
  * @param[in] clk value can be either SCK_RISINGEDGE or SCK_FALLINGEDGE
  * @return    No return value
  **/
void vSPIClockPolarityControl(uint8_t clk) {
	if (clk == SCK_FALLINGEDGE)
		LPC_SPI->SPCR |= 1 << BIT_SPCR_CPOL;
	else if (clk == SCK_RISINGEDGE)
		LPC_SPI->SPCR &= ~(1 << BIT_SPCR_CPOL);
}

/**
  * @brief     Selecting operating mode of SPI Peripheral
  * @param[in] mode value can be either SLAVE_MODE or MASTER_MODE
  * @return    No return value
  **/
void vSPIModeSelect(uint8_t mode) {
	if (mode == MASTER_MODE)
		LPC_SPI->SPCR |= 1 << BIT_SPCR_MSTR;
	else if (mode == SLAVE_MODE)
		LPC_SPI->SPCR &= ~(1 << BIT_SPCR_MSTR);
}

/**
  * @brief     Selecting shift direction  of each bit for data transfer in SPI Peripheral
  * @param[in] direction value can be either MSB_FIRST or LSB_FIRST
  * @return    No return value
  **/
void vSPIShiftDirectionSelect(uint8_t direction) {
	if (direction == LSB_FIRST)
		LPC_SPI->SPCR |= 1 << BIT_SPCR_LSBF;
	else if (direction == MSB_FIRST)
		LPC_SPI->SPCR &= ~(1 << BIT_SPCR_LSBF);
}


/**
  * @brief     Enabling interrupt  for  SPI Peripheral
  * @param[in] mode value can be either INT_DISABLE or INT_ENABLE
  * @return    No return value
  **/
void vSPIInterruptEnable(uint8_t mode) {
	if (mode == INT_ENABLE)
		LPC_SPI->SPCR |= 1 << BIT_SPCR_SPIE;
	else if (mode == INT_DISABLE)
		LPC_SPI->SPCR &= ~(1 << BIT_SPCR_SPIE);
}

/**
  * @brief     Enabling interrupt  for  SPI Peripheral
  * @param[in] bitnum value can be SIXTEEN_BIT,EIGHT_BIT,NINE_BIT,TEN_BIT,ELEVEN_BIT,TWELVE_BIT,THIRTEEN_BIT,FOURTEEN_BIT,FIFTEEN_BIT.
  * @return    No return value
  **/
void vSPIBitNumber(uint8_t bitnum) {
	switch (bitnum) {
	case EIGHTBIT:
		LPC_SPI->SPCR |= EIGHTBIT << BIT_SPCR_BITS;
		break;
	case NINE_BIT:
		LPC_SPI->SPCR |= NINE_BIT << BIT_SPCR_BITS;
		break;
	case TEN_BIT:
		LPC_SPI->SPCR |= TEN_BIT << BIT_SPCR_BITS;
		break;
	case ELEVEN_BIT:
		LPC_SPI->SPCR |= ELEVEN_BIT << BIT_SPCR_BITS;
		break;
	case TWELVE_BIT:
		LPC_SPI->SPCR |= TWELVE_BIT << BIT_SPCR_BITS;
		break;
	case THIRTEEN_BIT:
		LPC_SPI->SPCR |= THIRTEEN_BIT << BIT_SPCR_BITS;
		break;
	case FOURTEEN_BIT:
		LPC_SPI->SPCR |= FOURTEEN_BIT << BIT_SPCR_BITS;
		break;
	case FIFTEEN_BIT:
		LPC_SPI->SPCR |= FIFTEEN_BIT << BIT_SPCR_BITS;
		break;
	case SIXTEEN_BIT:
		LPC_SPI->SPCR |= SIXTEEN_BIT << BIT_SPCR_BITS;
		break;
	default:
		break;
	}
}

/**
  * @brief     Initializing SPI Peripheral
  * @return    No return value
  **/
void vSPISlaveSelect(void) {
	/* Select the slave which connected to this pin by clearing because its active low logic */
	vGpioClrPin(SPIPORT, SSELPIN);
}

/**
  * @brief     Initializing SPI Peripheral
  * @param[in] mode
  * @return    No return value
  **/
void vSPISlaveDeSelect(void) {
	/* Select the slave which connected to this pin by clearing because its active low logic */
	vGpioSetPin(SPIPORT, SSELPIN);
}


/**
  * @brief     Initializing SPI Peripheral
  * @param[in] mode
  * @return    No return value
  **/
uint8_t ucSPITransfer(LPC_SPI_TypeDef *SPIx, uint8_t bytetowrite) {

	uint8_t receivedbyte = 0;
	SPIx->SPDR = bytetowrite;
	while (!(SPIx->SPSR & 1 << BIT_SPSR_SPIF));
	receivedbyte = SPIx->SPDR;
	return receivedbyte;
}

/**
  * @brief     Initializing SPI Peripheral
  * @return    No return value
  **/
void vSPIInitialize(void){
	/* Step 1: Powering the SPI Peripheral */
	vSPIPowerControl(POWERON);
	/* Step 2: Clock select for SPI, here CCLK is 100MHz so PCLK going to use is ONEFOURTH, i.e 25MHz*/
	vSPIClockControl(ONEFOURTH);
	/* Step 3 : Bitnumber select. here selecting 8 bit data */
	vSPIBitNumSelect(EIGHT_BIT);
	/* Step 4 : Selecting method of clock phase control of data transfer. data transfers at first clock edge */
	vSPIClockPhaseControl(FIRST_CLOCKEDGE);
	/* Step 5 : Selecting method of clock polarity control of data transfer. data transfers at  falling edge of sck  */
	vSPIClockPolarityControl(SCK_FALLINGEDGE);
	/* Step 5 : Selecting SPI master mode*/
	vSPIModeSelect(MASTER_MODE);
	/* Step 6 : Selecting shift direction of data transfer*/
	vSPIShiftDirectionSelect(MSB_FIRST);
	/* Step 7 : setting sck frequency*/
	vSPISerialClkFreq(SSD1306CLKFREQ);
	/* Step 8 : set ssel pin as output*/
	vGpioSetDir(SPIPORT,SSELPIN,OUTPUT);
}

