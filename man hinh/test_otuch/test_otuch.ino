 int i, j,x,y,  value, Apins[2], Dpins[2], Values[2], found = 0;
#define _xp 7
#define _xm A2
#define _yp A2
#define _ym 6
void showpins(int A, int D, int value, const char *msg)
{
    Serial.print(msg);
    Serial.print(" (A" + String(A - A0) + ", D" + String(D) + ") = ");
    Serial.println(value);
}
int getY(){
  pinMode(_xp, INPUT);
  pinMode(_xm, INPUT);
  digitalWrite(_xp, LOW);
  digitalWrite(_xm, LOW);

  pinMode(_yp, OUTPUT);
  digitalWrite(_yp, HIGH);
  pinMode(_ym, OUTPUT);
  digitalWrite(_ym, LOW);

  return (1023 - analogRead(_xm));
  } 
int  getX(){
  pinMode(_yp, INPUT);
  pinMode(_ym, INPUT);
  digitalWrite(_yp, LOW);
  digitalWrite(_ym, LOW);

  pinMode(_xp, OUTPUT);
  digitalWrite(_xp, HIGH);
  pinMode(_xm, OUTPUT);
  digitalWrite(_xm, LOW);

  return (1023 - analogRead(_yp));
  }

void getPoint(){
   for (i = A0; i < A5; i++) pinMode(i, INPUT_PULLUP);
    for (i = 2; i < 10; i++) pinMode(i, INPUT_PULLUP);
    for (i = A0; i < A4; i++) {
        for (j = 5; j < 10; j++) {
            pinMode(j, OUTPUT);
            digitalWrite(j, LOW);
            value = analogRead(i);   // ignore first reading
            value = analogRead(i);
            if (value < 100) {
                showpins(i, j, value, "Testing :");
                if (found < 2) {
                    Apins[found] = i;
                    Dpins[found] = j;
                    Values[found] = value;
                    found++;
                }
            }
            pinMode(j, INPUT_PULLUP);
        }
    }
    if (found == 2) {
        Serial.println("Diagnosing as:-");
        for (i = 0; i < 2; i++) {
            showpins(Apins[i], Dpins[i], Values[i], (Values[i] < Values[!i]) ? "XM,XP: " : "YP,YM: ");
        }
    }
  }
// A2 -> tro ->  D6 cham vao tang tro 
// A2 ->  
void test(){
   pinMode(A2, INPUT);
   for (i = 6; i < 8; i++) pinMode(i, INPUT);
   for (i = A2; i < A3; i++) {
    
        for (j = 6; j < 8; j++) {
            pinMode(j, OUTPUT);
            digitalWrite(j, HIGH);
            value = analogRead(i);   // ignore first reading
            value = analogRead(i);
            
                showpins(i, j, value, "Testing :");
                
            pinMode(j, INPUT);
        }
        
        Serial.println(); 
        
    }
 
  }
  
void setup()
{
   
    Serial.begin(9600);
    
    
}

void loop()

{

           
    test(); 
    Serial.println("===================");
    delay(1000);

}
