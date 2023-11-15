#include <ESP8266WiFi.h>                 // thu vien mang cho esp8266 
#include <WiFiClient.h>                  // 
#include <ESP8266WebServer.h>            // webserver 
#include <ESP8266mDNS.h>               // thu vien dinh nghia ten mien
#include <ESP8266HTTPUpdateServer.h>  // thu vien update
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <Servo.h>
const char* ssid ="Nguyen Tiem" ;//"TRUNG TUONG";
const char* password ="58642110" ;///"khongcowifi";
////////////////////
//     server    ///
////////////////////
WiFiUDP Udp;
unsigned int localUdpPort = 88;  // local port to listen on
char incomingPacket[11];  // buffer for incoming packets
char  replyPacket[] = "esp8266 UDP hi!";  // a reply string to send back

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

IPAddress staticIP(192, 168, 1, 130);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

IPAddress remoteIp ;
int pos = 0;    // variable to store the servo position
#define PIN          4
#define NUMPIXELS      8

const char* host = "boot";
const char* updatePath = "/update";
const char* updateUsername = "";     //password
const char* updatePassword = "";      // password

ESP8266WebServer webServer(80);
ESP8266HTTPUpdateServer httpUpdater;
//-----------------------------------------//
const char MainPage[] PROGMEM = R"=====(
  <!DOCTYPE html> 
  <html>
   <head> 
       <title>OTA-Nguyen Van Tiem</title> 
       <style> 
          body{
            text-align: center;
          }
       </style>
       <meta name="viewport" content="width=device-width,user-scalable=0" charset="UTF-8">
   </head>
   <body> 
      <div>
        <img src='https://dienthongminhesmart.000webhostapp.com/firmware_ota.jpg' height='200px' width='330px'>
      </div>
      <div>
        <button onclick="window.location.href='/update'">UPLOAD FIRMWARE</button><br><br>

      </div>
      <script>
      </script>
   </body> 
  </html>
)=====";

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Servo myservo;  // create servo object to control a servo
int caythong = 15; 
int phongkhach = 2; 
int san =16; 
int garaR = 14; 
int garaB =13; 
int garaG =12; 
int ledTran =4;
int Tran =5;  
//byte fs=0,fct=0,fk=0,fr=0,fg=0,fb=0,fm=0,fmr=0,fmg=0,fmb=0;
int f[10]; 
void MoMai(){
 
  for (pos = 145; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  }
  void DongMai(){
      for (pos = 0; pos <= 145; pos += 1) { // goes from 0 degrees to 180 degrees
    
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  }

void batphongkhach(){
   digitalWrite(phongkhach, LOW);
  }
void tatphongkhach(){
   digitalWrite(phongkhach,HIGH );
  }

void batsan(){
   digitalWrite(san, LOW);
  }
void tatsan(){
   digitalWrite(san, HIGH);
  }
    
void batcaythong(){
    digitalWrite(caythong, LOW);   // turn the LED on (HIGH is the voltage level)
                     // wait for a second
  }
  void tatcaythong(){
    digitalWrite(caythong, HIGH);   // turn the LED on (HIGH is the voltage level)
                   // wait for a second
  }

void batG(int a){
   analogWrite(garaG, a);
  }
void tatG(){
   digitalWrite(garaG, LOW);
  }
    
void batR(int a){
    analogWrite(garaR, a);
  }
  void tatR(){
    digitalWrite(garaR, LOW);   // turn the LED on (HIGH is the voltage level)
                   // wait for a second
  } 
void batB(int a){
   analogWrite(garaB, a);
  }
void tatB(){
   digitalWrite(garaB, LOW);
  }
  
void rst(){
  tatG();tatB();tatR();
  tatphongkhach();
  tatsan();
  tatcaythong();
  }

void control(){
  
  }
  
void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
   WiFi.begin(ssid, password);
  WiFi.config(staticIP, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
 Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  Udp.begin(localUdpPort);
  myservo.attach(5);  
pinMode(caythong, OUTPUT);
pinMode(phongkhach, OUTPUT);
pinMode(garaR, OUTPUT);
pinMode(garaB, OUTPUT);
pinMode(garaG, OUTPUT);
pinMode(san, OUTPUT);
rst(); 
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
 
  pixels.begin(); // This initializes the NeoPixel library.

for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255,128,128)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(100);
}
 batsan(); 
 batcaythong();
  batphongkhach();
  batR(1023); 
 
  batG(1023);
 MoMai();   
 delay(1000);
 // MoMai();   
 delay(1000);
  DongMai();

   MDNS.begin(host);     // multicast DNS
  MDNS.addService("http", "tcp", 80);

  httpUpdater.setup(&webServer, updatePath, updateUsername, updatePassword); // 
  webServer.on("/",[]{
    String s = MainPage;
    webServer.send(200,"text/html",s);
  });
  webServer.begin();
  Serial.println("Web Server is started!");
}

void loop() {
   MDNS.update();
  webServer.handleClient();
  ///////////////////////////
 int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
      
     for(int i =0 ; i<10; i++){
      f[i] =(int) incomingPacket[i];
      }
      
      if(incomingPacket[0]=='0'){
     digitalWrite(san, LOW); // bat la 0
      }else{
        digitalWrite(san, HIGH); // bat la 0
        }

      if(incomingPacket[1]=='0'){
     digitalWrite(caythong, LOW); // bat la 0
      }else{
        digitalWrite(caythong, HIGH); // bat la 0
        }

        if(incomingPacket[2]=='0'){
     digitalWrite(phongkhach, LOW); // bat la 0
      }else{
        digitalWrite(phongkhach, HIGH); // bat la 0
        }
         
     
     
     analogWrite(garaR, f[3]);
     analogWrite(garaG, f[4]);
     analogWrite(garaB, f[5]);
    
        for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(f[7],f[8],f[9])); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.
  //  delay(100);
}
 if(incomingPacket[6]=='0'){
       MoMai();   

      }else{
        if(incomingPacket[6]=='1')
         DongMai();
         
        }
    }
    
   Serial.printf("UDP packet contents: %s\n", incomingPacket);
  }
  
}
