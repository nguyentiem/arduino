
int led =13; 
char a[7]; 
void setup() {
  // put your setup code here, to run once:
     Serial.begin(9600);
     pinMode(led,OUTPUT);
}
int sosanh(char a[7],char*b){
  for(int i =0 ;i<7; i++){
    if(a[i]!=b[i]) return 0;
    }
    return 1;
}

void loop() {
   if (Serial.available() > 0) {
    
        Serial.readBytes(a,7);
         
        Serial.println(a);
       
       
         
        
   if(sosanh(a,"tat den")==1){
      digitalWrite(led,LOW);
      Serial.println("da tat den");
     }else{
       if(sosanh(a,"bat den")==1){
      digitalWrite(led,HIGH);
      Serial.println("da bat den");
       }
     }
     
    }
   
}
