//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN
int ln=0,ld =0, la =0,rn=0,rd=0,ra=0; 
//address through which two modules communicate.
const byte address[6] = "00001";
void readData(){
  ln = analogRead(A0);
  ld = analogRead(A1);
  la = analogRead(A2);
  rn = analogRead(A3);
  rd = analogRead(A4);
  ra = analogRead(A5);
  
  } 
  
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
   radio.begin();
  
  //set the address
  radio.openWritingPipe(address);
  
  //Set module as transmitter
  radio.stopListening();
}

// the loop routine runs over and over again forever:
void loop() {
  readData();
  String a = String(ln)+String(" ")+String(ld)+String(" ")+String(la)+String(" ")+String(rn)+String(" ")+String(rd)+String(" ")+String(ra);
    char* text= (char*)calloc(40,sizeof(char));
     strcpy(text,"Nguyen Van Tiem" );//a.c_str()
     Serial.println(text); 
  radio.write(text, sizeof(text));
  free(text); 
  delay(1000);        // delay in between reads for stability
}
