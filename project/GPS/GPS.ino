#include <TinyGPS.h>
#include <SoftwareSerial.h>
long lat, lon;
float flat, flon;
float degree, degree_d = 0 ;
int s; 
unsigned long age;
TinyGPS gps;
SoftwareSerial mySerial(3, 4); 
void gpsdump(TinyGPS &gps)
{  
  gps.get_position(&lat, &lon, &age);
  gps.f_get_position(&flat, &flon, &age);
 
  Serial.print("Lat/Long(10^-5 deg): "); Serial.print(lat); Serial.print(", "); Serial.print(lon);Serial.println();
  //gps.f_get_position(&flat, &flon, &age); //printFloat(flat,5); Serial.print(", "); printFloat(flon,5);
  Serial.print(" Fix age: "); Serial.print(age); Serial.println("ms.");
  Serial.print("Alt(cm): "); Serial.print(gps.altitude() / 100); Serial.print(" Course(10^-2 deg): ");
  s = gps.f_speed_kmph();
  Serial.print(s); Serial.println(" km/h");

}



int getLocation() {
  bool newdata = false;
  unsigned long start = millis();
  // Every 5 seconds we print an update
  while (millis() - start < 10)
  {
    if (mySerial.available())
    {
      char c = mySerial.read();

      if (gps.encode(c))
      {
        newdata = true;
        break;  // uncomment to print new data immediately!
      }
    }
  }


  if (newdata) {
    Serial.println("Acquired Data");

    gpsdump(gps);

    Serial.println();
    return 1;
  } else {
    Serial.println("no conected");
    return 0;
  }
}

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);   // monito
 mySerial.begin(9600); // begin GPS
}

void loop() {
  // put your main code here, to run repeatedly:
getLocation();
}
