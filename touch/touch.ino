
int led = 13; 
int n =0; 
int but = 8; 

void setup() {
  // put your setup code here, to run once:
pinMode(led,OUTPUT);
pinMode(but,INPUT);
 digitalWrite(led,LOW);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  if(digitalRead(but)==1){
    n+=1;
   
    if(n%2 ==0){
      digitalWrite(led,LOW);
      }
      else{
          digitalWrite(led,HIGH);
      }
    } 
    delay(100);
    //delay(100);
    
     // delay(100);

}
