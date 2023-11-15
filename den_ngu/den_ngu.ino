#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
const char* ssid = "Dịu";
const char* password = "97931508";
WiFiServer server(88);
IPAddress staticIP(192,168,0,22);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

#define PIN          D7
#define NUMPIXELS      8
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
 byte R[NUMPIXELS];
byte G[NUMPIXELS];
byte B[NUMPIXELS]; 
int delayval = 500; // delay for half a second


void connectWifi()
{ Serial.begin(9600);
  Serial.printf("Connecting to %s \n", ssid);
  
  WiFi.config(staticIP, gateway, subnet);
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

void updt(){
     // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
   for(int i=0;i<NUMPIXELS;i++){
    
    pixels.setPixelColor(i, pixels.Color(R[i],G[i],B[i])); 
    pixels.show(); // This sends the updated pixel color to the hardware.
    }  
  }
  
void getdata(){
  WiFiClient client = server.available();
   if (client) {
     while (client.connected())
    {
      if (client.available())
      {
        char line[24];
        memset(line, 0, 24);
        client.readBytes(line, 24);
        for(int i=0 ;i<8 ;i++){
          
          R[i] = (int)line[i];
          Serial.println("R"+String(i)+" : "+String(R[i]));
          G[i] = (int) line[8+i];
          Serial.println("G"+String(i)+" : "+String(G[i]));
          B[i] = (int) line[16+i]; 
          Serial.println("B"+String(i)+" : "+String(B[i]));
          }
        updt(); 
      }

    }
    client.stop();
  }
 }

  
void setup() {

  pixels.begin(); // This initializes the NeoPixel library.
  for (int u =0 ;u<255;u+=50){
   for(int v =0 ; v<255; v+=50){
   for(int t=0 ; t<255; t+=50){
   for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(u,v,t)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(10);
   }
   }
  }
  }
   connectWifi();
 }

void loop() {

   getdata(); 
   
}
