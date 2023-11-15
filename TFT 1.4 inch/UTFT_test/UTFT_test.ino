

#include <UTFT.h>
#include <SPI.h>
int tem  =20, hour=0 , day=1 , month=1, year =2020, second=0 , minitue=0;
int speed = 50; 
int x =40, y =40; 
int r = 35 ;
int xc=80;
int prespeed =0; 
int m =300; 
//extern unsigned int mylinh[0xEA6];
extern uint8_t SmallFont[]; 
extern uint8_t BigFont[];
extern uint8_t Font[];
// Declare an instance of the class
UTFT myGLCD(ST7735,11,13,10,9,8);  // Remember to change the model parameter to suit your display module!

void draw(){
  myGLCD.setContrast(64);
  myGLCD.setColor(0,255,255);
  myGLCD.drawLine(0, 115, 128, 115);

  myGLCD.setColor(255,255,0);
  myGLCD.print("Nguyen Tiem", CENTER, 116);
  myGLCD.setColor(255,0,0);
    myGLCD.drawLine(x-(r*cos((-60)*PI/180)), y - (r*sin((-60)*PI/180)), x,y);
    myGLCD.drawLine(x-(r*cos((240)*PI/180)), y - (r*sin((240)*PI/180)), x,y);
    // myGLCD.setColor(255,0,0);
   for(int i = -59; i <240 ; i++){
    if((i+60)%30==0){
      myGLCD.setColor(0,0,255);
      myGLCD.drawLine(x-((r+2)*cos((i)*PI/180)), y - ((r+2)*sin((i)*PI/180)), x-((r-5)*cos((i)*PI/180)),y - ((r-5)*sin((i)*PI/180)));
      // myGLCD.drawLine(x-((r+1)*cos((i)*PI/180)), y - (r*sin((i)*PI/180)), x-((r-5)*cos((i)*PI/180)),y - ((r-5)*sin((i)*PI/180)));
      }else{
    myGLCD.setColor(255,0,0);    
    myGLCD.drawPixel(x-(r*cos(i*PI/180)),y - (r*sin(i *PI/180)));
     myGLCD.drawPixel(x-((r+1)*cos(i*PI/180)),y - ((r+1)*sin(i *PI/180)));
      myGLCD.drawPixel(x-((r+2)*cos(i*PI/180)),y - ((r+2)*sin(i *PI/180)));
      }
    }
     
    myGLCD.setColor(255,200,100);
    myGLCD.print("tem: ", xc,5);
    myGLCD.print("pre: ",  xc,25);
    myGLCD.print("alt: ",  xc,45);
   
    myGLCD.print("time: ",  0,80);
    myGLCD.print("date: ",  0,95);
     
//    myGLCD.setColor(0,255,255);
//    myGLCD.setFont(BigFont);
//    myGLCD.print(String(speed), 25,60);
//    myGLCD.setFont(SmallFont);  
    myGLCD.setColor(255,255,255);
    myGLCD.print("speed",  21,25);
    myGLCD.setColor(0,255,0);
    
  
     
  }
void capnhat(){
  for(int i=1 ;i<100;i++){
    speed =i ; 
   myGLCD.setColor(0,255,255);
   myGLCD.setFont(BigFont);
    myGLCD.print(String(speed), 25,60);
    myGLCD.setFont(SmallFont);  
    myGLCD.setColor(255,255,255);
      myGLCD.print("speed",  21,25);
        myGLCD.setColor(0,0,0);
      myGLCD.drawLine(x-((r-10)*cos((prespeed*3-60)*PI/180)), y - ((r-10)*sin((prespeed*3-60)*PI/180)), x,y);
      myGLCD.setColor(0,255,0);
      myGLCD.drawLine(x-((r-10)*cos((speed*3-60)*PI/180)), y - ((r-10)*sin((speed*3-60)*PI/180)), x,y);
//         myGLCD.drawLine(x-((r-10)*cos((speed*3-60)*PI/180)), y - ((r-10)*sin((speed*3-60)*PI/180)), x,y);
    prespeed =speed; 
    delay(10); 
  }    
  }
 
void setup()
{
  randomSeed(0);
  myGLCD.InitLCD(PORTRAIT);
  myGLCD.setFont(SmallFont);
 
  myGLCD.clrScr();
  

}

void loop()
{ 
  draw();
  capnhat();
  // myGLCD.drawCircle(y, x, r);
//   myGLCD.drawLine(x-(r*cos(0)) ,y - (r*sin(0)), x,y);
 
}
