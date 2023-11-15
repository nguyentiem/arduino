#include "Adafruit_GFX.h"    // Core graphics library
#include "MCUFRIEND_kbv.h"   // Hardware-specific library
#include "TouchScreen.h" // only when you want to use touch screen
#include "Fonts/FreeSans9pt7b.h"    // when you want other fonts
#include "Fonts/FreeSans12pt7b.h" // when you want other fonts
#include "Fonts/FreeSerif12pt7b.h" // when you want other fonts
#include "FreeDefaultFonts.h" // when you want other fonts
#include "SPI.h"  // using sdcard for display bitmap image
#include "SD.h"  

MCUFRIEND_kbv tft;

#define BLACK 0x0000
#define NAVY 0x000F
#define DARKGREEN 0x03E0
#define DARKCYAN 0x03EF
#define MAROON 0x7800
#define PURPLE 0x780F
#define OLIVE 0x7BE0
#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEF
#define BLUE 0x001F
#define GREEN 0x07E0
#define CYAN 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define ORANGE 0xFD20
#define GREENYELLOW 0xAFE5
#define PINK 0xF81F
#include "Ard_Logo.h" 
void showmsgXY(int x, int y, int sz, const GFXfont *f, const char *msg)
{
 int16_t x1, y1;
 uint16_t wid, ht;
 tft.setFont(f);
 tft.setCursor(x, y);
 tft.setTextSize(sz);
 tft.println(msg);
}
uint8_t r = 255, g = 255, b = 255;
uint16_t color;
void setup()
{
 Serial.begin(9600);
 uint16_t ID = tft.readID();
 tft.begin(ID);
 tft.invertDisplay(true);
 tft.setRotation(1);
}
void loop(void)
{
 tft.invertDisplay(true);
 tft.fillScreen(WHITE);
 tft.drawRGBBitmap(100, 50, test, 350, 200);
delay(1000);
 tft.setTextSize(2);
 for (int j = 0; j < 20; j++) {
   color = tft.color565(r -= 12, g -= 12, b -= 12);
   tft.setTextColor(color);
   showmsgXY(95, 280, 1, &FreeSans12pt7b, "ELECTROPEAK PRESENTS");
   delay(20);
 }
delay(1000);
 for (int i = 0; i < 480; i++) {
   tft.vertScroll(0, 480, i);
   tft.drawFastVLine(i, 0, 320, 0xffff); // vertical line
   delay(5);}
   while (1);
 }
