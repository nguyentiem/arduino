#include <UTFTGLUE.h>              //use GLUE class and constructor
UTFTGLUE myGLCD(0, A2, A1, A3, A4, A0); //all dummy ar
int W, H ;
int hx, hy, ax,ay, gx,gy, arm_x,army;  
void draw_heard() {
  myGLCD.clrScr();
 
  myGLCD.setColor(0, 255, 255);
  myGLCD.print("HEARD", 5, 15);
  
}

void draw_sin() {
  myGLCD.clrScr();

  myGLCD.setColor(0, 255, 255);
  myGLCD.print("Sin", 5, 15);
  for (int i = 1; i < 478; i++)
  {
    myGLCD.drawPixel(i, 159 + (sin(((i * 1.13) * 3.14) / 180) * 95)); // bat dau tu dong 159 len xuong
  }

}

void draw_cos() {
  myGLCD.setColor(255, 0, 0);
  myGLCD.print("Cos", 5, 27);
  for (int i = 1; i < 478; i++)
  {
    myGLCD.drawPixel(i, 159 + (cos(((i * 1.13) * 3.14) / 180) * 95));
  }
}



void draw_intro() {
  myGLCD.clrScr();

  myGLCD.setColor(255, 0, 0); //
  myGLCD.fillRect(0, 0, 479, 13);
  myGLCD.setColor(64, 64, 64);
  myGLCD.fillRect(0, 306, 479, 319);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.print("* đồ án tốt nghiệp *", CENTER, 1);
  myGLCD.setBackColor(64, 64, 64);
  myGLCD.setColor(255, 255, 0);
  myGLCD.print("design by Nguyen Tiem", CENTER, 307);

  myGLCD.setColor(0, 0, 255);
  myGLCD.drawRect(0, 14, 479, 305);

  // Draw crosshairs
  myGLCD.setColor(0, 0, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawLine(239, 15, 239, 304);
  myGLCD.drawLine(1, 159, 478, 159);
  for (int i = 9; i < 470; i += 10)
    myGLCD.drawLine(i, 157, i, 161);
  for (int i = 19; i < 220; i += 10)
    myGLCD.drawLine(237, i, 241, i);

}
void setup()
{
 
   
  randomSeed(analogRead(0));

  //set up
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  W = myGLCD.width();
  H = myGLCD.height();
}

void loop()
{
  int buf[478];
  int x, x2;
  int y, y2;
  int r;
  draw_sin();
  delay(2000);
}
