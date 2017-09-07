///////////////////////////////////////////////////////
// Author: Nguyen Phan Hung Thuan                   
// Version 1.0                                       
// 07/09/2017                                        
// International University - HCM National University
// hungthuanmk@gmail.com
// https://www.facebook.com/hungthuanmk
/////////////////////////////////////////////////////

#define DEBUG true

// DEFINITION //////////////////////////////////////
  // MOTOR /////////////
  #define IN1 3
  #define IN2 5
  #define IN3 6
  #define IN4 9
  #define MAX_SPEED 255
  #define MIN_SPEED 0
  
  // COLOR SENSOR /////
  #define S0 A0
  #define S1 A1
  #define S2 A2
  #define S3 A3
 // #define S4 A4
  #define sensorOut A4
  
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
void readColorSensor();
bool crossLine();
////////////////////////////////////////////////////

void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
  
  if (DEBUG)
    Serial.begin(9600);

  // REGULATION //////////////////////////////////
  delay(2000);
  ///////////////////////////////////////////////
}
  
void loop()
{
  readColorSensor();
 // if (crossLine == true)
  {
    // SMART BACKWARD
  }
//  else // CrossLine == false == in battlefield
  {
//     if (distance >= distanceThreshold)
     {  // ATTACK
   //     m1Forward(MAX_SPEED); 
    //    m1Forward(MAX_SPEED);
     }
//     else
     {  // FIND OPPONENT 
     //   m1Forward(MAX_SPEED);
     //   m2Backward(MAX_SPEED);
     }
  }
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
  analogWrite(IN3, speed);
  digitalWrite(IN4, LOW);// dont need to use PWM
}
 
void m2Backward(int speed){ 
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  analogWrite(IN4, 255 - speed);
  digitalWrite(IN3, HIGH);// dont need to use PWM
}

void readColorSensor(){
  // Setting CLEAR filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  C = pulseIn(sensorOut, LOW);
     // C = map(C, 2,25,255,0);
  if (DEBUG)
  {
    Serial.print("C= ");
    Serial.print(C);
    Serial.print("\t");
  }
  delay(5);
  
  // Setting RED filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  R = pulseIn(sensorOut, LOW);
      //R = map(R, 25,72,255,0);
  if (DEBUG)
  {
    Serial.print("R= ");
    Serial.print(R);
    Serial.print("\t");
  }
  delay(5);
  
  // Setting GREEN filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  G = pulseIn(sensorOut, LOW);
      //G = map(G, 30,90,255,0);
  if (DEBUG)
  {
    Serial.print("G= ");
    Serial.print(G);
    Serial.print("\t");
  }
  delay(5);
  
  // Setting BLUE filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  B = pulseIn(sensorOut, LOW);
      //B = map(B, 25,70,255,0);
  if (DEBUG)
  {
    Serial.print("B= ");
    Serial.print(B);
    Serial.print("\n");
  }
  delay(5);
 
}

bool crossLine(){
  readColorSensor();
 // if ((R <= rThreshold) && (G <= gThreshold) && (B <= bThreshold))
  if (C <= cThreshold)
    return true;
  else
    return false;
}

