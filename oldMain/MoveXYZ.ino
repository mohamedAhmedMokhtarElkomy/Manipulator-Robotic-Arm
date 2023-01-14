#include <math.h>
int objX = 311;
int objY = 388;
int objZ = 0;
float xyRatio = 9.7;
float zRatio = 27;

const int pin_mainStep = 3;
const int pin_mainDir = 4;

const int pin_baseStep = 6;
const int pin_baseDir = 7;

const int pin_secStep = 9;
const int pin_secDir = 8;

int a1 = 0;  // length of link a1 in cm
int a2 = 20;  // length of link a2 in cm
int a3 = 0;  // length of link a3 in cm
int a4 = 20;  // length of link a4 in cm
int zo = 10;
int yo = 27;

// Desired Position of End effector
int x = (int)(objX/xyRatio) - 32;
int y = 48 - (int)(objY/xyRatio) + yo;
int z = (objZ/zRatio) - zo;


char input;

void rotate(int pin_step, int steps){
    steps = steps * 2;
    for(int i = 0; i < steps; i++)
    {
      digitalWrite(pin_step, HIGH);
      delayMicroseconds(10000);
  
      digitalWrite(pin_step, LOW);
      delayMicroseconds(10000);
    }
}

float INVtheta1(int y, int z){
    // Equations for Inverse kinematics
    float r1 = sqrt(pow(y,2)+pow(z,2));  // eqn 1
    float phi_1 = acos((pow(a4,2)-pow(a2,2)-pow(r1,2))/(-2*a2*r1));  // eqn 2
    float phi_2 = atan2(z, y);  // eqn 3  
    return (phi_1-phi_2)*180/3.1415;
  }
  
float INVtheta2(int y, int z){
    // Equations for Inverse kinematics
    float r1 = sqrt(pow(y,2)+pow(z,2));   
    float phi_3 = acos((pow(r1,2)-pow(a2,2)-pow(a4,2))/(-2*a2*a4));
    return 180 - (phi_3)*180/3.1415;
  }

float INVtheta3(int x, int y){
  if(x<0)
  return abs((atan2(y,x)*180/3.1415) - 90);
  return abs(90 - (atan2(y,x)*180/3.1415));
  }
void setup() {
  
  pinMode(pin_baseStep, OUTPUT);
  pinMode(pin_baseDir, OUTPUT);

  pinMode(pin_mainStep, OUTPUT);
  pinMode(pin_mainDir, OUTPUT);

  pinMode(pin_secStep, OUTPUT);
  pinMode(pin_secDir, OUTPUT);
   
  Serial.begin(9600); 
  Serial.println("Hello From arduino");
  Serial.print(x);
  Serial.print("  ");
  Serial.print(y);
  Serial.print("  ");
  Serial.print(z);
  Serial.println("  ");
}
 
void loop() {
  if(Serial.available()){
      input = Serial.read();
      Serial.println(input);
      
      if(input == '0'){
        digitalWrite(pin_mainDir, 0);
        float th1 = INVtheta1(y,z);
        Serial.println(th1); 
        rotate(pin_mainStep, th1);
        
      }
      else if(input == '1'){
        digitalWrite(pin_secDir, 1);
        float th2 = INVtheta2(y,z);
        Serial.println(90-th2); 
        rotate(pin_secStep, 90- th2);
        
      }else if(input == '2'){
        if(x<0)
          digitalWrite(pin_baseDir, 1);
        else
          digitalWrite(pin_baseDir, 0);
        
        float th3 = INVtheta3(x,y);
        Serial.println(th3); 
        rotate(pin_baseStep, th3);
        
      }
  }
}
