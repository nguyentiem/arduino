   int input = 4;
int xuat =5;
int truyen =6;
void  khoa(int n ){
  if(n==0){
    digitalWrite(input,LOW);
      }
      else{
         digitalWrite(input,HIGH);
      }
}

void dich(int n,int n1){
   digitalWrite(xuat,LOW);
  for(int i=1;i<=8;i++){
    int t = n1&1;
   khoa(t);
    digitalWrite(truyen,LOW);
     n1=n1>>1;
     digitalWrite(truyen,HIGH);
  }
  for(int i=1;i<=8;i++){
    int t = n&1;
   khoa(t);
    digitalWrite(truyen,LOW);
     n=n>>1;
     digitalWrite(truyen,HIGH);
  }
}
void I(){
  //
  for(int i =0; i<255;i++){
  digitalWrite(xuat,LOW);
    dich(0x7e,0x1e);
     digitalWrite(xuat,HIGH);
     delay(2);
     digitalWrite(xuat,LOW);
    dich(0x18,0x00);
     digitalWrite(xuat,HIGH);
     delay(2);
  }
}
void L(){
  for(int i =0; i<255;i++){
  digitalWrite(xuat,LOW);
    dich(0x7e,0x7e);
     digitalWrite(xuat,HIGH);
     delay(2);
     digitalWrite(xuat,LOW);
    dich(0x06,0x00);
     digitalWrite(xuat,HIGH);
     delay(2);
  }
}
void O(){
   for(int i =0; i<255;i++){
  digitalWrite(xuat,LOW);
    dich(0x7e,0x1e);
     digitalWrite(xuat,HIGH);
     delay(2);
     digitalWrite(xuat,LOW);
    dich(0x66,0x00);
     digitalWrite(xuat,HIGH);
     delay(2);
  }
}
void V(){
   for(int i =0; i<255;i++){
  digitalWrite(xuat,LOW);
    dich(0x18,0x7e);
     digitalWrite(xuat,HIGH);
     delay(2);
     digitalWrite(xuat,LOW);
    dich(0x66,0x81);
     digitalWrite(xuat,HIGH);
     delay(2);
  }
}
void E(){
   for(int i =0; i<255;i++){
  digitalWrite(xuat,LOW);
    dich(0x06,0x00);
     digitalWrite(xuat,HIGH);
     delay(2);
     digitalWrite(xuat,LOW);
    dich(0x7e,0x12);
     digitalWrite(xuat,HIGH);
     delay(2);
  }
}
void Y(){
   for(int i =0; i<255;i++){
  digitalWrite(xuat,LOW);
    dich(0x18,0x70);
     digitalWrite(xuat,HIGH);
     delay(2);
     digitalWrite(xuat,LOW);
    dich(0x24,0x87);
     digitalWrite(xuat,HIGH);
     delay(1);
     digitalWrite(xuat,LOW);
    dich(0x42,0x8f);
     digitalWrite(xuat,HIGH);
     delay(1);
     
  }
}
void U(){
 for(int i =0; i<255;i++){
  digitalWrite(xuat,LOW);
    dich(0x66,0x00);
     digitalWrite(xuat,HIGH);
     delay(2);
     digitalWrite(xuat,LOW);
    dich(0x7e,0x7e);
     digitalWrite(xuat,HIGH);
     delay(2);
  }
}
void T(){
   for(int i =0; i<255;i++){
  digitalWrite(xuat,LOW);
    dich(0x7e,0x9f);
     digitalWrite(xuat,HIGH);
     delay(2);
     digitalWrite(xuat,LOW);
    dich(0x18,0x00);
     digitalWrite(xuat,HIGH);
     delay(2);
  }
}
void i(){
  digitalWrite(xuat,LOW);
    dich(0x18,0x00);
     digitalWrite(xuat,HIGH);
     delay(1000);
}
void M(){
   for(int i =0; i<255;i++){
  digitalWrite(xuat,LOW);
    dich(0x66,0x00);
     digitalWrite(xuat,HIGH);
     delay(2);
     digitalWrite(xuat,LOW);
    dich(0x18,0xe7);
     digitalWrite(xuat,HIGH);
     delay(2);
  }
}
void cho(int a){
  digitalWrite(xuat,LOW);
    dich(0x00,0x00);
     digitalWrite(xuat,HIGH);
   digitalWrite(xuat,LOW);
    dich(0x00,0x00);
     digitalWrite(xuat,HIGH);
  delay(a);
}
void setup() {
  // put your setup code here, to run once:
pinMode(input,OUTPUT);
pinMode(xuat,OUTPUT);
pinMode(truyen,OUTPUT);
 
}

void loop() {
  T();
  cho(500);
  i();
  cho(500);
  E();
  cho(500);
  M();
 cho(1000);    
}
