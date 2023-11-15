#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
#include <Arduino.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include <SocketIOclient.h>
#include "DHT.h"
#define DHTPIN 5 // what digital pin we're connected to
#define DHTTYPE DHT11 // DHT 11
#ifndef APSSID
#define APSSID "DEVICE"
#define APPSK  ""
#endif
#define USE_SERIAL Serial

const char *softAP_ssid = APSSID;
const char *softAP_password = APPSK;
DHT dht(DHTPIN, DHTTYPE);
int pin = 2;
int onoff = 0;
const char *myHostname = "esp8266";

char Ssid[32] ;  // ten wifi
char Password[32]; // passwifi
char Link[100]; // ten http
char Name[32];// ten thiet bi
char IDAcc[5];
char IDHome[5];
char IDRoom[5] ;
char IDDecv[5];
char Value[5];
char Type[5];
int val = 1;
char flagDlt = '0';
char *message;

int flagRorW = 0;
/* Soft AP network parameters */
IPAddress apIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 0);
WiFiUDP Udp;
unsigned int localUdpPort = 88;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
//char  replyPacket[] = "esp8266 UDP hi!";  // a reply string to send back
ESP8266WiFiMulti WiFiMulti;
SocketIOclient socketIO;

void socketIOEvent(socketIOmessageType_t type, uint8_t * payload, size_t length) {
  Serial.println(type);
  switch (type) {
    case sIOtype_DISCONNECT:
      break;
    case sIOtype_CONNECT:
      socketIO.send(sIOtype_CONNECT, "/");
      break;
    case sIOtype_EVENT:
      USE_SERIAL.printf("[IOc] get event: %s\n", payload);
      message = (char*)payload;
      if (message[10] == 't') { // get
        flagDlt = message[strlen(message) - 3];

        if (flagDlt == '-') {
          Serial.println("thiet bi dat bi xoa");
        } else {
          val = (message[strlen(message) - 3] - 47) % 2;
          pinMode(pin, OUTPUT);
          digitalWrite(pin, val);
          Serial.println(val);
        }
      }
      break;
    case sIOtype_ACK:
      break;
    case sIOtype_ERROR:
      break;
    case sIOtype_BINARY_EVENT:
      break;
    case sIOtype_BINARY_ACK:
      break;
  }
}

///         32    32      100    32      5     5       5         5       5
//Load ten wifi- pass -  link - name - IDACC-IDHome - IDRoom - IDDecv - Type

uint64_t messageTimestamp = 0;
void push() {// 2 giay push 1 laanf
  uint64_t now = millis();

  if (now - messageTimestamp > 2000) {

    String output = "";
    output = "[\"push\",";
    output += "\"" + String(IDAcc) + String("*") + String(IDHome) + String("*") + String(IDRoom) + String("*") + String(IDDecv) + String("*") + String(IDDecv) + String("*") + String(Value) + "*-" + "\"" + String("]");
    messageTimestamp = now;
    USE_SERIAL.println(output);
    socketIO.sendEVENT(output);
  }
}
//void getData() {
//  uint64_t now = millis();
//  uint64_t messageTimestamp;
//  if (now - messageTimestamp > 2000) {
//
//    String output = "";
//    output = "[\"get\",";
//    output += "\"" + String(IDAcc) + String("*") + String(IDHome) + String("*") + String(IDRoom) + String("*") + String(IDDecv) + "\"" + String("]");
//    messageTimestamp = now;
//    USE_SERIAL.println(output);
//    socketIO.sendEVENT(output);
//  }
//}

void clear() {
  memset(Ssid, 0, 32);
  memset(Password, 0, 32);
  memset(Link, 0, 100);
  memset(Name, 0, 32);
  memset(IDAcc, 0, 5);
  memset(IDHome, 0, 5);
  memset(IDRoom, 0, 5);
  memset(IDDecv, 0, 5);
}

int readRom() {
  int index = 0;
  clear();
  EEPROM.begin(512);
  for (int i = 0; i < 32; i++) {
    Ssid[i] = char(EEPROM.read(index));
    index++;
  }
  if (Ssid[0] == 0 ) {
    return 0;
  }
  for (int i = 0; i < 32; i++) {
    Password[i] = char(EEPROM.read(index));
    index++;
  }
  for (int i = 0; i < 100; i++) {
    Link[i] = char(EEPROM.read(index));
    index++;
  }
  for (int i = 0; i < 32; i++) {
    Name[i] = char(EEPROM.read(index));
    index++;
  }
  
  for (int i = 0 ; i < 5 ; i++) {
    IDAcc[i] =  char(EEPROM.read(index));
    index++;
  }
  for (int i = 0 ; i < 5 ; i++) {
    IDHome[i] =  char(EEPROM.read(index));
    index++;
  }
  for (int i = 0 ; i < 5 ; i++) {
    IDRoom[i] =  char(EEPROM.read(index));
    index++;
  }
  for (int i = 0 ; i < 5 ; i++) {
    IDDecv[i] =  char(EEPROM.read(index));
    index++;
  }
  for (int i = 0 ; i < 5 ; i++) {
    Type[i] =  char(EEPROM.read(index));
    index++;
  }
  Serial.println("================READ ROM================");


  Serial.println(Ssid);

  Serial.println(Password);
  Serial.println(Link);

  Serial.println(Name);

  Serial.println(IDAcc);
  Serial.println(IDHome);
  Serial.println(IDRoom);
  Serial.println(IDDecv);
  Serial.println(Type);
  Serial.println("================end================");
  return 1 ;
}
/** Store WLAN credentials to EEPROM */
void saveRom() {

  EEPROM.begin(512);
  for (int i = 0 ; i < 250; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
  EEPROM.begin(512);
  int index = 0;
  for (int i = 0; i < 32; i++) {
    EEPROM.write(index,  Ssid[i]);
    index++;
  }
  for (int i = 0; i < 32; i++) {
    EEPROM.write(index,  Password[i]);
    index++;
  }
  for (int i = 0; i < 100; i++) {
    EEPROM.write(index,  Link[i]);
    index++;
  }
  for (int i = 0; i < 32; i++) {
    EEPROM.write(index,  Name[i]);
    index++;
  }
  
  for (int i = 0 ; i < 5 ; i++) {
    EEPROM.write(index,  IDAcc[i]);
    index++;
  }
  for (int i = 0 ; i < 5 ; i++) {
    EEPROM.write(index,  IDHome[i]);
    index++;
  }
  for (int i = 0 ; i < 5 ; i++) {
    EEPROM.write(index,  IDRoom[i]);
    index++;
  }
  for (int i = 0 ; i < 5 ; i++) {
    EEPROM.write(index,  IDDecv[i]);
    index++;
  }
  for (int i = 0 ; i < 5 ; i++) {
    EEPROM.write(index,  Type[i]);
    index++;
  }
  EEPROM.commit();
}

void clearRom() {
  EEPROM.begin(512);
  for (int i = 0 ; i < 250; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
}

int connectWifi() {
  int flag = 1;

  for (int i = 0 ; i < 2 ; i++) {

    // readRom();
    Serial.print("Connecting to wifi: ");
    Serial.print(Ssid);
    Serial.print(" ");
    Serial.println(Password);
    WiFi.disconnect();
    WiFi.begin(Ssid, Password);
    int dem = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");

      if (dem >= 30) {// qua thoi gian 
        flag = 0;
        break;
      }
      dem++;
    }
    if (dem < 30) {
      Serial.println("connected wifi !");
      return 1;
    }
  }
  return flag;
}

void softReset() {
  ESP.restart();
}

void configMode() { // xoa thiet bi
  WiFi.mode(WIFI_AP);
  Serial.println();
  Serial.println("Configuring access point...");
  clear();
  clearRom();
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAPConfig(apIP, apIP, netMsk);
  WiFi.softAP(softAP_ssid, softAP_password);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}

void decode(char *str) {
  char *token = strtok(str, "*");

  clear();

  if (token != NULL)
  {
    strcpy(Ssid, token);
    token = strtok(NULL, "*");
  }
  if (token != NULL)
  {
    strcpy(Password, token);
    token = strtok(NULL, "*");
  }
  if (token != NULL)
  {
    strcpy(Link, token);
    token = strtok(NULL, "*");
  }
  if (token != NULL)
  {
    strcpy(Name, token);
    token = strtok(NULL, "*");
  }
  
  if (token != NULL)
  {
    strcpy(IDAcc, token);
    token = strtok(NULL, "*");
  }
  if (token != NULL)
  {
    strcpy(IDHome, token);
    token = strtok(NULL, "*");
  }
  if (token != NULL)
  {
    strcpy(IDRoom, token);
    token = strtok(NULL, "*");
  }
  if (token != NULL)
  {
    strcpy(IDDecv, token);
    token = strtok(NULL, "*");
  }
  if (token != NULL)
  {
    strcpy(Type, token);
    token = strtok(NULL, "*");
  }
  Serial.println("================config================");


  Serial.println(Ssid);

  Serial.println(Password);
  Serial.println(Link);

  Serial.println(Name);

  Serial.println(IDAcc);
  Serial.println(IDHome);
  Serial.println(IDRoom);
  Serial.println(IDDecv);
   Serial.println(Type);
  Serial.println("================end================");
}
int  recv() {
  memset(incomingPacket, 0, 255);
  int len = 0;
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    len = Udp.read(incomingPacket, 255);
    if (len == 0) return 0;
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);
    //decode mess
    //
    return len;
  } else {
    return 0;
  }
  return 0;
}

int send(char* replyPacket) {
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  Udp.write(replyPacket);
  Udp.endPacket();
}


void configEsp() {
    Serial.println("che do config");
  do {
    configMode(); // che do config

    while (recv() == 0) { // cho den khi nhan d ki tu
    }
    decode(incomingPacket);// ten wifi- pass -  link - name - RorW -IDACC-IDHome - IDRoom - IDDecv - Type . daco
    if (connectWifi()) {
      send("1");
      break;
    } else {
      send("0");
    }
  } while (1);
  ///////// ket noi wifi thanh cong /////////
  saveRom();
  WiFi.softAPdisconnect (true);
}
void setup() {

  Serial.begin(9600);
  // readroom
 
  if (readRom() == 1) {
    int flag = 0;
    Serial.println("doc rom thanh cong");
    for (int i = 0 ; i < 2 ; i++) {
      Serial.print("Connecting to wifi: ");
      Serial.print(Ssid);
      Serial.print(" ");
      Serial.println(Password);
      WiFi.disconnect();
      WiFi.begin(Ssid, Password);
      int dem = 0;
      while (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
        Serial.print(".");

        if (dem >= 30) {
          flag = 1;
          break;
        }
        dem++;
      }
      if (dem < 30) {
        Serial.println("connected wifi !");
        flag =0; 
        break; 
      }
    }
    if (flag == 1) {
      Serial.println("connected fail config again");
      configEsp();
    }
  } else {
    Serial.println("Rom trong vao che do config");
    configEsp();
  }
//// 
  socketIO.begin(Link, 3000, "/socket.io/?EIO=4"); // ""/socket.io/?transport=websocket
  // event handler
  socketIO.onEvent(socketIOEvent);
  pinMode(12, INPUT);
  dht.begin();
  pinMode(pin, OUTPUT);
}

void loop() {

  if (flagDlt == '-') {
    clear();
    clearRom();
    flagDlt = '0';
    softReset();
  }
  socketIO.loop();
  if (strcmp(Type, "1")==0) { //
    //Serial.println("den");
    if (digitalRead(12) == 1) {
      while (digitalRead(12) == 1);
      val = (val + 1) % 2;
      digitalWrite(pin, val);
      if (val == 1) {
        // tat
        memset(Value, 0, 5);
        strcpy(Value, "0");
      } else { // bat
        memset(Value, 0, 5);
        strcpy(Value, "1");
      }
      String output = "";
      output = "[\"push\",";
      output += "\"" + String(IDAcc) + String("*") + String(IDHome) + String("*") + String(IDRoom) + String("*") + String(IDDecv)  + String("*") + String(Value) + "*-*-*-" + "\"" + String("]");
      socketIO.sendEVENT(output);
      USE_SERIAL.println(output);
    }
    uint64_t now = millis();
    if (now - messageTimestamp > 2000) {

      String output = "";
      output = "[\"get\",";
      output += "\"" + String(IDAcc) + String("*") + String(IDHome) + String("*") + String(IDRoom) + String("*") + String(IDDecv) + "\"" + String("]");
      messageTimestamp = now;
      USE_SERIAL.println(output);
      socketIO.sendEVENT(output);
    }

//    continue;
  }
  if (strcmp(Type, "6")==0) {
    Serial.println("cam bien nhiet do");
    float t = dht.readTemperature();
    memset(Value,0,5);
    dtostrf(t, 5, 2, Value);
    if(Value==NULL){
       strcpy(Value,"0");
       }
    
    push();
   
  }
}
