#include <QTRSensors.h>
// motors
const int LeftIn1 = 9;
const int LeftIn2 = 8;
const int RightIn1 = 7;
const int RightIn2 = 6;
const int RightPWM = 10;
const int LeftPWM = 11;
// audio sensor
const int pin = A0;  
// ultrasonic sensor
const int trig = 5;
const int echo = 4;

//line sensor stuff
QTRSensors qtr;
const uint8_t SensorCount = 2;
uint16_t sensorValues[SensorCount];

void setup()
{
  // configure the line sensors
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A2, A3}, SensorCount);
  Serial.begin(9600);
  // ultrasonic sensor
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  // motors
  pinMode(LeftIn1, OUTPUT);
  pinMode(LeftIn2, OUTPUT);
  pinMode(RightIn1, OUTPUT);
  pinMode(RightIn2, OUTPUT);
  pinMode(LeftPWM, OUTPUT);
  pinMode(RightPWM, OUTPUT);
  // reads the threshold sound of the room
  threshold();
 
}

void loop()
{
  // for line sensor
int  black = 375; // is min val showed for black in all lighting 
int  white = 150; // is max val showed for white in all lighting 
// reads sensor values then
int  right = analogRead(A2);
int  left = analogRead(A3);
// values for the audio sensor and the ultrasonic sensor
 float val;
 float threshold;
 val = analogRead(pin);  
 long duration, cm;

// big if statement for the audio sensor
if (val > 10 + threshold) // detects timmy screaming
  {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  // convert the time into a distance
  cm = microsecondsToCentimetres(duration);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();  
  delay(100);
//if statement to then check if there is an object within 50 cm of it
      if (cm <= 50){
       digitalWrite(LeftIn1, LOW);
       digitalWrite(LeftIn2, HIGH);
       digitalWrite(RightIn1, LOW);
       digitalWrite(RightIn2, HIGH);
      }else{
        digitalWrite(LeftIn1, LOW);
        digitalWrite(LeftIn2, LOW);
        digitalWrite(RightIn1, LOW);
        digitalWrite(RightIn2, LOW);
      }
} 
   else 
   {
    // set ultrasonic sensor as being off
    digitalWrite(echo, LOW);
    digitalWrite(trig, LOW);
    //line array stuff to check for line 
         if (right > black && left > black){
          goForward();
        }else if (right < white && left > black){
          turnLeft();
        } else if (right > black && left < white){
          turnRight();
        } else if (right < white && left < white){
          turnRight();
        }
   }  
  Serial.println(val,DEC);//print the sound value to serial
  delay(100);
}

long microsecondsToCentimetres(long microseconds)
{
  return microseconds / 29 / 2;
}

void threshold(){
  int read1 = analogRead(pin);
  delayMicroseconds(100);
  int read2 = analogRead(pin);
  delayMicroseconds(100);
  int read3 = analogRead(pin);
  delayMicroseconds(100);
  int read4 = analogRead(pin);
  delayMicroseconds(100);
  int read5 = analogRead(pin);
  delayMicroseconds(100);
  //averaging 
  float threshold = ((read1 + read2 + read3 + read4 + read5)/5);
  Serial.print("threshold ");
  Serial.print(threshold);

  return threshold;
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
