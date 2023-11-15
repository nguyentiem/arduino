#include <SFE_BMP180.h>
SFE_BMP180 pressure;
#define ALTITUDE 0
int temp =0;
void readTemp() {
  char status = 0;
  double T;
  if (status == 0) {
    status = pressure.startTemperature();
    delay(5);
  }
  status = pressure.getTemperature(T);
  if (status != 0)
  {
    temp = T - 7;
  }
Serial.println(temp);
}
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
   while (!pressure.begin());
}

void loop() {
  // put your main code here, to run repeatedly:
  readTemp();
}
