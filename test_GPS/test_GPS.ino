#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);

}

void loop()
{
 

 
  Serial.println(gps.location.lat());
  Serial.println(gps.location.lng());
  
  printDateTime(gps.date, gps.time);
  Serial.println(gps.altitude.meters());
  Serial.println(gps.course.deg());
  Serial.println(gps.speed.kmph());
  
  
 

  Serial.println();
  
  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}

// This custom version of delay() ensures that the gps object
// is being "fed".
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
  char da[32];
 char tim[32]; 
  if (!d.isValid())
  {
    Serial.print(F("********** "));
     
  }
  else
  {
    // String dat = String(d.month())+String(":")+String( d.day())+String(":")+String(d.year());
    
    sprintf(da, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serial.println(String("date")+String(da));
  }
  
  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
  
    sprintf(tim, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.println(String("time")+String(tim));
  }

 
  smartDelay(0);

}
