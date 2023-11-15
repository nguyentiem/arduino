
char state;
 int n =0; 
void setup() {

 pinMode(9, OUTPUT);
 pinMode(10, OUTPUT);
 pinMode(11, OUTPUT);
 pinMode(12, OUTPUT);
 Serial.begin(9600); // Kết nối bluetooth module ở tốc độ 9600
}
 
void loop() {
 
 if(Serial.available() > 0){
   // Đọc giá trị nhận được từ bluetooth
   state = Serial.read();
 } else 
   state = 0;
   Serial.println(state);
    if(state=='1'){
       n++;
      if(n%2==1){ 
        digitalWrite(13,HIGH);
      }else{
         digitalWrite(13,LOW);
      }  
    }

}
