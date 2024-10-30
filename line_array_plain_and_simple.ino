#include <QTRSensors.h>
const int LeftIn1 = 9;
const int LeftIn2 = 8;
const int RightIn1 = 7;
const int RightIn2 = 6;
const int RightPWM = 10;
const int LeftPWM = 11;



QTRSensors qtr;

const uint8_t SensorCount = 2;
uint16_t sensorValues[SensorCount];

void setup()
{
  // configure the sensors
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A2, A3}, SensorCount);
  Serial.begin(9600);
}


void loop()
{
int  black = 375; // is min val will need to change for calibration
int  white = 150; // is max val will need to chang for calibration

int  right = analogRead(A2);
int  left = analogRead(A3);
  
  
  if (right > black && left > black){
    goForward();
  }else if (right < white && left > black){
    turnLeft();
  } else if (right > black && left < white){
    turnRight();
  } else if (right < white && left < white){
    turnRight();
    // back up a bit then turn??
  }
  
}

void goForward()
{
  analogWrite(LeftPWM, 150);
  analogWrite(RightPWM, 150); 
  digitalWrite(LeftIn1, LOW);
  digitalWrite(LeftIn2, HIGH);
  digitalWrite(RightIn1, LOW);
  digitalWrite(RightIn2, HIGH); 
  delay(25);
  digitalWrite(LeftIn1, LOW);
  digitalWrite(LeftIn2, LOW);
  digitalWrite(RightIn1, LOW);
  digitalWrite(RightIn2, LOW); 
  delay(50);
}

void turnLeft()
{
  analogWrite(LeftPWM, 150);
  analogWrite(RightPWM, 150);
  digitalWrite(LeftIn1, HIGH);
  digitalWrite(LeftIn2, LOW);
  digitalWrite(RightIn1, LOW);
  digitalWrite(RightIn2, HIGH);
  delay(25);
  digitalWrite(LeftIn1, LOW);
  digitalWrite(LeftIn2, LOW);
  digitalWrite(RightIn1, LOW);
  digitalWrite(RightIn2, LOW); 
  delay(50);  

}

void turnRight()
{
  analogWrite(LeftPWM, 150);
  analogWrite(RightPWM, 150);
  digitalWrite(LeftIn1, LOW);
  digitalWrite(LeftIn2, HIGH);
  digitalWrite(RightIn1, HIGH);
  digitalWrite(RightIn2, LOW);
  delay(25);
  digitalWrite(LeftIn1, LOW);
  digitalWrite(LeftIn2, LOW);
  digitalWrite(RightIn1, LOW);
  digitalWrite(RightIn2, LOW); 
  delay(50);
}
