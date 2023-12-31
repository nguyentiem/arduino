#include <Adafruit_SSD1306.h>
 
#define OLED_Address 0x3C
Adafruit_SSD1306 oled(1);

int x=0;
int lastx=0;
int lasty=0;
int LastTime=0;
bool BPMTiming=false;
bool BeatComplete=false;
int BPM=0;

#define UpperThreshold 550
#define LowerThreshold 500

void setup() {
  oled.begin(SSD1306_SWITCHCAPVCC, OLED_Address);
  oled.clearDisplay();
  Serial.begin(9600);
  oled.setTextSize(2);
}


void loop() 
{
  if(x>127)  
  {
    oled.clearDisplay();
    x=0;
    lastx=x;
  }

  int value=analogRead(0);
  oled.setTextColor(WHITE);
  Serial.println(value/8);
  int y=(value/8)-63+16 ;
  oled.writeLine(lastx,lasty,x,y,WHITE);
   // oled.writeLine(0,0,128,64,WHITE);
  lasty=y;
  lastx=x;
  // calc bpm

  if(value>UpperThreshold)
  {
    if(BeatComplete)
    {
      BPM=millis()-LastTime;
      BPM=int(60/(float(BPM)/1000));
      BPMTiming=false;
      BeatComplete=false;
    }
    if(BPMTiming==false)
    {
      LastTime=millis();
      BPMTiming=true;
    }
  }
  if((value<LowerThreshold)&(BPMTiming))
    BeatComplete=true;
    // display bpm
//  oled.writeFillRect(0,50,128,16,BLACK);
  oled.setCursor(5,5);
  oled.print(BPM);
  oled.print(" BPM");
  oled.display();
  x++;
}
