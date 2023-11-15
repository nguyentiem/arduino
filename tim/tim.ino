int tem =0 , tim=0, pre=0 , nguong=0 ; 
int flag =0; // the setup routine runs once when you press reset:
int start =0, fin =0; 
long s =0,count =0; 
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
   tim = analogRead(A5);
   if(tim>750&& flag ==0){
    
     flag =1;
     fin = millis(); 
     if(fin-start>200){
         tem = (60000/(fin-start));
        
         if(tem>40&&tem<200&&pre>0&&pre<200){ 
         tem = tem*0.7+pre*0.3;  
          s+=tem; 
         count+=1;
         tem = s/count; 
       
          
            Serial.println(String(tem));
         if(count==5){
          s =0;count =0; 
          }
          } 
       pre = tem ; 
       start = fin; 
       } 
       
     
    }else{
      if(tim<700){
        flag =0; 
        }
      }
 
}
