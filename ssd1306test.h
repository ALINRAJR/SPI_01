

#ifndef SSD1306TEST_H_
#define SSD1306TEST_H_

/* Includes -----------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/**
  * @brief    Perform the testing for screen border function.
   * @return  No return value
  **/
void vSSD1306TestBorder(void);
/**
  * @brief     Perform the testing font functions.
  * @return    No return value
  **/
void vSSD1306TestFonts(void);
/**
  * @brief     Perform the testing frames per second of data written.
  * @return    No return value
  **/
void vSSD1306TestFPS(void);
/**
  * @brief     Perform test of function to test all functions.
  * @return    No return value
  **/
void vSSD1306TestAll(void);
/**
  * @brief     Perform test of function to draw a line
  * @return    No return value
  **/
void vSSD1306TestLine(void);
/**
  * @brief     Perform test of function to draw a rectangle
  * @return    No return value
  **/
void vSSD1306TestRectangle(void);
/**
  * @brief     Perform test of function to draw a circle
  * @return    No return value
  **/
void vSSD1306TestCircle(void);
/**
  * @brief     Perform test of function to draw an arc
  * @return    No return value
  **/
void vSSD1306TestArc();
/**
  * @brief     Perform test of function to draw a polyline
  * @return    No return value
  **/
void vSSD1306TestPolyline(void);

#endif /* SSD1306TEST_H_ */
