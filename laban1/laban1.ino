#include <Wire.h>
#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>


Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(31); //khai bao la ban 1D
float degree; 
void getDegree() {
  sensors_event_t event;
  mag.getEvent(&event);
  float Pi = 3.14159;
  float heading = (atan2(event.magnetic.y, event.magnetic.x) * 180) / Pi;
  float yHeading = (atan2(event.magnetic.z, event.magnetic.x)*180)/Pi;
  float zHeading = (atan2(event.magnetic.z, event.magnetic.y)*180)/Pi;
  
  // float heading = (atan2(event.magnetic.y, event.magnetic.x) * 180) / Pi;
  // float heading = (atan2(event.magnetic.y, event.magnetic.x) * 180) / Pi;
  if (heading < 0) {
    heading = 360 + heading;
  }
   if (yHeading< 0) {
    yHeading = 360 + yHeading;
  }
   if (zHeading < 0) {
    zHeading = 360 + zHeading;
  }
  
  Serial.print("Compass Heading: ");
  Serial.println(heading);
  Serial.println(yHeading);
  Serial.println(zHeading);
  Serial.println("=====================");

}

void setup()
{
 Serial.begin(9600);
 Wire.begin();
  

  if (!mag.begin()) {

    Serial.println("Ooops, no la ban detected ... Check your wiring!");
  }
  
}
void loop()
{
   getDegree();
   delay(1000);
}
