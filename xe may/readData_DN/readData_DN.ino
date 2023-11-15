#include <SFE_BMP180.h>
SFE_BMP180 pressure;
#define ALTITUDE 0 

#define CAI 0
#define TRO 1
#define GIUA 2
#define APUT 3
#define UT 4

int ut = 0, ap_ut = 0, giua = 0, tro = 0, cai = 0;  // thong so analog
int gut = 0, gap_ut = 0, ggiua = 0, gtro = 0, gcai = 0;   // goc gap ngon tay
int temp =0,heart =0; 
String message="";//[30];
int dem = 0 ;
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
  if (ap_ut >= 50 && ap_ut < 630) {
    gap_ut  = map(ap_ut, 50, 630, 0, 90);

  }
  if (ap_ut >= 630 && ap_ut < 750) {
    gap_ut  = map(ap_ut, 630, 750, 90, 160);

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
  if (tro < 50) {
    gtro = 0;
  }
  if (tro  >= 50 && tro < 300) {
    gtro  = map(tro, 50, 300, 0, 90);

  }
  if (tro >= 300 && tro < 500) {
    gtro  = map(tro, 300, 500, 90, 170);

  }
  if (tro >= 500) {
    tro  = 170;
  }
  /////////////// cai /////////////////
  if (cai < 50) {
    gcai = 0;
  }
  if (cai >= 50 && cai < 400) {
    gcai  = map(cai, 50, 400, 0, 90);

  }
  if (cai >= 400 && cai < 600) {
    gcai  = map(cai, 400, 600, 90, 160);

  }
  if (cai >= 600) {
    gcai  = 170;
  }
  //  rut = map(gut, 0, 170, 0, 100);
  //  rap_ut = map(gap_ut,0,170,0,100);
  //  rgiua = map(ggiua, 0, 170, 0, 100);
  //  rtro = map(gtro, 0, 170, 0, 100);
  //  rcai = map(gcai, 0, 170, 0, 100);

}

void readHeart(){
  
  }
  
void readTemp(){
   char status=0;
   double T; 
   while(status==0){
    status = pressure.startTemperature();
    delay(5); 
   }
    status = pressure.getTemperature(T);
    if (status != 0)
    {
     temp =T - 6;
    }  

  }
    
void readData() {
 
  char tem;
  if (Serial.available()) {
    tem = Serial.read();
    if (tem == 'a') {
       Serial.flush();

      cai = analogRead(CAI);
      tro = analogRead(TRO);

      giua = analogRead(GIUA);
      ap_ut = analogRead(APUT);
      ut = analogRead(UT);
      message = String(cai)+String(" ")+String(tro)+String(" ")+String(giua)+String(" ")+String(ap_ut)+String(" ")+String(ut)+String(" ")+String(temp)+String(" ")+String(heart);
      Serial.println(message);
    }
  }
 
}
void setup()
{
  
  Serial.begin(9600);
  pinMode(CAI, INPUT);
  pinMode(TRO, INPUT);
  pinMode(GIUA, INPUT);
  pinMode(APUT, INPUT);
  pinMode(UT, INPUT);
  
  while(!pressure.begin());
 
}

void loop()
{  
  readTemp();
    /////////////////////////////////
    ////////////////////////////////
    readData();
  

 
}
