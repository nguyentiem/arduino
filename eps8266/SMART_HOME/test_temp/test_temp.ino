#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>
#include <SocketIOclient.h>
#include "DHT.h"
#define DHTPIN 4   
#define DHTTYPE DHT11 // DHT 11
ESP8266WiFiMulti WiFiMulti;
SocketIOclient socketIO;
float tem =0; 
#define USE_SERIAL Serial
String output;
int val =1; 
 
char mess; 
char*message; 
DHT dht(DHTPIN, DHTTYPE);

void socketIOEvent(socketIOmessageType_t type, uint8_t * payload, size_t length) {
  Serial.println(type);
    switch(type) {
        case sIOtype_DISCONNECT:
            USE_SERIAL.printf("[IOc] Disconnected!\n");
            break;
        case sIOtype_CONNECT:
            USE_SERIAL.printf("[IOc] Connected to url: %s\n", payload);
          
            // join default namespace (no auto join in Socket.IO V3)
            
            socketIO.send(sIOtype_CONNECT, "/");
            break;
        case sIOtype_EVENT:
          //  USE_SERIAL.printf("[IOc] get event: %s\n", payload);
             //Serial.println(String(strlen((char*)payload)));
             message = (char*)payload;
//             Serial.println(message[10]);
//              Serial.println(message[strlen(message)-3]);
             if(message[10]=='t'){// get
                val = (message[strlen(message)-3]-47)%2;
                Serial.println(val); 
              }
            // mess=  message[strlen(message)]
             Serial.println(message);
            break;
        case sIOtype_ACK:
            USE_SERIAL.printf("[IOc] get ack: %u\n", length);
            hexdump(payload, length);
            
            break;
        case sIOtype_ERROR:
            USE_SERIAL.printf("[IOc] get error: %u\n", length);
            hexdump(payload, length);
            break;
        case sIOtype_BINARY_EVENT:
            USE_SERIAL.printf("[IOc] get binary: %u\n", length);
            hexdump(payload, length);
            break;
        case sIOtype_BINARY_ACK:
            USE_SERIAL.printf("[IOc] get binary ack: %u\n", length);
            hexdump(payload, length);
            break;
    }
}

void setup() { 
    USE_SERIAL.begin(9600);
 dht.begin();
 WiFi.begin("Nguyen Tiem", "58642110");
 /*Solange keine Verbindung zu einem AccessPoint (AP) aufgebaut wurde*/
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 Serial.println("connected.");
 Serial.print(" IP ");
 Serial.println(WiFi.localIP());
    // server address, port and URL
    //socketIO.begin("192.168.1.21",3000);
 socketIO.begin("192.168.1.21",3000,"/socket.io/?EIO=4");// ""/socket.io/?transport=websocket
    // event handler
    socketIO.onEvent(socketIOEvent);
     
}

unsigned long messageTimestamp = 0;
int len =0; 
char temp[5] ; 
void loop() {

      
       
   memset(temp, 0, 5);
   float t = dht.readTemperature();
    dtostrf(t, 5, 2, temp);
    
    socketIO.loop();
    
    uint64_t now = millis();

    if(now - messageTimestamp > 2000) {
      String tem ="1*1*1*3*3*"+String(temp);
     output="[\"push\","; 
        output+="\""+String(tem)+"*-"+"\""+String("]");  
        messageTimestamp = now;
       /// USE_SERIAL.println(output);
        socketIO.sendEVENT(output);
    }
}
