#include <MyRealTimeClock.h>

#include <RtcDS1307.h>
#include <RtcDS3231.h>


#include <RTClib.h>

#include <Wire.h>



//Wiring SCLK -> 6, I/O -> 7, CE -> 8
//Or CLK -> 6 , DAT -> 7, Reset -> 8

MyRealTimeClock myRTC(6, 7, 8); //If you change the wiring change the pins here also

void setup() {
 Serial.begin(9600);

// Set the current date, and time in the following format:
 // seconds, minutes, hours, day of the week, day of the month, month, year
 myRTC.setDS1302Time(15, 22, 21, 7, 14, 1, 2018); //Here you write your actual time/date as shown above 
 //but remember to "comment/remove" this function once you're done
 //The setup is done only one time and the module will continue counting it automatically
}

void loop() {

   myRTC.updateTime();

// Start printing elements as individuals
 Serial.print("Current Date / Time: ");
 Serial.print(myRTC.dayofmonth); //You can switch between day and month if you're using American system
 Serial.print("/");
 Serial.print(myRTC.month);
 Serial.print("/");
 Serial.print(myRTC.year);
 Serial.print(" ");
 Serial.print(myRTC.hours);
 Serial.print(":");
 Serial.print(myRTC.minutes);
 Serial.print(":");
 Serial.println(myRTC.seconds);

// Delay so the program doesn't print non-stop
 delay(1000);
}
