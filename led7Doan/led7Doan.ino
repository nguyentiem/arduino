

//Tạo đối tượng led 7 đoạn
//SevSeg myDisplay;
  int digit1 = 8; //Pin chung nhóm 1
  int digit2 = 5; //Pin chung nhóm 2
  int digit3 = 11; //Pin chung nhóm 3
  int digit4 = 13; //Pin chung nhóm 4
  int a , b, c ,d;
  //Khai báo pin các nhánh của led đơn
  int segA = 7; //Nhánh led A
  int segB = 6; //Nhánh led B
  int segC = 10; //Nhánh led C
  int segD = 3; //Nhánh led D
  int segE = 9; //Nhánh led E
  int segF = 4; //Nhánh led F
  int segG = 2; //Nhánh led G
  int segDP = 12; //Dấu chấm
  int n =0;
 void ht(int led,int den){
  digitalWrite(led,LOW);
   digitalWrite(segC,LOW);
    digitalWrite(segD,LOW);
    digitalWrite(segG,LOW);
    digitalWrite(segF,LOW);
    digitalWrite(segA,LOW);
     digitalWrite(segE,LOW);
     digitalWrite(segB,LOW);
  switch(den){
    case 0: 
     digitalWrite(segC,HIGH);
    digitalWrite(segD,HIGH);
    digitalWrite(segF,HIGH);
    digitalWrite(segA,HIGH);
     digitalWrite(segE,HIGH);
     digitalWrite(segB,HIGH);
    case 1:
    digitalWrite(segB,HIGH);
    digitalWrite(segC,HIGH);
    break;
    case 2:
    digitalWrite(segA,HIGH);
    digitalWrite(segB,HIGH);
    digitalWrite(segE,HIGH);
    digitalWrite(segD,HIGH);
    digitalWrite(segG,HIGH);
    break;
    case 3:
    digitalWrite(segA,HIGH);
    digitalWrite(segB,HIGH);
    digitalWrite(segC,HIGH);
    digitalWrite(segD,HIGH);
    digitalWrite(segG,HIGH);
    break;
    case 4:
     digitalWrite(segC,HIGH);
    digitalWrite(segB,HIGH);
    digitalWrite(segG,HIGH);
    digitalWrite(segF,HIGH);
    break;
    case 5: 
    digitalWrite(segC,HIGH);
    digitalWrite(segD,HIGH);
    digitalWrite(segG,HIGH);
    digitalWrite(segF,HIGH);
    digitalWrite(segA,HIGH);
    break;
    case 6:
    digitalWrite(segC,HIGH);
    digitalWrite(segD,HIGH);
    digitalWrite(segG,HIGH);
    digitalWrite(segF,HIGH);
    digitalWrite(segA,HIGH);
     digitalWrite(segE,HIGH);
     break;
     case 7:
      digitalWrite(segA,HIGH);
     digitalWrite(segC,HIGH);
    digitalWrite(segB,HIGH);
    break;
    case 8:
    digitalWrite(segC,HIGH);
    digitalWrite(segD,HIGH);
    digitalWrite(segG,HIGH);
    digitalWrite(segF,HIGH);
    digitalWrite(segA,HIGH);
     digitalWrite(segE,HIGH);
     digitalWrite(segB,HIGH);
     break;
     case 9:
      digitalWrite(segC,HIGH);
    digitalWrite(segD,HIGH);
    digitalWrite(segG,HIGH);
    digitalWrite(segF,HIGH);
    digitalWrite(segA,HIGH);
     digitalWrite(segB,HIGH);
  }
 }

void setup()
{
 pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
   pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
     pinMode(6, OUTPUT);
     pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
   pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
     pinMode(11, OUTPUT);
     pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
      ht(digit1,0);
      ht(digit3,0);
      ht(digit2,0);
      ht(digit4,0);
      digitalWrite(segDP,HIGH);
}

void loop()
{     
    n++;
    if(n==3600){
      n=0;
    }
      a= n/600;
      b = (n/60)%10;
      c =(n%60)/10;
      d = (n%10);
      for(int i=0 ;i<255;i++){
         digitalWrite(digit2,HIGH);
       digitalWrite(digit4,HIGH);
       digitalWrite(digit3,HIGH);
      ht(digit1,a);
      
      delay(1);
      digitalWrite(digit1,HIGH);
       digitalWrite(digit4,HIGH);
       digitalWrite(digit3,HIGH);
      ht(digit2,b);
      delay(1);
      digitalWrite(digit2,HIGH);
       digitalWrite(digit4,HIGH);
       digitalWrite(digit1,HIGH);
      ht(digit3,c);
      delay(1);
      digitalWrite(digit2,HIGH);
       digitalWrite(digit1,HIGH);
       digitalWrite(digit3,HIGH);
      ht(digit4,d);
      delay(1); 
      
      }
}
