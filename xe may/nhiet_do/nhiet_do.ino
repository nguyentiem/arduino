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
int temp = 0, heart = 0;
int tem = 0 , tim = 0, pre = 0 , nguong = 0 ;
int flag = 0; // the setup routine runs once when you press reset:
int start = 0, fin = 0;
String message = ""; //[30];
int dem = 0 ;

void readHeart() {
  tem = 0; flag = 0; pre = 0; fin = start = millis();
  int srt = millis();
  int s = 0, count = 0;
  while (millis() - srt < 5000) {
    tim = analogRead(A5);
    if (tim > 700 && flag == 0) {

      flag = 1;
      fin = millis();
      if (fin - start > 200) {
        tem = (60000 / (fin - start));
        if (tem > 40 && tem < 200 && pre > 0 && pre < 200) {
          tem = tem * 0.7 + pre * 0.3;
          s += tem;
          count += 1;
          tem = s / count;
          if (count == 5) {
            s = 0;
            count = 0;
          }
        }
        pre = tem ;
        start = fin + 30;
      }
    } else {
      if (tim < 700) {
        flag = 0;
      }
    }
  }
  //  Serial.println(tem);
  heart = tem ;
}

void readTemp() {
  char status = 0;
  double T;
  if (status == 0) {
    status = pressure.startTemperature();
    delay(5);
  }
  status = pressure.getTemperature(T);
  if (status != 0)
  {
    temp = T - 6;
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
      message = String(cai) + String(" ") + String(tro) + String(" ") + String(giua) + String(" ") + String(ap_ut) + String(" ") + String(ut) + String(" ") + String(temp) + String(" ") + String(heart);
      Serial.println(message);
    }else{
       if (tem == '1') {
      readHeart();
      readTemp();
      cai = analogRead(CAI);
      tro = analogRead(TRO);

      giua = analogRead(GIUA);
      ap_ut = analogRead(APUT);
      ut = analogRead(UT);
      message = String(cai) + String(" ") + String(tro) + String(" ") + String(giua) + String(" ") + String(ap_ut) + String(" ") + String(ut) + String(" ") + String(temp) + String(" ") + String(heart);
      Serial.println(message);
      }
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

  while (!pressure.begin());
  readHeart();
}

void loop() {
  readTemp();
  //  Serial.println(temp);
  //    /////////////////////////////////
  //    ////////////////////////////////
  readData();
  //


}
