 #include <Wire.h> //I2C Arduino Library

#define address 0x1E //0011110b, I2C 7bit address of HMC5883
int ax = 0 ,ay=0 ,az=0 ; 
void setup(){
  //Initialize Serial and I2C communications
  Serial.begin(9600);
  Wire.begin();
  
  //Put the HMC5883 IC into the correct operating mode
  Wire.beginTransmission(address); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();
}
 void loop(){
  
  int x,y,z; //triple axis data

  //Tell the HMC5883L where to begin reading data
  Wire.beginTransmission(address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  
 
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(address, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
  }
  if(ax!=x&&ay!=y&& az !=z ){ 
    Serial.println("Compass Heading: ");
    ay = y; 
    ax = x; 
    az = z; 
  Serial.println(x);
  Serial.println(y);
  Serial.println(z);
  Serial.println("=====================");
  }



  
   float Pi = 3.14159;
//  int  heading = (atan2(y,x) * 180) / Pi;
//  int yHeading = (atan2(z,x)*180)/Pi;
//  int  zHeading = (atan2(z,y)*180)/Pi;
//  
// 
//  if (heading < 0) {
//    heading = 360 + heading;
//  }
//   if (yHeading< 0) {
//    yHeading = 360 + yHeading;
//  }
//   if (zHeading < 0) {
//    zHeading = 360 + zHeading;
//  }
//  if(ax!=heading&&ay!=yHeading&& az !=zHeading ){ 
//    Serial.println("Compass Heading: ");
//    ay = yHeading; 
//    ax = heading; 
//    az = zHeading; 
//  Serial.println(heading);
//  Serial.println(yHeading);
//  Serial.println(zHeading);
//  Serial.println("=====================");
//  }
  
  
}
