/*
 * IRremoteESP8266: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * This is very simple teaching code to show you how to use the library.
 * If you are trying to decode your Infra-Red remote(s) for later replay,
 * use the IRrecvDumpV2.ino (or later) example code instead of this.
 * An IR detector/demodulator must be connected to the input kRecvPin.
 * Copyright 2009 Ken Shirriff, http://arcfn.com
 * Example circuit diagram:
 *  https://github.com/crankyoldgit/IRremoteESP8266/wiki#ir-receiving
 * Changes:
 *   Version 0.2 June, 2017
 *     Changed GPIO pin to the same as other examples.
 *     Used our own method for printing a uint64_t.
 *     Changed the baud rate to 115200.
 *   Version 0.1 Sept, 2015
 *     Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009
 */

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
int temp = 0 ; 
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
const char* ssid = "Nguyen Tiem";      //"Nguyen Tiem";
const char* password = "58642110";       //"58642110";
int frame =0 ; 
WiFiServer server(88);
IPAddress staticIP(192, 168, 1, 22);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
int red = D2;
int green = D1; 
int blue= D0; 
int pwmr =0, pwmb =0, pwmg =0;
// An IR detector/demodulator is connected to GPIO pin 14(D5 on a NodeMCU
// board).
// Note: GPIO 16 won't work on the ESP8266 as it does not have interrupts.
const uint16_t kRecvPin = D5;

IRrecv irrecv(kRecvPin);

decode_results results;
void recv_ir(){
  if (irrecv.decode(&results)) {
    // print() & println() can't handle printing long longs. (uint64_t)
    serialPrintUint64(results.value, HEX);
    temp =results.value; 
    Serial.println("");
    irrecv.resume();  // Receive the next value
  }
  delay(100);
  }

  void connectWifi()
{
  

  //WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  server.begin();
}
void recv() {
  WiFiClient client = server.available();
  // wait for a client (web browser) to connect
  if (client)
  {
    Serial.println("connected!");
    while (client.connected())
    {
      if (client.available())
      {

        char line[4];
        memset(line, 0, 4);
        client.readBytes(line, 4);
        frame = (int)line[0];
        pwmr = (int)line[1];
        pwmg = (int)line[2];
        pwmb = (int)line[3];
        Serial.println(line);
      }


    }
    delay(1); // give the web browser time to receive the data

    // close the connection:
    client.stop();
    Serial.println("[Client disonnected]");
  }

  Serial.println("out");
}


void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();  // Start the receiver
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(kRecvPin);
   pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}
//FF30CF   1
//FF18E7   2
//FF7A85   3
//+ FFA857
//FF10EF    4
// FF38C7    5
// FF5AA5     6
// off FFA25D
//  

void loop() {
  
recv_ir();
 switch(temp){
  case 0xFF30CF:
         digitalWrite(green,LOW); 
       
       digitalWrite(red,HIGH);
       
       digitalWrite(blue,LOW);
  break; 
  case 0xFF18E7 :
       digitalWrite(green,LOW); 
     
       digitalWrite(red,LOW);
    
       digitalWrite(blue,HIGH);
  break;
  case 0xFF7A85:
       digitalWrite(green,HIGH); 
     
       digitalWrite(red,LOW);
    
       digitalWrite(blue,LOW);
  break;
  case 0xFF10EF:
     pwmr = (pwmr+100)>1023?1023:(pwmr+100); 
      temp =0 ;
  break;
  case 0xFF38C7:
   pwmb = (pwmb+100)>1023?1023:(pwmb+100);  
      temp =0;
  break;
      
  case 0xFF5AA5:
  pwmg = (pwmg+100)>1023?1023:(pwmg+100); 
     
         temp =0; 
  break;
  
   case 0xFF42BD:
       pwmr = (pwmr-100)<0?0:(pwmr-100); 
     
         temp =0; 
  break;
  case 0xFF4AB5:
     
     pwmb = (pwmb-100)<0?0:(pwmb-100); 
         temp =0; 
  break;
  case 0xFF52AD:
       
       pwmg = (pwmg-100)<0?0:(pwmg-100); 
         temp =0; 
  break;
  case 0xFFA25D:
   digitalWrite(green,LOW); 
     
   digitalWrite(red,LOW);
    
    digitalWrite(blue,LOW);
     pwmg=pwmb=pwmr=0  ;
  break;
  case 0:
       analogWrite(green,pwmg); 
     
       analogWrite(red,pwmr);
    
       analogWrite(blue,pwmb); 
       
       break;
  }
}
