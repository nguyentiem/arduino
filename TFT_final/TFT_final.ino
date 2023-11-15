#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"
#include "Fonts/FreeSans9pt7b.h"    // when you want other fonts
#include "Fonts/FreeSans12pt7b.h" // when you want other fonts
#include "Fonts/FreeSerif12pt7b.h" // when you want other fonts
#include "FreeDefaultFonts.h" // when you want other fonts 
#include "img.h"
#define BLACK 0x0000
#define NAVY 0x000F
#define DARKGREEN 0x03E0
#define DARKCYAN 0x03EF
#define MAROON 0x7800
#define PURPLE 0x780F
#define OLIVE 0x7BE0
#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEF
#define BLUE 0x001F
#define GREEN 0x07E0
#define CYAN 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define ORANGE 0xFD20
#define GREENYELLOW 0xAFE5
#define PINK 0xF81F
#define GREY    0x8410
#define Aut 25
#define Aaut 30
#define Agiua 35
#define Atro 30
#define Acai 20
char message[30];
int dem =0;
int flag =0;  
int a[7];

int h, w; // chieu cao chieu rong
int temp =0; 
int heart =0; 
           /// thong so ve ngon tay 
int ut = 0, ap_ut = 0, giua = 0, tro = 0, cai = 0;  // thong so analog 
int gut = 0, gap_ut = 0, ggiua = 0, gtro = 0, gcai = 0;   // goc gap ngon tay 
int rut = 0, rap_ut = 0, rgiua = 0, rtro = 0, rcai = 0;  // thong so rate 
        // toa do dau ngon tay 
int xgoc_ut,ygoc_ut; 
int xgoc_cai,ygoc_cai ; // cai
int xgoc_ap_ut , ygoc_ap_ut;
int xgoc_giua , ygoc_giua ; 
int xgoc_tro , ygoc_tro;

int xut[180], xap_ut[180], xgiua[180], xtro[180], xcai[180];
int yut[180], yap_ut[180], ygiua[180], ytro[180], ycai[180];
int preUt=0,preApUt =0, preGiua=0,preTro =0, preCai =0;  
int moc ;

// gui du lieu tho
// gui du lieu chuan hoa
MCUFRIEND_kbv tft(A3, A2, A1, A0, A4);
void init_vitri(){
   xgoc_ut = w / 2 - (sqrt(3) * 30);ygoc_ut=  h - 30; 
   xgoc_cai= w / 2 + (sqrt(3) * 30);ygoc_cai = h - 30; // cai
   xgoc_ap_ut = w / 2 - 30; ygoc_ap_ut =h - (sqrt(3) * 30);
   xgoc_giua = w / 2;ygoc_giua =h - 60; 
   xgoc_tro =w / 2 + 30, ygoc_tro = h - (sqrt(3) * 30);
   
  for(int i =0 ; i<180; i++){
    xut[i] =xgoc_ut - (Aut*0.5*abs(cos(i*PI/180))+0.5*Aut)*cos((i+30)*PI/180);
    yut[i] = ygoc_ut - (Aut*0.5*abs(cos(i*PI/180))+0.5*Aut)*sin((i+30)*PI/180);
    xap_ut[i] =xgoc_ap_ut - (Aaut*0.5*abs(cos(i*PI/180))+0.5*Aaut)*cos((i+60)*PI/180);
    yap_ut[i] = ygoc_ap_ut - (Aaut*0.5*abs(cos(i*PI/180))+0.5*Aaut)*sin((i+60)*PI/180);
    xgiua[i] = xgoc_giua; 
    ygiua[i] = ygoc_giua- Agiua*cos(i*PI/180); 
    xtro[i] = xgoc_tro - (Atro*0.5*abs(cos(i*PI/180))+0.5*Atro)*cos((120-i)*PI/180);
    ytro[i] = ygoc_tro - (Atro*0.5*abs(cos(i*PI/180))+0.5*Atro)*sin((120-i)*PI/180);
    xcai[i] = xgoc_cai - (Acai*0.5*abs(cos(i*PI/180))+0.5*Acai)*cos((150-i)*PI/180);
    ycai[i] = ygoc_cai - (Acai*0.5*abs(cos(i*PI/180))+0.5*Acai)*sin((150-i)*PI/180);
    }
  }
void cat(){
  
  
   char * token = strtok(message, " ");
        // loop through the string to extract all other tokens
        for (int i = 0; i < 7, token != NULL; i++) {
          a[i] = atoi(token);
          token = strtok(NULL, " ");
        }
        cai = a[0] ;
        tro = a[1];
        giua = a[2];
        ap_ut = a[3];
        ut = a[4];
        temp = a[5];
        heart = a[6]; 
        Serial.println(cai);
        Serial.println(tro);
        Serial.println(giua);
        Serial.println(ap_ut);
        Serial.println(ut);
        Serial.println(temp);
        Serial.println(heart);
  }

void tinh_toan() {
  if (ut < 50) {
    gut = 0;
  }
  if (ut >= 50 && ut < 300) {
    gut  = map(ut, 50, 300, 0, 90);

  }
  if (ut >= 300 && ut < 500) {
    gut  = map(ut, 300, 500, 90, 160);

  }
  if (ut >= 500) {
    gut  = 170;
  }
  ////////////// ap ut /////////////
  if (ap_ut < 50) {
    gap_ut = 0;
  }
  if (ap_ut >= 50 && ap_ut < 400) {
    gap_ut  = map(ap_ut, 50, 400, 0, 90);

  }
  if (ap_ut >= 400 && ap_ut < 750) {
    gap_ut  = map(ap_ut, 400, 750, 90, 169);

  }
  if (ap_ut >= 750) {
    gap_ut  = 170;
  }
  ////////////////// giua ///////////
  if (giua < 50) {
    ggiua = 0;
  }
  if (giua >= 50 && giua < 550) {
    ggiua  = map(giua, 50, 550, 0, 90);

  }
  if (giua >= 550 && giua < 800) {
    ggiua  = map(giua, 550, 800, 90, 160);

  }
  if (giua >= 800) {
    giua  = 170;
  }
  ////////////////tro /////////////
  if (tro < 70) {
    gtro = 0;
  }
  if (tro  >= 70 && tro < 300) {
    gtro  = map(tro, 50, 300, 0, 90);

  }
  if (tro >= 300 && tro < 600) {
    gtro  = map(tro, 300, 600, 90, 170);

  }
  if (tro >= 600) {
    gtro  = 170;
  }
  /////////////// cai /////////////////
  if (cai < 90) {
    gcai = 0;
  }
  if (cai >= 90 && cai < 400) {
    gcai  = map(cai, 90, 400, 0, 90);

  }
  if (cai >= 400 && cai < 500) {
    gcai  = map(cai, 400, 500, 90, 160);

  }
  if (cai >= 500) {
    gcai  = 170;
  }
  rut = map(gut, 0, 170, 0, 100);
  rap_ut = map(gap_ut,0,170,0,100);
  rgiua = map(ggiua, 0, 170, 0, 100);
  rtro = map(gtro, 0, 170, 0, 100);
  rcai = map(gcai, 0, 170, 0, 100); 
   
}

//////// ve do thi cac ngon tay 
void drawUt(int n) {
  tft.fillRect(moc,     120, 20, -100, 0x0000);
  tft.fillRect(moc,     120, 20, -n, GREEN);
  // ve so  analog
}
void drawAu(int n) {
  tft.fillRect(2 * moc + 20, 120, 20, -100, 0x0000);
  tft.fillRect(2 * moc + 20, 120, 20, -n, GREEN);
   // v
}
void drawGi(int n) {
  tft.fillRect(3 * moc + 40 , 120, 20, -100, 0x0000);
  tft.fillRect(3 * moc + 40 , 120, 20, -n, GREEN);

}
void drawTr(int n) {
  tft.fillRect(4 * moc + 60 , 120, 20, -100, 0x0000);
  tft.fillRect(4 * moc + 60 , 120, 20, -n, GREEN);

}
void drawCa(int n) {
  tft.fillRect(5 * moc + 80, 120, 20, -100, 0x0000);
  tft.fillRect(5 * moc + 80, 120, 20, -n, GREEN);
}

///// ve cac dot ngon tay 
void drawNgonUt(int n){   // dua vao goc gap ngon tay
  // xoa cai cu
    tft.fillCircle(xut[preUt], yut[preUt], 2, 0x0000);
   // ve line 
    tft.drawLine(xgoc_ut,ygoc_ut ,xut[preUt], yut[preUt], 0x0000);
    tft.fillCircle(xut[n], yut[n], 2, ORANGE);
   // ve line 
    tft.drawLine(xgoc_ut,ygoc_ut ,xut[n], yut[n], YELLOW);
    preUt =n; 
 
  }
  
void drawNgonAUt(int n){
   tft.fillCircle(xap_ut[preApUt], yap_ut[preApUt], 2, 0x0000);  
  tft.drawLine(xgoc_ap_ut ,ygoc_ap_ut,xap_ut[preApUt], yap_ut[preApUt], 0x0000);
  tft.fillCircle(xap_ut[n], yap_ut[n], 2, ORANGE);  
  tft.drawLine(xgoc_ap_ut ,ygoc_ap_ut,xap_ut[n], yap_ut[n], YELLOW);
  preApUt =n ; 
  }
  
  
void drawNgonGiua(int n){
   tft.fillCircle(xgiua[preGiua], ygiua[preGiua], 2, 0); // giữa 
  tft.drawLine(xgoc_giua,ygoc_giua,xgiua[preGiua],ygiua[preGiua], 0);
  tft.fillCircle(xgiua[n], ygiua[n], 2, ORANGE); // giữa 
  tft.drawLine(xgoc_giua,ygoc_giua,xgiua[n],ygiua[n], YELLOW);
  preGiua =n ; 
  }
  
void drawNgonTro(int n){
  tft.fillCircle(xtro[preTro], ytro[preTro], 2, 0);
 tft.drawLine(xgoc_tro,ygoc_tro ,xtro[preTro], ytro[preTro], 0);
 tft.fillCircle(xtro[n], ytro[n], 2, ORANGE);
 tft.drawLine(xgoc_tro,ygoc_tro ,xtro[n], ytro[n], YELLOW);
 preTro  = n; 
  
  }

void drawNgonCai(int n){
   tft.fillCircle(xcai[preCai], ycai[preCai], 2, 0);
 tft.drawLine(xgoc_cai,ygoc_cai,xcai[preCai], ycai[preCai], 0);
 tft.fillCircle(xcai[n], ycai[n], 2, ORANGE);
 tft.drawLine(xgoc_cai,ygoc_cai,xcai[n], ycai[n], YELLOW);
 preCai =n ; 
  }


  ///////////////
void initDraw() {
  // ve do thi
  tft.drawRect(moc - 1,     120, 22, -100, GREEN);
  tft.drawRect(2 * moc + 20 - 1, 120, 22, -100, GREEN);
  tft.drawRect(3 * moc + 40 - 1, 120, 22, -100, GREEN);
  tft.drawRect(4 * moc + 60 - 1, 120, 22, -100, GREEN);
  tft.drawRect(5 * moc + 80 - 1, 120, 22, -100, GREEN);
  /// ve nhan
  tft.setTextColor(RED, GREY);
  tft.setTextSize(2);
  tft.setCursor(moc, 135);
  tft.print("ut");
  tft.setCursor(2 * moc + 20, 135);
  tft.print("au");
  tft.setCursor(3 * moc + 40, 135);
  tft.print("gi");
  tft.setCursor(4 * moc + 60, 135);
  tft.print("tr");
  tft.setCursor(5 * moc + 80, 135);
  tft.print("ca");
  // ve chu do an 
  tft.setTextColor(WHITE, 0);
  tft.setTextSize(2);
   tft.setCursor(60, h/2+40);
   tft.print("Do An Tot Nghiep");
   /// ve nhiet do 
   tft.setTextColor(YELLOW, 0);
   tft.setTextSize(2);
   tft.setCursor(30, h/2+65);
   tft.print("Nhiet do");
   /// ve nhip tim 
   tft.setTextColor(YELLOW  , 0);
   tft.setTextSize(2);
   tft.setCursor(200, h/2+65);
   tft.print("Nhip tim");
  // ve cum ban tay
  tft.fillCircle(w / 2, h, 30, BLUE);
  ///// ve dot thu nhat
  tft.fillCircle(w / 2 - (sqrt(3) * 15), h - 15, 5, WHITE); // ut
  tft.fillCircle(w / 2 - 15, h - (sqrt(3) * 15), 5, WHITE); // ap ut
  tft.fillCircle(w / 2, h - 30, 5, WHITE);      // giua
  tft.fillCircle(w / 2 + (sqrt(3) * 15), h - 15, 5, WHITE); // tro
  tft.fillCircle(w / 2 + 15, h - (sqrt(3) * 15), 5, WHITE); // cai
  ///////// ve dot thu 2
  
   tft.fillCircle(w / 2 - (sqrt(3) * 30), h - 30, 5, WHITE); // ut
  tft.fillCircle(w / 2 - 30, h - (sqrt(3) * 30), 5, WHITE); // ap ut
  tft.fillCircle(w / 2, h - 60, 5, WHITE);     // giua
  tft.fillCircle(w / 2 + 30, h - (sqrt(3) * 30), 5, WHITE); // tro
  tft.fillCircle(w / 2 + (sqrt(3) * 30), h - 30, 5, WHITE); // cai

  tft.drawLine(w / 2 - (sqrt(3) * 15),h - 15 ,w / 2 - (sqrt(3) * 30), h - 30, YELLOW);
  tft.drawLine(w / 2 - 15,h - (sqrt(3) * 15) ,w / 2 - 30, h - (sqrt(3) * 30), YELLOW);
  tft.drawLine(w / 2,h - 30 ,w / 2, h - 60, YELLOW);
  tft.drawLine(w / 2 + (sqrt(3) * 15),h - 15 ,w / 2 + (sqrt(3) * 30), h - 30, YELLOW);
  tft.drawLine(w / 2 + 15,h - (sqrt(3) * 15) ,w / 2 + 30, h - (sqrt(3) * 30), YELLOW);
  
  tft.drawRGBBitmap(w/2-33, h/2-33, hust, 67, 67);
  
   
}

void getInfor(){

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
  cat();
  }
  
void getInfor1(){

Serial1.println("1");
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
  cat();
  }
void draw() {

   getInfor(); 
   tft.setTextColor(YELLOW, 0);
   tft.setTextSize(2);
   tft.setCursor(65, h/2+85);
   tft.print(String(temp));
   /// ve nhip tim 
   tft.setTextColor(GREEN  , 0);
   tft.setTextSize(2);
   tft.setCursor(235, h/2+85);
   tft.print(String(heart));
   tinh_toan();
         drawAu(rap_ut); 
      drawCa(rcai); 
      drawUt(rut); 
      drawGi(rgiua); 
      drawTr(rtro); 
   drawNgonAUt(gap_ut); 
   drawNgonCai(gcai); 
   drawNgonUt(gut); 
   drawNgonGiua(ggiua); 
   drawNgonTro(gtro);  
}

void initSc()
{  

   tft.setTextColor(YELLOW  , 0);
   tft.setTextSize(1);
   tft.setCursor(20,10);
   tft.print("* HaNoi University of Science and Technology *");
   tft.setTextColor(YELLOW  , 0);
   tft.setTextSize(1);
   tft.setCursor(10,460);
   tft.print("School of Information Technology and Communication");
   tft.drawRGBBitmap(w/2-33, h/2-33, hust, 67, 67);  
   tft.setTextColor(GREENYELLOW  , 0);
   tft.setTextSize(2);
   tft.setCursor(15,300);
   tft.print("Keep your hands relaxed!");
   
   tft.setTextColor(CYAN  , 0);
   tft.setCursor(15,50);
   tft.print("Name: Nguyen Van Tiem"); 
   tft.setCursor(15,75);
   tft.print("ID: 20164039"); 
   tft.setCursor(15,100);
   tft.print("Class: CNTT&TT1.01_K61"); 
   tft.drawLine(0,25 ,320, 25, BLUE);
   tft.drawLine(0,450 ,320, 450, BLUE);
   tft.drawRGBBitmap(w/2-33, h/2-33, hust, 67, 67);
   getInfor1();  
  int start = millis(); 
 while(millis()-start<6000){
 
  tft.setTextColor(RED  , 0);
    tft.setCursor(70, 330);
   tft.print("Wait ");
   tft.print(String(6-(millis()-start)/1000));
   tft.print(" seconds.");
  }
  
  }
void setup() {
  Serial.begin(9600);
    // put your setup code here, to run once:
  Serial1.begin(9600);
  pinMode(A15,INPUT);
  pinMode(A14,INPUT);
  pinMode(A13,INPUT);
  pinMode(A12,INPUT);
  pinMode(A11,INPUT);
  
  uint16_t ID = tft.readID();
  tft.begin(ID);
  w = tft.width(); //int16_t width(void);
  h = tft.height(); //int16_t height(void);
  moc = (w - 100) / 6 ;
 tft.fillScreen(0x0000);
  tft.setRotation(0);
  initSc();
  
  init_vitri(); 
  tft.fillScreen(0x0000);
  tft.setRotation(0);
  
  initDraw();
  
}

void loop() {
// initSc();
//  // put your main code here, to run repeatedly:
  draw();
  

}
