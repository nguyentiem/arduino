int data = 8; 
int latch = 10; 
int clk   =9; 
int dataH = 11; 
int latchH = 12; 
int clkH   =13;

int a[4][4]={0x7FFF,0xBFFF,0xDFFF,0xEFFF,
             0xF7FF,0xFBFF,0xFDFF,0xFEFF,
             0xFF7F,0xFFBF,0xFFDF,0xFFEF,
             0xFFF7,0xFFFB,0xFFFD,0xFFFE};

int b[4]={0x80,0x40,0x20,0x10};

void shilf1(int y){
  digitalWrite(clk,LOW);
  digitalWrite(latch,LOW);
  int tem = y; 
  for(int i =0 ; i<16 ;i++){
    byte x = tem%2;
    tem >>=1; 
    digitalWrite(data,x);
    digitalWrite(clk,HIGH);
    digitalWrite(clk,LOW);
    }
   digitalWrite(latch,HIGH);
      digitalWrite(latch,LOW);
  }
  
  void shilf2(int y){
  digitalWrite(clkH,LOW);
  digitalWrite(latchH,LOW);
  int tem = y; 
  for(int i =0 ; i<8 ;i++){
    byte x = tem%2;
    tem >>=1; 
    digitalWrite(dataH,x);
    digitalWrite(clkH,HIGH);
    digitalWrite(clkH,LOW);
    }
   
    digitalWrite(latchH,HIGH);
    digitalWrite(latchH,LOW);
  }
  void off(){
       shilf1(0xFFFF);
    }
  void T(){
  for(int i=0;i<100;i++){
     shilf2( 0X30);
     shilf1(0x7FFF);
     off();
     shilf2( 0XF0);
     shilf1(0xBFFF);
 
     shilf2( 0XF0);
      shilf1(0xDFFF);
      
      shilf2( 0X30);
      shilf1(0xEFFF);
      
      off();
      }
      
 for(int i=0;i<100;i++){
     shilf2( 0X30);
     shilf1(0x77FF);
     off();
     shilf2( 0XF0);
     shilf1(0xBBFF);
 
     shilf2( 0XF0);
      shilf1(0xDDFF);
      
      shilf2( 0X30);
      shilf1(0xEEFF);
      
      off();
      }
       for(int i=0;i<100;i++){
     shilf2( 0X30);
     shilf1(0x777F);
     off();
     shilf2( 0XF0);
     shilf1(0xBBBF);
 
     shilf2( 0XF0);
      shilf1(0xDDDF);
      
      shilf2( 0X30);
      shilf1(0xEEEF);
      
      off();
      }
       for(int i=0;i<100;i++){
     shilf2( 0X30);
     shilf1(0x7777);
     off();
     shilf2( 0XF0);
     shilf1(0xBBBB);
 
     shilf2( 0XF0);
      shilf1(0xDDDD);
      
      shilf2( 0X30);
      shilf1(0xEEEE);
      
      off();
      }
     
       for(int i=0;i<500;i++){
     shilf2( 0X30);
     shilf1(0xF77F);
     off();
     shilf2( 0XF0);
     shilf1(0xFBBF);
 
     shilf2( 0XF0);
      shilf1(0xFDDF);
      
      shilf2( 0X30);
      shilf1(0xFEEF);
      
      off();
      }  
  }

void I(){
  for(int i=0;i<100;i++){
     
    
     shilf2( 0XF0);
     shilf1(0xBFFF);
 
     shilf2( 0XF0);
      shilf1(0xDFFF);
      
     
      }
      
 for(int i=0;i<100;i++){
    
     shilf2( 0XF0);
     shilf1(0xBBFF);
 
     shilf2( 0XF0);
      shilf1(0xDDFF);
    
      }
       for(int i=0;i<100;i++){
   
     shilf2( 0XF0);
     shilf1(0xBBBF);
 
     shilf2( 0XF0);
      shilf1(0xDDDF);
      
     
      }
       for(int i=0;i<100;i++){
    
     shilf2( 0XF0);
     shilf1(0xBBBB);
 
     shilf2( 0XF0);
      shilf1(0xDDDD);
      
     
      }
     
       for(int i=0;i<500;i++){
    
     shilf2( 0XF0);
     shilf1(0xFBBF);
 
     shilf2( 0XF0);
      shilf1(0xFDDF);
      
      
      }  
  }



  void test(){
    for(int i=0;i<4;i++){
  for(int j=0;j<4;j++){
    for(int z=0 ;z<4;z++){
      dpl(j,z,i);
      delay(100);
      }
    }
  }
    }
void dpl(int x,int y, int z){
 shilf1(a[x][y]);
 shilf2( b[z]);
  
  }

void mua(){
    int a,c=0xFFFF,d=0xFFFF,b=0xFFFF;
  
  
       a=random(65536);
   for(int v =0;v<16;v++){
    int tem =random(2);
    a|=tem;
    a<<=1;
    
    }
  for(int i =0;i<16;i++){
  
   
    for(int u=0;u<100;u++){
    
      shilf1(a);
      shilf2( 0x10);
      shilf1(b);
      shilf2( 0x20);
      shilf1(c);
      shilf2( 0x40);
      
      shilf1(d);
      shilf2( 0x80);
      
       
    }
    int tem =a; 
    a =d;
    d=c; 
    c =b; 
    b =tem;
    
    
    }
  }

void setup() {
  // put your setup code here, to run once:
pinMode(data,OUTPUT);
pinMode(clk,OUTPUT);
pinMode(latch,OUTPUT);
pinMode(dataH,OUTPUT);
pinMode(clkH,OUTPUT);
pinMode(latchH,OUTPUT);

digitalWrite(data,LOW);
digitalWrite(clk,LOW);
digitalWrite(latch,LOW);

digitalWrite(dataH,LOW);
digitalWrite(clkH,LOW);
digitalWrite(latchH,LOW);

}

void loop() {
test();
T();
while(1){mua();

}
}
