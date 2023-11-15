int pin = 13;

void setup() {

  pinMode(pin, OUTPUT);
}


void loop() {
  digitalWrite(pin, LOW);
  delay(1000);         //dừng 1
  digitalWrite(pin, HIGH);
  delay(1000);               //dừng 1
}
