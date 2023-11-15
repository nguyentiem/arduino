
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


int pos = 0;    // variable to store the servo position

#define PIN          13

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
 
int delayval = 500; // delay for half a second

void setup() {
  pinMode(2,OUTPUT);
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
 
  pixels.begin(); // This initializes the NeoPixel library.

for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,255,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(500);
}
delay(1000);
for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.
    
}
  
 }

void loop() {
   digitalWrite(2,HIGH);
   delay(1000);
 digitalWrite(2,LOW);
   delay(1000);
 

}
