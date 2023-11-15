int led =11 ; 
int but = 8; 
int n =0; 
void setup() {
  // put your setup code here, to run once:

pinMode(led,OUTPUT);
pinMode(but,INPUT);

}

void loop() {
  while(true){
  if(digitalRead(but)==HIGH){
    n++;
  }
  if(n%2==0){
    digitalWrite(led,LOW);
  }
  else{

    digitalWrite(led,HIGH);
  }
  
  delay(100);
  }
  // put your main code here, to run repeatedly:

}
