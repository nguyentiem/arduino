#define _clock 7
#define _latch 6
#define _data 5
void setup() {
  // put your setup code here, to run once:
 pinMode(_latch, OUTPUT);
  pinMode(_clock, OUTPUT);
  pinMode(_data, OUTPUT);
}
void truyen(int a ){
  
}
void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(_latch, LOW);
    shiftOut(_data, _clock, LSBFIRST, 0);
    shiftOut(_data, _clock, LSBFIRST, 255);
   digitalWrite(_latch, HIGH);
  delay(1000);
}
