//#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>



long lat, lon;
float flat, flon;
float degree, degree_d = 0 ;
unsigned long age;
//int left_duong = D0;   // chân dương động cơ trái
//int left_am = D3 ;     // chân âm động cơ trái 
//int right_am = D4;       // chân âm động cơ phải
//int right_duong = D5 ;     //chân dương động cơ phải 
//
//float P  ; 
//float D ;
//float I ;
//int Kp = 120, Ki = 0, Kd = 200;
//int error, preError;
//int pwm = 0 ;


//SoftwareSerial mySerial(D6, D7);    // tx gps nối với D6    rx nối với D7 
//TinyGPS gps;
////// chân la bàn nối tương ứng vào I2c của esp 
Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(12345); //khai bao la ban


//float X, Y; // save disnation
//int x;
//int y;
//int z;   // altitude
//int s ;  // speed

///// GPS//////////////////



////////////// lay toa do ///////////////////////////
//
//void gpsdump(TinyGPS &gps)
//{  
//  gps.get_position(&lat, &lon, &age);
//  gps.f_get_position(&flat, &flon, &age);
// 
//  Serial.print("Lat/Long(10^-5 deg): "); Serial.print(lat); Serial.print(", "); Serial.print(lon);Serial.println();
//  //gps.f_get_position(&flat, &flon, &age); //printFloat(flat,5); Serial.print(", "); printFloat(flon,5);
//  Serial.print(" Fix age: "); Serial.print(age); Serial.println("ms.");
//  Serial.print("Alt(cm): "); Serial.print(gps.altitude() / 100); Serial.print(" Course(10^-2 deg): ");
//  s = gps.f_speed_kmph();
//  Serial.print(s); Serial.println(" km/h");
//
//}
//

//
//int getLocation() {
//  bool newdata = false;
//  unsigned long start = millis();
//  // Every 5 seconds we print an update
//  while (millis() - start < 10)
//  {
//    if (mySerial.available())
//    {
//      char c = mySerial.read();
//
//      if (gps.encode(c))
//      {
//        newdata = true;
//        break;  // uncomment to print new data immediately!
//      }
//    }
//  }
//
//
//  if (newdata) {
//    Serial.println("Acquired Data");
//
//    gpsdump(gps);
//
//    Serial.println();
//    return 1;
//  } else {
//
//    return 0;
//  }
//}
//
//
////////// ham lay goc tu la ban////////////////

void getDegree() {
  sensors_event_t event;
  mag.getEvent(&event);
  float Pi = 3.14159;
  float heading = (atan2(event.magnetic.y, event.magnetic.x) * 180) / Pi;
  if (heading < 0) {
    heading = 360 + heading;
  }
  degree = heading;
  Serial.print("Compass Heading: ");
  Serial.println(heading);



}
//////////////////// PID /////////////////////////////
//////////// lay toa doc dduoc luon hay khong ?
/////////// cho vao if else
//
//void Stop() {
//  digitalWrite(left_duong, LOW);
//  digitalWrite(right_duong, LOW);
//  digitalWrite(left_am, LOW);
//  digitalWrite(right_am, LOW);
//}
//
//float readData(float goc) { // tinh gc lech so voi truc da chon
//  getDegree();
//  float tem = degree - goc;
//  if (tem < 180 && tem > -180)
//    return  tem ;
//  else {
//    if (tem > 180)
//      return tem - 360;
//    else {
//      if (tem < -180) {
//        return tem + 360;
//      }
//    }
//  }
//}
//
//float PID(float goc) {     // caculate pid
//  error = readData(goc);
//  Serial.print("goc loi: ") ;Serial.println(error);
//  if (abs(error) > 20) pwm = 0;
//  else pwm = 400;
//
//  P = error ;
//  D = error - preError;
//  I += D ;
//  float pid = Kp * P + Ki * I + Kd * D;
//  preError = error ;
//  return pid;
//}
//
//void control_goc(float goc) { // neu goc am thi tang toc banh trai
//  // neu goc duong tang toc banh phai
//   float hc = PID(goc);
//
//  int spd1 = pwm - hc ;
//  int spd2 = pwm + hc ;
//  /// kiem tra toc doc de quay xe
//  // toc do san
//  // toc do quay manh nhat
//  // toc do di thang
//  // set lai gia tri cho can chinh
//  analogWrite(left_duong, (int)(pwm - hc));
//  digitalWrite(left_am, LOW);
//
//  analogWrite(right_duong, (int)(pwm + hc));
//  digitalWrite(left_am, LOW);
//}
//
//float caculate_anpha(float x, float y) {
//  while(!getLocation());
//  /// convert to radian 
//  x = x*PI/180; 
//  y = y*PI/180; 
//  flat = flat*PI/180;
//  flon = flon*PI/180; 
////  float a = sin(0.5*(x-lat))*sin(0.5*(lat-x))+cos(lat)*cos(x)*sin(0.5*(y-lon))*sin(0.5*(y-lon));
////  float dis = 2*6371*atan(sqrt(a)/sqrt(1-a);
//  float df = sin(y-flon)*cos(x);
//  float dfi = cos(flat)*sin(x)-sin(flat)*cos(x)*cos(y-flon);
//  float goc =atan(df/dfi); 
//  return  goc*180/PI;
//}
//
//
//int check(float x, float y) {
//  if (x - flat < 3.0 && y - flon < 3.0)
//    return 1 ;
//  else
//    return 0;
//}
//
//
//void control_vitri(float x, float y) {
//  float goc =  caculate_anpha(x, y);
//  control_goc(goc);
//  getLocation();
//  if (check(x, y)) {
//    Stop();
//    return ;
//  }
//}
//
//
//void control_quydao(float R){
//  // di theo hinh tròn bán kính R 
//    
//}

//////////////////void setup ///////////////////
void setup() {
//  pinMode(left_am, OUTPUT);
//  pinMode(left_duong, OUTPUT);
//  pinMode(right_am, OUTPUT);
//  pinMode(right_duong, OUTPUT);

  Serial.begin(9600);   // monito
 //   setupWifi();
  Wire.begin();   // i2c
  //mySerial.begin(9600); // begin GPS
  if (!mag.begin()) {

    Serial.println("Ooops, no la ban detected ... Check your wiring!");

  }
}
//////////////////////////////////////////////



void loop() {

 getDegree();
 //Serial.println(caculate_anpha(21.047861,105.785469));
 delay(1000);
}
