#include<Servo.h>

int servoPin =9;

void setup() {
  // put your setup code here, to run once:
   pinMode(servoPin,OUTPUT);
    Serial.begin(9600); 
    analogWrite(servoPin,0);
   
}

void loop() {
    for(int i =0 ;i <250 ;i+=10){
 
   

      analogWrite(servoPin, i);//do tang 
      delay(100);// do nhay
 }
 analogWrite(servoPin, 0);
 delay(1000);

//delay(1000);
//  for(int i =0 ;i <1000 ;i+=20){
//    // analogWrite(servoPin,30);
////////     // digitalWrite(servoPin, 1);
//    delay(100);
//////Serial.println(i);
//      analogWrite(servoPin, i);
//////      //  delay(10);
// }
// delay(1000);
}
