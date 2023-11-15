#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"
#include <stdint.h>
#include "TouchScreen.h" // only when you want to use touch screen 
//#include "bitmap_mono.h" // when you want to display a bitmap image from library
//#include "bitmap_RGB.h" // when you want to display a bitmap image from library
#include "Fonts/FreeSans9pt7b.h"    // when you want other fonts
#include "Fonts/FreeSans12pt7b.h" // when you want other fonts
#include "Fonts/FreeSerif12pt7b.h" // when you want other fonts
#include "FreeDefaultFonts.h" // when you want other fonts 
#include "SPI.h"  // using sdcard for display bitmap image
#include "SD.h"
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
#define GREEN 0x07E0 // hong tim 
#define CYAN 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF  // den 
#define ORANGE 0xFD20
#define GREENYELLOW 0xAFE5
#define PINK 0xF81F
#define YP A2  
#define XM A3 
#define YM 8   
#define XP 9   
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);



 
///////////////////////////// khai bao bien /////////////////
MCUFRIEND_kbv tft;
uint16_t w, h;
uint16_t ox = 0, oy = 0;
int ave = 0, avec = 0, avet = 0;


////////////////////////////ve duongt trung binh////////////////////////////////////
void aveg(void)
{
  int z = 0;
  Serial.println(ave);
  Serial.println(avec);
  avet = ave / avec;
  Serial.println(avet);
  avet = avet * 32;
  for (int i = 0; i < 24; i++) {
    for (uint16_t a = 0; a < 3; a++) {
      tft.drawLine(avet + a, z, avet + a, z + 10, 0xFB21);
    } // thick
    for (uint16_t a = 0; a < 2; a++) {
      tft.drawLine(avet - a, z, avet - a, z + 10, 0xFB21);
    } delay(100); z = z + 20;
  }
}

///////////////////////////ve dau cham ///////////////////////////////////////
void dchart_10x10(uint16_t nx, uint16_t ny) {
  ave += nx; avec++; nx = nx * 32; ny = ny * 48;
  tft.drawCircle(nx, ny, 10, 0x0517);
  tft.drawCircle(nx, ny, 9, 0x0517);
  tft.fillCircle(nx, ny, 7, 0x0517);
  delay (100); 
  ox = nx; oy = ny;
}

///////////////////////////////ve do thi////////////////////////////////////////
void dotchart_10x10(uint16_t nx, uint16_t ny) {
  ave += nx; avec++; // bien tinh trung binh 
  //nx = nx * 32; ny = ny * 48;       // ti le phong 
  int plus = 0;
  float fplus = 0; 
  int sign = 0; 
  int y = 0, x = 0; y = oy; x = ox;
  float xmines, ymines; xmines = nx - ox; ymines = ny - oy;
  if (ox > nx)
  { 
    xmines = ox - nx;
    sign = 1;
  }
  else
    sign = 0;
    /////////////// to nen /////////////
//  for (int a = 0; a < (ny - oy); a++)
//  {
//    fplus += xmines / ymines;
//    plus = fplus;
//    if (sign == 1)
//      tft.drawFastHLine(0, y, x - plus, 0xBFDF);
//    else
//      tft.drawFastHLine(0, y, x + plus, 0xBFDF);
//    y++;
//    delay(5);
//  }

      //// ve duong /////
      
//  for (uint16_t a = 0; a < 2; a++) {
//    tft.drawLine(ox + a, oy, nx + a, ny, 0x01E8);
//  } // thick
  //for (uint16_t a = 0; a < 2; a++) {
    tft.drawLine(ox, oy , nx, ny , 0x01E8);
 // }
  ox = nx;
  oy = ny;
}



void draw_heard(uint16_t nx, uint16_t ny){
  
  
  
  }



////////////////////////////////////////////////////////////////////
void setup() {
  tft.reset();              /// reset LCD
  Serial.begin(9600);
  uint16_t ID = tft.readID();  /// lay ID va dat Id vao bien (LCD )
  tft.begin(ID);
  w = tft.width(); //int16_t width(void);
  h = tft.height(); //int16_t height(void);
  tft.invertDisplay(true);
  tft.fillScreen(0x0000);
}


void loop() {
   // a point object holds x y and z coordinates
  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
     Serial.print("X = "); Serial.print(p.x);
     Serial.print("\tY = "); Serial.print(p.y);
     Serial.print("\tPressure = "); Serial.println(p.z);
     tft.drawPixel(p.x,p.y,0xFB21);
  }
//  dotchart_10x10(3, 0);
//  dotchart_10x10(2, 1);
//  dotchart_10x10(4, 2);
//  dotchart_10x10(4, 3);
//  dotchart_10x10(5, 4);
//  dotchart_10x10(3, 5);
//  dotchart_10x10(6, 6);
//  dotchart_10x10(7, 7);
//  dotchart_10x10(9, 8);
//  dotchart_10x10(8, 9);
//  dotchart_10x10(10, 10);
//  dchart_10x10(3, 0);
//  dchart_10x10(2, 1);
//  dchart_10x10(4, 2);
//  dchart_10x10(4, 3);
//  dchart_10x10(5, 4);
//  dchart_10x10(3, 5);
//  dchart_10x10(6, 6);
//  dchart_10x10(7, 7);
//  dchart_10x10(9, 8);
//  dchart_10x10(8, 9);
//  dchart_10x10(10, 10);
//  tft.setRotation(0);
//  tft.setTextSize(2);
//  tft.setTextColor(0x01E8);
//  tft.setCursor(20, 20);
//  tft.print("Average");
//  int dl = 20;
//  for (int i = 0; i < 6; i++) {
//    for (uint16_t a = 0; a < 3; a++) {
//      tft.drawLine(dl, 40 + a, dl + 10, 40 + a, 0xFB21);
//    }
//    dl += 16;
//  }
//  tft.setRotation(0);
//  aveg();
 
}
