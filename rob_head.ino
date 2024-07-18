#include<Servo.h>
#define trig_lf 10
#define echo_lf 11
#define trig_ri 2
#define echo_ri 3
int pos =0;
int distance_lf=0,t_lf=0;
int distance_ri=0,t_ri=0;
Servo myservo;
#include <MaxMatrix.h>
int DIN = 7;   // DIN pin of MAX7219 module
int CLK = 5;   // CLK pin of MAX7219 module
int CS = 6;    // CS pin of MAX7219 module
int maxInUse = 1;
MaxMatrix m(DIN, CS, CLK, maxInUse); 
char eyes_open[] = {9, 9,  //4 Column, 8 Row
   B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111

           };
char eyes_close[] = {9, 9,
  B00000000,
  B00000000,
  B00000000,
  B11111111,
  B11111111,
  B00000000,
  B00000000,
  B00000000
           };
 char eyes_right[] = {9, 9,  //4 Column, 8 Row
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B00000000,
  B00000000,
  B00000000,
  B00000000
           };
 char eyes_left[] = {9, 9,  //4 Column, 8 Row
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B11111111,
  B11111111,
  B11111111,
  B11111111
           };
void setup()
{
 myservo.attach(9);

  Serial.begin (9600);
  pinMode (trig_lf,OUTPUT);
  pinMode (echo_lf,INPUT);
  pinMode (trig_ri,OUTPUT);
  pinMode (echo_ri,INPUT);
  //pinMode(2, OUTPUT);
   lookaround();
    m.init(); // MAX7219 initialization
  m.setIntensity(5); // initial led matrix intensity, 0-15
   m.writeSprite(0, 0, eyes_open);
}

void loop() {
    //eyes();
  
  // put your main code here, to run repeatedly:
  digitalWrite(trig_lf,LOW);
  delayMicroseconds(5);
  digitalWrite(trig_lf,HIGH); 
  delayMicroseconds(10);
  digitalWrite(trig_lf,LOW);
  t_lf=pulseIn(11,HIGH);
  distance_lf=t_lf/57;
  Serial.print(distance_lf);
  Serial.println("  lf_cm");
 //----------------------------------------------
   
   digitalWrite(trig_ri,LOW);
  delayMicroseconds(5);
  digitalWrite(trig_ri,HIGH); 
  delayMicroseconds(10);
  digitalWrite(trig_ri,LOW);
  t_ri=pulseIn(3,HIGH);
  distance_ri=t_ri/57;
  Serial.print(distance_ri);
  Serial.println("  ri_cm");
  //delay(10);
  //--------------------------------------
  if (distance_lf <= 20){
  moveleft();
  }
  else {
    //delay(750);
  //pos=90;
 // myservo.write(90);
 // eyes();
  }
  //------------------------------------
   if (distance_ri <= 20){
  moveright();
  }
  else {
    //delay(750);
  //pos=90;
 // myservo.write(90);
 // eyes();
  
  }
  if (distance_ri > 20 && distance_lf > 20 ){
      myservo.write(90);
      eyes();
  }
  if (distance_ri <= 20 && distance_lf <= 20 ){
      
      lookaround();
  }
  
} 
void moveleft(){
  //if(pos>=0){
    //pos=pos-1;
    myservo.write(0);
     m.writeSprite(0, 0, eyes_left);
   // delay(15);
  //}
}
void moveright(){
  //if(pos<=180){
    //pos=pos+1;
    myservo.write(180);
     m.writeSprite(0, 0, eyes_right);
    //delay(15);
 // }
}
void lookaround(){
   //Servo Look around
  //myservo.attach(9);
   m.writeSprite(0, 0, eyes_open);
  for(pos = 90; pos <= 180; pos += 1){
        myservo.write(pos);
        delay(15);
      }
      for(; pos >= 0; pos-= 1) {
        myservo.write(pos);
        delay(15);
     }
     for(; pos<=90; pos += 1) {
        myservo.write(pos);
        delay(15);
        
     }
}
void eyes(){
    m.writeSprite(0, 0, eyes_open);
  delay(1000);
  m.writeSprite(0, 0, eyes_close);
  delay(50);
}
