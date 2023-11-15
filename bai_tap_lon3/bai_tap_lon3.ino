#include <ESP8266WiFi.h>
int cb1 = 14;
int cb2 = 12;
int cb3 = 13;
int cb4 = 5;
int cb5 = 4;
int dc1a = 15;
int dc1b = 16;
int dc2a = 0;
int dc2b = 2;

int preDoc=4; ; // luu trang thai den truoc  
int flag =0 ; // luu trang thai doc
int preFlag = flag ;  // trang thai doc luc truoc 
int flagLine =0 ;
int error = 0;
int preError = 0;
int preError2= 0; 
int P, D, PIDvalue;
//int Kp = 300 , Kd = 350;   // 230 -300
byte sgn[5]; // luu cac den 1 2 3 4 5 ->
int PWM[10]= {1000,900,700,500,450,450,450,450,450};
int hesoP[5]= {0, 65,80,110,120}; 
int hesoD[5]= {0,100,180,250,300}; 
int result[34];
const char* ssid = "Tiem";
const char* password = "11111111";

WiFiServer server(80); // khoi tao socket
WiFiClient client;
IPAddress staticIP(192, 168, 43, 30);
IPAddress gateway(192, 168, 43, 1);
IPAddress subnet(255, 255, 255, 0);

void setupWifi()
{
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s \n", ssid);
  WiFi.begin(ssid, password);
  WiFi.config(staticIP, gateway, subnet);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
   Serial.println();
  
  if (WiFi.status() == WL_CONNECTED)
  {
 
  Serial.printf("Connected, mac address: %s\n", WiFi.macAddress().c_str());  
  Serial.println();
  Serial.print("DNS #1, #2 IP: ");
  WiFi.dnsIP().printTo(Serial);
  Serial.print(", ");
  WiFi.dnsIP(1).printTo(Serial);
  Serial.println();
  Serial.printf("pass: %s ", WiFi.psk().c_str() );
  Serial.println();
  server.begin();
  }
}

void Stop() {
  digitalWrite(dc1a, LOW);
  digitalWrite(dc1b, LOW);
  digitalWrite(dc2a, LOW);
  digitalWrite(dc2b, LOW);
}

byte  readSgn() {
   byte a ; 
  sgn[0] = digitalRead(cb1);
  sgn[1] = digitalRead(cb2);
  sgn[2] = digitalRead(cb3) ;
  sgn[3] = digitalRead(cb4);
  sgn[4] = digitalRead(cb5);
 
  if(sgn[0]==sgn[4]&&sgn[0]==1){
    flag = 0; // nen mau den vach trang 
  }else{
     if(sgn[0]==sgn[4]&&sgn[0]==0)
        flag =1;  // nen mau trang vach den
     else{
         flag = preFlag; 
     } 
  }
  preFlag = flag ; 
 if(flag==0){
   sgn[0]^=1;
    sgn[1]^=1;
    sgn[2]^=1;
    sgn[3]^=1; 
    sgn[4]^=1;
  }
    sgn[1]<<=1;
    sgn[2]<<=2;
    sgn[3]<<=3; 
    sgn[4]<<=4; 
    a = sgn[0]|sgn[1]|sgn[2]|sgn[3]|sgn[4];
    
   return a; 
}




void calculatePID()
{
  byte t =readSgn();
  if(t==0){  // trang thai ra khoi duong  //xet pre -4->4
//   if(preError==0||flagLine==10000){
//   
//    while(t==0){
//      // dieu khien di lui
//        digitalWrite(dc1a, LOW );
//        digitalWrite(dc2a, LOW);
//        analogWrite(dc1b, 450);
//        analogWrite(dc2b, 450);
//        
//        t = readSgn();
//        delay(10);
//        digitalWrite(dc1a, HIGH);
//        digitalWrite(dc2a, HIGH);
//  
//     }
//     
//     digitalWrite(dc1a, HIGH);
//     digitalWrite(dc2a, HIGH);
//     flagLine=0; 
//     }else{
      if(preError>=2){
        t =  16;
        
        }else{
          if(preError<=-2){
           t =15; 
            }else{
              t =preDoc;
              }
          }
    
      //flagLine++; 
      //}
    //}else{
     //  flagLine=0; 
      //}
  }
        error=result[t];
        if(error==10) {
        error =  preError;
        }  
        
  preDoc = t; 
  P = error;
  D = error - preError;
  if(D!=0) preError2 = preError;
  PIDvalue = (hesoP[abs(P)]*P)  + (hesoD[abs(P)] * D);
  
  result[0] = preError = error;
  
}

void control() {
 calculatePID();
 int tem ; 
 int td1,td2 ; 
 if(abs(error)>abs(preError)){
  tem = PWM[abs(error)];
  }
 else{
  tem = PWM[abs(preError)];
  }
 

  td1 = (tem + PIDvalue)>1023?1023:(tem + PIDvalue);
  td2 = (tem - PIDvalue)>1023?1023: (tem - PIDvalue); 
  if(td1<0){
     digitalWrite(dc1a, LOW);
     analogWrite(dc1b,300  );//td2 
    
     
     analogWrite(dc2a, td2);
     digitalWrite(dc2b, LOW);
    }else{
      if(td2<0){
          digitalWrite(dc1b, LOW);
          analogWrite(dc1a, td1);
          digitalWrite(dc2a, LOW);
          analogWrite(dc2b, 300);//td1 
        }else{
            digitalWrite(dc1b, LOW);
            digitalWrite(dc2b, LOW);
            analogWrite(dc1a, td1);
            analogWrite(dc2a, td2);
          }
      }
}





int compare(char*a,char*b,int len){
   for(int i =0; i<len; i++){
      if(a[i]!=b[i]) return 0;
    }
    return 1;
  }
void connectWifi() {
  client = server.available();
  if (client)
  {
    while (client.connected())
    {
      Stop();
      if (client.available())
      {
        char line[100];
        memset(line, 0, 100);
        client.readBytes(line, 100);

        if (compare(line,"lui",strlen("lui")))
        { client.println("di lui !");
          digitalWrite(dc1b, HIGH);
          digitalWrite(dc2b, HIGH);
         
          delay(500);
          digitalWrite(dc1b, LOW);
          digitalWrite(dc2b, LOW);
        }
        else if (compare(line,"tien",strlen("tien"))) { 
          client.println("di tien !");
       
           digitalWrite(dc1a, HIGH);
          digitalWrite(dc2a, HIGH);
         
          delay(500);
          digitalWrite(dc1a, LOW);
          digitalWrite(dc2a, LOW);
        }
        else {
          if (compare(line,"start",strlen("start"))) {
            client.println("xe chay!");
            while (!client.available()) {
              control();
            }
          }
          else {
             if (compare(line,"stop",strlen("stop")))
            {
              client.println("Stop!");
               Stop();
            } 
          }

        }
      }

    }
    client.stop();
  }
}

void setup() {

  for(int i = 0; i < 34;i++) result[i]=10; 
   result[7]=-4;
   result[0]=preError; 
   result[28]= 4;
   result[1]= -4;
   result[2]= -2;
   result[3]=-3;
   result[4]= 0;
   result[6]=-1; 
   result[12]= 1;
   result[8]= 2;
   result[24]=3;
   result[30] = 4; 
   result[15] =-4;
   result[16]= 4;

  pinMode(cb1, INPUT);
  pinMode(cb2, INPUT);
  pinMode(cb3, INPUT);
  pinMode(cb4, INPUT);
  pinMode(cb5, INPUT);
  pinMode(dc1a, OUTPUT);
  pinMode(dc1b, OUTPUT);
  pinMode(dc2a, OUTPUT);
  pinMode(dc2b, OUTPUT);
  digitalWrite(dc1b, LOW);
  digitalWrite(dc2b, LOW);
  Stop();
  //setupWifi();
  
}

void loop() {
  // connectWifi();
control();

 
  
    }
