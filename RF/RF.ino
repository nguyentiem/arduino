int data[10]={0,1,1,1,0,0,0,1,0,1}; 
int in = 8; 
int out = 9; 
void setup() {
  
  Serial.begin(9600);
  pinMode(in,OUTPUT);
  pinMode(out,OUTPUT); 

}

void loop() {
 for(int i =0 ; i<10; i++){
    digitalWrite(out,data[i]);
    Serial.println(digitalRead(in));
    delay(1000);
  }
  
}
