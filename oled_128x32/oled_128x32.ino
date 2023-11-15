#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); //  

 void setup(void) {
   u8g2.begin();
}

  void loop(void) {
   u8g2.clearBuffer();          // clear the internal memory
   u8g2.setFont(u8g2_font_6x10_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(8,29,"XIN CHAO"); // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display
   delay(1000);

   u8g2.clearBuffer();         // clear the internal memory
   u8g2.setFont(u8g2_font_6x10_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(7,29,"TOI LA");  // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display
   delay(800);

   u8g2.clearBuffer();         // clear the internal memory
   u8g2.setFont(u8g2_font_6x10_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(8,29,"NGUYEN ");  // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display
   delay(1000);

     u8g2.clearBuffer();         // clear the internal memory
   u8g2.setFont(u8g2_font_6x10_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(8,29,"  TIEM  ");  // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display
   delay(1000);

   u8g2.clearBuffer();         // clear the internal memory
   u8g2.setFont(u8g2_font_6x10_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(8,29," HUST");  // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display
   
   delay(1000);

   
}
