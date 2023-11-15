int latchPin = 8;
//chân SH_CP của 74HC595
int clockPin = 12;
//Chân DS của 74HC595
int dataPin = 11;
int button =9; 
int n =0; 
const int Seg[10] = {
  0b11000000,//0 - các thanh từ a-f sáng
  0b11111001,//1 - chỉ có 2 thanh b,c sáng
  0b10100100,//2
  0b10110000,//3
  0b10011001,//4
  0b10010010,//5
  0b10000010,//6
  0b11111000,//7
  0b10000000,//8
  0b10010000,//9
};


void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(button,INPUT); 
}

void loop() { 

 if(digitalRead(button)==0){
    while(digitalRead(button)==0);
    n++; 
 }
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, Seg[n]);  
  digitalWrite(latchPin, HIGH);
  //shiftout - end
  if(n>9) n =9; 
 
}
