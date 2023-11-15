#include "DigiKeyboard.h"
void setup() {
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.println("");
  
}
void loop() {
  DigiKeyboard.delay(1000);
  DigiKeyboard.println("1412");
  
}
