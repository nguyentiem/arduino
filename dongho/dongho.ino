
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h" 




const char *ssid     = "Nguyen Tiem";
const char *password = "58642110";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

//Week Days
String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
SSD1306Wire  display(0x3c, 5, 4);




int screenW = 128;
int screenH = 64;
int clockCenterX = screenW/2;
int clockCenterY = ((screenH-16)/2)+8;   // top yellow part is 16 px height
int clockRadius = 32;
int currentHour ; 
int currentMinute ; 
int currentSecond ;
String weekDay ;
int monthDay ;
int currentMonth ;
String currentMonthName ;
int currentYear ;
int n = 0 ;
void analogClockFrame( ) {
  display.clear();
  display.drawCircle(clockCenterX , clockCenterY ,2);
  
  for( int z=0; z < 360;z= z + 30 ){
  //Begin at 0° and stop at 360°
    float angle = z ;
    angle = ( angle / 57.29577951 ) ; //Convert degrees to radians
    int x2 = ( clockCenterX + ( sin(angle) * clockRadius ) );
    int y2 = ( clockCenterY - ( cos(angle) * clockRadius ) );
    int x3 = ( clockCenterX + ( sin(angle) * ( clockRadius - ( clockRadius / 8 ) ) ) );
    int y3 = ( clockCenterY - ( cos(angle) * ( clockRadius - ( clockRadius / 8 ) ) ) );
    display.drawLine( x2 , y2  , x3  , y3);
  }
 for( int z=90; z <= 360;z= z + 90 ){
  //Begin at 0° and stop at 360°
  float angle ;
  float rad;
  if(z==90){
     angle = z-15 ;
     rad= clockRadius-8;
    }
    if(z ==180){
     angle = z+8 ;
     rad= clockRadius-13;
    }
    if(z==270){
     angle = z+15 ;
     rad= clockRadius-6;
    }
    if(z ==360){
     angle = z-10 ;
     rad= clockRadius-2;
    }
  
 
    
    angle = ( angle / 57.29577951 ) ; //Convert degrees to radians
    int x_2 = ( clockCenterX + ( sin(angle) * rad ) );
    int y_2 = ( clockCenterY - ( cos(angle) * rad ) );
    
  display.setFont(ArialMT_Plain_10);
  display.drawString(x_2, y_2, String(z/30));
  }
  // display second hand
  float angle = currentSecond * 6 ;
  angle = ( angle / 57.29577951 ) ; 
  int x3 = ( clockCenterX + ( sin(angle) * ( clockRadius - ( clockRadius / 5 ) ) ) );
  int y3 = ( clockCenterY - ( cos(angle) * ( clockRadius - ( clockRadius / 5 ) ) ) );
  display.drawLine( clockCenterX  , clockCenterY  , x3  , y3 );
  //
  // display minute hand
  angle = currentMinute * 6 ;
  angle = ( angle / 57.29577951 ) ; //Convert degrees to radians
  x3 = ( clockCenterX + ( sin(angle) * ( clockRadius - ( clockRadius / 4 ) ) ) );
  y3 = ( clockCenterY - ( cos(angle) * ( clockRadius - ( clockRadius / 4 ) ) ) );
  display.drawLine( clockCenterX  , clockCenterY  , x3  , y3 );
 
  // display hour hand
  angle = currentHour* 30 + int( (currentMinute / 12 ) * 6 )   ;
  angle = ( angle / 57.29577951 ) ; //Convert degrees to radians
  x3 = ( clockCenterX + ( sin(angle) * ( clockRadius - ( clockRadius / 2 ) ) ) );
  y3 = ( clockCenterY - ( cos(angle) * ( clockRadius - ( clockRadius / 2 ) ) ) );
  display.drawLine( clockCenterX  , clockCenterY , x3  , y3 );

  switch((currentSecond)%6){
    case 0:
   display.setFont(ArialMT_Plain_10);
    display.drawString(10,2 , "T");
    
    display.drawString(115,2 , "H");
    
    
    break;
   
    case 1:
     display.setFont(ArialMT_Plain_10);
  display.drawString(10,2 , "T");
    display.drawString(10,16 , "I");
   
    display.drawString(115,2 , "H");
    display.drawString(115,16 , "U");
    
    
   
     break;
    case 2:
     display.setFont(ArialMT_Plain_10);
    display.drawString(10,2 , "T");
    display.drawString(10,16 , "I");
    display.drawString(10,30 , "E");
  
    display.drawString(115,2 , "H");
    display.drawString(115,16 , "U");
    display.drawString(115,30 , "S");
    
    
     break;
    case 3:
     display.setFont(ArialMT_Plain_10);
    display.drawString(10,2 , "T");
    display.drawString(10,16 , "I");
    display.drawString(10,30 , "E");
    display.drawString(10,44 , "M");
    display.drawString(115,2 , "H");
    display.drawString(115,16 , "U");
    display.drawString(115,30 , "S");
    display.drawString(115,44 , "T");
     break;
    default:
     display.setFont(ArialMT_Plain_10);
    display.drawString(10,2 , "T");
    display.drawString(10,16 , "I");
    display.drawString(10,30 , "E");
    display.drawString(10,44 , "M");
    display.drawString(115,2 , "H");
    display.drawString(115,16 , "U");
    display.drawString(115,30 , "S");
    display.drawString(115,44 , "T");
    break;
    
    }

  
  display.display();

}

void digitalClockFrame( int16_t x, int16_t y) {
   display.clear();
   
  String currentDate =String(monthDay) + "-" + String(currentMonth) + "-" +String(currentYear) ;
  String timenow = String(currentHour)+":"+String(currentMinute)+":"+String(currentSecond);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  
    display.setFont(ArialMT_Plain_10);
  display.drawString(clockCenterX + x, 0, String(weekDay) );
   display.setFont(ArialMT_Plain_16);
  display.drawString(clockCenterX + x , 15, currentDate );
  display.setFont(ArialMT_Plain_24);
  display.drawString(clockCenterX + x , clockCenterY + y, timenow );
  display.display();
 
  
}


void setup() {
  
  Serial.begin(115200);
  
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("connected");
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
    timeClient.begin();
  timeClient.setTimeOffset(25200);
}

void loop() {

  timeClient.update();
 unsigned long epochTime = timeClient.getEpochTime();
 currentHour = timeClient.getHours();
 currentMinute = timeClient.getMinutes();
 currentSecond = timeClient.getSeconds();
 weekDay = weekDays[timeClient.getDay()];
  struct tm *ptm = gmtime ((time_t *)&epochTime); 
   monthDay = ptm->tm_mday;
   currentMonth = ptm->tm_mon+1;
   currentMonthName = months[currentMonth-1];
   currentYear = ptm->tm_year+1900;
  
     if(n%2) {
        analogClockFrame( ) ;
    
    }else{
       digitalClockFrame(0,0);
      }
      
    
 
  
   
  
  
}
