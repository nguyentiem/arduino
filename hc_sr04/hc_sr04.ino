const int trig = 9;     // chân trig của HC-SR04
const int echo = 8;     // chân echo của HC-SR04
unsigned long a;
int b;        
void setup()
{
  Serial.begin(9600);  
   pinMode(trig,OUTPUT);
   pinMode(echo,INPUT);
}
 
void loop()
{
    
    digitalWrite(trig,LOW);   // tắt chân tri
delayMicroseconds(2);
    digitalWrite(trig,HIGH);   // phát xung từ chân tri
  delayMicroseconds(5);
    digitalWrite(trig,LOW);   // tắt chân tri
a =pulseIn(echo,HIGH);
 b = int (a/2/29.412);
  Serial.print(b);
  Serial.println("cm");
  delay(1000);
}
