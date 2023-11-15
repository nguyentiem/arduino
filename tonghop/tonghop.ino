#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_LSM303DLH_Mag.h>
#include <Wire.h>

Adafruit_BMP280 bmp; // I2C

Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(31); //khai bao la ban 1D
  float temp, pressure; 
  float degree; 
  float Pi = 3.14159;
  float xheading ;
  float yHeading;
  float zHeading;

void getDegree() {
   sensors_event_t event;
   mag.getEvent(&event);
  
   xheading = (atan2(event.magnetic.y, event.magnetic.x) * 180) / PI;
   yHeading = (atan2(event.magnetic.z, event.magnetic.x)*180)/PI;
   zHeading = (atan2(event.magnetic.z, event.magnetic.y)*180)/PI;
  
 
  if (xheading < 0) {
    xheading = 360 + heading;
  }
   if (yHeading< 0) {
    yHeading = 360 + yHeading;
  }
   if (zHeading < 0) {
    zHeading = 360 + zHeading;
  }
  
  Serial.println("Compass Heading: ");
  Serial.println(heading);
  Serial.println(yHeading);
  Serial.println(zHeading);
  Serial.println("=====================");

}

void getTemp(){
   temp = bmp.readTemperature();
   pressure =bmp.readPressure(); 
   Serial.println("Temperature: " + String(bmp.readTemperature()) + "*C");
   Serial.println("Pressure: " + String(bmp.readPressure()) + "Pa");
  }

void get_Gyro_Accel(){
  
  }

void setup()
{
  
  Serial.begin(9600);
  while(!bmp.begin()) {
    Serial.println("Not Connect BMP");
    delay(500);
  }
  while (!mag.begin()) {

    Serial.println("Ooops, no la ban detected ... Check your wiring!");
    delay(500);
  }
 
}

void loop()
{

  
  delay(1000);
}
