#define ledbrd 13
#define rxpin 0
#define txpin 1
//http://www.instructables.com/id/Uploading-sketches-to-Pro-Mini-using-Arduino-UNO-b/
void setup()
{
    pinMode(ledbrd, OUTPUT); // initialize digital pin 13 as an output.
    Serial.end(); // disable the serial port to start using the tx and rx and input port
    pinMode(rxpin, INPUT); //set the serial rx pin as general input
    pinMode(txpin, INPUT); // set the serial tx pin as general input
}
// Very low duty cycle blink to indicate idle mode of UNO board
void loop()
{
    digitalWrite(ledbrd, HIGH); // turn the LED on
    delay(1); // wait for a very short (minimum) time
    digitalWrite(ledbrd, LOW); // turn the LED off
    delay(4000); // wait for many seconds
}
