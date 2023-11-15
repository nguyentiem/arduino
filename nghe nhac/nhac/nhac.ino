
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
int bassl = 0, bassr = 0, treble = 0;
int r, g, b;
int pos = 0;    // variable to store the servo position
int amax = 0;
#define PIN1          6
#define PIN2          2
#define PIN3          8
#define NUMPIXELS      31
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, PIN3, NEO_GRB + NEO_KHZ800);
void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  pixels.begin(); // This initializes the NeoPixel library.
  pixels1.begin(); // This initializes the NeoPixel library.
   pixels2.begin();
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  r = random(0, 128);
  g = random(0, 128);
  b = random(0, 128);
  for (int i = 0; i < 10; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(r, g, b)); // Moderately bright green color.
    pixels1.setPixelColor(i, pixels.Color(r, g, b)); // Moderately bright green color.
     pixels2.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show(); // This sends the updated pixel color to the hardware.
    pixels1.show();
   pixels2.show();
  }
}
int temmax = 0;
uint64_t messageTimestamp = 0 ;

void loop() {

  

}
