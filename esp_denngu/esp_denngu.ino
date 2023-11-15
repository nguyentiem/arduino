#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN        5// On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 8 // Popular NeoPixel ring size
// Replace with your network credentials
const char* ssid = "Dịu";
const char* password = "23091998";


int r=0,g=0,b=0; 
String redValue = "0";
String greenValue = "0";
String blueValue = "0";
const char* PARAM_INPUT1 = "value";
const char* PARAM_INPUT2 = "value";
const char* PARAM_INPUT3 = "value";
const char* PARAM_INPUTON = "value";
const char* PARAM_INPUTOFF = "value";
AsyncWebServer server(80);
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Design by Nguyen Tiem</title>
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 2.3rem;}
    p {font-size: 1.9rem;}
    body {max-width: 400px; margin:0px auto; padding-bottom: 25px;}
    .slider { -webkit-appearance: none; margin: 14px; width: 360px; height: 25px; background: #FFD65C;
      outline: none; -webkit-transition: .2s; transition: opacity .2s;}
    .slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 35px; height: 35px; background: #F44336; cursor: pointer;}
    .slider::-moz-range-thumb { width: 35px; height: 35px; background: #003249; cursor: pointer; }
    
     .slidered { -webkit-appearance: none; margin: 14px; width: 360px; height: 25px; background: #FFD65C;
      outline: none; -webkit-transition: .2s; transition: opacity .2s;}
    .slidered::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 35px; height: 35px; background: #4CAF50; cursor: pointer;}
    .slidered::-moz-range-thumb { width: 35px; height: 35px; background: #003249; cursor: pointer; } 
    
     .sliderblue { -webkit-appearance: none; margin: 14px; width: 360px; height: 25px; background: #FFD65C;
      outline: none; -webkit-transition: .2s; transition: opacity .2s;}
    .sliderblue::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 35px; height: 35px; background: #2359FD; cursor: pointer;}
    .sliderblue::-moz-range-thumb { width: 35px; height: 35px; background: #003249; cursor: pointer; }
    .button {
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.button1 {background-color: #E4E4EB;} 
.button2 {background-color: #008CBA;}
  </style>
</head>
<body>
  <h2>ESP Web Server</h2>
  <p><span id="textRedValue">%SLIDERVALUE%</span></p>
  <p><input type="range" onchange="updateSliderRed(this)" id="redSlider" min="0" max="1023" value="%SLIDERVALUE%" step="1" class="slider"></p>
   <p><span id="textGreenValue">%SLIDERVALUE1%</span></p>
  <p><input type="range" onchange="updateSliderGreen(this)" id="greenSlider" min="0" max="1023" value="%SLIDERVALUE1%" step="1" class="slidered"></p>
   <p><span id="textBlueValue">%SLIDERVALUE2%</span></p>
  <p><input type="range" onchange="updateSliderBlue(this)" id="blueSlider" min="0" max="1023" value="%SLIDERVALUE2%" step="1" class="sliderblue"></p>
  <p>
  <button class="button button1" onclick="turnOff()">OFF</button>
  <button class="button button2" onclick="turnOn()">ON</button>
  </p>
  
<script>
function updateSliderRed(element) {
  var redValue = document.getElementById("redSlider").value;
  document.getElementById("textRedValue").innerHTML = redValue;
  console.log(redValue);
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/red?value="+redValue, true);
  xhr.send();
}
function updateSliderGreen(element) {
  var greenValue = document.getElementById("greenSlider").value;
  document.getElementById("textGreenValue").innerHTML = greenValue;
  console.log(greenValue);
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/green?value="+greenValue, true);
  xhr.send();
}
function updateSliderBlue(element) {
  var blueValue = document.getElementById("blueSlider").value;
  document.getElementById("textBlueValue").innerHTML = blueValue;
  console.log(blueValue);
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/blue?value="+blueValue, true);
  xhr.send();
}
function turnOff() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/off?value=1", true);
  xhr.send();
}
function turnOn() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/on?value=1", true);
  xhr.send();
}
</script>
</body>
</html>
)rawliteral";

// Replaces placeholder with button section in your web page
String processor(const String& var){
  //Serial.println(var);
  if (var == "SLIDERVALUE"){
    return redValue;
  }
  if (var == "SLIDERVALUE1"){
    return greenValue;
  }
  if (var == "SLIDERVALUE2"){
    return blueValue;
  }
  return String();
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

 #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/slider?value=<inputMessage>
  server.on("/red", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT1)) {
      inputMessage = request->getParam(PARAM_INPUT1)->value();
      redValue = inputMessage;
    
      r =redValue.toInt(); 
      r = r/4;  
      displayLed(); 
    } 
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });
  
   server.on("/green", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT2)) {
      inputMessage = request->getParam(PARAM_INPUT2)->value();
      greenValue = inputMessage;
      g = greenValue.toInt();
      g = g/4; 
      Serial.println(g); 
      displayLed();
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });

server.on("/blue", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT3)) {
      inputMessage = request->getParam(PARAM_INPUT3)->value();
      blueValue = inputMessage;
      b = blueValue.toInt();
      b = b/4; 
      displayLed();
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });
  /// off 
 server.on("/off", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUTOFF)) {
      inputMessage = request->getParam(PARAM_INPUTOFF)->value();
    
      pixels.clear(); 
      pixels.show();
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });

server.on("/on", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUTON)) {
      inputMessage = request->getParam(PARAM_INPUTON)->value();
    r = random(255);
     g =random(255);
     b =random(255);
      displayLed();
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });


  server.begin();
}
  void displayLed(){
    pixels.clear(); 
     for(int i=0; i<NUMPIXELS; i++){
        pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  pixels.show();
    }
void loop() {
  
}
