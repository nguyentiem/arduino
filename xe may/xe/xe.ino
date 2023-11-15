

#include <UTFT.h>
#include <SPI.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
int  hour = 0 , day = 1 , month = 1, year = 2020, second = 0 , minute = 0;
int speed = 50, alt = 0,  pre = 1, tem = 0;
float lat = 0.0, lon = 0.0;
//char da[32];
//char tim[32];
int x = 40, y = 40;
int r = 35 ;
int xc = 80;
int prespeed = 0;
int m = 300;
//extern unsigned int mylinh[0xEA6];
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t Font[];
// Declare an instance of the class
UTFT myGLCD(ST7735, 11, 13, 10, 9, 8); // Remember to change the model parameter to suit your display module!

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{

  if (!d.isValid())
  {
    Serial.print(F("********** "));

  }
  else
  {
    // String dat = String(d.month())+String(":")+String( d.day())+String(":")+String(d.year());
    day = d.day();
    month = d.month();
    year = d.year();
   // sprintf(da, "%02d/%02d/%02d ", d.month(), d.day(), d.year());

  }

  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    hour =  t.hour()+7;
    minute = t.minute();
    second =  t.second();
   // sprintf(tim, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());

  }


  smartDelay(100);

}
void getGPS() {
  Serial.println(gps.location.lat());
  Serial.println(gps.location.lng());
  lat = gps.location.lat();
  lon = gps.location.lng();
  printDateTime(gps.date, gps.time);
  alt = gps.altitude.meters();

  speed = gps.speed.kmph();

}


void draw() {
  myGLCD.setContrast(64);
  myGLCD.setColor(0, 255, 255);
  myGLCD.drawLine(0, 115, 128, 115);

  myGLCD.setColor(255, 255, 0);
  myGLCD.print("Nguyen Tiem", CENTER, 116);
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawLine(x - (r * cos((-60)*PI / 180)), y - (r * sin((-60)*PI / 180)), x, y);
  myGLCD.drawLine(x - (r * cos((240)*PI / 180)), y - (r * sin((240)*PI / 180)), x, y);
  // myGLCD.setColor(255,0,0);
  for (int i = -59; i < 240 ; i++) {
    if ((i + 60) % 30 == 0) {
      myGLCD.setColor(0, 0, 255);
      myGLCD.drawLine(x - ((r + 2)*cos((i)*PI / 180)), y - ((r + 2)*sin((i)*PI / 180)), x - ((r - 5)*cos((i)*PI / 180)), y - ((r - 5)*sin((i)*PI / 180)));
      // myGLCD.drawLine(x-((r+1)*cos((i)*PI/180)), y - (r*sin((i)*PI/180)), x-((r-5)*cos((i)*PI/180)),y - ((r-5)*sin((i)*PI/180)));
    } else {
      myGLCD.setColor(255, 0, 0);
      myGLCD.drawPixel(x - (r * cos(i * PI / 180)), y - (r * sin(i * PI / 180)));
      myGLCD.drawPixel(x - ((r + 1)*cos(i * PI / 180)), y - ((r + 1)*sin(i * PI / 180)));
      myGLCD.drawPixel(x - ((r + 2)*cos(i * PI / 180)), y - ((r + 2)*sin(i * PI / 180)));
    }
  }

  myGLCD.setColor(255, 200, 100);
  myGLCD.print("tem: ", xc, 5);
  myGLCD.print("alt: ",  xc, 25);
  

  myGLCD.print("time: ",  0, 80);
  myGLCD.print("date: ",  0, 95);

  myGLCD.setColor(255, 255, 255);
  myGLCD.print("speed",  21, 25);
  myGLCD.setColor(0, 255, 0);
  for(int i =0 ; i<100; i++){
    speed = i; 
     myGLCD.setColor(0, 255, 255);
  myGLCD.setFont(BigFont);
  myGLCD.printNumI(speed, 25, 60,1,0);
  myGLCD.setFont(SmallFont);
  
      myGLCD.setColor(255, 255, 255);
      myGLCD.print("speed",  21, 25);
      myGLCD.setColor(0, 0, 0);
      myGLCD.drawLine(x - ((r - 10)*cos((prespeed * 3 - 60)*PI / 180)), y - ((r - 10)*sin((prespeed * 3 - 60)*PI / 180)), x, y);
      myGLCD.setColor(0, 255, 0);
      myGLCD.drawLine(x - ((r - 10)*cos((speed* 3 - 60)*PI / 180)), y - ((r - 10)*sin((speed * 3 - 60)*PI / 180)), x, y);
      delay(10);
         prespeed = speed;
    }


}
void capnhat() {
  //smartDelay(2000);
  getGPS();
  myGLCD.setColor(0, 255, 255);
  myGLCD.setFont(BigFont);
  
  myGLCD.printNumI(speed, 25, 60,2,1);
  Serial.println(speed);
  myGLCD.setFont(SmallFont);
  //date
   myGLCD.print(String(hour)+String(":")+String(minute)+String(":")+String(second), 40, 80);
  //time
  myGLCD.print(String(day)+String("/")+String(month)+String("/")+String(year), 40, 95);
  //alt
  myGLCD.print(String(alt), xc, 45);
  
  
//  if (prespeed > speed) {
//    for (int i =prespeed ; i <=speed ; i-- ) {
//      myGLCD.setColor(255, 255, 255);
//      myGLCD.print("speed",  21, 25);
//      myGLCD.setColor(0, 0, 0);
//      myGLCD.drawLine(x - ((r - 10)*cos((i * 3 - 60)*PI / 180)), y - ((r - 10)*sin((i * 3 - 60)*PI / 180)), x, y);
//      myGLCD.setColor(0, 255, 0);
//      //delay(10); 
//      myGLCD.drawLine(x - ((r - 10)*cos((i * 3 - 60)*PI / 180)), y - ((r - 10)*sin((i * 3 - 60)*PI / 180)), x, y);
//      //delay(10); 
//      
//    }
// 
//
//  } else {
//    for (int i = prespeed; i <=speed; i++ ) {
//      myGLCD.setColor(255, 255, 255);
//      myGLCD.print("speed",  21, 25);
//      myGLCD.setColor(0, 0, 0);
//      myGLCD.drawLine(x - ((r - 10)*cos((i * 3 - 60)*PI / 180)), y - ((r - 10)*sin((i * 3 - 60)*PI / 180)), x, y);
//      myGLCD.setColor(0, 255, 0);delay(10);
//      myGLCD.drawLine(x - ((r - 10)*cos((i * 3 - 60)*PI / 180)), y - ((r - 10)*sin((i * 3 - 60)*PI / 180)), x, y);
//      //
//    }
//   
//  }
   myGLCD.setColor(255, 255, 255);
      myGLCD.print("speed",  21, 25);
      myGLCD.setColor(0, 0, 0);
      myGLCD.drawLine(x - ((r - 10)*cos((prespeed * 3 - 60)*PI / 180)), y - ((r - 10)*sin((prespeed * 3 - 60)*PI / 180)), x, y);
      myGLCD.setColor(0, 255, 0);
      //delay(10); 
      myGLCD.drawLine(x - ((r - 10)*cos((speed* 3 - 60)*PI / 180)), y - ((r - 10)*sin((speed  * 3 - 60)*PI / 180)), x, y);
      
  prespeed = speed;
}

void setup()
{

  Serial.begin(9600);
  ss.begin(GPSBaud);
  randomSeed(0);
  myGLCD.InitLCD(PORTRAIT);
  myGLCD.setFont(SmallFont);

  myGLCD.clrScr();
  draw();
   
}

void loop()
{

  capnhat();


}
