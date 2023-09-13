
/* Includes -----------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>

/* Private includes ----------------------------------------------------------*/
#include "ssd1306.h"
#include "ssd1306test.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
extern volatile unsigned long SysTickCnt;

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/**
  * @brief   Get systick time
  * @return  systick time count
  **/
unsigned long GetTick(void)
{
	return SysTickCnt;
}

/**
  * @brief   SysTick vDelay
  * @return  No return value
  **/
void vDelay (unsigned long tick) {

	unsigned long systickcnt;
	systickcnt = SysTickCnt;
	while ((SysTickCnt - systickcnt) < tick);
}

/**
  * @brief   Perform the testing for screen border function.
  * @return  No return value
  **/
void vSSD1306TestBorder() {

	vSSD1306Fill(Black);

    uint32_t start = GetTick();
    uint32_t end = start;
    uint8_t x = 0;
    uint8_t y = 0;
    do {
    	 vSSD1306DrawPixel(x, y, Black);

        if((y == 0) && (x < 127))
            x++;
        else if((x == 127) && (y < (SSD1306_HEIGHT-1)))
            y++;
        else if((y == (SSD1306_HEIGHT-1)) && (x > 0))
            x--;
        else
            y--;

       vSSD1306DrawPixel(x, y, White);
        vSSD1306UpdateScreen();

        vDelay(5);
        end = GetTick();
    } while((end - start) < 8000);

    vDelay(1000);
}

/**
  * @brief     Perform the testing font functions.
  * @return    No return value
  **/
void vSSD1306TestFonts() {
    uint8_t y = 0;
	vSSD1306Fill(Black);

	#ifdef SSD1306_INCLUDE_FONT_16x26
    vSSD1306SetCursor(2, y);
    vSSD1306WriteString("Font 16x26", Font_16x26, White);
    y += 26;
	#endif

	#ifdef SSD1306_INCLUDE_FONT_11x18
    vSSD1306SetCursor(2, y);
    vSSD1306WriteString("Font 11x18", Font_11x18, White);
    y += 18;
	#endif

	#ifdef SSD1306_INCLUDE_FONT_7x10
    vSSD1306SetCursor(2, y);
    vSSD1306WriteString("Font 7x10", Font_7x10, White);
    y += 10;
	#endif

	#ifdef SSD1306_INCLUDE_FONT_6x8
    vSSD1306SetCursor(2, y);
    vSSD1306WriteString("Font 6x8", Font_6x8, White);
	#endif

    vSSD1306UpdateScreen();
}

/**
  * @brief     Perform the testing frames per second of data written.
  * @return    No return value
  **/
void vSSD1306TestFPS() {
    vSSD1306Fill(White);

    uint32_t start = GetTick();
    uint32_t end = start;
    int fps = 0;
    char message[] = "ABCDEFGHIJK";

    vSSD1306SetCursor(2,0);
    vSSD1306WriteString("Testing...", Font_11x18, Black);

    do {
        vSSD1306SetCursor(2, 18);
        vSSD1306WriteString(message, Font_11x18, Black);
        vSSD1306UpdateScreen();

        char ch = message[0];
        memmove(message, message+1, sizeof(message)-2);
        message[sizeof(message)-2] = ch;

        fps++;
        end = GetTick();
    } while((end - start) < 5000);

    vDelay(1000);

    char buff[64];
    fps = (float)fps / ((end - start) / 1000.0);
    snprintf(buff, sizeof(buff), "~%d FPS", fps);

    vSSD1306Fill(White);
    vSSD1306SetCursor(2, 2);
    vSSD1306WriteString(buff, Font_11x18, Black);
    vSSD1306UpdateScreen();
}

/**
  * @brief     Perform test of function to draw a line
  * @return    No return value
  **/
void vSSD1306TestLine() {

  vSSD1306Line(1,1,SSD1306_WIDTH - 1,SSD1306_HEIGHT - 1,White);
  vSSD1306Line(SSD1306_WIDTH - 1,1,1,SSD1306_HEIGHT - 1,White);
  vSSD1306UpdateScreen();
  return;
}

/**
  * @brief     Perform test of function to draw a rectangle
  * @return    No return value
  **/
void vSSD1306TestRectangle() {
  uint32_t delta;

  for(delta = 0; delta < 5; delta ++) {
	  vSSD1306DrawRectangle(1 + (5*delta),1 + (5*delta) ,SSD1306_WIDTH-1 - (5*delta),SSD1306_HEIGHT-1 - (5*delta),White);
   }
  vSSD1306UpdateScreen();
  return;
}

/**
  * @brief     Perform test of function to draw a circle
  * @return    No return value
  **/
void vSSD1306TestCircle() {
  uint32_t delta;

  for(delta = 0; delta < 5; delta ++) {
	vSSD1306DrawCircle(20* delta+30, 15, 10, White);
  }
  vSSD1306UpdateScreen();
  return;
}

/**
  * @brief     Perform test of function to draw an arc
  * @return    No return value
  **/
void vSSD1306TestArc() {
  vSSD1306DrawArc(30, 30, 30, 20, 270, White);
  vSSD1306UpdateScreen();
  return;
}

/**
  * @brief     Perform test of function to draw a polyline
  * @return    No return value
  **/
void vSSD1306TestPolyline() {
  SSD1306_VERTEX loc_vertex[] =
  {
      {35,40},
      {40,20},
      {45,28},
      {50,10},
      {45,16},
      {50,10},
      {53,16}
  };

  vSSD1306Polyline(loc_vertex,sizeof(loc_vertex)/sizeof(loc_vertex[0]),White);
  vSSD1306UpdateScreen();
  return;
}

/**
  * @brief     Perform test of function to test all functions.
  * @return    No return value
  **/
void vSSD1306TestAll() {
    vSSD1306Initialize();
    vSSD1306TestFPS();
    vDelay(3000);
    vSSD1306TestBorder();
    vSSD1306TestFonts();
    vDelay(3000);
    vSSD1306Fill(Black);
    vSSD1306TestRectangle();
    vSSD1306TestLine();
    vDelay(3000);
    vSSD1306Fill(Black);
    vSSD1306TestPolyline();
    vDelay(3000);
    vSSD1306Fill(Black);
    vSSD1306TestArc();
    vDelay(3000);
    vSSD1306Fill(Black);
    vSSD1306TestCircle();
    vDelay(3000);
}

