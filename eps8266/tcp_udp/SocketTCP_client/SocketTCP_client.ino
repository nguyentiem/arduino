<<<<<<< 571645d5af3b343ddc376a4fabc4f2d7d53caba4
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h> //https://github.com/Links2004/arduinoWebSockets
WebSocketsClient webSocket;
const char* ssid = "SCKT"; //Đổi thành wifi của bạn
const char* password = "huhu123"; //Đổi pass luôn
const char* ip_host = "192.168.1.150"; //Đổi luôn IP host của PC nha
const uint16_t port = 3000; //Port thích đổi thì phải đổi ở server nữa
const int LED = 2;
const int BTN = 0;
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      {
        Serial.printf("[WSc] Connected to url: %s\n", payload);
      }
      break;
    case WStype_TEXT:
      Serial.printf("[WSc] get text: %s\n", payload);
      if (strcmp((char*)payload, "LED_ON") == 0) {
        digitalWrite(LED, 0); // Khi client phát sự kiện "LED_ON" thì server sẽ bật LED
      } else if (strcmp((char*)payload, "LED_OFF") == 0) {
        digitalWrite(LED, 1); // Khi client phát sự kiện "LED_OFF" thì server sẽ tắt LED
      }
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      break;
  }
}
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BTN, INPUT);
  Serial.begin(115200);
  Serial.println("ESP8266 Websocket Client");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  webSocket.begin(ip_host, port);
  webSocket.onEvent(webSocketEvent);
}
void loop() {
  webSocket.loop();
  static bool isPressed = false;
  if (!isPressed && digitalRead(BTN) == 0) { //Nhấn nút nhấn GPIO0
    isPressed = true;
    webSocket.sendTXT("BTN_PRESSED");
  } else if (isPressed && digitalRead(BTN)) { //Nhả nút nhấn GPIO0
    isPressed = false;
    webSocket.sendTXT("BTN_RELEASE");
  }
=======
#include <ESP8266WiFi.h>
const char* ssid = "Nguyen Tiem";
const char* password = "58642110";
const char* host = "192.168.1.21"; //IP des Java-Servers
const int serverPort = 88; //Port des Java-Servers (ServerSocket)
void setup() {
 Serial.begin(9600); //Kontrollausgabe aktivieren
// delay(800);
 Serial.println();
 Serial.print("connect to wifi: ");
 Serial.print(ssid);

 WiFi.begin(ssid, password);
 /*Solange keine Verbindung zu einem AccessPoint (AP) aufgebaut wurde*/
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 Serial.println("connected.");
 Serial.print(" IP ");
 Serial.println(WiFi.localIP());
 /*Signalstärke des AP*/
 long rssi = WiFi.RSSI();
 Serial.print("(RSSI) to AP:");
 Serial.print(rssi);
 Serial.println(" dBm");
}
void loop() {
 WiFiClient client;

 if (!client.connect(host, serverPort)) {
 Serial.print("X");
 return;
 }

 client.println("esp8266 hello");
 delay(100);
 /*Echo vom Java-Server lesen und ausgeben*/
 String line = client.readStringUntil('\n');
 Serial.print(line);
 Serial.println();
 /*Verbindung zum Java-Server schliessen*/
 
 client.flush();
 client.stop();
 
>>>>>>> add project esp8266
}
