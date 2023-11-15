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
void clearRom() {
  EEPROM.begin(512);
  for (int i = 0 ; i < 250; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
}
void setup() {
  // put your setup code here, to run once:
clearRom() ;
}

void loop() {
  // put your main code here, to run repeatedly:

}
