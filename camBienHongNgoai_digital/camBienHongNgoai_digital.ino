//int led =13; 
int input1 =2; 
int input2 = 3;
int duong1 =8; 
int duong2 =10; 
int am1= 9;
int am2 =11;
int pwm1 =5;
int pwm2 = 6; 
void setup() { 
   pinMode(duong1,OUTPUT);
   pinMode(input1,INPUT);
   pinMode(input2,INPUT);
   pinMode(duong2,OUTPUT);
   pinMode(am1,OUTPUT);
   pinMode(am2,OUTPUT);
   pinMode(pwm1,OUTPUT);
   pinMode(pwm2,OUTPUT);
}

void loop() {
        int a = digitalRead(input1);
       int  b=  digitalRead(input2);
  // put your main code here, to run repeatedly:
    if(a==1&&b==1){
       digitalWrite(duong1, LOW); //Cho chân IN1 ở trạng thái LOW
         digitalWrite(am1, LOW); //Cho chân IN2 ở trạng thái LOW
        analogWrite(pwm1, 120); //Tốc độ là 100% (255)

 
//        digitalWrite(am1, LOW); //Cho chân IN1 ở trạng thái HIGH
//         digitalWrite(am2, LOW); //Cho chân IN2 ở trạng thái LOW
//         analogWrite(pwm2, 255); //Tốc độ là 120/255
     }else{
         if(a==1&&b ==0){
                   digitalWrite(duong1, HIGH); //Cho chân IN1 ở trạng thái LOW
                    digitalWrite(am1, LOW); //Cho chân IN2 ở trạng thái LOW
                    analogWrite(pwm1, 120); //Tốc độ là 100% (255)
//                    digitalWrite(am1, LOW); //Cho chân IN1 ở trạng thái HIGH
//                   digitalWrite(am2, LOW); //Cho chân IN2 ở trạng thái LOW
//                   analogWrite(pwm2, 255); //Tốc độ là 120/255
          }else{
                if(a==0&&b==1){
                    digitalWrite(duong1, LOW); //Cho chân IN1 ở trạng thái LOW
                    digitalWrite(am1, HIGH); //Cho chân IN2 ở trạng thái LOW
                    analogWrite(pwm1, 255); //Tốc độ là 100% (255)
//            
//                    digitalWrite(am1, LOW); //Cho chân IN1 ở trạng thái HIGH
//                   digitalWrite(am2, LOW); //Cho chân IN2 ở trạng thái LOW
//                   analogWrite(pwm2, 120); //Tốc độ là 120/255
                }else{
                   digitalWrite(duong1, HIGH); //Cho chân IN1 ở trạng thái LOW
                    digitalWrite(am1, LOW); //Cho chân IN2 ở trạng thái LOW
                    analogWrite(pwm1, 255); //Tốc độ là 100% (255)
                    
//                    digitalWrite(am1, LOW); //Cho chân IN1 ở trạng thái HIGH
//                   digitalWrite(am2, LOW); //Cho chân IN2 ở trạng thái LOW
//                   analogWrite(pwm2, 120); //Tốc độ là 120/255
          }
      }
}
}
