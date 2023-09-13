

/* Includes -----------------------------------------------------------------*/
#include <math.h>
#include <stdlib.h>
#include <string.h>  // For memcpy
#include <stdint.h>

/* Private includes ----------------------------------------------------------*/
#include "ssd1306.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

// Screenbuffer
static uint8_t SSD1306_Buffer[SSD1306_BUFFER_SIZE];

// Screen object
static SSD1306_t SSD1306;

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/**
  * @brief     Set a Delay
  * @param[in] count value can be set as desired for a convinient delay
  * @return    No return value
  **/
void vSSD1306delay(uint32_t count)
{
int i,j;
	for(i=0;i<0xA0;i++)
		for(j=0;j<count;j++);
}

/**
  * @brief     Resetting SSD1306 by setting the RESET PIN
  * @return    No return value
  **/
void vSSD1306Reset(void) {
    // CS = High (not selected)
	vSPISlaveDeSelect();
    // Reset the OLED
   vGpioClrPin(SSD1306_RESET_PORT,SSD1306_RESET_PIN);
   vSSD1306delay(10);
   vGpioSetPin(SSD1306_RESET_PORT,SSD1306_RESET_PIN);
   vSSD1306delay(10);
}

/**
  * @brief     Writing a byte into the command register
  * @param[in] byte value is the byte that has to be transferred to the command register of OLED
  * @return    No return value
  **/
void vSSD1306WriteCommand(uint8_t byte) {
	vSPISlaveSelect(); //OLED Select
	vGpioClrPin(SSD1306_DC_PORT, SSD1306_DC_PIN); // command
	ucSPITransfer(SSD1306_SPI_PORT,byte);
	vSPISlaveDeSelect(); // un-select OLED
    //Or deselect can be used by setting the CS_PIN pin and select can be used by clearing the CS_PIN  pin
}

/**
  * @brief     Writes data into the SSD1306 OLED Data register
  * @param[in] buffer is the buffer register from which data has to be written
  * @param[in] buff_size is the  size of data bytes to be transferred.
  * @return    No return value
  **/
void vSSD1306WriteData(uint8_t* buffer, size_t buff_size) {
	vSPISlaveSelect(); //OLED Select
	vGpioSetPin(SSD1306_DC_PORT, SSD1306_DC_PIN); // data
	while(buff_size>0)
	{
	ucSPITransfer(SSD1306_SPI_PORT,*buffer++);
	buff_size--;
	}
	vSPISlaveDeSelect(); // un-select OLED
}

/**
  * @brief     Fills the Screenbuffer with values from a given buffer of a fixed length
  * @return    status code
  **/
SSD1306_Error_t SSD1306_Error_tvSSD1306FillBuffer(uint8_t* buf, uint32_t len) {

	SSD1306_Error_t ret = SSD1306_ERR;
    if (len <= SSD1306_BUFFER_SIZE) {
        memcpy(SSD1306_Buffer,buf,len);
        ret = SSD1306_OK;
    }
    return ret;
}

/**
  * @brief     Initialize the OLED screen
  * @return    No return value
  **/
void vSSD1306Initialize(void) {
   /*step 1: set the the CS Pin and DC pin as OUTPUT*/
   vGpioSetDir(SSD1306_DC_PORT,SSD1306_DC_PIN ,OUTPUT);
   vGpioSetDir(SSD1306_CS_PORT,SSD1306_CS_PIN ,OUTPUT);

   /*step 2: Reset the OLED*/
   vSSD1306Reset();

   /* STEP 3:Wait for the screen to boot*/
    vSSD1306delay(100);

    /* STEP 3:Initialize the OLED*/
    vSSD1306SetDisplayOn(0); //display off

    vSSD1306WriteCommand(0x20); // Set Memory Addressing Mode
    vSSD1306WriteCommand(0x00); // 00b,Horizontal Addressing Mode;
    							// 01b,Vertical Addressing Mode;
                                // 10b,Page Addressing Mode (RESET);
                                // 11b,Invalid

    vSSD1306WriteCommand(0xB0); //Set Page Start Address for Page Addressing Mode,0-7

#ifdef SSD1306_MIRROR_VERT
    vSSD1306WriteCommand(0xC0); // Mirror vertically
#else
    vSSD1306WriteCommand(0xC8); //Set COM Output Scan Direction
#endif

    vSSD1306WriteCommand(0x00); //---set low column address
    vSSD1306WriteCommand(0x10); //---set high column address

    vSSD1306WriteCommand(0x40); //--set start line address - CHECK

    vSSD1306SetContrast(0xFF);

#ifdef SSD1306_MIRROR_HORIZ
    vSSD1306WriteCommand(0xA0); // Mirror horizontally
#else
    vSSD1306WriteCommand(0xA1); //--set segment re-map 0 to 127 - CHECK
#endif

#ifdef SSD1306_INVERSE_COLOR
    vSSD1306WriteCommand(0xA7); //--set inverse color
#else
    vSSD1306WriteCommand(0xA6); //--set normal color
#endif

    /* STEP 4:Set multiplex ratio.*/
#if (SSD1306_HEIGHT == 128)
    /* STEP 5:Found in the Luma Python lib for SH1106.*/
    vSSD1306WriteCommand(0xFF);
#else
    vSSD1306WriteCommand(0xA8); //--set multiplex ratio(1 to 64) - CHECK
#endif

#if (SSD1306_HEIGHT == 32)
    vSSD1306WriteCommand(0x1F); //
#elif (SSD1306_HEIGHT == 64)
    vSSD1306WriteCommand(0x3F); //
#elif (SSD1306_HEIGHT == 128)
    vSSD1306WriteCommand(0x3F); // Seems to work for 128px high displays too.
#else
#error "Only 32, 64, or 128 lines of height are supported!"
#endif

    vSSD1306WriteCommand(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content

    vSSD1306WriteCommand(0xD3); //-set display offset - CHECK
    vSSD1306WriteCommand(0x00); //-not offset

    vSSD1306WriteCommand(0xD5); //--set display clock divide ratio/oscillator frequency
    vSSD1306WriteCommand(0xF0); //--set divide ratio

    vSSD1306WriteCommand(0xD9); //--set pre-charge period
    vSSD1306WriteCommand(0x22); //

    vSSD1306WriteCommand(0xDA); //--set com pins hardware configuration - CHECK
#if (SSD1306_HEIGHT == 32)
    vSSD1306WriteCommand(0x02);
#elif (SSD1306_HEIGHT == 64)
    vSSD1306WriteCommand(0x12);
#elif (SSD1306_HEIGHT == 128)
    vSSD1306WriteCommand(0x12);
#else
#error "Only 32, 64, or 128 lines of height are supported!"
#endif

    vSSD1306WriteCommand(0xDB); //--set vcomh
    vSSD1306WriteCommand(0x20); //0x20,0.77xVcc

    vSSD1306WriteCommand(0x8D); //--set DC-DC enable
    vSSD1306WriteCommand(0x14); //
  vSSD1306SetDisplayOn(1); //--turn on SSD1306 panel

  /* STEP 6:Clear screen */
   vSSD1306Fill(Black);

   /* STEP 8:Flush buffer to screen*/
    vSSD1306UpdateScreen();

    /* STEP 9: Set default values for screen object*/
    SSD1306.CurrentX = 0;
    SSD1306.CurrentY = 0;

    SSD1306.Initialized = 1;
}

/**
  * @brief     Fill the whole screen of OLED with the given color
  * @param[in] color is the desired color which we select for the OLED screen color. here it is black
  * @return    No return value
  **/
void vSSD1306Fill(SSD1306_COLOR color) {
    /* Set memory */
    uint32_t i;

    for(i = 0; i < sizeof(SSD1306_Buffer); i++) {
        SSD1306_Buffer[i] = (color == Black) ? 0x00 : 0xFF;
    }
}

/**
  * @brief      Write the screenbuffer with changed to the screen
  * @return    No return value
  **/
void vSSD1306UpdateScreen(void) {
    // Write data to each page of RAM. Number of pages
    // depends on the screen height:
    //
    //  * 32px   ==  4 pages
    //  * 64px   ==  8 pages
    //  * 128px  ==  16 pages
    for(uint8_t i = 0; i < SSD1306_HEIGHT/8; i++) {
        vSSD1306WriteCommand(0xB0 + i); // Set the current RAM page address.
        vSSD1306WriteCommand(0x00);
        vSSD1306WriteCommand(0x10);
       vSSD1306WriteData(&SSD1306_Buffer[SSD1306_WIDTH*i],SSD1306_WIDTH);
    }
}

/**
  * @brief     Draw one pixel in the screenbuffer
  * @param[in] x is the x co-ordinate
  * @param[in] y is the y co-ordinate
  * @param[in] color is the Pixel color of the screen
  * @return    No return value
  **/
void vSSD1306DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color) {
    if(x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) {
      /*Don't write outside the buffer*/
        return;
    }

   /*Check if pixel should be inverted*/
    if(SSD1306.Inverted) {
        color = (SSD1306_COLOR)!color;
    }

    /*Draw in the right color*/
    if(color == White) {
        SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
    } else {
        SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
    }
}

/**
  * @brief     Draw 1 char to the screen buffer
  * @param[in] FontDef is the font used for the character
  * @param[in] color is the choosen color in which character has to be drawn on screen
  * @return    No return value
  **/
char vSSD1306WriteChar(char ch, FontDef Font, SSD1306_COLOR color) {
    uint32_t i, b, j;

    /*Check if character is valid*/
    if (ch < 32 || ch > 126)
        return 0;

    /*Check remaining space on current line*/
    if (SSD1306_WIDTH < (SSD1306.CurrentX + Font.FontWidth) ||
        SSD1306_HEIGHT < (SSD1306.CurrentY + Font.FontHeight))
    {
        // Not enough space on current line
        return 0;
    }

    // Use the font to write
    for(i = 0; i < Font.FontHeight; i++) {
        b = Font.data[(ch - 32) * Font.FontHeight + i];
        for(j = 0; j < Font.FontWidth; j++) {
            if((b << j) & 0x8000)  {
                vSSD1306DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR) color);
            } else {
                vSSD1306DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR)!color);
            }
        }
    }

    // The current space is now taken
    SSD1306.CurrentX += Font.FontWidth;

    // Return written char for validation
    return ch;
}

/**
  * @brief     Write full string to screenbuffer
  * @param[in] Font is the font type to write the string
  * @param[in] color is the selected color for string.
  * @return    No return value
  **/
char vSSD1306WriteString(char* str, FontDef Font, SSD1306_COLOR color) {
    // Write until null-byte
    while (*str) {
        if (vSSD1306WriteChar(*str, Font, color) != *str) {
            // Char could not be written
            return *str;
        }

        // Next char
        str++;
    }

    // Everything ok
    return *str;
}

/**
  * @brief     Set the position of cursor on the screen
  * @param[in] y is the position of cursor on the y co-ordinate.
  * @return    No return value
  **/
void vSSD1306SetCursor(uint8_t x, uint8_t y) {
    SSD1306.CurrentX = x;
    SSD1306.CurrentY = y;
}

/**
  * @brief     Draw line by Bresenhem's algorithm on the screen
  * @param[in] x1 is the start position of line on the x co-ordinate.
  * @param[in] x2 is the last position of line on the x co-ordinate.
  * @param[in] y1 is the start position of line on the y co-ordinate.
  * @param[in] y2 is the last position of line on the y co-ordinate.
  * @param[in] color is the selected color to draw the line.
  * @return    No return value
  **/
void vSSD1306Line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color) {
  int32_t deltaX = abs(x2 - x1);
  int32_t deltaY = abs(y2 - y1);
  int32_t signX = ((x1 < x2) ? 1 : -1);
  int32_t signY = ((y1 < y2) ? 1 : -1);
  int32_t error = deltaX - deltaY;
  int32_t error2;

  vSSD1306DrawPixel(x2, y2, color);
    while((x1 != x2) || (y1 != y2))
    {
    vSSD1306DrawPixel(x1, y1, color);
    error2 = error * 2;
    if(error2 > -deltaY)
    {
      error -= deltaY;
      x1 += signX;
    }
    else
    {
    /*nothing to do*/
    }

    if(error2 < deltaX)
    {
      error += deltaX;
      y1 += signY;
    }
    else
    {
    /*nothing to do*/
    }
  }
  return;
}
/**
  * @brief     Draw polyline on the screen.
  * @return    No return value
  **/
void vSSD1306Polyline(const SSD1306_VERTEX *par_vertex, uint16_t par_size, SSD1306_COLOR color) {
  uint16_t i;
  if(par_vertex != 0){
    for(i = 1; i < par_size; i++){
      vSSD1306Line(par_vertex[i - 1].x, par_vertex[i - 1].y, par_vertex[i].x, par_vertex[i].y, color);
    }
  }
  else
  {
    /*nothing to do*/
  }
  return;
}
/*Convert Degrees to Radians*/
static float ssd1306_DegToRad(float par_deg) {
    return par_deg * 3.14 / 180.0;
}
/*Normalize degree to [0;360]*/
static uint16_t ssd1306_NormalizeTo0_360(uint16_t par_deg) {
  uint16_t loc_angle;
  if(par_deg <= 360)
  {
    loc_angle = par_deg;
  }
  else
  {
    loc_angle = par_deg % 360;
    loc_angle = ((par_deg != 0)?par_deg:360);
  }
  return loc_angle;
}

/**
  * @brief     Draw an Arc on the screen.Draw angle is beginning from 4 quart of trigonometric circle (3pi/2)
  * @param[in] y is the starting position of arc on the y co-ordinate.
  * @param[in] radius is the value of arc radius
  * @param[in] start_angle is the angle  at which arc should begin
  * @param[in] sweep is the angle covered by the arc
  * @param[in] color is the selected color in which the arc is drawn.
  * @return    No return value
  **/
void vSSD1306DrawArc(uint8_t x, uint8_t y, uint8_t radius, uint16_t start_angle, uint16_t sweep, SSD1306_COLOR color) {
    #define CIRCLE_APPROXIMATION_SEGMENTS 36
    float approx_degree;
    uint32_t approx_segments;
    uint8_t xp1,xp2;
    uint8_t yp1,yp2;
    uint32_t count = 0;
    uint32_t loc_sweep = 0;
    float rad;

    loc_sweep = ssd1306_NormalizeTo0_360(sweep);

    count = (ssd1306_NormalizeTo0_360(start_angle) * CIRCLE_APPROXIMATION_SEGMENTS) / 360;
    approx_segments = (loc_sweep * CIRCLE_APPROXIMATION_SEGMENTS) / 360;
    approx_degree = loc_sweep / (float)approx_segments;
    while(count < approx_segments)
    {
        rad = ssd1306_DegToRad(count*approx_degree);
        xp1 = x + (int8_t)(sin(rad)*radius);
        yp1 = y + (int8_t)(cos(rad)*radius);
        count++;
        if(count != approx_segments)
        {
            rad = ssd1306_DegToRad(count*approx_degree);
        }
        else
        {
            rad = ssd1306_DegToRad(loc_sweep);
        }
        xp2 = x + (int8_t)(sin(rad)*radius);
        yp2 = y + (int8_t)(cos(rad)*radius);
        vSSD1306Line(xp1,yp1,xp2,yp2,color);
    }

    return;
}
/**
  * @brief     Draw circle by Bresenhem's algorithm
  * @param[in] par_x is the position at x co-ordinate where to start the circle.
  * @param[in] par_y is the position at y co-ordinate where to start the circle.
  * @param[in] par_y is the color in which circle should be drawn.
  * @return    No return value
  **/
void vSSD1306DrawCircle(uint8_t par_x,uint8_t par_y,uint8_t par_r,SSD1306_COLOR par_color) {
  int32_t x = -par_r;
  int32_t y = 0;
  int32_t err = 2 - 2 * par_r;
  int32_t e2;

  if (par_x >= SSD1306_WIDTH || par_y >= SSD1306_HEIGHT) {
    return;
  }

    do {
      vSSD1306DrawPixel(par_x - x, par_y + y, par_color);
      vSSD1306DrawPixel(par_x + x, par_y + y, par_color);
      vSSD1306DrawPixel(par_x + x, par_y - y, par_color);
      vSSD1306DrawPixel(par_x - x, par_y - y, par_color);
        e2 = err;
        if (e2 <= y) {
            y++;
            err = err + (y * 2 + 1);
            if(-x == y && e2 <= x) {
              e2 = 0;
            }
            else
            {
              /*nothing to do*/
            }
        }
        else
        {
          /*nothing to do*/
        }
        if(e2 > x) {
          x++;
          err = err + (x * 2 + 1);
        }
        else
        {
          /*nothing to do*/
        }
    } while(x <= 0);

    return;
}

/**
  * @brief     Draw a rectangle on the screen.
  * @param[in] x1 is the start position of rectangle on the x coordinate.
  * @param[in] x2 is the last position of rectangle on the x coordinate.
  * @param[in] y1 is the start position of rectangle on the y coordinate.
  * @param[in] y2 is the last position of rectangle on the y coordinate.
  * @param[in] color is the selected color to draw the rectangle.
  * @return    No return value
  **/
void vSSD1306DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color) {
  vSSD1306Line(x1,y1,x2,y1,color);
  vSSD1306Line(x2,y1,x2,y2,color);
  vSSD1306Line(x2,y2,x1,y2,color);
  vSSD1306Line(x1,y2,x1,y1,color);

  return;
}
 /**
 * @brief     Sets the contrast of the display.
 * @param[in] value contrast to set.
 * @note      Contrast increases as the value increases.
 * @note      RESET = 7Fh.
 * @return    No return value
 **/
void vSSD1306SetContrast(const uint8_t value) {
    const uint8_t kSetContrastControlRegister = 0x81;
    vSSD1306WriteCommand(kSetContrastControlRegister);
    vSSD1306WriteCommand(value);
}
/**
 * @brief Set Display ON/OFF.
 * @param[in] on 0 for OFF, any for ON.
 * @return    No return value
 **/

void vSSD1306SetDisplayOn(const uint8_t on) {
    uint8_t value;
    if (on) {
        value = 0xAF;   // Display on
        SSD1306.DisplayOn = 1;
    } else {
        value = 0xAE;   // Display off
        SSD1306.DisplayOn = 0;
    }
    vSSD1306WriteCommand(value);
}

uint8_t ssd1306_GetDisplayOn() {
    return SSD1306.DisplayOn;
}
