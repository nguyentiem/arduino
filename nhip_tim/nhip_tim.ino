#define USE_ARDUINO_INTERRUPTS true 
#include <PulseSensorPlayground.h> 



//// Variables
const int PluseWire = 5; // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13; // The on-board Arduino LED, close to PIN 13.
int Threshold = 550; // Determine which Signal to "count as a beat" and which to ignore.
// Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
// Otherwise leave the default "550" value.

PulseSensorPlayground pulseSensor; // Creates an instance of the PulseSensorPlayground object called "pulseSensor"
void setup() {
//pinMode(PluseWire,INPUT); 
Serial.begin(9600); // For Serial Monitor


// Configure the PulseSensor object, by assigning our variables to it.
pulseSensor.analogInput(PluseWire);
pulseSensor.blinkOnPulse(LED13); //auto-magically blink Arduino's LED with heartbeat.
pulseSensor.setThreshold(Threshold);

// Double-check the "pulseSensor" object was created and "began" seeing a signal.
if (pulseSensor.begin()) {
Serial.println("We created a pulseSensor Object !"); //This prints one time at Arduino power-up, or on Arduino reset.

Serial.print(" Heart Rate Monitor");

}
}

void loop() {

int myBPM = pulseSensor.getBeatsPerMinute(); // Calls function on our pulseSensor object that returns BPM as an "int".
// "myBPM" hold this BPM value now.
int bien_do =pulseSensor.getPulseAmplitude();
int sig = pulseSensor.getLatestSample();
if (pulseSensor.sawStartOfBeat()) { // Constantly test to see if "a beat happened".
Serial.println("♥ A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
Serial.print("BPM: "); // Print phrase "BPM: "
Serial.println(myBPM); // Print the value inside of myBPM.
Serial.print("amp: "); // Print phrase "BPM: "
Serial.print(bien_do);
Serial.print("signal: "); // Print phrase "BPM: "
Serial.print(sig);
}

delay(20); // considered best practice in a simple sketch.
}
