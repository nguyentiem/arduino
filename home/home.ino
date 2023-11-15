
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"
//#include <Servo.h>
int caythong = 15; 
int phongkhach = 2; 
int san =16; 
int garaR = 14; 
int garaB =13; 
int garaG =12; 
bool fls=0,fct=0,fr=0,fb=0,fg=0,fk=0;
int lenh =0; 
//Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
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
int pos = 0;    // variable to store the servo position
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

void batphongkhach(){
   digitalWrite(phongkhach, LOW);
  }
void tatphongkhach(){
   digitalWrite(phongkhach,HIGH );
  }

void batsan(){
   digitalWrite(san, LOW);
  }
void tatsan(){
   digitalWrite(san, HIGH);
  }
    
void batcaythong(){
    digitalWrite(caythong, LOW);   // turn the LED on (HIGH is the voltage level)
                     // wait for a second
  }
  void tatcaythong(){
    digitalWrite(caythong, HIGH);   // turn the LED on (HIGH is the voltage level)
                   // wait for a second
  }

void batG(int a){
   analogWrite(garaG, a);
  }
void tatG(){
   digitalWrite(garaG, LOW);
  }
    
void batR(int a){
    analogWrite(garaR, a);
  }
  void tatR(){
    digitalWrite(garaR, LOW);   // turn the LED on (HIGH is the voltage level)
                   // wait for a second
  } 
void batB(int a){
   analogWrite(garaB, a);
  }
void tatB(){
   digitalWrite(garaB, LOW);
  }
  
void rst(){
  tatG();tatB();tatR();
  tatphongkhach();
  tatsan();
  tatcaythong();
  }
  
void setup() {
pinMode(caythong, OUTPUT);
pinMode(phongkhach, OUTPUT);
pinMode(garaR, OUTPUT);
pinMode(garaB, OUTPUT);
pinMode(garaG, OUTPUT);
pinMode(san, OUTPUT);
rst(); 
 //myservo.attach(9);  // attaches the servo on pin 9 to the servo object
//  for (pos = 145; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(30cc);                       // waits 15ms for the servo to reach the position
//  }
//  delay(2000);
//  for (pos = 0; pos <= 145; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
batsan(); 
 batcaythong();
  batphongkhach();
  batR(1023); 
 
  batG(1023);
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
  
    
       digitalClockFrame(0,0);
    
  
  

}
