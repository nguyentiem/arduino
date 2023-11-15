#include <SoftwareSerial.h>
//SoftwareSerial ss(4, 3);
char message[30];
int dem =0;
int flag =0;  
int a[5];
int ut = 0, giua = 0, tro = 0, cai = 0 , aput = 0;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  Serial1.begin(9600);
}
void cat(){
  
   char * token = strtok(message, " ");
        // loop through the string to extract all other tokens
        for (int i = 0; i < 5, token != NULL; i++) {
          a[i] = atoi(token);
          token = strtok(NULL, " ");
        }
        cai = a[0] ;
        tro = a[1];
        giua = a[2];
        aput = a[3];
        ut = a[4];
        Serial.println(cai);
        Serial.println(tro);
        Serial.println(giua);
        Serial.println(aput);
        Serial.println(ut);
  }
  
void loop() {
  Serial1.println("a");
  // Serial.flush();  
  memset(message,0,30);
 // unsigned long start = millis();
  char tem = -1;  
  dem=0; 
  flag =0; 
  // Every 5 seconds we print an update
  while (1)
  {
  
    if (Serial1.available()) {
           // đọc chữ liệu
      tem =   Serial1.read();
     
      message[dem] = tem;
      dem++;
      if (tem == '\n') {       //Xuất dữ liệ    
     
      break;
      }
  
  
 } 

  }
  Serial.print(message);
  delay(300);
cat();
}
