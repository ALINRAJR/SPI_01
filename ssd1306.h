
#ifndef SSD1306_H_
#define SSD1306_H_

/* Includes -----------------------------------------------------------------*/
//#include <stddef.h>
//#include <_ansi.h>

/* Private includes ----------------------------------------------------------*/
#include "ssd1306fonts.h"
#include "spi.h"
#include "gpio.h"

/* Private typedef -----------------------------------------------------------*/

// Enumeration for screen colors
typedef enum {
    Black = 0x00, // Black color, no pixel
    White = 0x01  // Pixel is set. Color depends on OLED
} SSD1306_COLOR;

typedef enum {
    SSD1306_OK = 0x00,
    SSD1306_ERR = 0x01  // Generic error.
} SSD1306_Error_t;

// Struct to store transformations
typedef struct {
    uint16_t CurrentX;
    uint16_t CurrentY;
    uint8_t Inverted;
    uint8_t Initialized;
    uint8_t DisplayOn;
} SSD1306_t;

typedef struct {
    uint8_t x;
    uint8_t y;
} SSD1306_VERTEX;

/* Private define ------------------------------------------------------------*/

// SSD1306 OLED height in pixels
#ifndef SSD1306_HEIGHT
#define SSD1306_HEIGHT          64
#endif

// SSD1306 width in pixels
#ifndef SSD1306_WIDTH
#define SSD1306_WIDTH           128
#endif

#ifndef SSD1306_BUFFER_SIZE
#define SSD1306_BUFFER_SIZE   SSD1306_WIDTH * SSD1306_HEIGHT / 8
#endif

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

// Procedure definitions
/**
  * @brief     Initialize the OLED screen
  * @return    No return value
  **/
void vSSD1306Initialize(void);
/**
  * @brief     Fill the whole screen of OLED with the given color
  * @param[in] color is the desired color which we select for the OLED screen color. here it is black
  * @return    No return value
  **/
void vSSD1306Fill(SSD1306_COLOR color);
/**
  * @brief      Write the screenbuffer with changed to the screen
  * @return    No return value
  **/
void vSSD1306UpdateScreen(void);
/**
  * @brief     Draw one pixel in the screenbuffer
  * @param[in] x is the x co-ordinate
  * @param[in] y is the y co-ordinate
  * @param[in] color is the Pixel color of the screen
  * @return    No return value
  **/
void vSSD1306DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color);
/**
  * @brief     Draw 1 char to the screen buffer
  * @param[in] FontDef is the font used for the character
  * @param[in] color is the choosen color in which character has to be drawn on screen
  * @return    No return value
  **/
char vSSD1306WriteChar(char ch, FontDef Font, SSD1306_COLOR color);
/**
  * @brief     Write full string to screenbuffer
  * @param[in] Font is the font type to write the string
  * @param[in] color is the selected color for string.
  * @return    No return value
  **/
char vSSD1306WriteString(char* str, FontDef Font, SSD1306_COLOR color);
/**
  * @brief     Set the position of cursor on the screen
  * @param[in] y is the position of cursor on the y co-ordinate.
  * @return    No return value
  **/
void vSSD1306SetCursor(uint8_t x, uint8_t y);
/**
  * @brief     Draw line by Bresenhem's algorithm on the screen
  * @param[in] x1 is the start position of line on the x co-ordinate.
  * @param[in] x2 is the last position of line on the x co-ordinate.
  * @param[in] y1 is the start position of line on the y co-ordinate.
  * @param[in] y2 is the last position of line on the y co-ordinate.
  * @param[in] color is the selected color to draw the line.
  * @return    No return value
  **/
void vSSD1306Line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
/**
  * @brief     Draw an Arc on the screen.Draw angle is beginning from 4 quart of trigonometric circle (3pi/2)
  * @param[in] y is the starting position of arc on the y co-ordinate.
  * @param[in] radius is the value of arc radius
  * @param[in] start_angle is the angle  at which arc should begin
  * @param[in] sweep is the angle covered by the arc
  * @param[in] color is the selected color in which the arc is drawn.
  * @return    No return value
  **/
void vSSD1306DrawArc(uint8_t x, uint8_t y, uint8_t radius, uint16_t start_angle, uint16_t sweep, SSD1306_COLOR color);
/**
  * @brief     Draw circle by Bresenhem's algorithm
  * @param[in] par_x is the position at x co-ordinate where to start the circle.
  * @param[in] par_y is the position at y co-ordinate where to start the circle.
  * @param[in] par_y is the color in which circle should be drawn.
  * @return    No return value
  **/
void SSD1306DrawCircle(uint8_t par_x, uint8_t par_y, uint8_t par_r, SSD1306_COLOR color);
/**
  * @brief     Draw polyline on the screen.
  * @return    No return value
  **/
void vSSD1306Polyline(const SSD1306_VERTEX *par_vertex, uint16_t par_size, SSD1306_COLOR color);
/**
  * @brief     Draw a rectangle on the screen.
  * @param[in] x1 is the start position of rectangle on the x coordinate.
  * @param[in] x2 is the last position of rectangle on the x coordinate.
  * @param[in] y1 is the start position of rectangle on the y coordinate.
  * @param[in] y2 is the last position of rectangle on the y coordinate.
  * @param[in] color is the selected color to draw the rectangle.
  * @return    No return value
  **/
void vSSD1306DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color);
/**
 * @brief Sets the contrast of the display.
 * @param[in] value contrast to set.
 * @note Contrast increases as the value increases.
 * @note RESET = 7Fh.
 */
void vSSD1306SetContrast(const uint8_t value);
/**
 * @brief Set Display ON/OFF.
 * @param[in] on 0 for OFF, any for ON.
 */
void vSSD1306SetDisplayOn(const uint8_t on);
/**
 * @brief Reads DisplayOn state.
 * @return  0: OFF.
 *          1: ON.
 */
uint8_t ssd1306_GetDisplayOn();

// Low-level procedures
/**
  * @brief     Resetting SSD1306 by setting the RESET PIN
  * @return    No return value
  **/
void vSSD1306Reset(void);
/**
  * @brief     Writing a byte into the command register
  * @param[in] byte value is the byte that has to be transferred to the command register of OLED
  * @return    No return value
  **/
void vSSD1306WriteCommand(uint8_t byte);
/**
  * @brief     Writes data into the SSD1306 OLED Data register
  * @param[in] buffer is the buffer register from which data has to be written
  * @param[in] buff_size is the  size of data bytes to be transferred.
  * @return    No return value
  **/
void SSD1306WriteData(uint8_t* buffer, size_t buff_size);
SSD1306_Error_t SSD1306FillBuffer(uint8_t* buf, uint32_t len);


#endif /* SSD1306_H_ */
