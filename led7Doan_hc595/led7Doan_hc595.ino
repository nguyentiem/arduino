int latchPin = 6;
int clockPin = 7;
int dataPin = 5;
int d1 =9;
int d2= 10;
int d3 = 11;
int d4 =8;

byte a[] = { 0B00111111,// sang het a->g : 1->8; 
             0B00000110,//1 b-c
             0B01011011,//2 
             0B01001111,//3
             0B01100110,//4
             0B01101101,//5
             0B01111101,//6
             0B00000111,//7
             0B01111111,//8
             0B01101111,//9
             };
 void reset(){
         digitalWrite(d1, HIGH);   
          digitalWrite(d2, HIGH);   
           digitalWrite(d3, HIGH);   
            digitalWrite(d4, HIGH);   
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST,0);  
        digitalWrite(latchPin, HIGH);
  }
  void batDen(int k,int so){
           digitalWrite(d1, HIGH);   
          digitalWrite(d2, HIGH);   
           digitalWrite(d3, HIGH);   
            digitalWrite(d4, HIGH);
     digitalWrite(k, LOW);   
     digitalWrite(latchPin, LOW); 
     int tem1=0B01001111;
          for(int i=0;i<8;i++){
     
            int tem = tem1%2;
            tem1=tem1/2;
            if(tem==1){
               digitalWrite(dataPin, HIGH); 
            }else{
               digitalWrite(dataPin, LOW); 
            }
                digitalWrite(clockPin, LOW);

                digitalWrite(clockPin, HIGH);
          }
        digitalWrite(latchPin, HIGH);
  }
 void den1(int so){
reset();
             digitalWrite(d1, LOW); 
            
             digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, a[so]);  
        digitalWrite(latchPin, HIGH);
  }
   void den2(int so){
reset();
              digitalWrite(d2, LOW); 
              
              digitalWrite(latchPin, LOW);
              shiftOut(dataPin, clockPin, LSBFIRST, a[so]);  
              digitalWrite(latchPin, HIGH);
  }
    void den3(int so){
               reset();
              digitalWrite(d3, LOW); 
              
              digitalWrite(latchPin, LOW);
              shiftOut(dataPin, clockPin, LSBFIRST, a[so]);  
              digitalWrite(latchPin, HIGH);
  }
    void den4(int so){
               reset();
              digitalWrite(d4, LOW); 
                
              digitalWrite(latchPin, LOW);
              shiftOut(dataPin, clockPin, LSBFIRST, a[so]);  
              digitalWrite(latchPin, HIGH);
  }
void setup() {
   pinMode(latchPin, OUTPUT);
   pinMode(clockPin, OUTPUT);
   pinMode(dataPin, OUTPUT);
   pinMode(d1, OUTPUT);
   pinMode(d2, OUTPUT);
   pinMode(d3, OUTPUT);
    pinMode(d4, OUTPUT);
   
}

 
void loop() { 
//  n++;
//  if(n==99999) n =0;
// for(int i =1 ; i<255;i++){
//  den1(n%60);
//  delay(4);
//  den2(n/60%60);
//  delay(4);
//  den3(5);
//  delay(4);
//  den4(4);
//  delay(4);
// }
for(int i=0; i<=9;i++){
  den1(i);
  delay(1000);
  den2(i);
    delay(1000);

 batDen(d3,i);
  delay(1000);
}
}
