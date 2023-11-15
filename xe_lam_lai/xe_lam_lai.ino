#include <SoftwareSerial.h> 
#include <Adafruit_GFX.h>

#include "TinyGPS++.h"
TinyGPSPlus gps;
SoftwareSerial SoftSerial(4, 3); //RX, TX

void setup() 
{ 
  
  
  SoftSerial.begin(9600);  // the SoftSerial baud rate 
  delay(1000);
  Serial.begin(9600);      // the Serial port of Arduino baud rate. 
 
} 
void loop() 
{ 
  String altitude ;
  
  while (SoftSerial.available() > 0)
   gps.encode(SoftSerial.read());
  
  if (gps.location.isUpdated())
  {
    Serial.print("LAT="); Serial.print(gps.location.lat(), 6);
    Serial.print("  LNG="); Serial.println(gps.location.lng(), 6);
  }
  if (gps.altitude.isUpdated())
  {
    Serial.print("Altitude:");
    Serial.println(gps.altitude.meters());
    altitude = String((int)gps.altitude.meters())+" m";
    display.setCursor(18,35);
    display.print(altitude);
  }
}
