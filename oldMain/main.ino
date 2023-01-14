#include <Servo.h>

int closeAngle = 80;
int openAngle = 145; 
Servo servo;
int servoPin = 10;

const int pin_mainStep = 3;
const int pin_mainDir = 4;

const int pin_baseStep = 6;
const int pin_baseDir = 7;

const int pin_secStep = 9;
const int pin_secDir = 8;

char input;

void rotate(int pin_step){
  while(1)
  {
    if(Serial.available() && Serial.read() == '0')
      break;
    digitalWrite(pin_step, HIGH);
    delayMicroseconds(10000);
  
    digitalWrite(pin_step, LOW);
    delayMicroseconds(10000);
  }
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

  servo.attach(servoPin);
  servo.write(closeAngle);
}
 
void loop() {
  if(Serial.available()){
      input = Serial.read();
      Serial.println(input);
      
      if(input == 'r')
      {
        
        digitalWrite(pin_baseDir, 1);
        rotate(pin_baseStep);
        
      }
      else if(input == 'l'){
        digitalWrite(pin_baseDir, 0);
        rotate(pin_baseStep);
        
      }
      else if(input == 'u'){
        digitalWrite(pin_mainDir, 1);
        rotate(pin_mainStep);
        
      }
      else if(input == 'd'){
        digitalWrite(pin_mainDir, 0);
        rotate(pin_mainStep);
        
      }
      else if(input == 'f'){
        digitalWrite(pin_secDir, 0);
        rotate(pin_secStep);
        
      }
      else if(input == 'b'){
        digitalWrite(pin_secDir, 1);
        rotate(pin_secStep);
        
      }
      else if(input == 'x'){
        servo.write(openAngle);
        
      }
      else if(input == 's'){
        servo.write(closeAngle);
      }
      
  }
}
