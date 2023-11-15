/*****
 * doc sensor 1 tieng 1 lan
 * lay gio 1 gio  mot lan 
 * check dieu khien lien tuc 
 * neu dieu khien thay doi thi thay doi 
 * check dieu tu dong va dieu khien thu cong 
 * 
 * 
 */

#include <Adafruit_MQTT.h>            //Adafruit MQTT Libraries
#include <Adafruit_MQTT_Client.h>     //
#include <ESP8266WiFi.h>              //ESP8266 Wi-Fi libraries        //ESP8266 Wi-Fi libraries
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Adafruit_NeoPixel.h>

#define MB D4                   //declare the relay pin
#define SSD A0               // cam bien anh sang 
#define SSN D6                 // cam bien nuoc 
#define PIN        D3 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 44 // Popular NeoPixel ring size

#define WLAN_SSID "Trieu Thuy"//"Tenda_D1C960"          //enter your WiFi network name within the double quotes & 
#define WLAN_PASS "11111111"          //password here
#define WLAN_SSID1 "Tenda_D1C960"//"Tenda_D1C960"          //enter your WiFi network name within the double quotes & 
#define WLAN_PASS1 ""          //password here

#define AIO_SERVER       "io.adafruit.com"
#define AIO_SERVERPORT   1883               // use 8883 is used for SSL

#define AIO_USERNAME  "nguyentiem"
#define AIO_KEY       "aio_VCON06ZdRvdCxIdQi62Y9qN0VAO5"  //key of Adafruit IO (for this click the Golden Key in Adafruit IO Dashboard)

int fmode =0  ; // 0 thu cong 1 tu dong 
int fden = 0; 
int fbom = 0 ; 
int sden = 0 ; 
int sbom =0 ; 
int count = 0 ;

 int co =0; 
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");


WiFiClient client;    
// Create an ESP8266 WiFiClient class to connect to the MQTT server.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);              // Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Subscribe maybom = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/maybom");  // Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe den = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/denrgb");
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led");  

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); 

int currentHour ; 
int currentMinute ; 
int currentSecond ;
int fmark = 0 ; 
int hours = 0 ; 



void MQTT_connect() 
{
  int8_t ret;
  if (mqtt.connected())     // Stop if already connected.
  {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) 
  { 
       Serial.println(mqtt.connectErrorString(ret));                  // connect will return 0 for connected
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(1000);              // wait 5 seconds
       retries--;
       if (retries == 0) 
       {
         while (1);              // basically die and wait for WDT to reset me
       }
  }
  Serial.println("MQTT Connected!");
}
void batDen(){
  
   for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
  pixels.setPixelColor(i, pixels.Color(255, 0, 64));

  pixels.show();   // Send the updated pixel colors to the hardware.
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
  

   // delay(DELAYVAL); // Pause before next pass through loop
  }
  }
void tatDen(){
   for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
  pixels.setPixelColor(i, pixels.Color(0, 0, 0));

  pixels.show();   // Send the updated pixel colors to the hardware.
   
  }
  }
  
void getCmd(){
   String tem="0",tem1="0",tem2="0"; 
  MQTT_connect();
//   this is our 'wait for incoming subscription packets' busy subloop
//   try to spend your time here
//  if(count==0){
//  tem =  (char *) maybom.lastread; 
//  tem2 =  (char *) onoffbutton.lastread; 
//  tem1 = (char *)  den.lastread;
//  count = 1 ; 
//  if(tem=="0"){fbom=1;}
//        else{fbom =0;}
//        if(tem1=="0"){fden=1;}
//        else{fden =0;}
//        if(tem2=="0"){fmode=1;}
//        else{fmode =0;}
//  return ; 
  
//  } 
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(3000))) 
  {
    if (subscription == &maybom||subscription == &den||subscription==&onoffbutton) {
      
      Serial.print(F("Got: bom"));
      Serial.println((char *)maybom.lastread);
       tem= (char *) maybom.lastread; //converts the received 1 or 0 to string to compare in the if-else statement
     
      Serial.print(F("Got: den"));
      Serial.println((char *)den.lastread); 
         tem1 = (char *) den.lastread; //converts the received 1 or 0 to string to compare in the if-else statement
         
          Serial.print(F("Got: mode"));
      Serial.println((char *)onoffbutton.lastread);
         tem2 = (char *)onoffbutton.lastread; //converts the received 1 or 0 to string to compare in the if-else statement
       if(tem=="0"){fbom=0;}
        else{fbom =1;}
        if(tem1=="0"){fden=1;}
        else{fden =0;}
        if(tem2=="0"){fmode=1;}
        else{fmode =0;}
    } 
  }
   
}

void getInfor(){
  
  
  }

  
void getTime(){
   timeClient.update();
   currentHour = timeClient.getHours();
   currentMinute = timeClient.getMinutes();
   currentSecond = timeClient.getSeconds();
   
  }


void setup() 
{  
  Serial.begin(9600);
  pinMode(MB, OUTPUT);
  digitalWrite(MB, HIGH);  
  //pinMode(SSD,INPUT); 
  pinMode(SSN,INPUT);

  Serial.println();
  Serial.print("Connecting to ");       // Connect to WiFi access point.
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  for(int i= 0 ; i<20; i++){
   
    //co =0; 
  
    delay(500);
    // WiFi.begin(WLAN_SSID, WLAN_PASS);
    Serial.print(".");
    if(WiFi.status() ==WL_CONNECTED){
       co = 1;
       break;
      }
    
  }
 
   if(co ==0){
      Serial.println();
  Serial.print("Connecting to ");       // Connect to WiFi access point.
  Serial.println(WLAN_SSID1);
   WiFi.begin(WLAN_SSID1, WLAN_PASS1);
   while(WiFi.status() !=WL_CONNECTED){
     delay(500);
    // WiFi.begin(WLAN_SSID, WLAN_PASS);
    Serial.print(".");
    }
   }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
  timeClient.begin();
  timeClient.setTimeOffset(25200);
  mqtt.subscribe(&maybom);        // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&den);
  mqtt.subscribe(&onoffbutton);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)  
  getTime();     
}


void loop() 
{
  getCmd(); 
 
 if(fmode==0){ // che do thu cong
   Serial.println("che do thu cong");
    if(fbom == 1){
     
         Serial.println("bat may bom");
        digitalWrite(MB,0); // lennh va kho thi tuoi 
     
    }else{
       Serial.println("tat may bom");
      digitalWrite(MB,1); 
      }
   if(fden==0){
     Serial.println(analogRead(SSD));
    
       Serial.println("bat den");
      batDen(); 
     
    }else{
      Serial.println("tat den");
      tatDen(); 
      }
   
  }
  else{// che do tu dong
     Serial.println("che do tu dong");
     getTime(); 
     if(currentHour==6){
      if(fmark ==0){
        hours = currentMinute; 
          fmark =1; 
        }
         Serial.println(analogRead(SSD));
       if(analogRead(SSD)>800){
           Serial.println("tat den");
         tatDen(); 
        }else{
             Serial.println("bat den");
          batDen(); 
          }
     
      }
      if(currentHour>=6&&currentHour<19){
       Serial.println(analogRead(SSD));
         if(analogRead(SSD)>800){
             Serial.println("tat den");
         tatDen(); 
        }else{
             Serial.println("bat den");
          batDen(); 
          }
        }
        if(currentHour>=18||(currentHour>=0&&currentHour<6)){
          Serial.println(analogRead(SSD));
             Serial.println("tat den");
          tatDen();
          }
          Serial.println(String("MB: ")+String(digitalRead(SSN)));
          if(digitalRead(SSN)==0){
               Serial.println("tat May bom");
            digitalWrite(MB,1);
            }else{
              Serial.println("bat May bom");
              digitalWrite(MB,0);
              }
          // neu kho thi tuoi   
     Serial.print(currentHour);
     Serial.print(" ");
     Serial.print(currentMinute);
     Serial.print(" ");
     Serial.println(currentSecond);
    }
    Serial.println("=========================");
}
