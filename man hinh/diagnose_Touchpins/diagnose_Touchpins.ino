 /*chan A2 se doc 
khi tim x 

*/  
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;       // hard-wired for UNO shields anyway.




// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
 int i, j,x,y, preX,preY, Apins[5], Dpins[5], Values[5], found = 0;
 int tem,ID; 
void showpins(int A, int D, int value, String msg)
{
    Serial.print(msg);
    Serial.print(" (A" + String(A - A0) + ", D" + String(D) + ") = ");
    Serial.println(value);
}
void getPoint(){
     found = 0; 
     pinMode(A2, INPUT_PULLUP);
     pinMode(A0, OUTPUT);
     pinMode(6, INPUT_PULLUP);
     pinMode(7, INPUT_PULLUP);
     digitalWrite(A0, HIGH);
     
     pinMode(6, OUTPUT);
     digitalWrite(6, LOW);
            
     y = analogRead(A2);   // ignore first reading
     y = analogRead(A2);
     Values[found] = y;
     found++;
     pinMode(6, INPUT_PULLUP);
     pinMode(7, OUTPUT);
     digitalWrite(7, LOW);
            
     x = analogRead(A2);   // ignore first reading
     x = analogRead(A2);
     Values[found] = x;
     found++;
     pinMode(7, OUTPUT);
     pinMode(6, OUTPUT);
     pinMode(A2, OUTPUT);
     pinMode(A0, OUTPUT);
     Serial.println(x);
    Serial.println(y); 
     if(y<100&&x<=100&&y>=28 &&x>=59){
     y =10+ 30*(y-28); 
     x =15+ 11*(x-59); 
   }else{
    x= 0 ; 
    y= 0 ; 
    }
  }
void setup()
{
 
   
    Serial.begin(9600);
    Serial.println("Making all control and bus pins INPUT_PULLUP");
    Serial.println("Typical 30k Analog pullup with corresponding pin");
    Serial.println("would read low when digital is written LOW");
    Serial.println("e.g. reads ~25 for 300R X direction");
    Serial.println("e.g. reads ~30 for 500R Y direction");
    Serial.println("");
     //for (i = A0; i < A5; i++) 
    tft.reset();
    ID = tft.readID();
    tft.begin(ID);
    Serial.begin(9600);
   // show_Serial();
    tft.setRotation(0);
    tft.fillScreen(BLACK);
//    tft.setColor(0, 0, 255);
//  tft.setBackColor(0, 0, 0);
  
}

void loop()
{

       
          
     getPoint(); 
     tft.drawPixel(x,y,WHITE);     
    Serial.println(x);
    Serial.println(y); 
    Serial.println("=============");
       
    delay(1000);
  
}
