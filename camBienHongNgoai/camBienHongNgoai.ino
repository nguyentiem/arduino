int led = 6; 
int IN = A0; 

void setup() {
pinMode(led,OUTPUT);
 
//pinMode(IN,INPUT);
digitalWrite(led,LOW);
Serial.begin (9600);
}

void loop() {
int  sensorValue = analogRead (IN);
if(sensorValue<29){
  digitalWrite (led, HIGH);
  delay (100);}
  else{
  digitalWrite (led, LOW);
  delay (100);
  }
  Serial.println (sensorValue,DEC);
  
}
