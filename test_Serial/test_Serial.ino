void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
String mess = String("200 300 0 500 400");
Serial.println(mess);
delay(1000);
}
