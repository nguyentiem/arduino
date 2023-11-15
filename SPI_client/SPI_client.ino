#include<SPI.h>
volatile boolean received;
volatile char Slavereceived,Slavesend;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(MISO, OUTPUT);
   SPCR |= _BV(SPE);                       //Turn on SPI in Slave Mode
  received = false;

  SPI.attachInterrupt();                  //Interuupt ON is set for SPI commnucation
}

ISR (SPI_STC_vect)
{
  Slavereceived = SPDR;
  Serial.println(Slavereceived);
  received = true;
}

void loop() {
  if (received)                           //Logic to SET LED ON OR OFF depending upon the value recerived from master
  {
   // Serial.print(Slavereceived);
  }
}
