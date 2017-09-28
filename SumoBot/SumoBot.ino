///////////////////////////////////////////////////////
// Author: Nguyen Phan Hung Thuan                   
// Version 1.0                                       
// 07/09/2017                                        
// International University - HCM National University
// hungthuanmk@gmail.com
// https://www.facebook.com/hungthuanmk
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
//USgreen     GND->14  ECHO->15  TRIG->16  VCC->17
//USblue      GND->7   ECHO->6   TRIG->5   VCC->4
//L298        IN1->8   IN2->9    IN3->10   IN4->11
//COLORgreen  S0->33   S1->35    S2->39    S3->37  OUT->A15
//COLORblue   S0->A0   S1->A1    S2->A7    S3->A6  OUT->A5
/////////////////////////////////////////////////////

#include <NewPing.h>

#define DEBUG  true

// DEFINITION //////////////////////////////////////
  // MOTOR /////////////
  #define IN1 8
  #define IN2 9
  #define IN3 10
  #define IN4 11
  #define MAX_SPEED 100
  #define MIN_SPEED 0

  //
  #define GREEN 0
  #define BLUE  1
  
  // COLORgreen SENSOR /////
  #define S0_g 33
  #define S1_g 35
  #define S2_g 39
  #define S3_g 37
  #define sensorOut_g A15

  // COLORblue SENSOR /////  
  #define S0_b A0
  #define S1_b A1
  #define S2_b A7
  #define S3_b A6
  #define sensorOut_b A5

  // USgreen SENSOR          //USgreen     GND->14  ECHO->15  TRIG->16  VCC->17
  #define TRIG_g 16
  #define ECHO_g 15
  #define MAX_DISTANCE_g 50
  #define VCC_g 17
  #define GND_g 14
  NewPing USgreen(TRIG_g, ECHO_g, MAX_DISTANCE_g);

  // USblue SENSOR          //USblue      GND->7   ECHO->6   TRIG->5   VCC->4
  #define TRIG_b 5
  #define ECHO_b 6
  #define MAX_DISTANCE_b 50
  #define VCC_b 4
  #define GND_b 7
  NewPing USblue(TRIG_b, ECHO_b, MAX_DISTANCE_b);

  // OTHERS ///////////
  #define rThreshold 50
  #define gThreshold 50
  #define bThreshold 50
  #define cThreshold 50
  #define distanceThreshold 40
////////////////////////////////////////////////////

// VARIABLES //////////////////////////////////////
int R,G,B, C;
///////////////////////////////////////////////////

// PROTOTYPE //////////////////////////////////////
void m1Stop();
void m2Stop();
void m1Forward(int speed);
void m1Backward(int speed);
void m2Forward(int speed);
void m2Backward(int speed);
void readColorSensor(int GREENorBLUE);
bool crossedLine();
////////////////////////////////////////////////////

void setup()
{
  //motor setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  //color green setup
  pinMode(S0_g, OUTPUT);
  pinMode(S1_g, OUTPUT);
  pinMode(S2_g, OUTPUT);
  pinMode(S3_g, OUTPUT);
  pinMode(sensorOut_g, INPUT);  
  digitalWrite(S0_g, HIGH);
  digitalWrite(S1_g, HIGH);
  
  //color blue setup
  pinMode(S0_b, OUTPUT);
  pinMode(S1_b, OUTPUT);
  pinMode(S2_b, OUTPUT);
  pinMode(S3_b, OUTPUT);
  pinMode(sensorOut_b, INPUT);
  digitalWrite(S0_b, HIGH);
  digitalWrite(S1_b, HIGH);

  //ultrasonic green
  pinMode(TRIG_g, OUTPUT);
  pinMode(ECHO_g, INPUT);
  pinMode(VCC_g, OUTPUT);
  pinMode(GND_g, OUTPUT);
  digitalWrite(VCC_g, HIGH);
  digitalWrite(GND_g, LOW);

  //ultrasonic blue
  pinMode(TRIG_b, OUTPUT);
  pinMode(ECHO_b, INPUT);
  pinMode(VCC_b, OUTPUT);
  pinMode(GND_b, OUTPUT);
  digitalWrite(VCC_b, HIGH);
  digitalWrite(GND_b, LOW);
 
// analogWrite(IN4, 50);
  if (DEBUG)
    Serial.begin(9600);

  // REGULATION //////////////////////////////////
  delay(2000);
  ///////////////////////////////////////////////
}
  
void loop()
{
  m2Forward(100);
//  m1Backward(50);
 // readColorSensor(BLUE);
 //int a = USblue.ping_cm();
// if (a!=0)
 // Serial.println(a);
 // delay(10);
}

void m1Stop(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
 
void m2Stop(){
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
 
void m1Forward(int speed){ 
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  digitalWrite(IN1, HIGH);// dont need to use PWM
  analogWrite(IN2, 255 - speed);
}
 
void m1Backward(int speed){
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  digitalWrite(IN1, LOW);// dont need to use PWM
  analogWrite(IN2, speed);
}
 
void m2Forward(int speed){ 
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  analogWrite(IN4, speed);
  digitalWrite(IN3, LOW);// dont need to use PWM
}
 
void m2Backward(int speed){ 
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  analogWrite(IN4, 255 - speed);
  digitalWrite(IN3, HIGH);// dont need to use PWM
}

void readColorSensor(int GREENorBLUE){
  int s2,s3, out;
  if (GREENorBLUE == GREEN)
  { //green
    s2 = S2_g;
    s3 = S3_g;
    out = sensorOut_g;
  }
  else //blue
  {
    s2 = S2_b;
    s3 = S3_b;
    out = sensorOut_b;  
  }
  // Setting CLEAR filtered photodiodes to be read
  digitalWrite(s2, HIGH);
  digitalWrite(s3, LOW);
  C = pulseIn(out, LOW);
     // C = map(C, 2,25,255,0);
  if (DEBUG)
  {
    Serial.print("C= ");
    Serial.print(C);
    Serial.print("\t");
  }
  delay(5);
  
  // Setting RED filtered photodiodes to be read
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  R = pulseIn(out, LOW);
      //R = map(R, 25,72,255,0);
  if (DEBUG)
  {
    Serial.print("R= ");
    Serial.print(R);
    Serial.print("\t");
  }
  delay(5);
  
  // Setting GREEN filtered photodiodes to be read
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  G = pulseIn(out, LOW);
      //G = map(G, 30,90,255,0);
  if (DEBUG)
  {
    Serial.print("G= ");
    Serial.print(G);
    Serial.print("\t");
  }
  delay(5);
  
  // Setting BLUE filtered photodiodes to be read
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  B = pulseIn(out, LOW);
      //B = map(B, 25,70,255,0);
  if (DEBUG)
  {
    Serial.print("B= ");
    Serial.print(B);
    Serial.print("\n");
  }
  delay(5);
 
}

bool crossedLine(){
  readColorSensor(BLUE);
 // if ((R <= rThreshold) && (G <= gThreshold) && (B <= bThreshold))
  if (C <= cThreshold)
    return true;
  else
    return false;
}
