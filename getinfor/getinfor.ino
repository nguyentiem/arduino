/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A4);
  Serial.print(sensorValue);
   Serial.println(" ");
//
//   int sensorValue1 = analogRead(A1);
//  Serial.print(sensorValue1);
//   Serial.print(" ");
//
//   int sensorValue2 = analogRead(A2);
//  Serial.print(sensorValue2);
//   Serial.print(" ");
//
//   int sensorValue3 = analogRead(A3);
//  Serial.print(sensorValue3);
//   Serial.print(" ");
//
//   int sensorValue4 = analogRead(A4);
//  Serial.println(sensorValue4);
   
}
